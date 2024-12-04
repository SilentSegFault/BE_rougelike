# BE_rouglike project

# Custom Game Engine and Lua-Based Game  

This project showcases a fully custom-built game engine written in C and a Lua-based game that utilizes the engine's features. Developed as part of my studies, it combines low-level programming and scripting to create a modular, extensible framework for 2D games.  

## Project Overview  

The project consists of two primary components:  

1. **Game Engine** (C)  
2. **Game Logic** (Lua)  

The game engine is designed with a modular architecture, enabling flexibility and scalability. The gameplay logic, written in Lua, leverages the engine’s capabilities through a custom scripting API.  

---  

### Game Engine (C)  

The game engine consists of multiple modules, each contributing to specific functionality.  

#### Modules:  
- **Window**:  
  - Creates application windows using the **Win32 API**.  
  - Establishes **OpenGL context** for rendering.  
- **Logger**:  
  - Manages logging by creating log files and organizing them by creation time.  
  - Ensures structured debugging and error tracking.  
- **Utility**:  
  - Provides helper functions for common programming tasks.  
- **ResourceManager**:  
  - Handles resource management, including loading, saving, and managing animations, tilemaps, sprites, and other assets.  
  - Represents the most complex module, ensuring efficient resource handling.  
- **Rendering**:  
  - Defines rendering functions and capabilities for 2D graphics.  
- **Scripting**:  
  - Integrates the **Lua scripting language**, providing a custom API.  
  - Enables loading and running Lua scripts seamlessly.  
- **ECS** (Entity Component System):  
  - Implements a custom ECS architecture for flexible and efficient game entity management.  
- **Game**:  
  - Manages the main game loop, including updates and rendering.  

#### Core File:  
- **App.c**:  
  - Serves as the entry point for the application.  
  - Handles the initialization of game engine modules, the main application loop, and cleanup tasks.  

---  

### Game Logic (Lua)  

The gameplay logic is entirely written in Lua, taking advantage of the engine's scripting capabilities. It defines:  
- **Entities and Components**:  
  - Describes in-game objects and their behaviors.  
- **Gameplay Systems**:  
  - Implements game mechanics and interactions using the custom Lua API.  

This separation of engine and gameplay logic ensures flexibility, allowing rapid prototyping and iteration.  

---  

## Skills Gained  

Working on this project enhanced my expertise in several critical areas:  

1. **Low-Level Programming**:  
   - Developed a custom game engine in C, utilizing the Win32 API and OpenGL.  
   - Gained experience in optimizing resource management and rendering pipelines.  

2. **Game Engine Development**:  
   - Designed modular engine architecture with reusable and extensible components.  
   - Implemented core game engine systems like ECS, scripting, and rendering.  

3. **Scripting Integration**:  
   - Integrated the Lua scripting language into the engine.  
   - Designed and exposed a custom API for efficient scripting and game logic development.  

4. **System Design**:  
   - Balanced complexity across modules for maintainability and scalability.  
   - Created a seamless interaction between engine modules and Lua scripts.  

5. **Problem-Solving and Debugging**:  
   - Overcame challenges in low-level system programming, logging, and rendering optimization.  
   - Enhanced debugging skills through structured logging and error management.  

---  

This project highlights the interplay between low-level engine development and high-level gameplay scripting, emphasizing the importance of modularity and flexibility in game design.


## Build

### Requirements
You can build this project only on windows and you are required to have at least these three things 
CMake, c compiler and build system (preferably ninja or mingw-make)
You can download everything using [MSYS2](https://www.msys2.org/)  
You can read this article to learn [how to use CMake with MSYS2](https://www.msys2.org/docs/cmake/)  
Make sure that you added your enviroment bin directory to path! [How to add directory to path](https://stackoverflow.com/questions/44272416/how-to-add-a-folder-to-path-environment-variable-in-windows-10-with-screensho)

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
