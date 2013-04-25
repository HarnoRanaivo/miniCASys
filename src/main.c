/**
 * \file main.c
 * \brief Main
 * \author Harenome RAZANAJATO
 */
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <time.h>
#include <sys/time.h>

#include "matrix.h"
#include "operations.h"
#include "resol.h"

#define MIN 0.
#define MAX 100.

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 */
int main(int argc, char ** argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage : %s <taille_min> <inc> <nb_matrices> <output>\n", argv[0]);
        exit(EX_USAGE);
    }

    FILE * const output = fopen(argv[4], "w");
    if (output == NULL)
    {
        perror("fopen");
        exit(EX_IOERR);
    }

    srand48(time(NULL));

    int increment = atoi(argv[2]);
    int tailleMaj = atoi(argv[1]) + increment * atoi(argv[3]);

    for (int taille = atoi(argv[1]); taille < tailleMaj; taille += increment)
    {
        struct timeval tv1, tv2;
        unsigned long tempsNaif, tempsOpt;
        Matrix m = newMatrix(taille, taille);

        m = aleatoire(m, MIN, MAX);

        gettimeofday(&tv1, NULL);
        determinant_naif(m);
        gettimeofday(&tv2, NULL);
        tempsNaif = (tv2.tv_usec - tv1.tv_usec) / 10UL;

        gettimeofday(&tv1, NULL);
        determinant_opt(m);
        gettimeofday(&tv2, NULL);
        tempsOpt = (tv2.tv_usec - tv1.tv_usec) / 10UL;

        fprintf(output, "%d %lu %lu\n", taille, tempsNaif, tempsOpt);
        fflush(output);

        deleteMatrix(m);
    }

    fclose(output);

    FILE * const gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL || gnuplot == (FILE *)-1)
    {
        perror("popen");
        exit(EX_OSERR);
    }

    fprintf(gnuplot,
            "set style data histogram\n"
            "set style fill solid border\n"
            "set xlabel \"Taille\"\n"
            "set ylabel \"Temps\"\n"
            "plot '%s' u 2:xtic(1) ti \"Déterminant naïf\", '' u 3 ti \"Déterminant optimal\"\n",
            argv[4]);
    fflush(gnuplot);
    fclose(gnuplot);
    
    return 0;
}
