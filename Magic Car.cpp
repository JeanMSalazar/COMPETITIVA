#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Edge {
    int x, y, v;
    Edge(int a = 0, int b = 0, int c = 0) : x(a), y(b), v(c) {}

    bool operator<(const Edge& other) const {
        return v < other.v;
    }
};

vector<Edge> edges;
int parent[1005], rankSet[1005];

// Encuentra el representante del conjunto
int find(int x) {
    return parent[x] == x ? x : (parent[x] = find(parent[x]));
}

// Une dos conjuntos disjuntos
bool join(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;

    if (rankSet[x] > rankSet[y]) {
        rankSet[x] += rankSet[y];
        parent[y] = x;
    } else {
        rankSet[y] += rankSet[x];
        parent[x] = y;
    }
    return true;
}

// Intenta conectar `st` y `ed` con los edges disponibles
bool kruskal(int n, int m, const vector<Edge>& edgeList, int st, int ed, int& maxEdge) {
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
        rankSet[i] = 1;
    }

    for (int i = 0; i < m; ++i) {
        if (join(edgeList[i].x, edgeList[i].y)) {
            if (find(st) == find(ed)) {
                maxEdge = edgeList[i].v;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while (cin >> n >> m && (n + m)) {
        edges.resize(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].x >> edges[i].y >> edges[i].v;
        }

        sort(edges.begin(), edges.end());

        int a, b, q;
        cin >> a >> b >> q;

        while (q--) {
            int x, y;
            cin >> x >> y;

            int ret = numeric_limits<int>::max();
            int maxEdge;

            for (int i = 0; i < m; ++i) {
                // Crea una sublista desde i hasta final
                vector<Edge> subEdges(edges.begin() + i, edges.end());
                if (kruskal(n, m - i, subEdges, x, y, maxEdge)) {
                    ret = min(ret, maxEdge - edges[i].v);
                } else {
                    break;
                }
            }

            cout << (a + b + ret) << '\n';
        }
    }

    return 0;
}
