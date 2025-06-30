#include <iostream>
#include <vector>
#include <iomanip> // para std::setprecision
using namespace std;

const int MAX = 1000005;
using ll = long long;

bool Comp[MAX] = { false };
int Prime[MAX] = { 0 };
vector<int> Div[MAX];
double ans[MAX] = { 0.0 };

void Sieve() {
    for (int i = 2; i < MAX; i++) {
        if (Comp[i]) {
            Prime[i] = Prime[i - 1];
        }
        else {
            Prime[i] = 1 + Prime[i - 1];
            for (int j = 2 * i; j < MAX; j += i) {
                Comp[j] = true;
                Div[j].push_back(i);
            }
        }
    }

    for (int i = 2; i < MAX; i++) {
        for (int d : Div[i]) {
            ans[i] += ans[i / d];
        }
        ans[i] += Prime[i];
        ans[i] /= (Div[i].size() + 1 - Comp[i]); // Comp[i] es bool, se convierte a 0 o 1
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Sieve();

    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int N;
        cin >> N;
        cout << "Case " << cs << ": " << fixed << setprecision(10) << ans[N] << "\n";
    }

    return 0;
}
