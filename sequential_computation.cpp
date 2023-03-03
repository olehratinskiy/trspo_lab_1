#include <iostream>
#include <cmath>
#include <omp.h>
#include <unistd.h>
#include <iomanip>
using namespace std;

float matrix_elem(int row, int column) {
    return (pow(column, 2) + 3 * column + 2) / sqrt(row + 1);
}

float vector_elem(int row) {
    return (log(sqrt(row)) * tan(2 * row)) / (sin(row) + 3);
}


int main() {
    int n = 0;
    bool add = false;

    // input values
    cout << "n: ";
    cin >> n;

    float c[n] = {0};

    double t1, t2;
    t1 = omp_get_wtime();

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            c[i] += matrix_elem(i + 1, j + 1) * vector_elem(i + 1);
        }
    }

    t2 = omp_get_wtime();

    cout << endl << "Result:" << endl;
    for (int i = 0; i < n; i++) {
        cout << c[i] << " ";
    }
    cout << endl;

    cout << endl << "Time (seconds): " << setprecision(30) << t2 - t1 << endl;

}