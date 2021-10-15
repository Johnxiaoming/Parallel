//I can not get the right result. And didn't know the reason

# include <cstdlib>
# include <iostream>
#include <cmath>
# include <iomanip>
# include <omp.h>

using namespace std;

//****************************************************************************80
double cal_pi ( int n )
//****************************************************************************80
{
    int i;
    double x, pi, area;
    double sum=0;
    double h=2.0/n;

    #pragma omp parallel for
    for ( i = 0; i<n; i++ ) 
    {
      
        x = -1 + ( i + 0.5 ) * h;
        area= sqrt( 1 - x * x) * h;
        
        #pragma omp atomic 
        sum+=area;
    }

    pi=sum*2.0;
    
    return pi;
}

//****************************************************************************80
int main (int argc, char *argv[])
//****************************************************************************80
{
    int n, num_procs, num_threads;
    double pi, start, end;

    // Returns the number of processors that are available to the program
    num_procs = omp_get_num_procs();  

    // Returns the maximum value that can be returned by a call to the OMP_GET_NUM_THREADS function
    num_threads = omp_get_max_threads();  

    cout << "\n";
    cout << "SCHEDULE_OPENMP\n";
    cout << "  C++/OpenMP version\n";
    cout << "  Calculate Pi using numeric integration methods.\n";
    cout << "\n";
    cout << "  Number of processors available = " << num_procs << "\n";
    cout << "  Number of threads =              " << num_threads << "\n\n";
    cout << "Type N and enter: ";  
    cin >> n ;

    start = omp_get_wtime();  // start time check
    pi = cal_pi (n);
    end = omp_get_wtime();    // end time check

    cout << "  " << setw(8) << "N"
         << "  " << setw(18) << "Pi"
         << "  " << setw(18) << "Numer of threads"
         << "  " << setw(30) << "Elapsed wall clock time (sec)" << "\n";

    cout << "  " << setw(8) << n
         << "  " << setw(18) << pi
         << "  " << setw(18) << num_threads
         << "  " << setw(30) << end-start << "\n";

    return 0;
}
