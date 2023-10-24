#include <iostream>
#include <vector>
#include <cmath>

int size = 10;
int m = 14;
float eps = 0.0001;
int kmax = 1000;

std::vector<float> generateVectorX() {
    std::vector<float>  x(size, 0);
    for (int i = 0; i < size; ++i) {
        x[i] = (float)i + (float)m;
    }
    return x;
}

std::vector<float> multiply(std::vector<std::vector<float>> A, std::vector<float> x) {
    std::vector<float> ans(size, 0);
    {
        for (int i = 0; i < size; i++) {
            float sum = 0;
            for (int j = 0; j < size; j++) {
                sum += A[i][j] * x[j];
            }
            ans[i] = sum;
        }
    }
    return ans;
}

std::vector<std::vector<float>> generateMatrix() {
    std::vector<std::vector<float>> A(size, std::vector<float>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                A[i][j] = rand() % 5 - 4;
                A[i][i] -= A[i][j];
            }
        }

    }
    A[0][0] +=1;
    return A;
}

void printResults(std::vector<float> vector, int kNum) {
    if (kNum == kmax)
        std::cout << "Number of iterations has been exceeded" << std::endl;
    else
        std::cout << "Iteration " << kNum << std::endl;
    for (int i = 0; i < size; i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;
}

void JakobiMethod(std::vector<std::vector<float>> &A, std::vector<float>& f)
{
    std::vector<float> ans(size, 0);
    std::vector<float> copy(size, 0);
    //первая итерация
    for (int i = 0; i < size; ++i) {
        ans[i] = f[i]/A[i][i];
        copy[i] = ans[i];
    }

    int iterNumber = 0;
    for (int k = 1; k <= kmax; ++k) {
        for (int i = 0; i < size; ++i) {
            float sum = f[i];
            for (int j = 0; j < i; ++j) {
                sum-= A[i][j]*copy[j];
            }
            for (int j = i+1; j < size; ++j) {
                sum -= A[i][j]*copy[j];
            }
            copy[i] = ans[i];
            ans[i] = sum/A[i][i];
        }

        float maxConf = 0;
        for (int i = 0; i < size; ++i){
            float temp = std::abs(ans[i] - copy[i]);
            if (temp > maxConf)
                maxConf = temp;
        }
        iterNumber = k;
        if(maxConf < eps)
            break;
    }

    printResults(ans, iterNumber);
}

void RelaxationMethod(std::vector<std::vector<float>> &A, std::vector<float>& f, float w)
{
    std::vector<float> ans(size, 0);
    std::vector<float> copy(size, 0);

    for (int i = 0; i < size; ++i) {
        ans[i] = f[i]/A[i][i];
        copy[i] = ans[i];
    }

    int iterNumber = 0;
    for (int k = 1; k <= kmax; ++k) {
        for (int i = 0; i < size; ++i) {
            float sum = f[i];
            for (int j = 0; j < i; ++j) {
                sum-= A[i][j]*ans[j];
            }
            for (int j = i+1; j < size; ++j) {
                sum -= A[i][j]*ans[j];
            }
            copy[i] = ans[i];
            ans[i] = (1-w)*ans[i] +  w*(sum/A[i][i]);
        }

        float maxConf = 0;
        for (int i = 0; i < size; ++i){
            float temp = std::abs(ans[i] - copy[i]);
            if (temp > maxConf)
                maxConf = temp;
        }
        iterNumber = k;
        if(maxConf < eps)
            break;
    }

    printResults(ans, iterNumber);
}


int main()
{
    std::vector<std::vector<float>> matrix = generateMatrix();
    std::vector<float> x = generateVectorX();
    std::vector<float> f = multiply(matrix, x);
    //метод якоби
    JakobiMethod(matrix, f);
    
    //метод Гаусса-Зейделя
    RelaxationMethod(matrix, f, 1);

    //метод релаксации
    RelaxationMethod(matrix, f, 0.5);
    RelaxationMethod(matrix, f, 1.5);
    return 0;
}
