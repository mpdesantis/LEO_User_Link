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
	
main_subnet_test.o: test/main_subnet_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_subnet_test.cpp -o build/main_subnet_test.o

main_sender_test.o: test/main_sender_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_sender_test.cpp -o build/main_sender_test.o

main_receiver_test.o: test/main_receiver_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_receiver_test.cpp -o build/main_receiver_test.o

# Target to compile tests
.PHONY: tests
tests: main_subnet_test.o main_sender_test.o main_receiver_test.o message.o
		$(CC) -g -o bin/SUBNET_TEST build/main_subnet_test.o build/message.o
		$(CC) -g -o bin/SENDER_TEST build/main_sender_test.o build/message.o 
		$(CC) -g -o bin/RECEIVER_TEST build/main_receiver_test.o build/message.o  

# Target to compile simulator (ie. top model)
.PHONY: simulator
simulator: main_top.o message.o 
	$(CC) -g -o bin/ABP build/main_top.o build/message.o 
	
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
	@echo "clean" 
	@echo "\tClean built artifacts"

