#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase;
    cin >> testcase;

    while (testcase--) {
        string chars;
        double mini, maxi, preci, minr, maxr, precr;

        cin >> chars >> mini >> maxi >> preci >> minr >> maxr >> precr;

        // Forzar el primer y último carácter a espacio, como en el original
        chars[0] = ' ';
        chars[13] = ' ';

        for (double a = mini; a <= maxi + 1e-8; a += preci) {
            for (double b = minr; b <= maxr + 1e-8; b += precr) {
                float za = 0, zb = 0;
                float ca = b, cb = a;
                int i;

                for (i = 0; i < 12; ++i) {
                    float ta = za * za - zb * zb;
                    float tb = 2 * za * zb;
                    za = ta + ca;
                    zb = tb + cb;
                    if (za * za + zb * zb > 4.0f)
                        break;
                }

                cout << chars[i + 1];
            }
            cout << '\n';
        }

        if (testcase)
            cout << '\n';
    }

    return 0;
}
