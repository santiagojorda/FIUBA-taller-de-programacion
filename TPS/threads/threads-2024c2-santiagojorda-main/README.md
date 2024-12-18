> Hola! 👋🏼 El trabajo aun no esta finalizado, sigue en desarrollo! 💪🏼☕ - 15/10

# Threads

## Compilacion
- ```make``` para crear los ejecutables
- ```make -f MakefileThreads``` para compilar con "problemas de red"
- ```make clean``` para limpiar

## Ejecucion
- Servidor: ```./server <port>```
- Cliente: ```./client <hostname> <servname/port>```

### Ejemplo
- Servidor: ```./server 8081```
- Cliente: ```./client 127.0.0.1 8081```

<br>

## Testing
### Correr tests sin valgrind: 
    ./testcases/run_tests.sh ./ ./testcases/casos/ multi-client no-valgrind  60 10 yes
### Correr tests con valgrind: 
    ./testcases/run_tests.sh ./ ./testcases/casos/ multi-client valgrind  60 10
### Comparar Resultados:
    ./testcases/compare_outputs.sh ./testcases/casos ./testcases/salidas
<br>

## Uso de bibliotecas

1. **Biblioteca de Sockets de la cátedra Veiga** | Autor: eldipa | Licencia: GPL v2
    - [https://github.com/eldipa/hands-on-sockets-in-cpp](https://github.com/eldipa/hands-on-sockets-in-cpp)

2. **Biblioteca de Threads de la cátedra Veiga** | Autor: eldipa | Licencia: GPL v2
    - [https://github.com/eldipa/hands-on-threads](https://github.com/eldipa/hands-on-threads)
