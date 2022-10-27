//有向图
struct scc_tarjan {
    int dex, color;
    vector<int> belong, dfs, low, vis;

    vector<vector<int>> V;
    stack<int> S;
    int N;
    scc_tarjan(int N) {
        dex = color = 1;
        this->N = N;
        belong.resize(N);
        dfs.resize(N);
        low.resize(N);
        vis.resize(N);
        V.resize(N);
        for (int i = 0; i < N; i++)
            V[i].clear();
    }
    void add(int x, int y) { V[x].push_back(y); }
    void tarjan(int now) {
        dfs[now] = low[now] = dex++;
        S.push(now);
        vis[now] = true;
        for (int i = 0; i < (int)V[now].size(); i++) {
            int next = V[now][i];
            if (!dfs[next]) {
                tarjan(next);
                low[now] = min(low[now], low[next]);
            } else if (vis[next]) {
                low[now] = min(low[now], dfs[next]);
            }
        }
        if (low[now] == dfs[now]) {
            while (vis[now]) {
                int tp = S.top();
                S.pop();
                belong[tp] = color;
                vis[tp] = false;
            }
            color++;
        }
    }
    void build() {
        for (int i = 1; i <= N; i++) {
            if (!dfs[i])
                tarjan(i);
        }
    }
};
