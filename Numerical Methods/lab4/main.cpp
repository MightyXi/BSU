#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

int size = 4;
int m = 14;
float eps = 0.0001;
kmax = 1000;

std::vector<float> generateVectorX() {
    std::vector<float>  x(size, 0);
    for (size_t i = 0; i < size; ++i) {
        x[i] = i + m;
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
    return A;
}

std::vector<float> JakobiMethod(std::vector<std::vector<float>> &A, std::vector<float>& f)
{
    std::vector<float> ans(size, 0);
    //первая итерация
    for (int i = 0; i < size; ++i) {
        ans[i] = f[i]/A[i][i];
    }
    for (int k = 1; k <= kmax; ++k) {
        for (int i = 0; i < size; ++i) {
            float sum = f[i];
            for (int j = 0; j < i; ++j) {
                sum-=
            }

            for (int j = i+1; j < size; ++j) {
                
            }
        }
    }

    return ans;
}





void print5(std::vector<float> vector) {
    for (int i = 0; i < 5; i++)
        std::cout << vector[i] << " ";
    std::cout << "\n";
}


float relativeError(std::vector<float> x_, std::vector<float> x) {
    float max_1 = -1;
    for (int i = 0; i < size; i++) {
        max_1 = std::max(std::abs(x_[i] - x[i]), max_1);
    }
    float max_2 = -1;
    for (int i = 0; i < size; i++) {
        max_2 = std::max(std::abs(x[i]), max_2);
    }
    return max_1 / max_2;
}


int main()
{
    std::vector<std::vector<float>> matrix = generateMatrix();
    std::vector<float> x = generateVectorX();
    std::vector<float> f = multiply(matrix, x);

    std::vector<float> ans = ForwardRunThrough(matrix, f);



    std::cout << "5 cordinats of solution ";
    print5(ans);
    std::cout << "otnositelnaya pogreshnost " << relativeError(ans, x) << "\n";
    return 0;
}
