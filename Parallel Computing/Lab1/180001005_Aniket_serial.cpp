// This code is inspired from https://github.com/ahmadshafique/CYK-Parser/blob/master/CYK%20parser.cpp

#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define endl "\n"

#define N 1600

string grammar[N][N];	// Stores the grammar provided by the user
string temp[N];			
string parse_matrix[N][N];
int p,no_prod;		// no_prod stores the no of productions

void break_grammar(string a){	//Stores the RHS of grammar in the string array temp. Used to separate productions.

	int i;
	p=0;
	while(a.size()){

		i=a.find("|");

		int w=i;
		while(a[w-1]==' ')w--;	// Ignores space

		if(w>a.size()){

			temp[p++] = a;
			a="";
		}
		else{

			temp[p++] = a.substr(0,w); 
			w=i;
			while(a[w+1]==' ')w++;	// Ignores space
			a=a.substr(w+1,a.size());
		}
	}
}

string join(string a,string b){	//Joins different non terminals to get new parsing matrix value
	
	int i;
	string curr=a;
	for(i=0;i<b.size();i++)
		if(curr.find(b[i]) > curr.size())
			curr+=b[i];
	return (curr);
}

string check_red(string p){	//Iterates through complete grammar to check if the string p can be reduced or not

	int j,k;
	string curr="";
	for(j=0;j<no_prod;j++){

		k=1;

		while(grammar[j][k]!=""){

			if(grammar[j][k]==p){

				curr=join(curr,grammar[j][0]);
			}

			k++;
		}
	}	
	return curr;
}

string get_all_comb(string a, string b){ //Creates every possible combination of strings a and b

	int i,j;
	string temp1=a,re="";
	for(i=0;i<a.size();i++)
		for(j=0;j<b.size();j++){

			temp1="";
			temp1=temp1+a[i]+b[j];
			re=re+check_red(temp1);		//Checks if the current string can be obtained or not
		}		
	return re;
}

void print_table(string str){	// Prints the parsing table
	for(int i=0;i<str.size();i++)	
	{
		int k=0;
		int l=str.size()-i-1;
		for(int j=l;j<str.size();j++)
		{
			if(parse_matrix[k][j]!="")
			cout<<parse_matrix[k][j]<<"\t";
			else cout<<"phi\t";
			k++;
		}
		cout<<endl;
	}
}

int main(){

	int i,u,j,l,k;
	string a,str,curr,temp1,start;

	start="S";

	// cout<<"\nEnter the number of productions\n";
	// cout<<"Also enter each production in the format (S->AB|CD|a)\n";
	cin >> no_prod;
	cin.ignore();
	for(i=0;i<no_prod;i++){

		getline(cin,a);
		
		u=a.find("->");
		int w=u;

		while(a[w-1]==' ')w--; // Ignores space in grammar

		grammar[i][0] = a.substr(0,w);

		w=u+1;
		while(a[w+1]==' ')w++; // Ignores space in grammar

		a = a.substr(w+1, a.size());
		
		break_grammar(a);
		for(j=0;j<p;j++)
		{
			grammar[i][j+1]=temp[j];
		}
	}
	
	string st;

	// cout<<"\nEnter the string of symbols you need to check: ";
	getline(cin,str);

	auto begin = chrono::high_resolution_clock::now();

	for(i=0;i<str.size();i++){		//Assigns values to principal diagonal of matrix
	
		curr="";
		st = "";
		st+=str[i];
		for(j=0;j<no_prod;j++){

			k=1;
			while(grammar[j][k] != ""){

				if(grammar[j][k] == st){

					curr=join(curr,grammar[j][0]);
				}
				k++;
			}
		}
		parse_matrix[i][i]=curr;
	}

	for(k=1;k<str.size();k++){	//Assigns values to upper half of the matrix
	
		for(j=k;j<str.size();j++){
		
			curr="";
			for(l=j-k;l<j;l++){
			
				temp1 = get_all_comb(parse_matrix[j-k][l],parse_matrix[l+1][j]);
				curr = join(curr,temp1);
			}
			parse_matrix[j-k][j] = curr;
		}
	}

	// Prints the Parsing Table
	// print_table(str);
			
	int f=0;

	if(parse_matrix[0][str.size()-1].find(start)<=parse_matrix[0][str.size()-1].size()){	//Checks if last element of first row contains a Start variable
		cout<<"String can be parsed using this grammar\n";
	}else{
		cout<<"String cannot be parsed using this grammar\n";
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-begin);
	cout<<fixed<<setprecision(5) <<"Time Taken by serial program: "<< duration.count()/1000000.0 <<" s "<<endl;

	return 0;
}