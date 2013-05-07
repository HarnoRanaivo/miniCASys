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

#define VERSION "1.1.3"

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 */
int main(int argc, char ** argv)
{
    Bool erreursFichiers = FAUX;

    if (argc == 1)
        prompt(NULL);
    else if (rechercherMot("--version", (const char * const *)argv) || rechercherMot("-v", (const char * const *)argv))
            printf("Minicas, version %s\n"
                    "Copyright © 2013, MEYER Jérémy, RAZANAJATO Harenome.\n"
                    "<https://github.com/remove/miniCASys>\n",
                    VERSION
                  );
    else
    {
        for (int i = 1; i < argc; i++)
        {
            struct stat buffer;

            if (stat(argv[i], &buffer) == 0)
            {
                FILE * fichier = fopen(argv[i], "r");
                if (fichier != NULL)
                    prompt(fichier);
                else
                {
                    perror("fopen");
                }
            }
            else
            {
                fprintf(stderr, "Le fichier %s n'existe pas.\n", argv[i]);
                erreursFichiers = VRAI;
            }
        }
    }

    if (erreursFichiers)
        exit(EX_NOINPUT);

    return 0;
}
