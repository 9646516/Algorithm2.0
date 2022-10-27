#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
vector<pair<int, int>> V[maxn]; // pt dist
vector<pair<int, int>> Q[maxn]; // pt id
vector<pair<int, int>> Q2;
int dis[maxn], father[maxn], LCA[maxn];
bool vis[maxn];
int seek(int x) { return father[x] == x ? x : father[x] = seek(father[x]); }
void tarjan(int now) {
    vis[now] = true;
    for (int i = 0; i < (int)Q[now].size(); i++) {
        int next = Q[now][i].first;
        if (vis[next])
            LCA[Q[now][i].second] = seek(next);
    }
    for (int i = 0; i < (int)V[now].size(); i++) {
        int next = V[now][i].first;
        if (!vis[next]) {
            dis[next] = dis[now] + V[now][i].second;
            tarjan(next);
            father[next] = now;
        }
    }
}
int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        father[i] = i;
    for (int i = 1; i <= n; i++)
        V[i].clear();
    for (int i = 1; i <= n; i++)
        Q[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        V[a].push_back({b, c});
        V[b].push_back({a, c});
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        Q[a].push_back({b, i});
        Q[b].push_back({a, i});
        Q2.push_back({a, b});
    }
    tarjan(1);
    for (int i = 0; i < q; i++)
        cout << dis[Q2[i].first] + dis[Q2[i].second] - 2 * dis[LCA[i]] << endl;
    return 0;
}
/*
INPUT FORMAT:
* Line 1: N and Q
* Lines 2..N: Ai, Bi, and Li
* Lines N+1..N+Q: p1 and p2
*/