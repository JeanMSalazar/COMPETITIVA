#include <iostream>
#include <cmath>
using namespace std;

using ll = long long;

ll x, y, d;

void extendedEuclid(ll a, ll b) {
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    extendedEuclid(b, a % b);
    ll y1 = x - (a / b) * y;
    x = y;
    y = y1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll v, n1, n2, c1, c2;

    while (cin >> v, v) {
        cin >> c1 >> n1 >> c2 >> n2;
        extendedEuclid(n1, n2);

        if (v % d != 0) {
            cout << "failed\n";
        } else {
            x *= v / d;
            y *= v / d;

            // Reducimos n1 y n2 para evitar overflow
            ll n2d = n2 / d;
            ll n1d = n1 / d;

            // Cotas para n (usamos double para evitar truncamiento)
            ll lowerbound = static_cast<ll>(ceil(-static_cast<double>(x) / n2d));
            ll upperbound = static_cast<ll>(floor(static_cast<double>(y) / n1d));

            if (lowerbound <= upperbound) {
                ll x1 = x + n2d * lowerbound;
                ll y1 = y - n1d * lowerbound;
                ll cost1 = c1 * x1 + c2 * y1;

                ll x2 = x + n2d * upperbound;
                ll y2 = y - n1d * upperbound;
                ll cost2 = c1 * x2 + c2 * y2;

                if (cost1 < cost2)
                    cout << x1 << " " << y1 << '\n';
                else
                    cout << x2 << " " << y2 << '\n';
            } else {
                cout << "failed\n";
            }
        }
    }

    return 0;
}
