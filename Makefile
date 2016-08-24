all: programs

programs: manager.cpp worker.cpp
	mpiCC -std=c++11 -O3 -Wall -W  -I. -o manager manager.cpp
	mpiCC -std=c++11 -O3 -Wall -W  -I. -o worker worker.cpp
