# README
* Author: Michael De Santis
* CUID: 101213450
* Date: 2025/03/02

## Description
Discrete Event System Specification (DEVS) Model and Simulation of a Low Earth Orbit (LEO) User Link (UL). For additional information, please see the `doc/` directory.

## Contents
This repository's contents.

* `bin/`
    - Generated directory containing built executables for this repository.
* `build/`
    - Generated directory containing build files for this repository.
* `build_sim.sh`
    - Shell script defining build rules for host-architecture target.
* `cadmium_v2/`
    - Cadmium V2 repository `git` submodule.
* `CMakeLists.txt`
    - CMake build instructions for this repository.
* `doc/`
    - Directory containing documentation for this repository.
        1. Report: `LEO_User_Link.pdf`
        2. Assignment Document: `assignment1-DEVS.pdf`
        3. Cadmium V2 Developer Manual: `cadmium-v2-developer-manual.pdf`
        4. Cadmium V2 Installation Manual: `cadmium-v2-installation-manual.pdf`
        5. DEVS Graphs Manual: `devs-graphs-manual.pdf`
* `env.sh`
    - Shell script defining additional environment variables for this repository.
* `main/`
    - C++ source and header files for this repository's code.
* `output/`
    - Generated directory containing output logs from model simulation.
    
## Usage
Usage instructions for this project and repository.

### Installing and Configuring Cadmium V2
In order to compile this repository's source code, your system must have [Cadmium V2](https://github.com/Sasisekhar/cadmium_v2) available on your system, and accessible via the environment variable `$CADMIUM`. This library, and its own dependencies, are included within this repository as a `git` submodule. To ensure that your system's submodules are up-to-date prior to compilation, issue the following command:
```sh
git submodule update --init --recursive
```
Once the `cadmium_v2` sudmodule directory is available on your file system, enter that directory and follow the instructions provided therein for installation and configuration.  Once complete, you should be able to verify that your configuration is correct with the output of the following command:
```sh
$ echo $CADMIUM
<path-to>/LEO_User_Link/cadmium_v2/include
```
If the above environment variable is discrepant on your system, you can overwrite it by sourcing `env.sh` in this directory with the following command:
```sh
$ . env.sh
```

### Build
To build this project, issue the following command:
```sh
$ . build_sim.sh
```

### Execute
To execute this project, issue the following command:
```sh
./bin/leo_user_link
```

## Notes
* With permission and by instruction, this project uses the [blank project template](https://github.com/Sasisekhar/blank_project_rt) provided in the Cadmium V2 manual.
* With permission and by instruction, this project is informed by the [sample project](https://github.com/Sasisekhar/DEVS_manual_example) provided in the Cadmium V2 manual.
