#!/bin/bash

nworkers=2
comp_nodes=$(($nworkers+1))

sbatch <<-_EOF
#!/bin/bash
#SBATCH --job-name=dynamicMPI
#SBATCH --nodes=${comp_nodes}
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:02:00
#SBATCH --output=out.o

#srun -n 1 --ntasks-per-node 1 ./manager ${nworkers}
#./manager ${nworkers}
#/home/kardos/openmpi-2.0.1/bin/mpirun -np 1 ./manager ${nworkers}
mpirun -np 1 ./manager ${nworkers}
_EOF
