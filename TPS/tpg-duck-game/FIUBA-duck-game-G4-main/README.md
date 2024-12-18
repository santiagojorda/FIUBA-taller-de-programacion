> Autores: 
>  - Santiago Jorda (102924)
>  - Alexia Aroa (110014) 
>  - Felipe D'alto (110000)
 
# Cómo compilar y ejecutar 

### Introducción
Este documento explica paso a paso cómo compilar y ejecutar el proyecto [Nombre del proyecto].

### Requisitos previos
#### Uso de bibliotecas

1. **Biblioteca de Sockets de la cátedra Veiga** | Autor: eldipa | Licencia: GPL v2
    - [https://github.com/eldipa/hands-on-sockets-in-cpp](https://github.com/eldipa/hands-on-sockets-in-cpp)

2. **Biblioteca de Threads y Queque de la cátedra Veiga** | Autor: eldipa | Licencia: GPL v2
    - [https://github.com/eldipa/hands-on-threads](https://github.com/eldipa/hands-on-threads)

3. **Blioteca SDL2** 
    - [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)

4. **Biblioteca  yaml-cpp**
    - [https://github.com/jbeder/yaml-cpp.git](https://github.com/jbeder/yaml-cpp.git)

## Instalar

Menos SDL2, Cmake se encarga de de instalar las dependencias necesarias 

1 - En la terminal ejecutar 
```bash
sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev
```
2 - se deben descargar los siguietes .zip


- libsdl2-image ( 2.6.3, https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3)
- libsdl2-mixer (2.6.3, https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)
- libsdl2-ttf (2.20.2, https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2)

3 - Instalar QT
Tirar los siguientes comandos en una consola para instalar librerias asociadas a QT

sudo apt-get  install qtcreator qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools

sudo apt-get install libqt5charts5-dev libqt5datavisualization5-dev libqt5gamepad5-dev libqt5gstreamer-dev libqt5networkauth5-dev libqt5opengl5-dev libqt5remoteobjects5-dev libqt5scxml5-dev libqt5sensors5-dev libqt5serialbus5-dev libqt5serialport5-dev libqt5svg5-dev libqt5texttospeech5-dev libqt5virtualkeyboard5-dev libqt5waylandclient5-dev libqt5waylandcompositor5-dev libqt5webkit5-dev libqt5webchannel5-dev libqt5websockets5-dev libqt5webview5-dev libqt5x11extras5-dev libqt5xmlpatterns5-dev

sudo apt-get install qtmultimedia5-dev

4 - descompirmir y en cada una de las carpetas ejecutar 

```bash
cd nombre_de_la carpeta_descomprimida
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

5 - Ahora dentro de la carpeta de del repo FIUBA-duck-game-G4

```bash
mkdir build
cd build
cmake ..
sudo make install
```

## Ejecutar
Se requieren dos terminales 

Para el server en la primera:
```bash
 ./taller_server <servername>
```

Para el cliente en la segunda 
(por defecto se conecta en el puerto 8080)

```bash
 ./taller_client  <hostname> <servername>
```

### Ejemplo
- Servidor: 
```bash  
./taller_server 8080
```
- Cliente:
```bash  
/taller_client localhost 8080
```

Al ingresar el cliente, se abrirá la siguiente pantalla.

<image src="imgs/lobby1.png" alt="">

En caso de unirse a una partida o crear una nueva, se le abrirá el siguiente form.

<image src="imgs/lobby2.png" alt="">

Es obligatorio completar todos los campos para avanzar a la siguiente pantalla, en caso de algún faltante, se tira un mensaje debajo del input indicando el error.

<image src="imgs/lobby3.png" alt="">

Como máximo sobre un dispositivo pueden haber 2 jugadores.

<image src="imgs/lobby4.png" alt="">

El hostname debe ser el mismo con que el segundo parámetro que ingresamos por comando, en este caso, `localhost`
Ingresamos con el puerto 8081 y con 2 jugadores.

<image src="imgs/lobby7.png" alt="">

### Host (Botón new game)
Para esta ocasión, se eligió jugar en el dispositivo con 2 jugadores. En caso de ser host, aparecerá una pantalla donde tendrá permitido iniciar la partida con el botón "Start Game", sumado a una segunda pantalla que quedará en negro.

<image src="imgs/lobby5.png" alt="">

### Client Join (Botón join game)
Para el cliente que se quiera unir, tiene que ingresar un puerto que esté disponible. En este caso, el puerto 8081. Ingresamos con 1 jugador.
Se le abrirá un nueva pantalla.

<image src="imgs/lobby8.png" alt="">

Una vez que el host le de a Start Game, se empezará la partida con todos los jugadores.

<image src="imgs/lobby9.png" alt="">

## Jugar 

Para cerrar usa la tecla "q" o "esc"

### controles player 1:

| Acción             | Tecla |
|--------------------|-------|
| Saltar             | W     |
| Moverse a la derecha | D     |
| Moverse a la izquierda | A     |
| Agacharse          | S     |
| Soltar arma        | R     |
| Disparar           | E     |

### controles player 2:

| Acción             | Tecla |
|--------------------|-------|
| Saltar             | I     |
| Moverse a la derecha | L     |
| Moverse a la izquierda | J     |
| Agacharse          | K     |
| Soltar arma        | P     |
| Disparar           | O     |

Extras:

Las partidas se reinician cuando queda un jugador con vida, el ganador será el primero en obtener 10 vitorias.

## Terminar 
Una vez vean la pantalla End Game, la tecla q cierra el juego, para cerrar el server deben mandar una 'q' por consola de comandos 

- server:
````bash
q
````
