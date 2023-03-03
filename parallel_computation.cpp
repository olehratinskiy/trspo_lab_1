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
    int threads_num, n = 0;
    bool add = false;

    // input values
    cout << "n: ";
    cin >> n;
    cout << "threads_num: ";
    cin >> threads_num;

    float c[n] = {0};
    if (threads_num > n) threads_num = n;

    // set threads num and calc how many columns has one thread operate
    omp_set_num_threads(threads_num);
    float cols_per_thread = float(n) / float(threads_num);

    // check if you can equally distribute columns between threads
    if (ceilf(cols_per_thread) != cols_per_thread) {
        cols_per_thread = floor(cols_per_thread);
        add = true;
    }

    double t1, t2;
    t1 = omp_get_wtime();

    #pragma omp parallel shared(c, n, threads_num, cols_per_thread, add)
    {
        int thread = omp_get_thread_num();

        // find column up to which thread has to operate and
        // if thread is last and you couldn't distribute columns equally -> add additional last column to this thread
        int cols = cols_per_thread * (1 + thread);
        if (thread + 1 == threads_num && add) cols += 1;

        for (int j = thread * cols_per_thread; j < cols; j++) {
            for (int i = 0; i < n; i++) {
                #pragma omp atomic
                c[i] += matrix_elem(i + 1, j + 1) * vector_elem(i + 1);
            }
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