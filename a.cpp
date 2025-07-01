#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <cfloat>

using namespace std;

using Punto = vector<double>;

// -------------------- Utilidades --------------------

double distanciaEuclidiana(const Punto& a, const Punto& b) {
    double suma = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        double diferencia = a[i] - b[i];
        suma += diferencia * diferencia;
    }
    return sqrt(suma);
}

// -------------------- Inicialización K-Means++ --------------------

vector<Punto> seleccionarSemillasIniciales(const vector<Punto>& entradas, int numClusters) {
    random_device dispositivo;
    mt19937 generador(dispositivo());
    uniform_int_distribution<> distrib(0, entradas.size() - 1);

    vector<Punto> elegidos;
    int inicial = distrib(generador);
    elegidos.emplace_back(entradas[inicial]);

    while (elegidos.size() < static_cast<size_t>(numClusters)) {
        vector<double> distCuadradas;
        distCuadradas.reserve(entradas.size());

        double acumulador = 0.0;

        for (const auto& punto : entradas) {
            double menorDistancia = DBL_MAX;
            for (const auto& centro : elegidos) {
                double d = distanciaEuclidiana(punto, centro);
                if (d < menorDistancia) menorDistancia = d;
            }
            double contrib = menorDistancia * menorDistancia;
            distCuadradas.push_back(contrib);
            acumulador += contrib;
        }

        uniform_real_distribution<> ruleta(0, acumulador);
        double umbral = ruleta(generador);

        double sumaTemp = 0.0;
        for (size_t i = 0; i < entradas.size(); ++i) {
            sumaTemp += distCuadradas[i];
            if (sumaTemp >= umbral) {
                elegidos.push_back(entradas[i]);
                break;
            }
        }
    }

    return elegidos;
}

// -------------------- Asignación a clusters --------------------

vector<int> agruparPuntos(const vector<Punto>& puntos, const vector<Punto>& centros) {
    vector<int> resultado(puntos.size(), -1);
    for (size_t idx = 0; idx < puntos.size(); ++idx) {
        double mejor = DBL_MAX;
        int asignado = -1;
        for (size_t c = 0; c < centros.size(); ++c) {
            double d = distanciaEuclidiana(puntos[idx], centros[c]);
            if (d < mejor) {
                mejor = d;
                asignado = static_cast<int>(c);
            }
        }
        resultado[idx] = asignado;
    }
    return resultado;
}

// -------------------- Recalcular centroides --------------------

vector<Punto> actualizarCentros(const vector<Punto>& entradas, const vector<int>& etiquetas, int totalCentros) {
    size_t dimension = entradas[0].size();
    vector<Punto> nuevos(totalCentros, Punto(dimension, 0.0));
    vector<int> cantidades(totalCentros, 0);

    for (size_t i = 0; i < entradas.size(); ++i) {
        int cl = etiquetas[i];
        cantidades[cl]++;
        for (size_t d = 0; d < dimension; ++d)
            nuevos[cl][d] += entradas[i][d];
    }

    for (int c = 0; c < totalCentros; ++c) {
        if (cantidades[c] > 0) {
            for (size_t j = 0; j < dimension; ++j)
                nuevos[c][j] /= cantidades[c];
        }
    }

    return nuevos;
}

// -------------------- K-Means Principal --------------------

void ejecutarKMeans(const vector<Punto>& datos, int k, int limiteIter = 100) {
    auto centros = seleccionarSemillasIniciales(datos, k);
    vector<int> etiquetas;

    for (int iter = 0; iter < limiteIter; ++iter) {
        etiquetas = agruparPuntos(datos, centros);
        auto actualizados = actualizarCentros(datos, etiquetas, k);

        if (actualizados == centros) {
            break; // Convergencia
        }

        centros = move(actualizados);
    }

    // Resultado final
    for (size_t i = 0; i < datos.size(); ++i) {
        cout << "Punto #" << i << " → Cluster " << etiquetas[i] << '\n';
    }
}

// -------------------- Ejemplo de uso --------------------

int main() {
    vector<Punto> ejemplo = {
        {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0},
        {8.0, 8.0}, {1.0, 0.6}, {9.0, 11.0}
    };

    int cantidadClusters = 2;
    ejecutarKMeans(ejemplo, cantidadClusters);

    return 0;
}
