#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

std::vector<double> generateVectorB(size_t size) {
    std::vector<double>  ans(size, 0);
    for (size_t i = 0; i < size; ++i) {
        ans[i] = 23 + i;
    }
    return ans;
}

std::vector<double> mul(std::vector<std::vector<double>> A, std::vector<double> x) {
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
    std::vector<double> tmp(size, 0);
    std::vector<std::vector<double>> result(size, tmp);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            result[i][j] = rand() % 2000 - 1000;
    }
    return result;
}

std::vector<double> gaussianMethodNoLeadingElement(std::vector<std::vector<double>> matrix, std::vector<double> b) {
    std::vector<double> ans(b.size(), 0);
    for (int k = 0; k < b.size() - 1; k++) {
        for (int i = k + 1; i < b.size(); i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k + 1; j < b.size(); j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    for (int i = b.size() - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < b.size(); j++) {
            sum += matrix[i][j] * ans[j];
        }
        ans[i] = (b[i] - sum) / matrix[i][i];
    }
    return ans;
}

std::vector<double> gaussianMethodWithSelectingALeadingElement(std::vector<std::vector<double>> matrix, std::vector<double> b) {
    std::vector<double> ans(b.size(), 0);
    for (int k = 0; k < b.size() - 1; k++) {
        int numOfSwapColumn = k;
        double maxNumOfColumn = abs(matrix[k][k]);
        for (int i = k + 1; i < b.size(); i++) {
            if (abs(matrix[i][k]) > maxNumOfColumn) {
                numOfSwapColumn = i;
                maxNumOfColumn = abs(matrix[i][k]);
            }
        }
        if (numOfSwapColumn != k) {
            swap(matrix[k], matrix[numOfSwapColumn]);
            std::swap(b[k], b[numOfSwapColumn]);
        }
        for (int i = k + 1; i < b.size(); i++) {
            double factor = matrix[i][k] / matrix[k][k];
            for (int j = k; j < b.size(); j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    for (int i = b.size() - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < b.size(); j++) {
            sum += matrix[i][j] * ans[j];
        }
        ans[i] = (b[i] - sum) / matrix[i][i];
    }
    return ans;
}

void print5(std::vector<double> vector) {
    for (int i = 0; i < 5; i++)
        std::cout << vector[i] << " ";
    std::cout << "\n";
}

double normResidualVector(std::vector<std::vector<double>> matrix, std::vector<double> x_, std::vector<double> b) {
    std::vector<double> b_ = mul(matrix, x_);
    double max = -1;
    for (int i = 0; i < b.size(); i++) {
        max = std::max(std::abs(b_[i] - b[i]), max);
    }
    return max;
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


int main()
{
    int size = 3;
    std::vector<std::vector<double>> matrix = generateMatrix(size);
    std::vector<double> x = generateVectorB(size);
    std::vector<double> b = mul(matrix, x);
    std::vector<double> x_ = gaussianMethodNoLeadingElement(matrix, b);
    std::vector<double> y = gaussianMethodWithSelectingALeadingElement(matrix, b);

    std::cout << "Without choosing element" << "\n";

    std::cout << "5 cordinats of solution x* ";
    print5(x_);
    std::cout << "Norma vectora nevyazki " << normResidualVector(matrix, x_, b) << "\n";
    std::cout << "otnositelnaya pogreshnost " << relativeError(x_, x) << "\n";

    std::cout << "gauss with choosing main element\n";

    std::cout << "5 cordinats of solution x* ";
    print5(y);
    std::cout << "Norma vectora nevyazki " << normResidualVector(matrix, y, b) << "\n";
    std::cout << "Otnositelnaya pogreshnost " << relativeError(y, x) << "\n";

    return 0;
}
