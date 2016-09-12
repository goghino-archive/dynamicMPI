CC=mpic++
#CC=/home/kardos/openmpi-2.0.1/bin/mpic++ 

all: programs

clean:
	rm manager worker

programs: manager.cpp worker.cpp
	$(CC) -std=c++11 -O3 -Wall -W  -I. -o manager manager.cpp
	$(CC) -std=c++11 -O3 -Wall -W  -I. -o worker worker.cpp
