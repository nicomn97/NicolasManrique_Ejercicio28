#PBS -l nodes=1:ppn=4,mem=16gb,walltime=00:00:30
#PBS -M n.manrique10@uniandes.edu.co
#PBS -m abe
#PBS -N ejercicio28


module load mpich/3.2.1

cd /hpcfs/home/fisi4028/n.manrique10/NicolasManrique_Ejercicio28
mpicc mca.c -o mca.x -lm

mpirun -np 8 ./mca.x 25000

