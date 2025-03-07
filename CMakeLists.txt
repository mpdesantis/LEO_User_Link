cmake_minimum_required(VERSION 3.16)

# Project and executable name
set(projectName "leo_user_link")

# Default build without simulation
option(SIM "Build for simulation" OFF)

# Simulation options
if(SIM)
    message(STATUS "Building for simulation")
    add_definitions(-DSIM_TIME)
endif()

# Project configuration
project(${projectName})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Subdirectories for inclusion
add_subdirectory(main)
add_subdirectory(test)
