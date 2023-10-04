#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>

std::vector<double> generateVectorB(size_t size) {
    std::vector<double>  ans(size, 0);
    for (size_t i = 0; i < size; ++i) {
        ans[i] = 14 + i;
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
    std::vector<double> tmp(size, 0);
    std::vector<std::vector<double>> result(size, tmp);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            result[i][j] = rand() % 2000 - 1000;
    }
    return result;
}

std::vector<double> gaussWithoutMainElem(std::vector<std::vector<double>> matrix, std::vector<double> b) {
    std::vector<std::vector<double>> matrix_copy(b.size(), std::vector<double>(b.size(), 0));
    std::vector<double> b_copy(b.size(), 0);
    for(int i = 0; i < b.size(); ++i) {
        for(int j = 0; j < b.size(); ++j) {
            matrix_copy[i][j] = matrix[i][j];
        }
        b_copy[i] = b[i];
    }

    for(int k = 0; k < b.size() - 1; ++k) {
        for(int i = k + 1; i < b.size(); ++i) {
            double l = matrix_copy[i][k] / matrix_copy[k][k];
            matrix_copy[i][k] = 0.0f;
            for(int j = k + 1; j < b.size(); ++j) {
                matrix_copy[i][j] -= l * matrix_copy[k][j];
            }
            b_copy[i] -= l * b_copy[k];
        }
    }

    std::vector<double> x(b.size(), 0);
    x[b.size() - 1] = b_copy[b.size() - 1] / matrix_copy[b.size() - 1][b.size() - 1];
    for(int i = b.size() - 2; i >= 0; --i) {
        double sum = 0.0f;
        for(int j = i + 1; j < b.size(); ++j) {
            sum += matrix_copy[i][j] * x[j];
        }
        x[i] = (b_copy[i] - sum) / matrix_copy[i][i];
    }

    return x;
}

std::vector<double> gaussWithMainElem(std::vector<std::vector<double>> matrix, std::vector<double> b) {
    //Создание копий
    std::vector<std::vector<double>> matrix_copy(b.size(), std::vector<double>(b.size(), 0));
    std::vector<double> b_copy(b.size(), 0);
    for(int i = 0; i < b.size(); ++i) {
        for(int j = 0; j < b.size(); ++j) {
            matrix_copy[i][j] = matrix[i][j];
        }
        b_copy[i] = b[i];
    } //Прямой ход
    for(int k = 0; k < b.size() - 1; ++k) {
        double max = std::abs(matrix_copy[k][k]);
        int coord_str = 0;
        for(int i = k + 1; i < b.size(); ++i) {
            if(std::abs(matrix_copy[i][k]) > max) {
                max = std::abs(matrix_copy[i][k]);
                coord_str = i;
            }
        }

        //Свап строк матрицы
        if(max > std::abs(matrix_copy[k][k])) {
            std::swap(matrix_copy[k], matrix_copy[coord_str]);
            std::swap(b_copy[k], b_copy[coord_str]);
        }


        for(int i = k + 1; i < b.size(); ++i) {
            double l = matrix_copy[i][k] / matrix_copy[k][k];
            matrix_copy[i][k] = 0.0f;
            for(int j = k + 1; j < b.size(); ++j) {
                matrix_copy[i][j] -= l * matrix_copy[k][j];
            }
            b_copy[i] -= l * b_copy[k];
        }
    }

    //Обратный ход
    std::vector<double> x(b.size(), 0);
    x[b.size() - 1] = b_copy[b.size() - 1] / matrix_copy[b.size() - 1][b.size() - 1];
    for(int i = b.size() - 2; i >= 0; --i) {
        double sum = 0.0f;
        for(int j = i + 1; j < b.size(); ++j) {
            sum += matrix_copy[i][j] * x[j];
        }
        x[i] = (b_copy[i] - sum) / matrix_copy[i][i];
    }

    return x;
}

void print5(std::vector<double> vector) {
    for (int i = 0; i < 5; i++)
        std::cout << vector[i] << " ";
    std::cout << "\n";
}

double vectorNevyazki(std::vector<std::vector<double>> matrix, std::vector<double> x_, std::vector<double> b) {
    std::vector<double> b_ = multiply(matrix, x_);
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
    int size = 1700;
    std::vector<std::vector<double>> matrix = generateMatrix(size);
    std::vector<double> x = generateVectorB(size);
    std::vector<double> b = multiply(matrix, x);
    auto start = std::chrono::steady_clock::now();
    std::vector<double> x_ = gaussWithoutMainElem(matrix, b);
    auto end = std::chrono::steady_clock::now();
    const int time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    start = std::chrono::steady_clock::now();
    std::vector<double> y = gaussWithMainElem(matrix, b);
    end = std::chrono::steady_clock::now();
    const int time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Without choosing element" << "\n";

    std::cout << "5 cordinats of solution ";
    print5(x_);
    std::cout << "Norma vectora nevyazki " << vectorNevyazki(matrix, x_, b) << "\n";
    std::cout << "otnositelnaya pogreshnost " << relativeError(x_, x) << "\n";
    std::cout << "Runtime " << time1 << " ms\n";

    std::cout << "gauss with choosing main element\n";

    std::cout << "5 cordinats of solution ";
    print5(y);
    std::cout << "Norma vectora nevyazki " << vectorNevyazki(matrix, y, b) << "\n";
    std::cout << "Otnositelnaya pogreshnost " << relativeError(y, x) << "\n";
    std::cout << "Runtime " << time2 << " ms\n";
    return 0;
}
