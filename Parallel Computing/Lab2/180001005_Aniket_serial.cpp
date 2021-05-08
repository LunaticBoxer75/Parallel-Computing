// Uncomment lines 47-52 to output the pairwise distance

#include<bits/stdc++.h>

const int inf=1e7;
#define endl "\n"

using namespace std;

int n;
vector<int>matrix;

//Computes pairwise shortest distance between nodes
void Floyd_Warshall(){
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){

			int v=matrix[i*n+k];
			if(v==inf) continue;
			for(int j=0;j<n;j++){

				if(matrix[k*n+j]==inf) continue;
				int val=v+matrix[k*n+j];

				if(val<matrix[i*n+j]) matrix[i*n+j]=val;

			}
		}
	}
}

int main(){

	cin>>n;	// No of threads 

	matrix.resize(n*n); //Storing edges in 1D array of size n*n

	for(int i=0;i<n*n;i++) cin>>matrix[i]; //Taking input from user

	auto begin = chrono::high_resolution_clock::now();
	
	Floyd_Warshall();

	//Time taken
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-begin);
	cout<<fixed<<setprecision(5) <<"Time Taken by serial program: "<< duration.count()/1000000.0 <<" s "<<endl;

	// for(int i=0;i<n*n;i++){

	// 	cout<<matrix[i]<<"\t";
	// 	if((i+1)%n==0)cout<<endl;

	// }

	return 0;
}
