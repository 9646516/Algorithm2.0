struct Matrix {
    static const int N = 105;
    long long m[N][N];
    Matrix() {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                m[i][j] = 0;
    }
    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        Matrix c;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j] % MOD) % MOD;
        return c;
    }
    friend Matrix pow(Matrix a, long long b) {
        assert(n >= 0);
        Matrix ret;
        for (int i = 0; i < N; i++)
            ret.m[i][i] = 1;
        while (b) {
            if (b & 1)
                ret = ret * a;
            a = a * a;
            b >>= 1;
        }
        return res;
    }
};