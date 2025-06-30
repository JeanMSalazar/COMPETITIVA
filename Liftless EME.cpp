#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

const int maxn = 121;
const int maxm = 16;
const int INF = numeric_limits<int>::max();

string name;
int n, m;
int dist[maxn][maxm];

void reset() {
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxm; ++j) {
            dist[i][j] = (i == 0 ? 0 : INF);
        }
    }
}

bool input() {
    if (!(cin >> name)) return false;

    cin >> n >> m;
    reset();

    for (int k = 0; k < n - 1; ++k) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                int travel_cost;
                cin >> travel_cost;
                if (dist[k][i] != INF) {
                    dist[k + 1][j] = min(dist[k + 1][j], dist[k][i] + travel_cost + 2);
                }
            }
        }
    }

    return true;
}

void output() {
    int lo = INF;
    for (int i = 1; i <= m; ++i) {
        lo = min(lo, dist[n - 1][i]);
    }

    cout << name << '\n' << lo << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (input()) {
        output();
    }

    return 0;
}
