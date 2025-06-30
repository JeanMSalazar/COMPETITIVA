#include <iostream>
#include <vector>
#include <bitset>
#include <string>
using namespace std;

using vi = vector<int>;

vector<vi> AdjList;
bitset<30> visited, appeared;
vi finishOrder;

void dfs(int u) {
    visited.set(u);
    for (int v : AdjList[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
    finishOrder.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    AdjList.assign(30, vi());

    string prev, curr;
    cin >> prev;

    while (cin >> curr && curr != "#") {
        int len = min(prev.size(), curr.size());
        for (int i = 0; i < len; i++) {
            if (prev[i] != curr[i]) {
                int u = prev[i] - 'A';
                int v = curr[i] - 'A';
                appeared.set(u);
                appeared.set(v);
                AdjList[u].push_back(v);
                break;
            }
        }
        prev = curr;
    }

    for (int i = 0; i < 26; i++) {
        if (!visited[i] && appeared[i]) {
            dfs(i);
        }
    }

    for (int i = finishOrder.size() - 1; i >= 0; i--) {
        cout << static_cast<char>(finishOrder[i] + 'A');
    }
    cout << '\n';

    return 0;
}
