# Crispr Analysis Simulator
## Introduction
Crispr-based Covid-19 analysis simulation tool made for a student project.  
This simulator is not intended nor recommended for professional use.

## Quick Start
### Dependencies
- CMake (3.20+)
- OpenGL (Ver. 3.3)
### Cloning
This repository utilises submodules and must therefore be cloned recursively:
```sh
$ git clone https://github.com/rubensorensen/crispr_analyser.git
$ cd crispr_analyser
$ git submodule update --init --recursive --remote
```
### Building
#### Linux
```sh
$ mkdir build
$ cd build
$ cmake ..
$ make -j4
```
#### Windows
Generate Visual Studio Solution using CMake (3.20+).  
Build solution using Visual Studio. Make sure to copy glfw3.dll and libglew-shared.dll to executable directory.
#### MacOS
Project has not been tested on MacOS, but build process should be similar to Linux.
## Attributions
- Ubuntu font: https://fonts.google.com/specimen/Ubuntu
