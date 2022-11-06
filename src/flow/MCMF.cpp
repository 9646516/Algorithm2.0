// AGC031E
// AGC034D
//負辺あったら壊れるからBellman-Fordとかやるといいんじゃない？
template <class D> struct MCMF {
    const static D INF = 1e15;
    struct E {
        int to, rev, cap;
        D cost;
    };
    int n;
    vector<vector<E>> g;
    vector<D> h, d;
    vector<int> pv, pe;
    MCMF(int nn) : n(nn), g(nn), h(nn), d(nn), pv(nn), pe(nn) {}
    pair<int, int> add(int a, int b, int cap, D cost) {
        pair<int, int> res(a, g[a].size());
        g[a].push_back({b, (int)g[b].size(), cap, cost});
        g[b].push_back({a, (int)g[a].size() - 1, 0, -cost});
        return res;
    }
    pair<D, int> go(int s, int t, int f) {
        priority_queue<pair<D, int>, vector<pair<D, int>>, greater<pair<D, int>>> q;
        fill(d.begin(), d.end(), MCMF::INF);
        d[s] = 0;
        q.push({0, s});
        while (q.size()) {
            auto [a, v] = q.top();
            q.pop();
            if (d[v] < a)
                continue;
            for (int i = 0; i < (int)g[v].size(); i++) {
                E e = g[v][i];
                if (e.cap > 0) {
                    D w = d[v] + e.cost + h[v] - h[e.to];
                    if (w < d[e.to]) {
                        d[e.to] = w;
                        q.push({w, e.to});
                        pv[e.to] = v;
                        pe[e.to] = i;
                    }
                }
            }
        }
        if (d[t] == MCMF::INF)
            return {0, 0};
        for (int i = 0; i < n; i++)
            h[i] = min(h[i] + d[i], MCMF::INF);
        int a = f;
        for (int v = t; v != s; v = pv[v])
            a = min(a, g[pv[v]][pe[v]].cap);
        for (int v = t; v != s; v = pv[v]) {
            E &e = g[pv[v]][pe[v]];
            e.cap -= a;
            g[e.to][e.rev].cap += a;
        }
        return {a * h[t], a};
    }
    D calc(int s, int t, int f) {
        D res = 0;
        while (f > 0) {
            auto w = go(s, t, f);
            if (w.second == 0)
                return MCMF::INF;
            f -= w.second;
            res += w.first;
        }
        return res;
    }
};

