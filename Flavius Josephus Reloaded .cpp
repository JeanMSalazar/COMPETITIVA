#include <iostream>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, a, b;
    while (cin >> n >> a >> b) {
        map<int, int> COUNT;
        long long next = 0;
        int ret = static_cast<int>(n); // cantidad de valores distintos inicialmente
        while (true) {
            next = (a * ((next * next) % n) % n + b) % n;
            int& v = COUNT[next];
            v++;
            if (v == 2) ret--; // se repitió una vez
            if (v == 3) break; // se repitió dos veces, tercera aparición
        }
        cout << ret << '\n';
    }

    return 0;
}
