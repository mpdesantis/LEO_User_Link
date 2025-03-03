# Vars
CC=g++
CFLAGS=-std=c++17
PWD := $(shell pwd)

# Generate folders
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

# Includes
# Note: If you are failing these includes, you may need to update your git submdules.
# See README for additional information.
INCLUDECADMIUM=-I $(PWD)/cadmium/include
INCLUDEDESTIMES=-I $(PWD)/cadmium/DESTimes/include

# Default target to compile simulator and tests
.PHONY: all
all: simulator tests

# Object file targets
message.o: data_structures/message.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/message.cpp -o build/message.o

main_top.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) top_model/main.cpp -o build/main_top.o

.PHONY: idu
idu: main_idu_test.o

main_idu_test.o: test/main_idu_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_idu_test.cpp -o build/main_idu_test.o

.PHONY: odu
odu: main_odu_test.o

main_odu_test.o: test/main_odu_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_odu_test.cpp -o build/main_odu_test.o

.PHONY: satellite
satellite: main_satellite_test.o

main_satellite_test.o: test/main_satellite_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_satellite_test.cpp -o build/main_satellite_test.o

# Target to compile tests
.PHONY: tests
tests: main_idu_test.o main_odu_test.o main_satellite_test.o message.o
		$(CC) -g -o bin/idu_test build/main_idu_test.o build/message.o 
		$(CC) -g -o bin/odu_test build/main_odu_test.o build/message.o 
		$(CC) -g -o bin/satellite_test build/main_satellite_test.o build/message.o 

# Target to compile simulator (ie. top model)
.PHONY: simulator
simulator: main_top.o message.o 
	$(CC) -g -o bin/simulator build/main_top.o build/message.o 
	
# Target to clean
.PHONY: clean
clean: 
	rm -f bin/* build/*

# Target to print help
.PHONY : help
help:
	@echo "Available targets:\n"
	@echo "all  [DEFAULT TARGET]" 
	@echo "\tMake the simulator and tests"
	@echo "simulator" 
	@echo "\tMake the simulator (ie. top model) only"
	@echo "tests" 
	@echo "\tMake the tests only"
	@echo "idu" 
	@echo "\tMake the IDU test only"
	@echo "odu" 
	@echo "\tMake the ODU test only"
	@echo "satellite" 
	@echo "\tMake the Satellite test only"
	@echo "clean" 
	@echo "\tClean built artifacts"

