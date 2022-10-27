struct RollingHash {
    static const long long mo0 = 1e9 + 21, mo1 = 1e9 + 7;
    static const long long add0 = 1000010007, add1 = 1003333331;
    static const long long mul0 = 233, mul1 = 2333;
    static vector<long long> POW[2];
    vector<long long> H[2];
    void init(const string &s) {
        if (POW[0].empty()) {
            POW[0].push_back(1);
            POW[1].push_back(1);
        }
        while (POW[0].size() < s.size() + 10) {
            POW[0].push_back(POW[0].back() * mul0 % mo0);
            POW[1].push_back(POW[1].back() * mul1 % mo1);
        }
        H[0].push_back(0);
        H[1].push_back(0);
        for (int i = 0; i < s.size(); i++) {
            H[0].push_back((H[0].back() * mul0 + add0 + s[i]) % mo0);
            H[1].push_back((H[1].back() * mul1 + add1 + s[i]) % mo1);
        }
    }
    long long hash(int l, int r) { // s[l..r]
        if (l > r)
            return 0;
        else {
            long long F = (H[0][r + 1] + (mo0 - H[0][l] * POW[0][r + 1 - l] % mo0)) % mo0;
            long long S = (H[1][r + 1] + (mo1 - H[1][l] * POW[1][r + 1 - l] % mo1)) % mo1;
            return (F << 32) | S;
        }
    }
};
vector<long long> RollingHash::POW[2];