#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 5; // number of discrete points along one axis (excluding boundaries)
const double tol = 1e-8;
const double h = 1.0 / (N + 1); // number of discrete elements in 1D

void initialize(vector<vector<double>>& t)
{
    for (int i = 0; i <= N+1; ++i)
     {
        for (int j = 0; j <= N+1; ++j)
         {
             if(i==0 || i==N+1)t[i][j]=1;  //BC top and bottom surface=1, left and right surface=0
             else
             t[i][j]=0.0;
         } 
     }
    
}

void update(vector<vector<double>>& t)
 {  
    vector<vector<double>> tnew=t;   /*since the boundary conditions along i=0,1 and j=0,1 are known, the points to be calculated begin from the neighbouring 
                               points of the BCs */
    double error=1.0;
    int count=0;
    while (error>tol)
    {
    
     for (int i = 1; i <= N; ++i)
      {       
        for (int j = 1; j <= N; ++j)
         {
           tnew[i][j] = 0.25 * (t[i-1][j] + t[i+1][j] + t[i][j-1] + t[i][j+1]);
             error=abs((tnew[i][j]-t[i][j]));
            
            
            t[i][j]=tnew[i][j];
            
         }
       }
       count++;
       
    }
    cout<<"Number of iterations: "<<count<<endl;
       //return t;
}

void print_solution(const vector<vector<double>>& t)
 {
    for (int i = 0; i <= N+1; ++i)
     {
        for (int j = 0; j <= N+1; ++j)
         {
            cout << t[i][j] << "    ";
        }
        cout << endl;
    }
}

int main()
 {
    vector<vector<double>> t(N+2, vector<double>(N+2, 0.0)); // Solution grid with boundary

    initialize(t);
    //print_solution(t);
    update(t);

    //cout << "Converged in " << iter << " iterations." << endl;
    print_solution(t);

}
