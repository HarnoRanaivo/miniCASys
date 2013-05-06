/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file prompt.c
 * \brief Prompt (code)
 * \author Harenome RAZANAJATO
 */
#include "prompt.h"

static const struct
{
    Commande commande;
    const char * aide;
    const char * alias[5];
}
LCM[] =
{
    [CM_ADD] =
    {
        CM_ADD,
        "\tadd, addition\n" "\t\tAddition de matrices\n\n",
        { "add", "addition", NULL, },
    },

    [CM_NEW] =
    {
        CM_NEW,
        "\tmatrix, new\n"
        "\t\tCréation d'une nouvelle matrice.\n\n",
        { "matrix", "new", NULL, },
    },

    [CM_SUB] =
    {
        CM_SUB,
        "\tsub, soustraction\n"
        "\t\tSoustraction de matrices.\n\n",
        { "sub", "soustraction", "substraction", NULL, },
    },

    [CM_MULM] =
    {
        CM_MULM,
        "\tmult\n"
        "\t\tMultiplication de matrices.\n\n",
        { "mult", NULL, },
    },

    [CM_MULS] =
    {
        CM_MULS,
        "\tmuls\n"
        "\t\tMultiplication d'une matrice par un scalaire.\n\n",
        { "muls", NULL, },
    },

    [CM_EXP] =
    {
        CM_EXP,
        "\texpo\n"
        "\t\tExponentiation d'une matrice.\n\n",
        { "expo", NULL, },
    },

    [CM_TSP] =
    {
        CM_TSP,
        "\ttranspose\n"
        "\t\tTransposition d'une matrice.\n\n",
        { "transpose", NULL, },
    },

    [CM_DET] =
    {
        CM_DET,
        "\tdeterminant\n"
        "\t\tCalcul du déterminant.\n\n",
        { "determinant", NULL, },
    },

    [CM_INV] =
    {
        CM_INV,
        "\tinvert\n"
        "\t\tInversion d'une matrice.\n\n",
        { "invert", NULL, },
    },

    [CM_SOL] =
    {
        CM_SOL,
        "\tsolve\n"
        "\t\tRésolution d'un système.\n\n",
        { "solve", NULL, },
    },

    [CM_RK] =
    {
        CM_RK,
        "\trank\n"
        "\t\tCalcul du rang d'une matrice.\n\n",
        { "rank", NULL, },
    },

    [CM_SPD] =
    {
        CM_SPD,
        "\tspeedtest\n"
        "\t\tSpeedtest.\n\n",
        { "speedtest", NULL, },
    },

    [CM_AIDE] =
    {
        CM_AIDE,
        "\taide\n"
        "\t\tAide.\n\n",
        { "aide", NULL, },
    },

    [CM_QUIT] =
    {
        CM_QUIT,
        "\tquit\n"
        "\t\tQuitter le programme.\n\n",
        { "quit", "quitter", "q", NULL, },
    },

    [CM_INCONNU] =
    {
        CM_INCONNU,
        "\tAucune aide disponible pour cette commande car elle n'existe pas.\n\n",
        { NULL, },
    },
};

void afficherAideCommande(Commande c)
{
    printf("%s", LCM[c].aide);
}

void afficherPromptAide(void)
{
    printf("Aide :\n\n");
    for (int i = 0; i < CM_INCONNU; i++)
        printf("%s", LCM[i].aide);
}

Commande rechercherCommande(const char * ligne)
{
    char commande[32] = { '\0' };

    if (sscanf(ligne, "%31s", commande) == 1)
    {
        chaineEnMinuscules(commande);

        for (int i = 0; i < CM_INCONNU; i++)
            if (rechercherMot(commande, LCM[i].alias) == VRAI)
                return LCM[i].commande;
    }

    return CM_INCONNU;
}

Bool verifier(const char * chaine)
{
    char buffer[8] = { '\0' };

    printf("Êtes-vous sûr %s?\n? ", chaine);
    fflush(stdout);
    scanf("%7s%*[^\n]%*c", buffer);

    chaineEnMinuscules(buffer);

    return rechercherMot(buffer, (const char * []) { "o", "oui", NULL, });
}

int preparerLigneCommmande(char * chaine, char * decomposition[4])
{
    int parties = 1;
    char * parcours;

    for (int i = 0; i < 4; i++)
        decomposition[i] = NULL;

    /* partie avant le ':' */
    decomposition[0] = chaine;
    if ((parcours = strchr(chaine, ':')) != NULL)
    {
        *parcours = '\0';
        parcours += 1;
        parties++;
        /* Partie après le ':' */
        decomposition[1] = parcours;

        if ((parcours = strchr(parcours, '(')) !=  NULL)
        {
            *parcours = '\0';
            parcours += 1;
            parties++;
            /* Arguments de la commande, s'il y en a */
            decomposition[2] = parcours;

            if ((parcours = strchr(parcours, ')')) != NULL)
            {
                *parcours = '\0';
                parcours += 1;

                char reste[32];
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
        char buffer[32];

        if (decomposition[i] != NULL
            && sscanf(decomposition[i], "%s %s", buffer, buffer) == 2
           )
            return -parties;
    }

    return parties;
}

void afficherDonnee(const Donnee * d)
{
    if (estE(d))
        printf("%f\n", eDonnee(d));
    else
        displayMatrix(matriceDonnee(d));
}

Matrix * traiterCommande(Commande c, char * arguments, Variables * v)
{
    Matrix * m = NULL;
    char buffer1[64] = { '\0' };
    char buffer2[64] = { '\0' };
    E buffer3;
    int buffer4;

    switch(c)
    {
        case CM_NEW :
            if (contientMatriceValide(arguments))
                m = recupererMatrice(arguments, v);
            else
                printf("%s : matrice non valide.\n", arguments);
            break;

        case CM_ADD :
            if (sscanf(arguments, " %63[^,]%*[,]%63s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        printf("%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        printf("%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estMatrice(d2))
                {
                    if (!estMatrice(d1))
                        printf("%s n'est pas une matrice.\n", buffer1);
                    if (!estMatrice(d2))
                        printf("%s, n'est pas une matrice.\n", buffer2);
                }
                else
                {
                    const Matrix * m1 = matriceDonnee(d1);
                    const Matrix * m2 = matriceDonnee(d2);

                    if (nbLignes(m1) == nbLignes(m2) && nbColonnes(m1) == nbColonnes(m2))
                        m = addition(matriceDonnee(d1), matriceDonnee(d2));
                    else
                        printf("Les matrices n'ont pas la même taille.\n");
                }
            }
            break;

        case CM_SUB :
            if (sscanf(arguments, " %63[^,]%*[,]%63s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        printf("%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        printf("%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estMatrice(d2))
                {
                    if (!estMatrice(d1))
                        printf("%s n'est pas une matrice.\n", buffer1);
                    if (!estMatrice(d2))
                        printf("%s, n'est pas une matrice.\n", buffer2);
                }
                else
                {
                    const Matrix * m1 = matriceDonnee(d1);
                    const Matrix * m2 = matriceDonnee(d2);

                    if (nbLignes(m1) == nbLignes(m2) && nbColonnes(m1) == nbColonnes(m2))
                        m = soustraction(matriceDonnee(d1), matriceDonnee(d2));
                    else
                        printf("Les matrices n'ont pas la même taille.\n");
                }
            }
            break;

        case CM_MULM :
            if (sscanf(arguments, " %63[^,]%*[,]%63s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        printf("%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        printf("%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estMatrice(d2))
                {
                    if (!estMatrice(d1))
                        printf("%s n'est pas une matrice.\n", buffer1);
                    if (!estMatrice(d2))
                        printf("%s, n'est pas une matrice.\n", buffer2);
                }
                else
                {
                    const Matrix * m1 = matriceDonnee(d1);
                    const Matrix * m2 = matriceDonnee(d2);

                    if (nbColonnes(m1) == nbLignes(m2))
                        m = multiplication(matriceDonnee(d1), matriceDonnee(d2));
                    else
                        printf("Les matrices n'ont pas la même taille.\n");
                }
            }
            break;

        case CM_MULS :
            if (sscanf(arguments, " %63[^,]%*[,]%f", buffer1, &buffer3) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        printf("%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        printf("%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estE(d2))
                {
                    if (!estMatrice(d1))
                        printf("%s n'est pas une matrice.\n", buffer1);
                    if (!estE(d2))
                        printf("%s, n'est pas un scalaire.\n", buffer2);
                }
                else
                {
                    m = multiplierScalaire(matriceDonnee(d1), eDonnee(d2));
                }
            }
            break;

        case CM_EXP :
            if (sscanf(arguments, " %63[^,]%*[,]%d", buffer1, &buffer4) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);

                if (d1 == NULL)
                        printf("%s n'existe pas.\n", buffer1);
                else if (!estMatrice(d1))
                        printf("%s n'est pas une matrice.\n", buffer1);
                else if (buffer4 < 0)
                    printf("...\n");
                else
                    m = exponentiation(matriceDonnee(d1), buffer4);
            }
            break;

        case CM_TSP :
            if (sscanf(arguments, " %63[^,]", buffer1) == 1)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);

                if (d1 == NULL)
                    printf("%s n'existe pas.\n", buffer1);
                else if (!estMatrice(d1))
                    printf("%s n'est pas une matrice.\n", buffer1);
                else
                    m = transpose(matriceDonnee(d1));
            }
            break;

        case CM_INV :
            break;

        case CM_SOL :
            if (sscanf(arguments, " %63[^,]%*[,]%63s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        printf("%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        printf("%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estMatrice(d2))
                {
                    if (!estMatrice(d1))
                        printf("%s n'est pas une matrice.\n", buffer1);
                    if (!estMatrice(d2))
                        printf("%s, n'est pas une matrice.\n", buffer2);
                }
                else
                {
                    const Matrix * m1 = matriceDonnee(d1);
                    const Matrix * m2 = matriceDonnee(d2);

                    if (nbColonnes(m1) == nbLignes(m2))
                    {
                        Matrix * m0 = copieMatrice(m1);
                        Matrix * b0 = copieMatrice(m2);
                        Matrix * solution = newMatrix(1, nbLignes(m1));

                        gauss(m0, b0, solution);
                        deleteMatrix(m0);
                        deleteMatrix(b0);

                        m = solution;
                    }
                    else
                        printf("Les matrices n'ont pas la même taille.\n");
                }
            }
            break;

        case CM_RK :
            break;

        default :
            break;
    }

    return m;
}

void afficherPrompt(void)
{
    Variables * v = initVariables();

    /* Le reste du programme ne peut pas fonctionner sans v. */
    if (v == NULL)
        exit(EX_OSERR);

    Bool continuer = VRAI;

    do
    {
        int succes;
        char buffer[512] = { '\0' };
        /* buffer est initialisé à '\0', car les *scanf ne rajoutent ce '\0'
         * que pour le format %s. Avec le format %c ou une expression, ce
         * '\0' doit être ajouté ultérieurement, si on souhaite travailler
         * sur des chaînes de caractères valides.
         */

        printf("> ");
        fflush(stdout);

        /* Lecture des entrées de l'utilisateur. */
        succes = scanf("%511[^\n]%*[^\n]", buffer);
        getchar();

        if (succes == 1)
        {
            Commande c = CM_INCONNU;
            Donnee * d = NULL;
            char * parties[4];
            int ok = preparerLigneCommmande(buffer, parties);

            printf("%d\n", ok);
            switch (ok)
            {
                case 1 :
                    supprimerEspaces(parties[0]);
                    d = obtenirDonnee(v, parties[0]);
                    if (d != NULL)
                        afficherDonnee(d);
                    else
                    {
                        c = rechercherCommande(parties[0]);
                        if (c == CM_INCONNU)
                            printf("Commande inconnue ou variable non affectée.\n");
                        else if (c == CM_SPD)
                            printf("SPEEDTEST\n");
                        else if (c != CM_QUIT)
                            printf("Mauvaise utilisation de %s.\n", parties[0]);
                    }
                    break;

                case 2 :
                    supprimerEspaces(parties[0]);
                    c = rechercherCommande(parties[0]);
                    if (c != CM_INCONNU)
                        printf("%s : mot-clé réservé.\n", parties[0]);
                    else
                    {
                        E valeur;
                        if (sscanf(parties[1], "%f\n", &valeur) == 1)
                        {
                            char variable[32];
                            if (sscanf(parties[0], "%31s", variable) == 1)
                                v = ajouterE(v, variable, valeur);
                        }
                        else
                            printf("%s : Incorrect.\n", parties[1]);
                    }

                    break;

                case 3 :
                    supprimerEspaces(parties[0]);
                    c = rechercherCommande(parties[0]);
                    if (c != CM_INCONNU)
                        printf("%s : mot-clé réservé.\n", parties[0]);
                    else
                    {
                        /* supprimerEspaces(parties[1]); */
                        c = rechercherCommande(parties[1]);
                        if (c == CM_SPD || c == CM_QUIT)
                            printf("Incorrect.\n");
                        else if (c == CM_DET)
                        {
                            char buffer[32];
                            if (sscanf(parties[2], " %63[^,]", buffer) == 1)
                            {
                                const Donnee * d1 = obtenirDonnee(v, buffer);

                                if (d1 == NULL)
                                    printf("%s n'existe pas.\n", buffer);
                                else if (!estMatrice(d1))
                                    printf("%s n'est pas une matrice.\n", buffer);
                                else
                                {
                                    Matrix * m0 = copieMatrice(matriceDonnee(d1));
                                    E det = determinant_opt(m0);
                                    deleteMatrix(m0);
                                    v = ajouterE(v, parties[0], det);
                                    printf("\t%f\n", det);
                                }
                            }
                        }
                        else
                        {
                            /* printf("%s\n%s\n", parties[1], parties[2]); */
                            Matrix * m = traiterCommande(c, parties[2], v);
                            v = ajouterMatrice(v, parties[0], m);
                            if (m != NULL) displayMatrix(m);
                        }
                    }
                    break;

                case 4 :

                default :
                    printf("Syntaxe non valide.\n");
            }

            /* v = traiterLigneCommande(buffer, c, v); */
            if (c == CM_QUIT && verifier("de vouloir quitter le programme ") == VRAI)
            {
                continuer = FAUX;
            }
        }
    }
    while (continuer);

    v = libererVariables(v);
}
