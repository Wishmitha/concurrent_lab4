#include <iostream>
#include <chrono>

using namespace std;

double** fillMatrix(int n, bool randomize);
void printMatrix(int n, double **mat_add);
void multiplyMatrix(int n, double **mat_c, double **mat_a, double **mat_b);
void free (int n, double** matrix);

int main() {

    int n;

    cout << "Enter n value : ";
    cin >> n;

    // mat_c = mat_a * mat_b

    double** mat_a = fillMatrix(n, true);
    double** mat_b = fillMatrix(n, true);
    double** mat_c = fillMatrix(n, false);

    auto start = chrono::steady_clock::now();

    multiplyMatrix(n, mat_c, mat_a, mat_b);

    auto end = chrono::steady_clock::now();

    cout << "Elapesed Time : " << chrono::duration_cast<chrono::milliseconds>(end -start).count() << endl;

    free(n,mat_a);
    free(n,mat_b);
    free(n,mat_c);

    return 0;
}

double** fillMatrix(int n, bool randomize){

    double** matrix = new double* [n];

    for (int i=0; i<n; i++){
        matrix[i] = new double[n];
    }

    srand((unsigned)time(nullptr));

    for (int j=0; j<n; j++){
        for (int k=0; k<n; k++){
            if(randomize){
                matrix[j][k] = rand()%10;
            } else{
                matrix[j][k] = 0;
            }
        }
    }
    return matrix;
}

void multiplyMatrix(int n, double** mat_c, double** mat_a, double** mat_b){

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++)
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
        }

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

void free (int n, double** matrix) {

    for(int i = 0; i < n; i++) {
        delete [] matrix[i];
    }

    delete [] matrix;
}