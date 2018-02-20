#include <iostream>
#include <chrono>
#include "matrix.h"

using namespace std;

void printMatrix(int n, double **mat_add);

int main() {

    int n;
    char method;

    cout << "Enter n value : ";
    cin >> n;

    cout << "Select calculation method (s-sequential/p-parllel) : ";
    cin >> method;

    // mat_c = mat_a * mat_b

    double** mat_a = matrix::fillMatrix(n, true);
    double** mat_b = matrix::fillMatrix(n, true);
    double** mat_c = matrix::fillMatrix(n, false);

    auto start = chrono::steady_clock::now();

    if(method == 's'){
        matrix::multiplyMatrixSequential(n, mat_c, mat_a, mat_b);
    } else {
        matrix::multiplyMatrixParallel(n, mat_c, mat_a, mat_b);
    }

    auto end = chrono::steady_clock::now();

    cout << "Elapesed Time : " << chrono::duration_cast<chrono::milliseconds>(end -start).count() << endl;

    matrix::free(n,mat_a);
    matrix::free(n,mat_b);
    matrix::free(n,mat_c);

    return 0;
}

void printMatrix(int n, double** matrix){

    for (int i=0; i<n; i++){
        cout << endl;
        for (int j=0; j<n; j++){
            cout << matrix[i][j] << " ";
        }
    }

    cout << endl;
}

