# HeadGamingMouse
 Inertial Measurement Unit (IMU) based USB mouse/joystick implementation with a Raspberry Pi Pico.
 Using Arduino-core mbed os and pico gamepad library

## Contents

[Overview](#Overview)
- [Interface](#Interface)
- [Pre-Compiled Binaries](#Pre-compiled-binaries)


[Build cpp source](#Build-cpp)
- [windows](#Windows-cpp)
- [linux](#Linux-cpp)

[Build python source](#Build-python)
- [windows](#Windows-python)
- [linux](#Linux-python)
## Overview


### Interface




### Pre-Compiled binaries
Project pre-compiled binaries can be found here: [releases](https://github.com/ChromaticPanic/HeadGamingMouse/releases)

## Build cpp
### Windows cpp
Building the cpp source requires the following:  
OS: Win 10 x64  
Build tools and dependencies:  
- [ARM build tools](#ARM-build-tools)  
- [cmake](#cmake)  
- [mingw](#mingw)  
- [Qt5](#Qt5) 

- [git and github desktop](#github-desktop) *optional*   
- [Command Prompt](####Command-Prompt)  
- [Arduino IDE Setup](#Arduino) *optional*
- [VScode Setup](#VScode) *optional*  
- [Clion Setup](#CLion) *optional*  
 

#### ARM build tools

Install GNU Arm Embedded Toolchain

The GNU Arm Embedded Toolchain contains the Arm GCC compiler that we need to compile C and C++ code for the RP2040.

Head to the [GNU Arm Embedded Toolchain download page](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) and download the latest installer for Windows. e.g. gcc-arm-none-eabi-10-2020-q4-major-win32.exe.

Run the installer.

#### github desktop

#### cmake

#### mingw


#### Qt5


#### Command Prompt
1. open cmd
2. navigate to the project folder
```
Drive:\PathTo\ProjectFolder> cmake CMakeLists.txt -G "MinGW Makefiles" -B build
Drive:\PathTo\ProjectFolder> cmake --build build
```
3. The program is now a compiled exe in the build folder

#### VScode

#### CLion




### Linux cpp
Dependencies