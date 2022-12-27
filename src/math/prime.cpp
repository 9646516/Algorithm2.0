struct Sieve {
    std::vector<int> min_factor;
    std::vector<int> primes;
    Sieve(int MAXN) : min_factor(MAXN + 1) {
        for (int d = 2; d <= MAXN; d++) {
            if (!min_factor[d]) {
                min_factor[d] = d;
                primes.emplace_back(d);
            }
            for (const auto &p : primes) {
                if (p > min_factor[d] or d * p > MAXN)
                    break;
                min_factor[d * p] = p;
            }
        }
    }
    // Prime factorization for 1 <= x <= MAXN^2
    // Complexity: O(log x)           (x <= MAXN)
    //             O(MAXN / log MAXN) (MAXN < x <= MAXN^2)
    template <class T> std::map<T, int> factorize(T x) const {
        std::map<T, int> ret;
        assert(x > 0 and
               x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));
        for (const auto &p : primes) {
            if (x < T(min_factor.size()))
                break;
            while (!(x % p))
                x /= p, ret[p]++;
        }
        if (x >= T(min_factor.size()))
            ret[x]++, x = 1;
        while (x > 1)
            ret[min_factor[x]]++, x /= min_factor[x];
        return ret;
    }
    // Enumerate divisors of 1 <= x <= MAXN^2
    // Be careful of highly composite numbers https://oeis.org/A002182/list
    // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n, (# of div. of n)):
    // 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720
    template <class T> std::vector<T> divisors(T x) const {
        std::vector<T> ret{1};
        for (const auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        return ret; // NOT sorted
    }
};
Sieve sieve(10101010);