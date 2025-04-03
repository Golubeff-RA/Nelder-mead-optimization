#include "point.h"
#include <cmath>

double Measure(const std::vector<Point>& simplex) {
    if (!CheckDimensions(simplex)) {
        return -1;
    }
    
    // вычислим матрицу с координатами опорных векторов
    std::vector<std::vector<double>> matrix(simplex.size() - 1);
    for (size_t i = 1; i < simplex.size(); ++i) {
        matrix[i - 1].reserve(simplex.size() - 1);
        Point vec = simplex[i] - simplex[0];
        for (size_t j = 0; j < simplex.size() - 1; ++j) {
            matrix[i - 1][j] = vec[j];
        }
    }

    return std::abs(Determinant(matrix)) / Factorial(matrix.size());
}

bool CheckDimensions(const std::vector<Point>& simplex) {
    for (const Point& p : simplex) {
        if (p.Size() + 1 != simplex.size()) {
            return false;
        }
    }

    return true;
}

double Factorial (size_t n) {
    double answer = 1.0;
    for (size_t i = 1; i < n + 1; ++i) {
        answer *= i;
    }

    return answer;
}

double Determinant(const std::vector<std::vector<double>>& matrix) {
    size_t n = matrix.size();
    if (n == 1) {
        return matrix[0][0];
    }

    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0.0;

    for (size_t i = 0; i < n; ++i) {
        std::vector<std::vector<double>> minor(n - 1);
        for (size_t row = 1; row < n; ++row) {
            minor[row - 1].reserve(n - 1);
            size_t col_index = 0;
            for (size_t col = 0; col < n; ++col) {
                if (col != i) {
                    minor[row - 1][col_index] = matrix[row][col];
                    ++col_index;
                }
            }
        }
        det += matrix[0][i] * std::pow(-1, i) * Determinant(minor);

    }

    return det;
}