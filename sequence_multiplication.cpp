#include <iostream>

using namespace std;

void fillMatrix(int n, double *mat_add);
void printMatrix(int n, double *mat_add);
void multiplyMatrix(int n, double *mat_add_c, double *mat_add_a, double *mat_add_b);
void free (int n, double *mat_add);

int main() {

    int n;

    cout << "Enter n value : ";
    cin >> n;

    double a[n][n];
    double b[n][n];
    double c[n][n];

    fillMatrix(n, (double *)&a);
    printMatrix(n, (double *)&a);

    fillMatrix(n, (double *)&b);
    printMatrix(n, (double *)&b);

    multiplyMatrix(n, (double *)&c, (double *)&a, (double *)&b);
    printMatrix(n, (double *)&c);

/*    free((double *)&a);
    free((double *)&b);
    free((double *)&c);*/

    return 0;
}

void fillMatrix(int n, double *mat_add){

    srand((unsigned)time(nullptr)); // change this to generat

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            *(mat_add +j+ n*i) = rand()%5;
        }
    }
}

void multiplyMatrix(int n, double *mat_add_c, double *mat_add_a, double *mat_add_b){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            *(mat_add_c +j+ n*i) = 0;
            for(int k = 0; k < n; k++)
                *(mat_add_c +j+ n*i) += *(mat_add_a + k + n*i) * *(mat_add_b +j+ n*k);
        }
}

void printMatrix(int n, double *mat_add){
    for (int i=0; i<n; i++){
        cout << endl;
        for (int j=0; j<n; j++){
            cout << *(mat_add +j+ n*i) << " " ;
        }
    }
    cout << endl;
}


void free (int n, double *mat_add){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            delete (mat_add +j+ n*i);
        }
    }
}
