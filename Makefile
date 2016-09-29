#CC=mpic++
CC=~/privateapps/openmpi/2.0.1/bin/mpic++

all: programs

clean:
	rm manager worker

programs: manager.cpp worker.cpp
	$(CC) -std=c++11 -O3 -Wall -W  -I. -o manager manager.cpp
	$(CC) -std=c++11 -O3 -Wall -W  -I. -o worker worker.cpp

run:
	mpirun --mca btl_tcp_if_include eth0 --mca pml ob1 --mca btl tcp,sm,self -np 1 --hostfile my_hosts ./manager 1
	#mpirun -np 1 -npernode 1 ./manager 1
	#mpirun -np 1 --hostfile my_hosts ./manager 1
	#mpirun -np 1 --hostfile my_hosts  -host icsnode37 ./manager 1

