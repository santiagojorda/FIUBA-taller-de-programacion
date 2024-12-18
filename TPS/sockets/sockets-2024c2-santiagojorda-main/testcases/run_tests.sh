#!/bin/bash


#####################################################
# Uso:
# ----
#
#   ./test_client_server.sh <executables-folder> <cases-folder> <testing-model> <valgrind-mode> [timeout [kill_timeout]] [suppressions] [pretty-marker]
#
# donde:
#  - <executables-folder> es la carpeta donde ya estan compilados el client y server
#  - <cases-folder> es donde estan los casos de prueba
#  - <testing-model> puede ser:
#       - "no-server" (tp con solo un programa client),
#       - "single-client" (tp con 1 cliente y 1 servidor)
#       - "multi-client" (tp con 1 cliente y 1 servidor
#         donde cada test ejecuta multiples clientes).
#  - <valgrind-mode> puede ser "valgrind" o "no-valgrind"
#  - <timeout> es el tiempo en segundos q cada programa puede tardar
#  - <kill_timeout> es el tiempo en segundos *adicionales* a <timeout>
#  - <suppressions> es el archivo q contiene las supressiones de valgrind
#    (falsos positivos)
#  - <pretty-marker> es un string q se imprime entre cada tests para separalos
#    visualmente
#
# Ejemplo (TP Onboarding sin valgrind):
# -----------------------
#
#   ./test_client_server.sh ./ casos/ no-server no-valgrind  60 10
#
# Ejemplo (TP Sockets con valgrind):
# -----------------------
#
#   ./test_client_server.sh ./ casos/ single-client valgrind  60 10
#
# Ejemplo (TP Threads sin valgrind )
# ------------------------
#
#   ./test_client_server.sh ./ casos/ multi-client no-valgrind  60 10 yes
#
#
####################################################



if [ "$#" = "0" ]; then
    echo "Usage:"
    echo
    echo "$0 <executables-folder> <cases-folder> <testing-model> <valgrind-mode> [timeout [kill_timeout]] [suppressions]"
    echo
    exit 1
fi






# Ensure that all the stderr goes to the stdout
exec 2>&1

# When loop with 'for' and the list is of the form foo/*,
# if not file is found in foo/* do not treat 'foo/*' as a literal
# string, instead treat it as an empty list
shopt -s nullglob


######################################################
#
# Functions to abort the tests execution.
#

# Ref:
# https://stackoverflow.com/questions/2618403/how-to-kill-all-subprocesses-of-shell
kill_descendant_processes() {
    local pid="$1"
    local and_self="${2:-false}"
    if children="$(pgrep -P "$pid")"; then
        for child in $children; do
            kill_descendant_processes "$child" true
        done
    fi
    if [[ "$and_self" == true ]]; then
        kill -9 "$pid"
    fi
}

abort_tests() {
    echo "[***] Cancelando ejecucion de los casos..."

    # kill children processes (recursively)
    kill_descendant_processes "$$" >/dev/null 2>&1
    exit 1
}



######################################################
#
# Functions to check certain invariants. If something goes wrong
# the whole test execution should abort
#
assert_program_is_executable() {
    if [ ! -x "$1" ]; then
        echo "Error: El programa '$1' no existe o no tiene permisos de ejecucion."
        abort_tests
    fi
}

assert_program_is_in_the_path() {
    hash "$1" 2>/dev/null
    if [ "$?" != "0" ]; then
        echo "Error: $1 no esta instalado (no esta en el PATH)"
        abort_tests
    fi
}

assert_file_exists() {
    if [ ! -f "$1" ]; then
        echo "Error: el archivo '$1' no existe o no es un archivo"
        abort_tests
    fi
}

assert_folder_exists() {
    if [ ! -d "$1" ]; then
        echo "Error: la carpeta '$1' no existe o no es un carpeta"
        abort_tests
    fi
}

assert_not_empty() {
    if [ -z "$2" ]; then
        echo "Error: assert_not_empty bad call"
        abort_tests
    fi

    if [ -z "$1" ]; then
        echo "Error: la variable/parametro/argument $2 esta en blanco (vacio)"
        abort_tests
    fi
}

export -f assert_not_empty



if [ ! -d "$1" ]; then
    echo "Error: Argument 1 ($1) esta vacio, no existe o no es un directorio."
    abort_tests
fi
G_EXECUTABLES_FOLDER=$(realpath $1)
G_CASES_FOLDER=$2
G_TESTING_MODEL=${3}
G_VALGRIND_MODE=$4
G_TIMEOUT=${5:-60}
G_KILL_TIMEOUT=${6:-10}
suppressions_file=$7

# Marker definition
PRETTYPRINTMARKER=${8:-"-------------------------"}


######################################################
#
# Check all the arguments of the script
# Abort if something goes wrong
#
assert_folder_exists "$G_EXECUTABLES_FOLDER"
assert_folder_exists "$G_CASES_FOLDER"

assert_not_empty "$G_VALGRIND_MODE" "argumento 'valgrind-mode'"
assert_not_empty "$G_TIMEOUT" "argumento 'timeout'"
assert_not_empty "$G_KILL_TIMEOUT" "argumento 'kill-timeout'"

if [ "$G_VALGRIND_MODE" != "valgrind" -a "$G_VALGRIND_MODE" != "no-valgrind" ]; then
    echo "El modo valgrind '$G_VALGRIND_MODE' es desconocido. Debe ser o 'valgrind' o 'no-valgrind'"
    abort_tests
fi

if [ "$G_TESTING_MODEL" != "no-server" -a "$G_TESTING_MODEL" != "single-client" -a "$G_TESTING_MODEL" != "multi-client" ]; then
    echo "El modelo de testing '$G_TESTING_MODEL' es desconocido. Debe ser alguno de los siguientes: "
    echo " - 'no-server': para el TP que hay un solo programa y no hay un server."
    echo " - 'single-client': para el TP donde hay un solo cliente y server por test."
    echo " - 'multi-client': para el TP donde hay multiples clientes y un solo server por test."
    abort_tests
fi

if [ "$G_TESTING_MODEL" != "no-server" ]; then
    assert_program_is_executable "$G_EXECUTABLES_FOLDER/server"
fi

assert_program_is_executable "$G_EXECUTABLES_FOLDER/client"


######################################################
#
# Check that we have all the tools that we need.
# Abort if something goes wrong
#
assert_program_is_in_the_path tiburoncin
assert_program_is_in_the_path ss
assert_program_is_in_the_path valgrind




G_CANCEL_TESTS=0

valgrind_ret_on_error=42

# Build the command under valgrind with the memcheck activated (full check)
# Trace any subprocess and track which file descriptors were left open.
# --track-origins=yes allows to know the origin of an unitialized variable
# however is disabled here because consumes at least 100 MB of ram.
G_VALGRIND_CMD="valgrind \
--tool=memcheck \
--leak-check=full \
--leak-resolution=med \
--show-reachable=yes \
--trace-children=yes \
--track-fds=yes \
--track-origins=no \
--time-stamp=yes \
--num-callers=20 \
--error-exitcode=$valgrind_ret_on_error"

if [ "$G_VALGRIND_MODE" = "valgrind" ]; then
    if [ ! -z "$suppressions_file" -a ! -f "$suppressions_file" ]; then
        echo "Suppressions file '$suppressions_file' does not exist or it is not a file"
        abort_tests
    fi

    if [ ! -z "$suppressions_file" ]; then
        G_VALGRIND_CMD="$G_VALGRIND_CMD --suppressions=$suppressions_file"
    fi
fi

# Utilitary function to generate a command line by passing an executable
# file name, a file containing the invocation arguments, and a parameter
# indicating whether it should be executed with valgrind or not.
#
# Usage:
#   cmd_to_run_with_valgrind <prog-path> <args-file> <with-valgrind?> <valgrind-log-file>
#
# prog-path Is the path to the file to execute.
# args-file Is the path to a file containing the program invocation arguments.
# with-valgrind? Indicates whether the program should be executed with valgrind
#                or not. "valgrind" means yes, "no-valgrind" means no.
# valgrind-log-file If the previous arg is "valgrind", this one indicates the
#                   file where the valgrind log must be written.
#
cmd_to_run_with_valgrind () {
    cmd=$1
    valgrind_log=$2

    #assert_program_is_executable $program_path
    #cmd=$(_create_link $program_path)

    #cmd="$cmd $(cat "$args_file")"

    cmd="$G_VALGRIND_CMD --log-file=$valgrind_log $cmd"

    echo "$cmd"
}

######################################################
#
# Functions to manage TCP ports
#
G_PORT_RANGE_BEGIN=1500
pick_free_port () {
    for port in $(seq "$G_PORT_RANGE_BEGIN" 65000); do
        ss -tln | grep -q ":$port "
        if [ "$?" != "0" ]; then
            echo "$port"
            break;
        fi
    done
}

update_port_range_begin () {
    port=$1
    assert_not_empty "$1" "argumento 1 (port) de update_port_range_begin"
    G_PORT_RANGE_BEGIN=$((port + 1))
}


wait_for_port_to_be_listening () {
    port=$1
    assert_not_empty "$port" "argumento 1 (port) de wait_for_port_to_be_listening"

    is_listening=$(ss -tln | grep -c ":$port ")
    while [ "$is_listening" = "0" ]; do
        sleep 0.2
        is_listening=$(ss -tln | grep -c ":$port ")
    done
}

# Export the function so it can be called by other scripts
export -f wait_for_port_to_be_listening

#
############



######################################################
#
# Functions to spawn/run processes
#
run_with_timeout () {
    timeout --kill-after $G_KILL_TIMEOUT $G_TIMEOUT $@
}

run_func_with_timeout () {
    if [ "$#" != "1" ]; then
        # expect a single argument ($1)
        echo "Internal abort: bad run_func_with_timeout call ($#)"
        abort_tests
    fi
    timeout --kill-after $G_KILL_TIMEOUT $G_TIMEOUT bash -c "$1"
}

create_link_to_executable () {
    program_path="$1"

    assert_not_empty "$program_path" "argumento 1 (program_path) de create_link_to_executable"

    program_name="$(basename "$program_path")"

    if [ "$program_name" = "$program_path" ]; then
        if [ -L "$program_name" ]; then
            echo "Internal abort: bad create_link_to_executable ($program_name) ($program_path)"
            abort_tests
        fi

    else
        if [ -L "$program_name" ]; then
            rm $program_name
        fi
        ln -s "$program_path" .
    fi
}



######################################################
#
# Functions to check the results of a process
#
abort_tests_if_ret_code_is_timeout () {
    ret=$1
    cmd=$2
    if [ "$ret" = "124" -o "$ret" = "137" ]; then
        echo "[Error] El programa '$cmd' termino con un codigo de error '$ret' muy posiblemente por timeout."
        if [ "$ret" = "124" ]; then
            echo "Timeout luego de $G_TIMEOUT."
        else
            echo "Killed luego de $G_TIMEOUT + $G_KILL_TIMEOUT."
        fi

        # A timeout is critical because it means that we wasted a lot of time
        # in a single case. Abort to whole execution.
        #G_CANCEL_TESTS=1
        abort_tests
    fi
}

abort_tests_if_ret_code_is_non_zero () {
    ret=$1
    cmd=$2
    if [ "$ret" != "0" ]; then
        echo "[Error] El programa '$cmd' termino con un codigo de error '$ret'."

        # A timeout is critical because it means that we wasted a lot of time
        # in a single case. Abort to whole execution.
        #G_CANCEL_TESTS=1
        abort_tests
    fi
}


check_valgrind_ret_code_and_log () {
    ret=$1
    valgrind_out_file=$2
    who=$3

    res=$ret
    if [ "$G_VALGRIND_MODE" = "valgrind" ]; then
        # Valgrind does not return an error code if a program leaves some
        # file descriptors open but not leaking memory.
        #
        # This happens when a program leaves a socket open for example.
        #
        # So this is a workaround:
        # Find any "open file descriptor" message and filter
        # those which are from the stdout, stdin, stderr and valgrind log.
        # If any is found, fake a return code like valgrind would set
        egrep '^==[0-9:. ]+== Open file descriptor ' $valgrind_out_file | egrep -v '__(server|client_[0-9])_(valgrind|stdout|stderr|stdin|pipe|)__$' | egrep -v 'q\.pipe' >/dev/null
        if [ "$?" = "0" ]; then
            res="$valgrind_ret_on_error"
        fi
        egrep '^==[0-9:. ]+== Open AF_INET socket ' $valgrind_out_file >/dev/null
        if [ "$?" = "0" ]; then
            res="$valgrind_ret_on_error"
        fi

        # Same issue with the buffer overflow detections. In this case Valgrind
        # reports a line starting with "** ... **" instead of the traditional
        # "== ... ==".
        egrep '^\*\*[0-9:. ]+\*\* .* buffer overflow detected' $valgrind_out_file >/dev/null
        if [ "$?" = "0" ]; then
            res="$valgrind_ret_on_error"
        fi

        if [ "$res" = "$valgrind_ret_on_error" ]; then
            cat "$valgrind_out_file"
            echo # add a new line
            # This is not a critical error so we should proceed with the execution
            # of the rest of the cases
        else
            echo "Valgrind no encontro errores para el $who."
        fi
    fi
    return $res
}



spawn_server () {
    port=$1
    G_TESTING_MODEL=$2

    # Create empty files in case that none was provided
    if [ ! -f __server_stdin__ ]; then
        touch __server_stdin__
    fi

    # The __server_args__ file has the arguments for the command line
    # for the server. The special PORT string will be replaced by the port
    # choosen and received by this function (spawn_server).
    cat "__server_args__" | sed "s/PORT[2]\?/$port/" > "__server_args"

    if [ "$G_VALGRIND_MODE" = "valgrind" ]; then
        server_cmd=$(cmd_to_run_with_valgrind "./server" "__server_valgrind__")
    else
        server_cmd="./server"
    fi

    # Include the arguments to the program
    server_cmd="$server_cmd $(cat "__server_args")"

    # If G_TESTING_MODEL is multi-client, don't use __server_stdin__ to feed the server
    # but use 'q.pipe' instead. This is a way to send data to the server
    # interactively (useful to send a 'quit' message after all the tests
    # run for example)
    input_file=__server_stdin__
    if [ "$G_TESTING_MODEL" == "multi-client" ]; then
        input_file=q.pipe
    else
        if [ "$G_TESTING_MODEL" != "single-client" ]; then
            echo "Testing model '$G_TESTING_MODEL' unexpected: expected either 'single-client' or 'multi-client'."
            abort_tests
        fi
    fi

    echo "[=>] Comando a ejecutar (server): $server_cmd"
    timeout --kill-after $G_KILL_TIMEOUT $G_TIMEOUT $server_cmd < $input_file >__server_stdout__ 2>__server_stderr__
    ret=$?

    rm "__server_args"
    echo "$ret" > __server_ret__
}


# Runs a tiburoncin and renames the dump files so they are identifiables per-client.
#
spawn_tiburoncin () {
    tiburoncin_port=$1
    server_port=$2
    N=$3

    tiburoncin -A 127.0.0.1:$tiburoncin_port -B 127.0.0.1:$server_port -c -f "client_${N}_" >"/dev/null"
}


spawn_tiburoncin_and_client () {
    N=$1
    server_port=$2
    clients_pipe=$3

    descriptors_register=$N

    tiburoncin_port=$(pick_free_port)
    update_port_range_begin "$tiburoncin_port"

    if [ "$G_TESTING_MODEL" != 'no-server' ]; then
        echo "[=>] Ejecutando tiburoncin para el cliente $N (entre puertos $tiburoncin_port (tiburoncin) y $server_port (server))"
        spawn_tiburoncin $tiburoncin_port $server_port $N &

        echo "[=>] Esperando a que tiburoncin abra el puerto $tiburoncin_port (binding)"
        run_func_with_timeout "wait_for_port_to_be_listening $tiburoncin_port"
        ret=$?
        abort_tests_if_ret_code_is_timeout $ret "Esperar a tiburoncin que abra el puerto"
    fi

    # Replace the string PORT in the client's arguments by the choosen port.
    cat "__client_${N}_args__" | sed "s/PORT[2]\?/$tiburoncin_port/" > "__client.$N.args"

    if [ "$G_VALGRIND_MODE" = "valgrind" ]; then
        client_cmd=$(cmd_to_run_with_valgrind "./client" "__client_${N}_valgrind__")
    else
        client_cmd="./client"
    fi

    # Include the arguments to the command
    client_cmd="$client_cmd $(cat "__client.$N.args")"

    # Two ways to talk with the client: with a pipe (fifo) or with a plain
    # file. The former allows a more dynamic test where you could end up with
    # multiple clients connected to the server at the same time.
    # The latter is simpler for synchronous testing only.
    if [ "$clients_pipe" == "yes" ]; then
        mkfifo "__client_${N}_pipe__"
        client_input="__client_${N}_pipe__"
    else
        client_input="__client_${N}_stdin__"
        if [ ! -f "$client_input" ]; then
            # If the file doesn't exist, create one
            touch "$client_input"
        fi
    fi

    echo "[=>] Ejecutando cliente $N: $client_cmd"
    timeout --kill-after $G_KILL_TIMEOUT $G_TIMEOUT $client_cmd <$client_input >"__client_${N}_stdout__" 2>"__client_${N}_stderr__" &
    client_pid=$!
    echo "[=>] Cliente $N corriendo con process id (PID): $client_pid"
    descriptors_register="$descriptors_register $client_pid"

    if [ "$clients_pipe" == "yes" ]; then
        echo "[=>] Creando un pipe para el cliente $N"
        exec {fd}>$client_input
        echo "[=>] Pipe '$client_input' abierto con file descriptor (FD) $fd"
        descriptors_register="$descriptors_register $fd"
    fi

    echo "$descriptors_register" >> __client_descriptors__

    rm "__client.$N.args"
}


# Iterates over the folders within <G_CASES_FOLDER>, spawning a server and as many clients
# as files named client.n.in are present on each folder
#

for case_folder in $G_CASES_FOLDER/*; do
    if [ "$G_CANCEL_TESTS" = "1" ]; then
        echo "Pedido de cancelamiento de la ejecucion de tests..."
        abort_tests
    fi

    pushd "$case_folder" >/dev/null
    rm -f __client_descriptors__

    # Create the links to the executables server and client in the current directory
    if [ "$G_TESTING_MODEL" != 'no-server' ]; then
        create_link_to_executable "$G_EXECUTABLES_FOLDER/server"
    fi
    create_link_to_executable "$G_EXECUTABLES_FOLDER/client"

    if [[ "$G_VALGRIND_MODE" = "valgrind" ]]; then
        echo "[=>] Ejecutando caso de prueba '$case_folder' usando valgrind"
    else
        echo "[=>] Ejecutando caso de prueba '$case_folder'"
    fi
    some_valgrind_check_failed=0
    server_port=$(pick_free_port)
    update_port_range_begin "$server_port"

    clients_pipe="no"
    if [ "$G_TESTING_MODEL" != 'no-server' ]; then

        echo "[=>] El server estara usando el puerto TCP $server_port"

        if [ "$G_TESTING_MODEL" == "multi-client" ]; then
            mkfifo q.pipe
        fi

        assert_file_exists "__server_args__"

        echo "[=>] Lanzando servidor (en background)"
        time spawn_server $server_port $G_TESTING_MODEL &
        server_pid=$!

        if [ "$G_TESTING_MODEL" == "multi-client" ]; then
            echo "[=>] Abriendo un pipe para interactuar con el servidor"
            exec <> q.pipe
        fi

        echo "[=>] Esperando a que el server abra el puerto $server_port (binding)"
        run_func_with_timeout "wait_for_port_to_be_listening $server_port"
        wait_ret=$?

        if [ "$wait_ret" != "0" ]; then
            # We may have a timeout of wait_for_port_to_be_listening *or* may be the server
            # died first and never open the port so the timeout is not the root cause
            if ! kill -0 "$server_pid" > /dev/null 2>&1; then
                wait "$server_pid"
                echo "[=>] El server aparentemente murio antes de abrir el puerto"

                # We must cancel the tests execution because even if this was not
                # a true timeout we already spent a lot of time waiting and we
                # don't want to trigger a timeout in our caller, the Sercom
                abort_tests_if_ret_code_is_non_zero "$(cat __server_ret__) <- (may be)" "server"
            else
                # The server is still alive, let's check if the wait_for_port_to_be_listening
                # is the one that timedout
                abort_tests_if_ret_code_is_timeout "$wait_ret" "Esperar al server que abra el puerto"

                # It looks like wait_for_port_to_be_listening didn't timeout *but* failed
                # and returned non-zero code. Abort anyways.
                abort_tests_if_ret_code_is_non_zero "$wait_ret" "Esperar al server que abra el puerto"
            fi

            # should not be necessary, just in case
            echo "Internal abort on wait_for_port_to_be_listening timeout ($wait_ret)"
            abort_tests
        fi
    fi

    if [ -f "clients_schedule.sh" ]; then
        if [ "$G_TESTING_MODEL" != 'multi-client' ]; then
            echo "Testing model '$G_TESTING_MODEL' is incompatible with clients_schedule.sh. Only 'multi-client' makes sense."
            abort_tests
        fi

        clients_pipe="yes"
    else
        clients_pipe="no"
    fi

    # Spawn the clients. If the clients use a plain file as input
    # (file redirection) the clients will (probably) finish almost immediately
    # so the concurrency level will be quite indeterministic.
    #
    # If we use a pipe per client as input we will have much control over the
    # clients' execution life.
    for client_input in __client_*_args__; do
        clientn="${client_input#"__client_"}"; clientn="${clientn%"_args__"}"
        echo "[=>] Ejecutando tiburoncin junto con el cliente $clientn"

        assert_file_exists "__client_${clientn}_args__"
        time spawn_tiburoncin_and_client $clientn $server_port $clients_pipe
    done

    if [ "$clients_pipe" == "yes" ]; then
        echo "[=>] Enviando comandos a los clientes..."
        bash clients_schedule.sh
    fi

    assert_file_exists "__client_descriptors__"
    while read desc; do
        clientn=$(echo $desc | cut -d' ' -f1)
        clientpid=$(echo $desc | cut -d' ' -f2)
        clientpipefd=$(echo $desc | cut -d' ' -f3)

        if [ "$clients_pipe" == "yes" ]; then
            echo "[=>] Cerrando pipe para el cliente $clientn"
            exec {clientpipefd}>&-
        fi

        wait "$clientpid"
        client_ret=$?

        abort_tests_if_ret_code_is_timeout $client_ret "Client ${clientn} (pid ${clientpid})"

        if [ "$clients_pipe" == "yes" ]; then
            echo "[=>] Borrando pipe para el cliente $clientn"
            rm -f "__client_${clientn}_pipe__"
        fi

        check_valgrind_ret_code_and_log "$client_ret" "__client_${clientn}_valgrind__" "Client $clientn"
        check_valgrind_ret=$?

        echo "Cliente $clientn finalizo con codigo de salida $check_valgrind_ret"
        if [ "$check_valgrind_ret" = "$valgrind_ret_on_error" ]; then
            some_valgrind_check_failed=1
        fi

        echo "$client_ret" > "__client_${clientn}_ret__"

    done < __client_descriptors__

    if [ "$G_TESTING_MODEL" == "multi-client" ]; then
        echo "[=>] Enviando 'q' al server a travez del pipe"
        echo 'q' > q.pipe
        rm q.pipe
    fi

    if [ "$G_TESTING_MODEL" != 'no-server' ]; then
        echo "[=>] Esperando al server que es finalize"
        wait "$server_pid"
        server_ret=$(cat "__server_ret__")
        abort_tests_if_ret_code_is_timeout $server_ret "Server"
        check_valgrind_ret_code_and_log "$server_ret" "__server_valgrind__" "Server"
        check_valgrind_ret=$?
        echo "El server finalizo con codigo de salida $check_valgrind_ret"
        if [ "$check_valgrind_ret" = "$valgrind_ret_on_error" ]; then
            some_valgrind_check_failed=1
        fi
    fi

    # If the server/clients generated some output to stderr, print it.
    # but don't do this if we are using Valgrind.
    if [ "$G_VALGRIND_MODE" != "valgrind" ]; then
        if [ -s "__server_stderr__" ]; then
            echo "[=>] El servidor ha escrito en stderr:"
            cat "__server_stderr__" | hd
            echo
        fi

        for client_input in __client_*_args__; do
            clientn="${client_input#"__client_"}"; clientn="${clientn%"_args__"}"
            if [ -s "__client_${clientn}_stderr__" ]; then
                echo "[=>] El cliente ${clientn} ha escrito en stderr:"
                cat "__client_${clientn}_stderr__" | hd
                echo
            fi
        done
    fi
    popd >/dev/null

    # print marker so the render will know how to pretty-print
    # each part of this log (we want a separated rendering for
    # each test case)
    echo
    echo "$PRETTYPRINTMARKER"
done

if [ "$some_valgrind_check_failed" = "1" ]; then
    echo "Se detecto uno o varios errores con valgrind."
    exit 1
fi

exit 0
