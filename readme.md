# Project Structure

This project follows a clean and modular C architecture.  
All source files, headers, the main application entry point, and build artifacts are separated for clarity and scalability.

```
project/
│
├── src/       # All module .c files
├── include/   # All .h header files
├── app/       # main.c entry point
├── build/     # Compiled output (objects, executable)
├── Makefile   # Optional, if using Make instead of CMake
└── README.md
```

## Overview

- **src/**  
  Contains all implementation files used by modules.  
  These files compile into object files inside `build/objects/`.

- **include/**  
  Contains all public headers.  
  Each `.c` in `src/` should have a corresponding `.h` here.

- **app/**  
  Holds the `main.c` entry point.  
  This keeps program startup logic isolated from core modules.

- **build/**  
  Contains generated files such as:

  - `*.o` object files
  - the final compiled program  
    This directory is not committed to version control.

- **Makefile**  
  Defines how the project builds, links, and generates output files inside `build/`.

- **.gitignore**  
  Ensures build artifacts and temporary files are excluded from Git.

## Generating `compile_commands.json`

Some IDEs and tools (like clangd or VSCode C/C++ extensions) require a `compile_commands.json` file to understand your project’s build commands.

### Steps

1. Make sure you have an out-of-source build directory:

```bash
mkdir -p build
cd build
```

2. Run CMake with compile_commands.json export enabled:

```bash
cmake ..
cmake --build .
```

3. To make it visible to IDEs or tools expecting it in the project root, create a symbolic link:

```bash
ln -s build/compile_commands.json compile_commands.json
```
