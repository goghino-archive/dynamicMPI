#!/bin/bash
#
#SBATCH --job-name=test_mpi
#SBATCH --output=res_mpi.txt

#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --time=10:00

module load openmpi/2.0.1
srun -n 1 -N 1 ./manager 1
