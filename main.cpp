#include <iostream>
#include <chrono>
#include <omp.h>
#include <cmath>

using namespace std;

int n;
int samples = 4;

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

void serialMultiplicationCalculation();
void parallelMultiplicationCalculation();
void optimizedMultiplicationCalculation();

void printMatrices();

int main() {

    char method;
    cout << "Select calculation method (s-sequential/p-parllel/o-optimized) : ";
    cin >> method;

    fillMatrices();


    if(method == 's'){
        serialMultiplicationCalculation();
    } else if(method == 'p'){
        parallelMultiplicationCalculation();
    } else{
        transposeMatrix();
        flatMatrices();
        optimizedMultiplicationCalculation();
    }

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

void serialMultiplicationCalculation(){

    for (n = 200; n <= 2000; n = n + 200){

        double sample_times[samples];

        double sum = 0;

        for (int i = 0; i < samples; i++){
            double start = omp_get_wtime();
            sequentialMultiplication();
            double end = omp_get_wtime();

            sample_times[i] = end - start;
            sum +=sample_times[i];
        }

        double average = sum / samples;

        double std = 0;

        for (int j=0; j<samples; j++){
            std += (sample_times[j] - average)*(sample_times[j] - average);
        }

        std = sqrt(std/samples);

        double req_samples = pow(((100*1.96*std)/(5*average)),2);

        cout << "Serial : Average for n = " << n << " : " << average;
        cout << " Serial : Std for n = " << n << " : " << std;
        cout << " Serial : Required samples for n = " << n << " : " << req_samples;
        cout << endl;
    }
}

void parallelMultiplicationCalculation(){

    for (n = 200; n <= 2000; n = n + 200){

        double sample_times[samples];

        double sum = 0;

        for (int i = 0; i < samples; i++){
            double start = omp_get_wtime();
            parallelMultiplication();
            double end = omp_get_wtime();

            sample_times[i] = end - start;
            sum +=sample_times[i];
        }

        double average = sum / samples;

        double std = 0;

        for (int j=0; j<samples; j++){
            std += (sample_times[j] - average)*(sample_times[j] - average);
        }

        std = sqrt(std/samples);

        double req_samples = pow(((100*1.96*std)/(5*average)),2);

        cout << "Parallel : Average for n = " << n << " : " << average;
        cout << " Parallel : Std for n = " << n << " : " << std;
        cout << " Parallel : Required samples for n = " << n << " : " << req_samples;
        cout << endl;

    }
}

void optimizedMultiplicationCalculation(){

    for (n = 200; n <= 2000; n = n + 200){

        double sample_times[samples];

        double sum = 0;

        for (int i = 0; i < samples; i++){
            double start = omp_get_wtime();
            optimizedMultiplication();
            double end = omp_get_wtime();

            sample_times[i] = end - start;
            sum +=sample_times[i];
        }

        double average = sum / samples;

        double std = 0;

        for (int j=0; j<samples; j++){
            std += (sample_times[j] - average)*(sample_times[j] - average);
        }

        std = sqrt(std/samples);

        double req_samples = pow(((100*1.96*std)/(5*average)),2);

        cout << "Optimized : Average for n = " << n << " : " << average;
        cout << " Optimized : Std for n = " << n << " : " << std;
        cout << " Optimized : Required samples for n = " << n << " : " << req_samples;
        cout << endl;

    }
}


