template <int N = 60> struct linear_base {
    int flag; // whether contain 0
    array<ll, N + 1> p;
    vector<ll> base;
    linear_base() {
        for (int i = 0; i <= N; i++) {
            p[i] = 0;
        }
        flag = 0;
    }
    void insert(ll x) {
        for (int i = N; i >= 0; i--) {
            if (x >> i) {
                if (p[i]) {
                    x ^= p[i];
                } else {
                    p[i] = x;
                    return;
                }
            }
        }
        flag = 1;
    }
    void rebuild() {
        for (int i = 0; i <= N; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (p[i] & (1ll << j)) {
                    p[i] ^= p[j];
                }
            }
        }
        for (int i = 0; i <= N; i++) {
            if (p[i]) {
                base.push_back(p[i]);
            }
        }
    }
    ll ask_kth(ll x) { // x>=1
        if (flag) {
            x--;
        }
        if (x >= (1ll << base.size())) {
            return -1;
        }
        ll res = 0;
        for (int i = 0; i <= N; i++) {
            if (x & (1ll << i)) {
                res ^= base[i];
            }
        }
        return res;
    }
};