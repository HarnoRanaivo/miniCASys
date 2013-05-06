/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file parseur.c
 * \brief Parseur (code)
 * \author Harenome RAZANAJATO
 */
#include "parseur.h"

Bool contientMatriceValide(const char * chaine)
{
    Bool ferme = VRAI;

    for (const char * c = chaine; *c != '\0'; c++)
    {
        if (*c == '[')
        {
            if (ferme == VRAI)
                ferme = FAUX;
            else
                return FAUX;
        }
        else if (*c == ']')
        {
            if (ferme == FAUX)
                ferme = VRAI;
            else
                return FAUX;
        }
    }

    return ferme;
}

int compterLignes(const char * chaine)
{
    int n = 0;

    for (const char * s = strchr(chaine, '['); s != NULL; s = strchr(s, '['))
    {
        n++;
        s++;
    }

    return n;
}

int compterColonnes(const char * chaine)
{
    return compterTokens(chaine, ',');
}

char ** recupererLignesMatrice(char * chaine)
{
    int n = compterLignes(chaine);
    printf("%d\n", n);

    char ** lignes = MALLOCN(lignes, n);
    char * parcours = strchr(chaine, '[');

    for (int i = 0; i < n; i++)
    {
        lignes[i] = parcours;
        parcours = strchr(parcours + 1, '[');
        *(strchr(lignes[i], ']') + 1) = '\0';
    }

    return lignes;
}

Matrix * recupererMatrice(char * chaine, const Variables * v)
{
    int nLignes = compterLignes(chaine);
    char ** lignes = recupererLignesMatrice(chaine);
    int nColonnes = compterColonnes(lignes[0]);

    for (int i = 1; i < nLignes; i++)
        if (nColonnes != compterColonnes(lignes[i]))
        {
            printf("\t%s : Nombre de colonnes incorrect.\n", lignes[i]);
            free(lignes);
            return NULL;
        }

    Matrix * m = newMatrix(nLignes, nColonnes);

    for (int i = 0; i < nLignes; i++)
    {
        char * parcours = lignes[i] + 1;

        for (int j = 0; j < nColonnes; j++)
        {
            E element;

            if (sscanf(parcours, "%f", &element) == 1)
                setElt(m, i+1, j+1, element);
            else
            {
                char variable[64] = { '\0' };
                Donnee * d;

                if (sscanf(parcours, " %63[^],]", variable) == 1
                    && (d = obtenirDonnee(v, variable)) != NULL
                    && (estE(d))
                   )
                {
                    setElt(m, i+1, j+1, eDonnee(d));
                }
                else
                {
                    printf("%s : argument incorrect.\n", variable);
                    free(lignes);
                    m = deleteMatrix(m);
                    return NULL;
                }
            }

            parcours = strchr(parcours, ',') + 1;
        }
    }

    free(lignes);

    return m;
}

int preparerLigneCommmande(char * chaine, char * decomposition[4])
{
    int parties = 1;
    char * parcours;

    for (int i = 0; i < 4; i++)
        decomposition[i] = NULL;

    /* partie avant le ':' */
    decomposition[0] = chaine;

    /* Partie après le ':' */
    if ((parcours = strchr(chaine, ':')) != NULL)
    {
        *parcours = '\0';
        parcours += 1;
        parties++;
        decomposition[1] = parcours;

        /* Arguments de la commande, s'il y en a */
        if ((parcours = strchr(parcours, '(')) !=  NULL)
        {
            *parcours = '\0';
            parcours += 1;
            parties++;
            decomposition[2] = parcours;

            /* Éléments superflus. */
            if ((parcours = strchr(parcours, ')')) != NULL)
            {
                *parcours = '\0';
                parcours += 1;
                char reste[32];

                /* %s ignore les espaces...si la fin ne contient que des
                 * espaces, sscanf ratera...
                 */
                if (sscanf(parcours, "%31s", reste) == 1)
                {
                    parties++;
                    decomposition[3] = parcours;
                }
            }
            else
                return -parties;
        }
        else
            decomposition[2] = NULL;
    }
    else
        decomposition[1] = NULL;

    /* Vérification qu'il n'y a bien qu'un seul mot dans
     * les 2 premières parties.
     */
    for (int i = 0; i < 2; i ++)
    {
        char buffer[64];

        if (decomposition[i] != NULL
            && sscanf(decomposition[i], "%s %s", buffer, buffer) == 2
           )
            return -parties;
    }

    return parties;
}
