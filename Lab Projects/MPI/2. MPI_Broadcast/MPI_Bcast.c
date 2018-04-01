//Adam Eberlin siu850000376
//Lab 2

#include <stdio.h>
#include <string.h> 
#include <mpi.h>    

int main(void) {
   int        comm_sz;              
   int        my_rank;              
   int 	      buf;

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   buf = 0;
   while(buf >= 0){
 
      if (my_rank == 0) {
	   scanf("%d", &buf);
	   MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
	   if (buf < 0)
	        break;
	   }

      else {
	   MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);
	   printf("Rank = %d, Number = %d\n", my_rank, buf);
	   if (buf < 0)
	        break;
	   }    
      }
  
   MPI_Finalize(); 
   return 0;
}  

