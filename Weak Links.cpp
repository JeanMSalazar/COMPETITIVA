#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

const int MAXN = 1024;
vector<int> g[MAXN];
vector<pair<int, int>> bridge;
int visited[MAXN], depth[MAXN];

int findBridge(int u, int p, int dep) {
    visited[u] = 1;
    depth[u] = dep;
    int back = 0x3f3f3f3f;

    for (int v : g[u]) {
        if (v == p) continue;
        if (!visited[v]) {
            int b = findBridge(v, u, dep + 1);
            if (b > dep)
                bridge.emplace_back(min(u, v), max(u, v));
            back = min(back, b);
        }
        else {
            back = min(back, depth[v]);
        }
    }
    return back;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m && (n + m)) {
        for (int i = 0; i < n; ++i)
            g[i].clear();

        for (int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        fill(visited, visited + n, 0);
        bridge.clear();

        for (int i = 0; i < n; ++i)
            if (!visited[i])
                findBridge(i, -1, 0);

        sort(bridge.begin(), bridge.end());

        cout << bridge.size();
        for (const auto& p : bridge)
            cout << " " << p.first << " " << p.second;
        cout << '\n';
    }

    return 0;
}
