#include <vector>

const int MOD = 1e9 + 7;

class Matrix {
public:
    int n;
    std::vector<std::vector<int>> mat;

    Matrix(int size) : n(size) {
        mat.assign(n, std::vector<int>(n, 0));
    }

    void mul(const Matrix &other) {
        Matrix result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    result.mat[i][j] = (result.mat[i][j] + 1LL * mat[i][k] * other.mat[k][j] % MOD) % MOD;

        mat = result.mat;
    }
};