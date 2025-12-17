# Minimum CMake required version
cmake_minimum_required( VERSION 3.20.0 )

# set enviroment variables like the board in use
set(BOARD native_sim)

# Get Zephyr directory
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Project name and source files
project(Sim)
target_sources(app PRIVATE src/main.c)