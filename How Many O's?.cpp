#include <iostream>
using namespace std;

using ll = long long;

ll calcZeros(ll n) {
    if (n < 0) return 0;

    ll sum = 1;
    ll n10 = 1, ntail = 0;

    while (n) {
        if (n % 10 != 0) {
            sum += (n / 10) * n10;
        }
        else {
            sum += (n / 10 - 1) * n10 + (ntail + 1);
        }
        ntail += (n % 10) * n10;
        n /= 10;
        n10 *= 10;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m, n;
    while (cin >> m >> n) {
        if (m < 0 && n < 0)
            break;
        cout << calcZeros(n) - calcZeros(m - 1) << '\n';
    }

    return 0;
}
