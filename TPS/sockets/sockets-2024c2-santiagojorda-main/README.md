# Sockets

## Compilacion
- ```make``` para crear los ejecutables
- ```make clean``` para limpiar

## Ejecucion
1. Primero Ejecutar el servidor ```./server <port>```
2. Ejecutar el cliente ```./client <address> <port>```

### Ejemplo
```Bash
# Servidor
./server 8080

# Cliente
./client 127.0.0.1 8080

```

<br>

## Testing
1. Correr los tests ```./testcases/run_tests.sh ./ ./testcases/casos single-client valgrind 60 10```
2. Comparar diferencias ```./testcases/compare_outputs.sh ./testcases/casos ./testcases/salidas```

<br>

## Uso de bibliotecas

1. **Biblioteca de Sockets de la cátedra Veiga** | Autor: eldipa | Licencia: GPL v2
    - [https://github.com/eldipa/sockets-en-cpp](https://github.com/eldipa/sockets-en-cpp)
