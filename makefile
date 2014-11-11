
# Flags
CC = g++
CFLAGS = -g -Wall -Weffc++

# Executable "road_maintenance" depends on road_maintenance.o
road_maintenance: bin/road_maintenance.o
	@echo 'Building target: hello'
	@echo 'Invoking: C++ Linker'
	$(CC)  -o bin/road_maintenance bin/road_maintenance.o
	@echo 'Finished building target.'

 	
bin/road_maintenance.o:
	$(CC) -c -o bin/road_maintenance.o $(CFLAGS) src/road_maintenance.cpp

# Clean build directory
clean:
	rm -rf bin/*