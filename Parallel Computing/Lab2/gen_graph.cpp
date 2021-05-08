#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define double long double
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define mod 1000000007
#define ceil(a,b) (a+b-1)/b
#define endl "\n"
const int N=100005;
const int inf=1e18;
const double eps=1e-9;

#define oa(A) for(auto i:A)   cout<<i<<" ";cout<<endl;
#define o1(a) cout<<" "<<#a<<" : "<<a<<"\n"
#define o2(a,b) cout<<" "<<#a<<" : "<<a<<" "<<#b<<" : "<<b<<"\n"
#define o3(a,b,c) cout<<" "<<#a<<" : "<<a<<" "<<#b<<" : "<<b<<" "<<#c<<" : "<<c<<"\n"
#define o4(a,b,c,d) cout<<" "<<#a<<" : "<<a<<" "<<#b<<" : "<<b<<" "<<#c<<" : "<<c<<" "<<#d<<" : "<<d<<"\n"

int power(int a,int b){
    int res=1;
    while(b>0){
        if(b&1){
        	res=res*a;
		}
        a=a*a;
        b>>=1;
    }
    return res;
}
int pow1(int a,int b){
    int res=1;
    while(b>0){
        if(b&1){
            res=res*a;
            res%=mod;
        }
        a=a*a;
        a%=mod;
        b>>=1;
    }
    return res;
}
signed main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
	double a[3][4]={{0.12295, 0.08640, 0.06400, 0.05093}, {0.14912, 0.08706, 0.08006, 0.06391}, {0.16640, 0.12306, 0.08740, 0.07031}};

    double b[3][4]={{1.12189, 0.607250, 0.44229, 0.35309}, {1.46527, 0.772650, 0.58265, 0.38670}, {1.94779, 0.99002, 0.63527, 0.56444}};

    double c[3][4]={{6.57769, 3.958032, 2.77606, 2.17982}, {9.50987, 5.26070, 4.24912, 3.10543}, {15.20762, 7.54489, 5.17189, 4.02353}};

//Keeping n constant, time
       cout<<"([";
    for(int y=0;y<4;y++){
        cout<<"[";
        // for(int x=0;x<3;x++){
        //     if(x==0)cout<<a[x][0]/a[x][y];
        //     if(x==1)cout<<b[x][0]/b[x][y];
        //     if(x==2)cout<<c[x][0]/c[x][y];
        //     if(x+1<3)cout<<", ";

            cout<<a[1][0]/a[1][y]<<", ";
            cout<<b[1][0]/b[1][y]<<", ";
            cout<<c[1][0]/c[1][y];
            // cout<<", ";

        // }
        cout<<"],\n";
    }
    cout<<"])";







	
return 0;
}
