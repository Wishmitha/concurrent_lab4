//
// Created by wolfpack on 2/21/18.
//

#ifndef CONCURRENT_LAB4_MATRIX_H
#define CONCURRENT_LAB4_MATRIX_H


#include <cstdlib>

class matrix {

    public:

        static double** fillMatrix(int n, bool randomize){

            auto** matrix = new double* [n];

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

        static double* flatMatrix(int n, double** matrix){
            double flat_matrix[n*n];

            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    flat_matrix[i*n + j] = matrix[i][j];
                }
            }

            return flat_matrix;
        }

        static void multiplyMatrixSequential(int n, double** mat_c, double** mat_a, double** mat_b){

            for(int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++)
                        mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
                }
            }

        }

        static void multiplyMatrixParallel(int n, double** mat_c, double** mat_a, double** mat_b){

            #pragma omp parallel for
            for(int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++)
                        mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
                }
            }

        }

        static void free (int n, double** matrix) {

            for(int i = 0; i < n; i++) {
                delete [] matrix[i];
            }

            delete [] matrix;
        }

};


#endif //CONCURRENT_LAB4_MATRIX_H
