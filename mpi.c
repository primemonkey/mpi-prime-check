#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <mpi.h>


int main(int argc,char **argv) {

  Args ins__args;
  parseArgs(&ins__args, &argc, argv);

  //program input argument
  long inputArgument = ins__args.arg; 

  struct timeval ins__tstart, ins__tstop;

  int myrank,nproc;
  
  MPI_Init(&argc,&argv);

  // obtain my rank
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  // and the number of processes
  MPI_Comm_size(MPI_COMM_WORLD,&nproc);

  if(!myrank)
      gettimeofday(&ins__tstart, NULL);


  // run your computations here (including MPI communication)
	
	long counter = 0;
	long result = 0;
	
	long range = inputArgument / nproc;
	
	
		for(long i=range*myrank+1; i<=range*(myrank+1); i++)
		{
			if(inputArgument % i == 0)
				++counter;
		}
		
		
	
		
	MPI_Reduce(&counter, &result, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(myrank==0)
	{
		if(result==1)
			printf("It is prime numberb");
		else
			printf("It is not prime number");
	}



  // synchronize/finalize your computations

  if (!myrank) {
    gettimeofday(&ins__tstop, NULL);
    ins__printtime(&ins__tstart, &ins__tstop, ins__args.marker);
  }
  
  MPI_Finalize();

}
