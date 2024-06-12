# BE_rouglike project
Biomedical Hunter is a game about biomedical engineering student who has to fight evil biomachines to free his coleagues and professors.

## Introduction

Biomedical Hunter its rougelike game with rpg accents.

## Build

### Requirements
You can build this project only on windows and you are required to have at least these three things 
CMake, c compiler and build system (preferably ninja or mingw-make)
You can download everything using [MSYS2](https://www.msys2.org/)  
You can read this article to learn [how to use CMake with MSYS2](https://www.msys2.org/docs/cmake/)  
Make sure that you added your enviroment bin directory to path! [How to add folder to path](https://stackoverflow.com/questions/44272416/how-to-add-a-folder-to-path-environment-variable-in-windows-10-with-screensho)

### Downloading
First you have to download this project or clone it using git. 
To clone it open cmd in selected directory and use (dot in the end is important).
```console
    git clone https://github.com/LowLevelStudent/BE_rougelike.git .
```

### Building project
To create build open project directory in cmd create build directory and enter it 
```console
    mkdir build && cd build
```

Now use cmake to build this project (preferably with ninja or mingw-make)
```console
    cmake .. -G"Ninja"
```
or
```console
    cmake .. -G"MinGW Makefiles"
```
and finally
```console
    cmake --build .
```
/bin directory should be created inside /build with your game in here.
