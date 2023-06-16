# Left 4 Dead

# Taller de Programación I - Cátedra Veiga - FIUBA

# Trabajo Práctico Final

| Padrón | Alumnos                  |
|--------|--------------------------|
| 106753 | Bravo, Nicolas Francisco | 
|  96467 | Chávez Cabanillas, José  |
| 106171 | Davico, Mauricio         |


# Tabla de Contenidos

- [Guía de Instalación](#guia-de-instalación)
    - [Requisitos](#requisitos)
    - [Instalación de Dependencias](#instalación-de-dependecias)
- [Guía de Usuario](#guía-de-usuario)
    - [Formas de ejecución](#formas-de-ejecucción)
        - [Server](#server)
        - [Cliente](#cliente)
- [Cómo jugar](#cómo-jugar)
    - [Movimientos](#movimientos)
    - [Unirse a Partida](#unirse-a-partida)
- [Features](#features)
    - [Completados](#completados)
    - [Faltantes](#faltantes)

# Guía de instalación

## Requisitos

Uno de los requisitos más importantes que utiliza el juego es el sistema operativo sobre el cual se ejecuta, para lo cual se debera contar con alguna distribucion que utilice GNU/Linux como sistema operativo.

Además se debe contar tanto con git, CMake y Make, para la descarga del juego así como para la compilación del juego.

## Instalación de Dependecias

Los paquetes que usa el juego para ejecutarse, son SDL, Qt5 y YAML-cpp, dependiendo del gestor de paquetes del sistema operativo que se use, los paquetes a instalar son los mismos.

### Ubuntu: 

```
    sudo apt-get update
    sudo apt-get install git cmake make libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev qt5-default qtmultimedia5-dev libqt5multimedia5-plugins libyaml-cpp-dev libsdl2-mixer-dev
```

## Configuración e Instalación

Como primer paso se debe clonar este repositorio con el siguiente comando:
```
    git clone git@github.com:mdavic0/7542_Taller_TP_Final.git 
```
Después de eso se debe ingresar a la carpeta donde se clonó el repositorio, donde se tienen dos opciones de instalacion.

* CMake - Make: construye el proyecto sin instalarlo, para eso simplemente se deben ejecutar los siguientes comandos, dentro de la carpeta:

```
    mkdir build
    cd build
    cmake ..
    make
```

* tests

```
    mkdir build  
    cd build  
    cmake ..  
    make  
    ctest
```
# Guía de Usuario

## Formas de ejecucción

### Server

Localizarse dentro de la carpeta build, y ejecutar por consola el siguiente comando:

```
    ./server [PORT]
```

### Cliente

Localizarse dentro de la carpeta build, y ejecutar por consola el siguiente comando:

```
    ./client
```

## Cómo Jugar

### Movimientos

Los movimientos para ontrolar al Operador son los siguiente:

* Teclas A - W - S - D: Movimiento en las cuatro direcciones.
* Tecla SPACE: Disparo.

## Features

### Completados:

Cliente:
* Renderizado correcto del infectados, jugadores, mapa y Hud.
* Camara solo sigue al cliente
* Render de estado de cada jugador al presionar una acción.
* Sala de espera de jugadores.
* Si hay más de un jugador en partida y uno de ellos se desconecta., se activa el estado de muerto para dicho jugador.

Server:
* Movimiento desde el server de los jugadores.
* Spawn de enemigos aleatorios.
* Ataque de los jugadores hacia los infectados.
* El juego solo iniciar al recibir el evento start_game
* Si un cliente se desconecta, se elimina su queue correspondiente del juego.
* Envío del estado actual del jugador para un determinado evento.


### Faltantes:

Cliente:
- Hud no renderiza de acuerdo a la pantalla.
- No renderiza obstaculos, solo chocas con los obstaculos
- Falta renderizado de habilidades
- Cámara depende de la resolución de la pantalla, probado en una resolución 1440x900px

Server:
- Falta agregar ataque de zombies
- Falta End Game
- Falta Habilidades
- Acciones que dependan del tiempo.
- Falta definir tamaño del mapa y sus bordes, eso ocasiona que el spawn no se vea bien en el cliente.

Test:
- Faltan completar
