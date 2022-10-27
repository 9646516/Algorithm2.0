struct undirected_graph {
    int n;
    vector<pair<int, int>> edge;
    vector<int> deg;
    vector<vector<int>> dcc;
    stack<int> s;
    int times;
    vector<int> dfn, low, bridges, cutpoints;
    vector<vector<pair<int, int>>> v;

    undirected_graph(int n) { init(n); }
    void init(int n) {
        assert(n >= 0);
        this->n = n;
        edge.clear();
        deg = vector<int>(n + 1);
        times = 0;
        dfn = vector<int>(n + 1);
        low = vector<int>(n + 1);
        bridges = vector<int>();
        cutpoints = vector<int>(n + 1);
    }
    void addedge(int x, int y) {
        edge.push_back({x, y});
        deg[x]++;
        deg[y]++;
    }

    void tarjan(int x, int pre, int root) {
        s.push(x);
        int sons = 0;
        dfn[x] = low[x] = ++times;
        for (auto e : v[x]) {
            int y = e.first, id = e.second;
            if (id == pre)
                continue;
            if (!dfn[y]) {
                tarjan(y, id, root);
                low[x] = min(low[x], low[y]);
                if (dfn[x] < low[y])
                    bridges.push_back(id);
                if (x == root)
                    ++sons;
                else if (dfn[x] <= low[y]) {
                    cutpoints[x] = 1;
                }
                if (dfn[x] <= low[y]) {
                    vector<int> now;
                    int t;
                    do {
                        t = s.top();
                        s.pop();
                        now.push_back(t);
                    } while (t != y);
                    now.push_back(x);
                    dcc.emplace_back(move(now));
                }
            } else
                low[x] = min(low[x], dfn[y]);
        }
        if (x == root && sons >= 2)
            cutpoints[x] = 1;
    }
    void build_tarjan() {
        v = vector<vector<pair<int, int>>>(n + 1);
        for (int i = 0; i < edge.size(); ++i) {
            int x = edge[i].first, y = edge[i].second;
            v[x].push_back({y, i});
            v[y].push_back({x, i});
        }
        for (int x = 1; x <= n; ++x)
            if (!dfn[x])
                tarjan(x, -1, x);
    }
};