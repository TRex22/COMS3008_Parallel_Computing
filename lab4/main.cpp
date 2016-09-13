#include <iostream>
#include "omp.h"
#include <cmath>


using namespace std;

const int n = 1000000;

double function(double x){
     return cos(x);
}

double dx(double x,double h){
     double y2 = function(x+h);
     double y1 = function(x-h);
     
     return((y2-y1)/(2*h));
}

void parallel() {
     /*int n = 1000000;*/
     double interval=0.1;
     double* data = new double[n];
     double* output = new double[n];
     
     for(int i = 0;i < n;i++){
          data[i] = i*interval;
     }
     
     double start = omp_get_wtime();
     
     #pragma omp parallel for
     for(int i = 0;i < n;i++){
          output[i] = dx(i,interval/2);
     }
     
     double end = omp_get_wtime();
     
     for(int i = 0;i < n;i++){
          //cout<<data[i]<<":"<<output[i]<<"\n";
     }
     cout<<end-start<<"\n";
}

void serial() {
     /*int n = 1000000;*/
     double interval=0.1;
     double* data = new double[n];
     double* output = new double[n];
     
     for(int i = 0;i < n;i++){
          data[i] = i*interval;
     }
     
     double start = omp_get_wtime();
     
     //#pragma omp parallel for
     for(int i = 0;i < n;i++){
          output[i] = dx(i,interval/2);
     }
     
     double end = omp_get_wtime();
     
     for(int i = 0;i < n;i++){
          //cout<<data[i]<<":"<<output[i]<<"\n";
     }
     cout<<end-start<<"\n";
}

int main(){
     serial();
     parallel();
}
