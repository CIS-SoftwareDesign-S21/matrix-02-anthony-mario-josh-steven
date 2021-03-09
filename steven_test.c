#include <stdio.h>
#include <stdlib.h>

#include "mat.h"

#define MAT_SIZE 5

#define MATRICES 5 

int test_unoptimized(double *a, int arows, int acols,
                     double *b, int brows, int bcols,
                     double *c_actual);

void print_matrices(double* matrices[]);

int main(int argc, char *argv[])
{
    double*matrix_list[5];
    // for (int i = 0; i < MATRICES; i++){
    //     printf("Number: ")
    // }

    int i = 3;
    double *a = read_matrix_from_file("fourbythree.txt");
    // matrix_list[i] = a;
    // i++;
    // double *b = read_matrix_from_file("fourbythree.txt");
    // matrix_list[i] = b;
    // i++;
    // double *c_actual = read_matrix_from_file("threebythree.txt");
    // matrix_list[i] = c_actual;
    // i++;

    // read_matrices_from_file("threebyfour.txt",matrix_list);

    // for (int j = 0; j < i; j++){
    //     print_matrix(matrix_list[j],3,3);
    // }
    // double *a = read_matrix_from_file("a.txt");
    // double *b = read_matrix_from_file("b.txt");
    // double *c_actual = read_matrix_from_file("c.txt");

    // double *c_calc = malloc(3 * 3 * sizeof(double));

    // if (!test_unoptimized(a, 3, 4, b, 4, 3, c_actual))
    // {
    //     exit(1);
    // }

    // puts("All tests pass.");

    // free(a);
    // free(b);
    // free(c_actual);
}

// int test_unoptimized(double *a, int arows, int acols,
//                      double *b, int brows, int bcols,
//                      double *c_actual)
// {
//     double *c_calc = malloc(arows * bcols * sizeof(double));

//     mmult_simd(c_calc, a, arows, acols, b, brows, bcols);

//     int are_same = compare_matrices(c_actual, c_calc, arows, bcols);

//     free(c_calc);

//     return are_same;
// }

void print_matrices(double* matrices[]){

}

void matrix_gen(const char *path){
    srand(time(NULL));
}