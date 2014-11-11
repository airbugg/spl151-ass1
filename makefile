
# Flags
CC = g++
CFLAGS = -g -Wall -Weffc++

# Executable "road_maintenance" depends on road_maintenance.o
road_maintenance: bin/road_maintenance.o
	@echo 'Building target: road_maintenance'
	@echo 'Invoking: C++ Linker'
	$(CC)  -o bin/road_maintenance bin/road_maintenance.o
	@echo 'Finished building target.'

 	
bin/road_maintenance.o: src/road_maintenance.cpp include/road_maintenance.hpp
	$(CC) -c -o bin/road_maintenance.o $(CFLAGS) src/road_maintenance.cpp

# Clean build directory
clean:
	rm -rf bin/*