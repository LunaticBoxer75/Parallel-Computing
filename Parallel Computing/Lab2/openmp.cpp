// Uncomment lines 54-59 to output the pairwise distance

#include<bits/stdc++.h>
#include<omp.h>

const int inf=1e7;
#define endl "\n"
int size;

using namespace std;

int n;
vector<int>matrix;

void Floyd_Warshall(){
	for(int k=0;k<n;k++){

		#pragma omp parallel for num_threads(size) collapse(2)
		
			for(int i=0;i<n;i++){

				for(int j=0;j<n;j++){

					int v=matrix[i*n+k];
					if(v==inf) continue;
					if(matrix[k*n+j]==inf) continue;
					int val=v+matrix[k*n+j];

					if(val<matrix[i*n+j]) matrix[i*n+j]=val;

				}
			}
	}
}

int main(int argc, char **argv){

	size = atoi(argv[1]);

	cin>>n;

	matrix.resize(n*n); //Storing edges in 1D array of size n*n

	for(int i=0;i<n*n;i++) cin>>matrix[i];

	double start_time=omp_get_wtime();
	
	Floyd_Warshall();

	double final_tot=omp_get_wtime()-start_time;

	cout<<fixed<<setprecision(5) <<"Time Taken by openmp program: "<< final_tot <<" s "<<endl;

	// for(int i=0;i<n*n;i++){

	// 	cout<<matrix[i]<<"\t";
	// 	if((i+1)%n==0)cout<<endl;

	// }

	return 0;
}
