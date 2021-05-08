/*
 Author: 180001005 (Aniket Sangwan)
 */

#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;

/* MAX-1 is the largest possible value of any element in the array*/
const int MAX = 1000;

// Merges two equal sized arrays A and B in the list A. C acts as a temporary array.
void Merge(int A[], int B[], int C[], int size){

   int a1=0,b1=0,c1=0;

   while(a1<size && b1<size){

     if(A[a1]<=B[b1]){

         C[c1]=A[a1];
         c1++;a1++;

      }else{

         C[c1]=B[b1];
         c1++;b1++;
      }
   }

   //Remaining elements are inserted
   if(a1>=size){
      for(;c1<2*size;c1++,b1++)  C[c1]=B[b1];
   }else{
      for(;c1<2*size;c1++,a1++)  C[c1]=A[a1];
   }

   memcpy(A, C, 2*size*sizeof(int));

}

// Parallel Merge Sort using tree-structured communication
void Merge_sort(int A[], int local_n, int my_rank, int p, MPI_Comm comm){

   int partner,done=0,size=local_n;
   unsigned bitmask=1;
   int *B,*C;
   MPI_Status status;

   B=new int[p*local_n];
   C=new int[p*local_n];

   while(!done && bitmask<p){

      //Selecting slave process using bitmasking
      partner=my_rank^bitmask;
      if(my_rank>partner){

         // sorted array is sent to the master process
         MPI_Send(A, size, MPI_INT, partner, 0, comm);
         done=1;

      }else{

         //Master process receives the sorted array.
         MPI_Recv(B, size, MPI_INT, partner, 0, comm, &status);

         Merge(A, B, C, size);
         size=2*size;
         bitmask<<=1;

      }
   }

   free(B);
   free(C);
}

// Outputs the array
void Print_list(int A[], int n){
   int i;

   for(i=0;i<n;i++) printf("%d ",A[i]);
   printf("\n");

}

// Prints the contents of the global array
void Print_global_list(int A[], int local_n, int my_rank, int p, MPI_Comm comm){

   int* global_A=NULL;

   if(my_rank==0){

      //Parent process gathers array from every child
      global_A=new int[p*local_n];
      MPI_Gather(A, local_n, MPI_INT, global_A, local_n, MPI_INT, 0, comm);

      // cout<<"Initial global array: ";
      // Print_list(global_A, p*local_n);
      free(global_A);

   }else{

      // Locally sorted array is sent to the master process by every child process
      MPI_Gather(A, local_n, MPI_INT, global_A, local_n, MPI_INT, 0, comm);

   }

}  



// Random array generator for child processes
void Generate_list(int A[], int local_n, int my_rank){

   int i;

    srandom(my_rank+1);
    for(i=0;i<local_n;i++) A[i]=random() % MAX;
    sort(A, A+local_n);

}


/*-------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   int my_rank, p; //Current process rank and no of processes
   int* A; // Stores the array
   int n,local_n;
   MPI_Comm comm;

   MPI_Init(&argc, &argv);
   comm=MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   if(ceil(log2(p))!=floor(log2(p))){ cout<<"Number of processes should be a power of 2. Rerun the program\n";exit(1);}

   if(my_rank==0){

      cout<<"Enter the length of array\n";
      cin>>n;
      if(n%p!=0){ cout<<"Length of array should be divisible by the number of processes p\n";exit(1);}

   }

   MPI_Barrier(comm);
   double start=MPI_Wtime(); //Starts the timer

   MPI_Bcast(&n, 1, MPI_INT, 0, comm); // Broadcasts the no of elements in the array

   local_n=n/p; // No of elements for each process

   A=new int[p*local_n];

   Generate_list(A, local_n, my_rank);

   Print_global_list(A, local_n, my_rank, p, comm);

   Merge_sort(A, local_n, my_rank, p, comm);

   double end=MPI_Wtime()-start; // Total runtime 

   double max_time;

   MPI_Reduce(&end, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); // Gets the maximum of time taken by every process


   if (my_rank==0){
      // cout<<"After sorting: ";
      // Print_list(A, p*local_n);
      cout<<"Time taken is: "<<max_time<<endl;

   }

   free(A);

   MPI_Finalize();

   return 0;

}