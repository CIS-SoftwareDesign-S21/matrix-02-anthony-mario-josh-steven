/** 
 * Program to multiply a matrix times a vector using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "mat.h"
#define min(x, y) ((x) < (y) ? (x) : (y))

int grab_size(char *filename);

int main(int argc, char *argv[])
{
    int nrows, ncols, ntotal;
    double *aa, *b, *c;
    double *buffer;
    double *ans;
    double *times;
    double total_times;
    int run_index;
    int nruns;
    int myid, master, numprocs;
    double starttime, endtime;
    MPI_Status status;
    int i, j, k, numsent, sender;
    int anstype, row;

    srand(time(0));
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1)
    {
        aa = read_matrix_from_file(argv[1]);
        b = read_matrix_from_file(argv[2]);
        nrows = grab_size(argv[1]);
        ncols = nrows;
        ntotal = nrows * ncols;
        // aa = (double*)malloc(sizeof(double) * nrows * ncols);
        // b = (double*)malloc(sizeof(double) * ntotal);
        // c = (double *)malloc(sizeof(double) * ntotal);
        buffer = (double *)malloc(sizeof(double) * ncols);
        ans = (double *)malloc(sizeof(double) * ncols);
        master = 0;
        if (myid == master)
        {
            // Master Code goes here
            // aa = gen_matrix(nrows, ncols);
            // b = gen_matrix(nrows, ncols);
            starttime = MPI_Wtime();
            numsent = 0;
            MPI_Bcast(b, ntotal, MPI_DOUBLE, master, MPI_COMM_WORLD);
            for (i = 0; i < min(numprocs - 1, nrows); i++)
            {
                for (j = 0; j < ncols; j++)
                {
                    buffer[j] = aa[i * ncols + j];
                }
                MPI_Send(buffer, ncols, MPI_DOUBLE, i + 1, i + 1, MPI_COMM_WORLD);
                numsent++;
            }
            for (i = 0; i < nrows; i++)
            {
                MPI_Recv(ans, ncols, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
                         MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                anstype = status.MPI_TAG;
                for (int l = 0; l < ncols; l++)
                {
                    c[(anstype - 1) * ncols + l] = ans[l];
                }
                // c[anstype - 1] = ans;
                if (numsent < nrows)
                {
                    for (j = 0; j < ncols; j++)
                    {
                        buffer[j] = aa[numsent * ncols + j];
                    }
                    MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent + 1,
                             MPI_COMM_WORLD);
                    numsent++;
                }
                else
                {
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                }
            }
            endtime = MPI_Wtime();
            printf("%f\n", (endtime - starttime));
            // for(int t = 0; t < ntotal; t++){
            //     printf("The %dth entry is %lf",t,c[t]);
            // }
        }
        else
        {
            // Slave Code goes here
            MPI_Bcast(b, ntotal, MPI_DOUBLE, master, MPI_COMM_WORLD);
            if (myid <= nrows)
            {
                while (1)
                {
                    MPI_Recv(buffer, ncols, MPI_DOUBLE, master, MPI_ANY_TAG,
                             MPI_COMM_WORLD, &status);
                    if (status.MPI_TAG == 0)
                    {
                        break;
                    }
                    row = status.MPI_TAG;
                    // #pragma omp parallel
                    // #pragma omp shared(ans) for reduction(+:ans)
                    for (j = 0; j < ncols; j++)
                    {
                        ans[j] = 0;
                    }
                    for (k = 0; k < ncols; k++)
                    {
                        for (j = 0; j < ncols; j++)
                        {
                            ans[j] += buffer[k] * b[k * ncols + j];
                        }
                    }
                    MPI_Send(ans, ncols, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
                }
            }
        }
    }
    else
    {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}

int grab_size(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Unable to open file at path '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t buflen = 255;
    char buf[buflen];
    int n, m;

    if (!fgets(buf, buflen, fp))
    {
        fprintf(stderr, "Unable to read file at path '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    else if (sscanf(buf, "%d %d", &n, &m) != 2)
    {
        fprintf(stderr, "Unable to parse first line, expect '%%d %%d'.\n");
        exit(EXIT_FAILURE);
    }
    return n;
}