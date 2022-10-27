static ll inv[maxn + 555], invp[maxn + 555], p[maxn + 555];
inv[1] = 1;
for (int i = 2; i <= maxn; i++)
    inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
p[0] = 1;
for (int i = 1; i <= maxn; i++)
    p[i] = p[i - 1] * i % MOD;
invp[0] = 1;
for (int i = 1; i <= maxn; i++)
    invp[i] = invp[i - 1] * inv[i] % MOD;
auto C = [&](int a, int b) -> ll {
    if (a < b)
        return 0;
    else
        return p[a] * invp[b] % MOD * invp[a - b] % MOD;
};