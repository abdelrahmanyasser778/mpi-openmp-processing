#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>


 

int main ( int argc , char * argv []){
    int n , rank , numprocs , i;
    double mypi , FinalP , h , x;
     double p=0.0;
     int j =0; 
 // int k ;
     double s = 3.0;
    int valuePerProcess;
    double partial_sum ,sum;
    double power;
    double arr[1000000];
    double  startTime,endTime,speedUp,serialTime;
    MPI_Init(& argc ,& argv );
     MPI_Comm_size( MPI_COMM_WORLD ,& numprocs );
    MPI_Comm_rank( MPI_COMM_WORLD ,& rank );


            if ( rank == 0) 
            { 
                printf (" Enter the number : ");
                scanf ("%d" ,&n );
				startTime=MPI_Wtime();
            }
    MPI_Bcast(&n, 1, MPI_INT , 0 , MPI_COMM_WORLD );
    
              
  
               for ( j = rank+1 ; j <= n ; j += numprocs) {
      
                // printf(" rank is : %d the element of array is : %lf \n ",rank,pow(j,-s));
       partial_sum+=pow(j,-s);
       
               }
      
            MPI_Reduce (&partial_sum , &sum , 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD );

   if ( rank == 0) 
         { 
		double runTime,speedUp,efficiency;
				endTime=MPI_Wtime();
				runTime=endTime-startTime;
                printf (" The Total is : %lf \n",sum);
                printf (" Error = %.20lf \n",(1.202056903159594-sum));
				printf (" The runTime is : %lf \n",runTime);
				
				if(numprocs == 1){
					 speedUp=1,
					efficiency=1;
					printf("The speed up : %lf\n",speedUp);
			printf("The efficiency up : %lf\n",efficiency);
				}
				
				else {
			
			if(n==100){
			speedUp=0.001175/runTime;
	        efficiency=speedUp/numprocs;
			printf("The speed up : %lf\n",speedUp);
			printf("The efficiency up : %lf\n",efficiency);
			}
			if(n==1000){
				speedUp=0.000951/runTime;
	        efficiency=speedUp/numprocs;
			printf("The speed up : %lf\n",speedUp);
			printf("The efficiency up : %lf\n",efficiency);
			}
			}

   }
    MPI_Finalize();
    return EXIT_SUCCESS;
}




