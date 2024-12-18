#!/bin/bash

# Usage
#   compare_outputs.sh  <output got from cases folder> <expected from cases folder>
#
# We expect that <output got from cases folder> contains the files named in the
# same way than the ones found in <expected from cases folder>.
# Other files will be ignored.
#
# Both <output got> and <expected> folders must contain all the cases subfolders.
# In the first parameter, the subfolder must have the output obtained from
# the execution of the tests
# In the second parameter, each subfolder will have the expected outputs
# for that particular case

exec 2>&1
shopt -s nullglob

if [ "$#" != "2" -a "$#" != "3" ]; then
    echo "Usage:"
    echo
    echo "$0 <output got from cases folder> <expected from cases folder>"
    echo
    exit 1
fi

cases_folder=$1
expected_folder=$2

PRETTYPRINTMARKER=${3:-"-------------------------"}

echo
echo "Se compararan los archivos *obtenidos* con los *esperados*."
echo "Si se encuentran diferencias, estas se mostraran tal que:"
echo " - las lineas prefijadas con '-' provienen del archivo *obtenido* (tuyo);"
echo " - las prefijadas con '+' son del archivo *esperado* (el correcto)."
echo
echo "$PRETTYPRINTMARKER"

if [ ! -d "$expected_folder" ]; then
    echo "Error: $expected_folder no exite o no es un directorio."
    exit 1
fi

if [ ! -d "$cases_folder" ]; then
    echo "Error: $cases_folder no exite o no es un directorio."
    exit 1
fi

if [ "$cases_folder" = "$expected_folder" ]; then
    echo "Error: la carpeta donde deberian estar los resultados obtenidos es la misma carpeta donde estan los resultados esperados: la comparacion entonces seria SIEMPRE exitosa y no tiene sentido."
    exit 1
fi

err=0
for case_folder in $expected_folder/*; do
    case_name="$(basename "$case_folder")"
    # Show the differences recursively. Files that are not found in one side are
    # treated as "empty" files so they can be compared.
    # Trailing space is ignored.
    for filepath in $case_folder/*; do
        filename="$(basename "$filepath")"

        echo "[=>] Comparando $case_name/$filename..."
        diff  -u \
            --no-dereference --new-file \
            --ignore-trailing-space --strip-trailing-cr \
            "$cases_folder/$case_name/$filename" "$expected_folder/$case_name/$filename"
        ret=$?
        if [ "$ret" != "0" ]; then
            echo -e -n "\n\n"
            err=1
        fi
    done
    echo
    echo "$PRETTYPRINTMARKER"
done


if [ "$err" != "0" ]; then
    echo "[Error] Se encontraron diferencias entre las salidas obtenidas y las esperadas."
    exit 1
else
    echo "No se encontraron diferencias."
fi

exit 0
