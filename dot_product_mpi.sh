#!/bin/bash
#SBATCH -o 7.out
#SBATCH --reservation=csci4850
#SBATCH -n 32

module load openmpi/gcc/64/1.10.7
mpirun -np 2 /xfs2/courses/cs/csci4850/wanxiang.liu/csci5850/7 500000000
mpirun -np 4 /xfs2/courses/cs/csci4850/wanxiang.liu/csci5850/7 500000000
mpirun -np 8 /xfs2/courses/cs/csci4850/wanxiang.liu/csci5850/7 500000000
mpirun -np 16 /xfs2/courses/cs/csci4850/wanxiang.liu/csci5850/7 500000000
mpirun -np 32 /xfs2/courses/cs/csci4850/wanxiang.liu/csci5850/7 500000000

exit 0