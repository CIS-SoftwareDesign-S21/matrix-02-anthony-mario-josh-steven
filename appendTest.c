#include <stdio.h>
#include <stdlib.h>

void Append(FILE *inf, FILE *outf, const char *suffix);

int main()
{
    FILE *tmp = tmpfile();
    char *newline;
    char line[256];

    while ((p = fgets(line, 256, tmp)) != NULL)
    {
        line[strlen(line) - 1] = '\0'; /* Clears away  new line*/
        fprintf(fp, "%s %s\n", line, "test");
    }
}

void Append(FILE *inf, FILE *outf, const char *suffix)
{
    int ch;
    for (;;)
    {
        int ch = fgetc(inf);
        if (ch == '\n' || ch == EOF)
        {
            fputs(suffix, outf);
            if (ch == EOF)
            {
                break;
            }
        }
        fputc(ch, outf);
    }
}