#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"


double f(double x)
{
	exp(x)*sin(x);
}


double n_rand(double lambda)
{
	/* por ahora uso una distribucion exponencial para integrar */
	double u;
	u = rand() / (RAND_MAX + 1.0);

	return -log(1- u) / lambda;
}

double MCI(int N)
{
	double *x;
	x = malloc(sizeof(double *)*N);

	for(int i = 0; i < N; i++)
	{
            	x[i] = n_rand(0.05);
    	}

	double *F; 
	F = malloc(sizeof(double *)*N);

	for(int i = 0; i < N; i++)
	{
            	F[i] = f(x[i]);
    	}

	double sum = 0.0;
	
	for(int i = 0; i < N; i++)
	{
            	sum = sum + F[i];
    	}
	

	return sum/N; 
}

int main(int argc, char *argv[])
{

	int N = atoi(argv[1]);
	
	int rank, size;

	/* starts MPI */
	MPI_Init (&argc, &argv);
	/* get current process rank */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	/* get number of processes */
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	/* print the rank and number of processes */
        int nReal=N/(size-1);
        double integral;
        double vInt;

        if (rank!=0){
            vInt=MCA(nReal)/(size-1);
	}
        MPI_Reduce(&vInt, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );

        if(rank==0){
	    printf("%lf", integral);
        }
        MPI_Finalize();
        return 0;

}
