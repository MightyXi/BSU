#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>

int size = 3;
int m = 14;
int k = 2;
int lit = 50;

std::vector<double> generateVectorF(size_t size) {
    std::vector<double>  ans(size, 0);
    for (size_t i = 0; i < size; ++i) {
        ans[i] = m + i;
    }
    return ans;
}

double scalMul(std::vector<double> x, std::vector<double> y) {
    double ans = 0;
        for (int i = 0; i < x.size(); i++) {
            ans += x[i]*y[i];
        }
    return ans;
}

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
                matrix[i][j] = (double)rand() / RAND_MAX * -1000;
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
void LdltRtRDecomposition(std::vector<std::vector<double>> &matrix)
{
    std::vector<double> t(size);
    for (int k = 0; k < size - 1; ++k)
    {
        for (int i = k + 1; i < size; ++i)
        {
            t[i] = matrix[i][k];
            matrix[i][k] /= matrix[k][k];
            for (int j = k + 1; j <= i; ++j)
            {
                matrix[i][j] -= matrix[i][k] * t[j];
            }
        }
    }
}

// функция решения системы Ly=b
std::vector<double> SolveLyEqB(const std::vector<std::vector<double>> &lMatrix, const std::vector<double> &bVector)
{
    std::vector<double> y(size);
    for (int i = 0; i < size; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < i; j++)
        {
            sum += lMatrix[i][j] * y[j];
        }
        y[i] = bVector[i] - sum;
    }

    return y;
}

// функция решения системы Dz=y
std::vector<double> SolveDzEqY(const std::vector<std::vector<double>> &DMatrix, const std::vector<double> &yVector)
{
    std::vector<double> z(size);

    for (int i = 0; i < size; i++)
    {
        z[i] = yVector[i] / DMatrix[i][i];
    }

    return z;
}

// функция решения системы L^Tx=z
std::vector<double> SolveLTxEqZ(const std::vector<std::vector<double>> &ltMatrix, const std::vector<double> &zVector)
{
    std::vector<double> x(size);

    for (int i = size - 1; i >= 0; i--)
    {
        double sum = 0.0;
        for (int j = i + 1; j < size; j++)
        {
            sum += ltMatrix[j][i] * x[j];
        }
        x[i] = zVector[i] - sum;
    }

    return x;
}

// функция решения СЛАУ на основе LDL^T разложения
std::vector<double> SolveSystem(std::vector<std::vector<double>> &matrix, const std::vector<double> &vector)
{
    LdltRtRDecomposition(matrix);
    const std::vector<double> y = SolveLyEqB(matrix, vector);
    const std::vector<double> z = SolveDzEqY(matrix, y);
    const std::vector<double> x = SolveLTxEqZ(matrix, z);
    return x;
}




void print5(std::vector<double> vector) {
    for (int i = 0; i < 5; i++)
        std::cout << vector[i] << " ";
    std::cout << "\n";
}


double relativeError(std::vector<double> x_, std::vector<double> x) {
    double max_1 = -1;
    for (int i = 0; i < x.size(); i++) {
        max_1 = std::max(std::abs(x_[i] - x[i]), max_1);
    }
    double max_2 = -1;
    for (int i = 0; i < x.size(); i++) {
        max_2 = std::max(std::abs(x[i]), max_2);
    }
    return max_1 / max_2;
}

std::vector<double> cg(std::vector<std::vector<double>> &A, std::vector<double> &f, std::vector<double> &xZero){
    std::vector<double> xl = xZero;
    std::vector<double> fslae(size);
    std::vector<double> mvxl = f;
    for (size_t i = 0; i < size; i++){
        fslae[i] = f[i];
        xl[i] = xZero[i];
    }
    std::vector<double> rl(size, 0);
    std::vector<double> pl(size, 0);

    for (size_t i = 0; i < size; i++){
        rl[i] = fslae[i] - mvxl[i];
        pl[i] = rl[i];
    }

    double scal_rl_rl = scalMul(rl, rl);

    for (size_t i = 0; i < lit; i++){
        double rl_rl = scal_rl_rl;
        std::vector<double> mvpl = multiply(A, pl);
        double scal_mvpl_pl = scalMul(mvpl, pl);

        double alpha = rl_rl/scal_mvpl_pl;
        for (size_t j = 0; j < size; j++){
            xl[j] += alpha*pl[i];
            rl[j] -= alpha*mvpl[i];
        }

        scal_rl_rl = scalMul(rl, rl);
        double beta = scal_rl_rl/rl_rl;

        for (size_t j = 0; j < size; j++){
            pl[j] = rl[i] +beta*pl[i];
        }
    }


    return xl;
}


int main()
{
    std::vector<std::vector<double>> matrix = generateMatrix(size);
    std::vector<double> x = generateVectorF(size);
    std::vector<double> f = multiply(matrix, x);
    std::vector<double> xZero(size, 0);
    auto start = std::chrono::steady_clock::now();
    std::vector<double> x_ = cg(matrix, f, xZero);
    auto end = std::chrono::steady_clock::now();
    const int time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    start = std::chrono::steady_clock::now();
    const std::vector<double> y = SolveSystem(matrix, f);
    end = std::chrono::steady_clock::now();
    const int time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "cg" << "\n";

    std::cout << "5 cordinats of solution ";
    print5(x_);
    std::cout << "otnositelnaya pogreshnost " << relativeError(x_, x) << "\n";
    std::cout << "Runtime " << time1 << " ms\n";

    std::cout << "LDL\n";

    std::cout << "5 cordinats of solution ";
    print5(y);

    std::cout << "Otnositelnaya pogreshnost " << relativeError(y, x) << "\n";
    std::cout << "Runtime " << time2 << " ms\n";
    return 0;
}