# README
* Author: Michael De Santis
* CUID: 101213450
* Date: 2025/03/02

## Description
Discrete Event System Specification (DEVS) Model and Simulation of a Low Earth Orbit (LEO) User Link (UL). For additional information, please see `docs/`.

## Contents
This repository's contents.

* `atomics/`
    - Directory containing this repository's atomic models, implemented in Cadmium.
        1. `idu.hpp`
        2. `odu.hpp`
        3. `satellite.hpp`
* `bin/`
    - Generated directory containing this repository's compiled and linked executables.
* `build/`
    - Generated directory containing this repository's compiled object files.
* `data_structures`
    - Directory containing message data structures used in this repository's models.
        1. `message.hpp`
        2. `message.cpp`
* `docs/`
    - Directory containing documentation for this repository.
        1. Assignment Document: `assignment1-DEVS.pdf`
        2. Report: `LEO_User_Link.pdf`
* `input_data`
    - Directory containing input data to exercise the experimental frames defined for the model.
        1. `TODO.txt`
* `makefile`
    - Makefile governing the build of this repository's source code.
* `simulation_results/`
    - Generated directory containing simulation outputs.
* `test/` 
    - Directory containing unit tests of this repository's AMs.
        1. `main_idu_test.cpp`
        1. `main_odu_test.cpp`
        1. `main_satellite_test.cpp`
* `top_model/`
    - Directory containing the CM top model of the LEO User Link.
        1. `main.cpp`
    
## Usage
Usage instructions for this repository.

### Build
In order to compile this repository's source code, your system must have the [Cadmium](https://github.com/SimulationEverywhere/cadmium`) headers-only library available on your system. This library, and its own dependencies, are included within this repository as a `git` submodule. To ensure that your system's submodules are up to date prior to compilation, issue the following command:
```sh
git submodule update --init --recursive
```

### Including Cadmium in this Repository's Build Instructions
If you have pulled in the Cadmium library as a `git` submodule as per the above insructions, you should not need to modify the existing build instructions in this repository's `makefile`.
If you are not using this strategy, you will need to explicitly set the include path within this repository's `makefile` as follows, supplying your own paths for both the Cadmium library, as well as the DESTimes library that is itself a `git` submodule of the Cadmium repository.
```make
    INCLUDECADMIUM=-I <path-to>/cadmium/include
    INCLUDEDESTIMES=-I <path-to>/DESTimes/include
```

### Building the Project
To compile the simulator and the tests, issue the following command:
```sh
make
```
To see additional `make` targets, issue the following command:
```sh
make help
```

### Executing Tests
TODO
3 - Run subnet test
    1 - Open the terminal in the bin folder. 
    2 - To run the test, type in the terminal "./NAME_OF_THE_COMPILED_FILE" (For windows, "./NAME_OF_THE_COMPILED_FILE.exe"). 
    For this specific test you need to type:
            ./SUBNET_TEST (or ./SUBNET_TEST.exe for Windows)
    3 - To check the output of the test, go to the folder simulation_results and open  "subnet_test_output_messages.txt" and "subnet_test_output_state.txt"
4 - To run receiver and sender tests you just need to select the proper executable name in step 3.2

### Executing the Top Model
TODO
5 - Run the top model
    1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the bin folder.
    3 - To run the model, type in the terminal "./NAME_OF_THE_COMPILED_FILE NAME_OF_THE_INPUT_FILE". For this test you need to type:
        ./ABP ../input_data/input_abp_1.txt (for Windows: ./ABP.exe ../input_data/input_abp_1.txt)
    4 - To check the output of the model, go to the folder simulation_results and open "abp_output_messasges.txt" and "abp_output_state.txt"
    5 - To run the model with different inputs
        5.1. Create new .txt files with the same structure as input_abp_0.txt or input_abp_1.txt in the folder input_data
        5.2. Run the model using the instructions in step 3
        5.3. If you want to keep the output, rename a"abp_output_messasges.txt" and "abp_output_state.txt". Otherwise it will be overwritten when you run the next simulation.

