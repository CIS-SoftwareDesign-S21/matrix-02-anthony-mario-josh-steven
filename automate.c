#include <stdio.h>

#include <sys/times.h>
#include <stdlib.h>

#include "mat.h"
void dataGen1(int n, FILE *filename);
void dataGen(int n, FILE *filename, int num_func);

int main(int argc, char *argv[])
{

    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Unable to open file at path 'data.txt'\n");
        exit(EXIT_FAILURE);
    }

    // if (argc==3)
    // {
    //     int n = atoi(argv[1]);
    //     int num_func = atoi(argv[2]);
    //     // printf("check: %d, num_func: %d",n,num_func);
    //     dataGen(n,fp,num_func);
    // }
    if (argc > 1)
    {
        int n = atoi(argv[1]);
        dataGen1(n, fp);
    }
    else
    {
        fprintf(stderr, "Usage %s <n>\n", argv[0]);
    }
    fclose(fp);
}

void dataGen(int n, FILE *filename, int num_func)
{
    struct timespec start;
    struct timespec end;
    struct timespec res;
    double *a, *b, *c1, *c2;
    double times[2];
    int iterations = 0;

    puts("hello");

    int (*matrix_func[2])(double *, double *, int, int, double *, int, int) = {mmult, mmult_simd};

    while (iterations < 5)
    {
        a = gen_matrix(n, n);
        b = gen_matrix(n, n);
        c1 = malloc(sizeof(double) * n * n);
        c2 = malloc(sizeof(double) * n * n);
        printf("Calculating for size: %d\n", n);
        clock_gettime(CLOCK_REALTIME, &start);
        // mmult(c1, a, n, n, b, n, n);
        (*matrix_func[num_func])(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[0] = deltaTime(&start, &end);
        fprintf(filename, "%d, %f\n", n, times[0]);
        // clock_gettime(CLOCK_REALTIME, &start);
        // mmult_simd(c2, a, b, n);
        // clock_gettime(CLOCK_REALTIME, &end);
        // times[1] = deltaTime(&start, &end);
        // fprintf(filename, " %f\n", times[1]);
        // compare_matrices(c1, c2, n, n);
        n += 500;
        iterations++;
    }
}

void dataGen1(int n, FILE *filename)
{
    struct timespec start;
    struct timespec end;
    struct timespec res;
    double *a, *b, *c1, *c2;
    double times[4]={0};
    int iterations = 0;

    // puts("hello");
    // double line[6]={0};

    while (iterations < 6)
    {
        a = gen_matrix(n, n);
        b = gen_matrix(n, n);
        c1 = malloc(sizeof(double) * n * n);
        // c2 = malloc(sizeof(double) * n * n);
        printf("Calculating for size: %d\n", n);

        clock_gettime(CLOCK_REALTIME, &start);
        mmult(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[0] = deltaTime(&start, &end);
        fprintf(filename, "%d, %f,", n, times[0]);

        clock_gettime(CLOCK_REALTIME, &start);
        mmult_simd(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[1] = deltaTime(&start, &end);
        fprintf(filename, " %f,", times[1]);

        clock_gettime(CLOCK_REALTIME, &start);
        mmult_simdo3(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[2] = deltaTime(&start, &end);
        fprintf(filename, " %f,", times[2]);

        clock_gettime(CLOCK_REALTIME, &start);
        mmult_omp(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[3] = deltaTime(&start, &end);
        fprintf(filename, " %f\n", times[3]);

        n += n;
        iterations++;
    }
}
