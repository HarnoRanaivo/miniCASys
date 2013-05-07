/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file main.c
 * \brief Main
 * \author Harenome RAZANAJATO
 */
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <time.h>
#include <sysexits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base.h"
#include "matrix.h"
#include "operations.h"
#include "decompo.h"
#include "resol.h"
#include "prompt.h"

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 */
int main(int argc, char ** argv)
{
    if (argc == 1)
        prompt(NULL);
    else if (argc == 2)
    {
        struct stat buffer;

        if (stat(argv[1], &buffer) == 0)
        {
            FILE * fichier = fopen(argv[1], "r");
            if (fichier != NULL)
                prompt(fichier);
            else
            {
                perror("fopen");
                exit(EX_OSERR);
            }
        }
        else
        {
            fprintf(stderr, "Le fichier %s n'existe pas.\n", argv[1]);
            exit(EX_NOINPUT);
        }

    }
    else
    {
        fprintf(stderr, "Usage : %s [fichier]\n", argv[0]);
        exit(EX_USAGE);
    }

    return 0;
}
