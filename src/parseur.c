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
    if (strchr(chaine, '[') != NULL)
    {
        const char * parcours = chaine;

        while ((parcours = strchr(parcours, ']')) != NULL)
        {
            const char * c = parcours + 1;

            if (*c == ',' && strchr(c, '[' ) == NULL && strchr(c, ')') == NULL)
            {
                printf("Expected '[' or ')'\n");
                return FAUX;
            }
            else if (*c == ')' && strchr(c, '['))
            {
                printf("Error.\n");
                return FAUX;

            }
            else if (*c == '[')
            {
                printf("\"][\" : Expected ',' before '['\n");
                return FAUX;
            }
        }

        return VRAI;
    }

    return FAUX;
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
    /* return compterTokens(chaine, '['); */
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
    /* printf("%s\n", lignes[0]); */
    /* printf("%d, %d\n", nLignes, nColonnes); */

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
            {
                /* printf("%f\n", element); */
                setElt(m, i+1, j+1, element);
            }
            else
            {
                char variable[64] = { '\0' };
                Donnee * d;

                if (sscanf(parcours, " %63[^],]", variable) == 1
                    && (d = obtenirDonnee(v, variable)) != NULL
                    && (estE(d))
                   )
                {
                    /* printf("%f\n", eDonnee(d)); */
                    setElt(m, i+1, j+1, eDonnee(d));
                }
                else
                {
                    printf("%s ?!\n", variable);
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
