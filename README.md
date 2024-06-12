# BE_rouglike project
Biomedical Hunter is a game about biomedical engineering student who has to fight evil biomachines to free his coleagues and professors.

## Introduction

Biomedical Hunter its rougelike game with rpg accents.

## Build

### Requirements
You can build this project only on windows and you are required to have at least these three things 
CMake, c compiler and build system 
You can download everything using [MSYS2](https://www.msys2.org/) 
Make sure that you added your enviroment bin directory to path!

### Downloading
First you have to download this project or clone it using git. 
To clone it open cmd in selected directory and use (dot in the end is important).
```console
    git clone https://github.com/NewPopeButDarker/BE_rougelike.git .
```

### Building project
To create build open project directory in cmd create build directory and enter it 
```console
    mkdir build && cd build
```

Now use cmake to build this project (preferably with ninja or mingw make)
```console
    cmake .. -G"Ninja"
```
or
```console
    cmake .. -G"MinGW Makefiles"
```
```console
    cmake --build .
```
/bin directory should be created inside /build with your game in here.
