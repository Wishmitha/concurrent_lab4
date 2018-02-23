#include <iostream>
#include <chrono>

using namespace std;

int n;

/* Since the maximum required space for this lab is 2000, it is allocated initially. If the given n is less than 2000,
 * there will be free space remaining.*/

double mat_a[2000][2000];
double mat_b[2000][2000];
double mat_c[2000][2000];  // mat_c = mat_a * mat_b

double trans_mat_b[2000][2000]; // store the transpose of matrix b

double flat_mat_a[2000 * 2000];
double flat_trans_mat_b[2000 * 2000];
double flat_mat_c[2000 * 2000];

void fillMatrices();
void transposeMatrix();
void flatMatrices();
void sequentialMultiplication();
void parallelMultiplication();
void optimizedMultiplication();

void printMatrices();

int main() {

    cout << "Enter n value : ";
    cin >> n;

    char method;
    cout << "Select calculation method (s-sequential/p-parllel/o-optimized) : ";
    cin >> method;

    fillMatrices();

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    if(method == 's'){
        start = chrono::steady_clock::now();
        sequentialMultiplication();
        end = chrono::steady_clock::now();
    } else if(method == 'p'){
        start = chrono::steady_clock::now();
        parallelMultiplication();
        end = chrono::steady_clock::now();
    } else{
        transposeMatrix();
        flatMatrices();
        start = chrono::steady_clock::now();
        optimizedMultiplication();
        end = chrono::steady_clock::now();
    }

    cout << "Elapesed Time : " << chrono::duration_cast<chrono::milliseconds>(end -start).count() << endl;

    return 0;
}

void fillMatrices(){

    srand((unsigned)time(nullptr));

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            mat_a[i][j] = rand()%10;
            mat_b[i][j] = rand()%10;
            mat_c[i][j] = 0;
        }
    }
}

void transposeMatrix(){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            trans_mat_b[j][i] = mat_b[i][j];
        }
    }
}

void flatMatrices(){

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            flat_mat_a[i*n + j] = mat_a[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            flat_trans_mat_b[i*n + j] = trans_mat_b[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            flat_mat_c[i*n + j] = mat_c[i][j];
        }
    }
}


void sequentialMultiplication(){

    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
        }
    }

}

void parallelMultiplication(){

#pragma omp parallel for
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++)
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
        }
    }

}

void optimizedMultiplication(){

#pragma omp parallel for
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n/16; k++){
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k] * flat_trans_mat_b[j*n+k];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+1] * flat_trans_mat_b[j*n+k+1];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+2] * flat_trans_mat_b[j*n+k+2];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+3] * flat_trans_mat_b[j*n+k+3];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+4] * flat_trans_mat_b[j*n+k+4];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+5] * flat_trans_mat_b[j*n+k+5];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+6] * flat_trans_mat_b[j*n+k+6];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+7] * flat_trans_mat_b[j*n+k+7];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+8] * flat_trans_mat_b[j*n+k+8];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+9] * flat_trans_mat_b[j*n+k+9];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+10] * flat_trans_mat_b[j*n+k+10];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+11] * flat_trans_mat_b[j*n+k+11];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+12] * flat_trans_mat_b[j*n+k+12];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+13] * flat_trans_mat_b[j*n+k+13];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+14] * flat_trans_mat_b[j*n+k+14];
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+k+15] * flat_trans_mat_b[j*n+k+15];
            }

            for(int rem =0; rem < n%16; rem++){
                flat_mat_c[i*n + j] +=  flat_mat_a[j*n+rem] * flat_trans_mat_b[j*n+rem];
            }
        }
    }

}

void printMatrices(){

    for (int i=0; i<n; i++){
        cout << endl;
        for (int j=0; j<n; j++){
            cout << mat_a[i][j] << " ";
        }
    }

    cout << endl;

    for (int i=0; i<n; i++){
        cout << endl;
        for (int j=0; j<n; j++){
            cout << mat_b[i][j] << " ";
        }
    }

    cout << endl;

    for (int i=0; i<n; i++){
        cout << endl;
        for (int j=0; j<n; j++){
            cout << mat_c[i][j] << " ";
        }
    }

    cout << endl;

    for (int i=0; i<n; i++){
        cout << endl;
        for (int j=0; j<n; j++){
            cout << trans_mat_b[i][j] << " ";
        }
    }

    cout << endl;
    cout << endl;

    for (int i=0; i<n*n; i++){
        cout << flat_mat_a[i] << " ";
    }

    cout << endl;
    cout << endl;

    for (int i=0; i<n*n; i++){
        cout << flat_trans_mat_b[i] << " ";
    }

    cout << endl;
    cout << endl;

    for (int i=0; i<n*n; i++){
        cout << flat_mat_c[i] << " ";
    }

    cout << endl;
    cout << endl;
}


