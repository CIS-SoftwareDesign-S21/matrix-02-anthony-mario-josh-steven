#ifndef MAT_H
#define MAT_H
#include <time.h>

double *gen_matrix(int n, int m);
int compare_matrices(double* a, double* b, int nRows, int nCols);
double *read_matrix_from_file(const char *path);
void read_matrices_from_file(const char *path, double**matrices);
void print_matrix(double *a, int nrows, int ncols);
double deltaTime(struct timespec *start, struct timespec *end);
int grab_size(char *filename);

int mmult(double *c, 
          double *a, int aRows, int aCols, 
          double *b, int bRows, int bCols);

int mmult_omp(double *c,
		      double *a, int aRows, int aCols,
		      double *b, int bRows, int bCols);

int mmult_simd(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols);
          
int mmult_simdo3(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols);

int steven_mpi2(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols, int argc, char*argv[]);

#endif