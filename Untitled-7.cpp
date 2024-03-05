#include <iostream>
#include <vector>
#include <cmath>

const double EPSILON = 1e-9;

void swap_rows(std::vector<std::vector<double>>& matrix, int row1, int row2) {
    std::swap(matrix[row1], matrix[row2]);
}

void eliminate(std::vector<std::vector<double>>& matrix, int pivot_row, int pivot_col) {
    int n = matrix.size();
    double pivot_value = matrix[pivot_row][pivot_col];

    for (int row = 0; row < n; ++row) {
        if (row != pivot_row) {
            double factor = matrix[row][pivot_col] / pivot_value;
            for (int col = pivot_col; col < n + 1; ++col) {
                matrix[row][col] -= matrix[pivot_row][col] * factor;
            }
        }
    }
}

bool is_zero(double value) {
    return fabs(value) < EPSILON;
}

bool solve_system(std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();

    for (int col = 0, row = 0; col < n && row < n; ++col) {
        int pivot_row = row;
        for (int i = row; i < n; ++i) {
            if (fabs(matrix[i][col]) > fabs(matrix[pivot_row][col])) {
                pivot_row = i;
            }
        }

        if (is_zero(matrix[pivot_row][col])) {
            continue;
        }

        swap_rows(matrix, pivot_row, row);
        eliminate(matrix, row, col);
        ++row;
    }

    for (int i = 0; i < n; ++i) {
        if (is_zero(matrix[i][i])) {
            return false; // No solution
        }
    }

    for (int i = 0; i < n; ++i) {
        matrix[i][n] /= matrix[i][i];
        matrix[i][i] = 1;
    }

    return true; // Solution found
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n + 1));

    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        for (int j = 0; j < m + 1; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    if (solve_system(matrix)) {
        std::cout << "YES" << std::endl;
        for (int i = 0; i < n; ++i) {
            printf("%.2f ", matrix[i][n]);
        }
        std::cout << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
