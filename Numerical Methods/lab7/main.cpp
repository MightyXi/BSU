#include <iostream>
#include <valarray>
#include <chrono>

using namespace std;
const int n = 4;
float *A;
float *M;
float *min_M;

float randomFloat(int a, int b)
{
    return (float)(a + (rand() % (b - a))) + (float)(rand()) / (float)(RAND_MAX);
}

void FillA() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] =randomFloat(-50,50);
        }
    }
}
float * MatrixMultiplication(const float *A_, const float *X) {

    float * F = new float[n * n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float elem = 0;
            for (int k = 0; k < n; k++) {
                elem += A_[i * n + k] * X[k * n + j];
            }
            F[i*n+j] = elem;
        }
    }
    return F;
}

void MatrixMultiplication(float *&F, const float *A_, const float *X) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float elem = 0;
            for (int k = 0; k < n; k++) {
                elem += A_[i * n + k] * X[k * n + j];
            }
            F[i*n+j] = elem;
        }
    }
}
void printMatrix(int size, float *Mat){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout<<Mat[size*i+j]<<" ";
        }
        cout<<endl;
    }
}
void Fill_M_k_part(int k,float *&M){
    for(int i=0;i<n;i++){
        if(i!=k){
            for(int j=0;j<n;j++){
                if(i!=j){
                    M[k*n*n+i*n+j]=0;
                }else{
                    M[k*n*n+i*n+j]=1;
                }
            }

        }else{
            for(int j=0;j<n;j++){
                if(j!=k){
                    M[k*n*n+i*n+j]=-A[n*(k+1)+j]/A[n*(k+1)+k];
                }else{
                    M[k*n*n+i*n+j]=1/A[n*(k+1)+k];
                }
            }
        }
    }
}
void reversed_M_k(int k, float *&min_M){
    for(int i=0;i<n;i++){
        if(i!=k){
            for(int j=0;j<n;j++){
                if(i!=j){
                    min_M[k*n*n+i*n+j]=0;
                }else{
                    min_M[k*n*n+i*n+j]=1;
                }
            }
        }else{
            for(int j=0;j<n;j++){
                min_M[k*n*n+i*n+j]=A[n*(k+1)+j];
            }
        }
    }
}
int main() {
//    srand(time(0));
    A=new float [n*n];
    FillA();

    float trace=0;
    for(int i=0;i<n;i++){
        trace+=A[i * n + i];
    }


    cout<<"Matrix A:"<<endl;
    printMatrix(n, A);
    M=new float [n*n*(n-1)];
    min_M=new float[n*n*(n-1)];
    int k=n-2;
    float a;
    float *min_M_k=new float[n*n];
    float *M_k=new float[n*n];
    while(k>=0){
        a=A[n*(k+1)+k];
        if(a!=0 && abs(a)>=pow(10,-8)){
            Fill_M_k_part(k,M);
            reversed_M_k(k, min_M);
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    min_M_k[i*n+j]=min_M[k*n*n+n*i+j];
                    M_k[i*n+j]=M[k*n*n+n*i+j];
                }
            }
            float * temp = MatrixMultiplication(A,M_k);
            MatrixMultiplication(A,min_M_k, temp);


        }else{
            cout<<"The leading element is 0, rewriting matrix"<<endl;
            FillA();
            cout<<"A:"<<endl;
            printMatrix(n, A);

            trace=0;
            for(int i=0;i<n;i++){
                trace+=A[i * n + i];
            }
            k=n-2;
        }
        k--;
    }
    cout<<endl<<"Frobenius form\n";
    printMatrix(n, A);
    for(int i=n-1;i>0;i--){
        cout<<"M"<<i<<endl;
        for(int j=0;j<n;j++){
            for(int t=0;t<n;t++){
                cout<<M[(i-1)*n*n+j*n+t] <<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<"p1 "<<A[0]<<endl;
    cout << "SpA  " << trace;

    return 0;
}