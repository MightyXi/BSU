#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>

int size = 10;
int k = 2;
int iter = 50;

std::vector<double> multiply(std::vector<std::vector<double>> A, std::vector<double> x) {
    std::vector<double> ans(x.size(), 0);
    {
        for (int i = 0; i < x.size(); i++) {
            double sum = 0;
            for (int j = 0; j < x.size(); j++) {
                sum += A[i][j] * x[j];
            }
            ans[i] = sum;
        }
    }
    return ans;
}

std::vector<std::vector<double>> generateMatrix(int size) {
    std::vector<std::vector<double>> matrix(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; i++)
    {
        double diagElement = 0;
        for (int j = 0; j < size; j++)
        {
            if (i != j && matrix[i][j] == 0){
                matrix[i][j] = (double)rand() / RAND_MAX * -1000.0f;
                matrix[j][i] = matrix[i][j];
                diagElement -= matrix[i][j];
            }

        }
        if (i == 0)
        {
            matrix[i][i] = diagElement + std::pow(10, 2 - k);
        }
        else{
            matrix[i][i] = diagElement;
        }
    }
    return matrix;
}

double GetMaximumNorm(const std::vector<double> &vector)
{
    double result = -99999;

    for (int i = 0; i < size; ++i)
    {
        if (vector[i] > result)
        {
            result = vector[i];
        }
    }

    return result;
}

template <typename T>
void PrintVector(const std::vector<T> &vector, const int numberOfElements = 0, const std::string &message = "")
{
    if (message != "")
    {
        std::cout << message << ' ';
    }
    const int border = numberOfElements != 0 ? numberOfElements : vector.size();
    for (int i = 0; i < border; ++i)
    {
        std::cout << vector[i] << ' ';
    }
    std::cout << '\n';
}

int GetSign(const int number)
{
    if (number == 0)
        return 0;
    if (number > 0)
        return 1;
    return -1;
}


double GetScalarProduct(const std::vector<double> &v1, const std::vector<double> &v2)
{
    double res = 0;
    for (int i = 0; i < size; ++i)
    {
        res += v1[i] * v2[i];
    }
    return res;
}

void RunMethod(const std::vector<std::vector<double>> &matrix)
{
    std::vector<double> u(size, 0);
    u[0] = 1;
    std::vector<double> v(size);
    for (int i = 0; i < iter; ++i)
    {
        v = multiply(matrix, u);
        const double vNorm = GetMaximumNorm(v);
        for (int j = 0; j < size; ++j)
        {
            u[j] = v[j] / vNorm;
        }
    }

    int maxIndex = 0;
    for (int i = 1; i < size; ++i)
    {
        if (std::abs(v[maxIndex]) <= std::abs(v[i]))
        {
            maxIndex = i;
        }
    }

    PrintVector(u, u.size(), "u^k");

    double lambda = v[maxIndex] * GetSign(u[maxIndex]);
    std::cout << "lambda1 = vi^k+1* sign(ui^k) = " << lambda << '\n';

    std::vector<double> au = multiply(matrix, u);

    std::vector<double> residualVector(size);

    for (int i = 0; i < size; ++i)
    {
        residualVector[i] = au[i] - lambda * u[i];
    }

    // PrintVector(residualVector, residualVector.size(), "v^k+1 - labmda * u^k");
    std::cout << "Maximum norm = " << GetMaximumNorm(residualVector) << '\n';

    lambda = GetScalarProduct(v, u) / GetScalarProduct(u, u);
    std::cout << "lambda1 = (v^k+1, u^k)/(u^k,u^k) = " << lambda << '\n';
    for (int i = 0; i < size; ++i)
    {
        residualVector[i] = au[i] - lambda * u[i];
    }

    // PrintVector(residualVector, residualVector.size(), "v^k+1 - labmda * u^k");
    std::cout << "Maximum norm = " << GetMaximumNorm(residualVector);
}

int main()
{
    std::vector<std::vector<double>> matrix = generateMatrix(size);

    RunMethod(matrix);
    return 0;
}
