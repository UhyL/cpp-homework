#include "Matrix.h"
#include <iostream>

int main() {
    int n, p;

    std::cin >> n >> p;
    Matrix matrix(n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> matrix.mat[i][j];

    Matrix unity_matrix(n);

    for (int i = 0; i < n; ++i)
            unity_matrix.mat[i][i] = 1;

    while (p) {
        if (p & 1) {
            unity_matrix.mul(matrix);
        }
        matrix.mul(matrix);
        p >>= 1;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (j == n - 1)
                std::cout << unity_matrix.mat[i][j] << (std::endl);
            else
                std::cout << unity_matrix.mat[i][j] << " ";
        }
}