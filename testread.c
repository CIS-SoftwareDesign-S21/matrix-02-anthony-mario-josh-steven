#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "mat.h"

int grab_size(char *filename);

int main(int argc, char *argv[])
{

    double *aa;
    double *b;
    int nrows, ncols, ntotal;

    aa = read_matrix_from_file(argv[1]);
    b = read_matrix_from_file(argv[2]);
    nrows = grab_size(argv[1]);
    ncols = nrows;
    ntotal = nrows * ncols;
    // printf("The size of aa is: %ld and the size of aa[0] is: %ld\n", sizeof(aa), sizeof(*aa));
    printf("The number of rows is: %d, cols: %d, total: %d\n", nrows, ncols, ntotal);
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