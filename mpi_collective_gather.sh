#!/bin/bash
#SBATCH -o mpi_collective_gather.out
#SBATCH --reservation=csci4850
#SBATCH -n 4
module load openmpi/gcc/64/1.10.7
mpirun /xfs2/courses/cs/csci4850/wanxiang.liu/csci5850/mpi_collective_gather
exit 0