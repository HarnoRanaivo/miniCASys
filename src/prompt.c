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

static const char * INTROAIDE =
"Aide :\n\n"
"L'affectation d'une valeur à une variable se fait comme suit :\n"
"\t<nomvariable> : <valeur>\n"
"Les valeurs que l'on peut affecter à une variable sont :\n"
"- un flottant.\n"
"\ta : 4\n"
"- une autre variable, si elle existe (son contenu sera copié).\n"
"\tb : a\n"
"- le résultat d'une commande retournant une matrice ou un flottant.\n"
"\tm : matrix([1, 2], [3, 4])\n"
"\td : determinant(m)\n\n"
"Les commandes disponibles sont :\n\n";

static const struct
{
    Commande commande;
    const char * aide;
    const char * alias[5];
}
LCM[] =
{
    [CM_NEW] =
    {
        CM_NEW,
        "\tmatrix, new\n"
        "\t\tmatrix(<déclaration>)\n\n"
        "\t\tCréation d'une nouvelle matrice.\n"
        "\t\tChaque ligne doit contenir le même nombre de colonnes. Le résultat\n"
        "\t\tde cette commande doit être affecté à une variable.\n\n"
        "\t\tExemples :\n"
        "\t\t\tm1 : matrix([1])\n"
        "\t\t\tm2 : matrix([1, 2], [3, 4], [5, 6])\n"
        "\t\t\tm3 : matrix([1, 2, 3], [4, 5, 6])\n\n",
        { "matrix", "new", NULL, },
    },

    [CM_ADD] =
    {
        CM_ADD,
        "\tadd, addition\n"
        "\t\taddition(<matrice>,<matrice>)\n\n"
        "\t\tAddition de deux matrices.\n"
        "\t\tLes deux matrices doivent avoir la même taille. Le résultat de\n"
        "\t\tcette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6])\n"
        "\t\t\tm2 : matrix([7, 8, 9], [10, 11, 12])\n"
        "\t\t\tm3 : addition(m1, m2)\n\n",
        { "add", "addition", NULL, },
    },

    [CM_SUB] =
    {
        CM_SUB,
        "\tsub, substraction, sous, soustraction\n"
        "\t\tsub(<matrice>,<matrice>)\n\n"
        "\t\tSoustraction de deux matrices.\n"
        "\t\tLes deux matrices doivent avoir la même taille. Le résultat de\n"
        "\t\tcette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6])\n"
        "\t\t\tm2 : matrix([7, 8, 9], [10, 11, 12])\n"
        "\t\t\tm3 : sub(m2, m1)\n\n",
        { "sub", "sous", "soustraction", "substraction", NULL, },
    },

    [CM_MULM] =
    {
        CM_MULM,
        "\tmult, multmatrice\n"
        "\t\tmult(<matrice>,<matrice>)\n"
        "\t\tMultiplication de deux matrices.\n"
        "\t\tLe nombre de colonnes de la première matrice doit être\n"
        "\t\tégal au nombre de lignes de la seconde matrice.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6])\n"
        "\t\t\tm2 : matrix([7, 8, 9], [10, 11, 12], [13, 14, 15])\n"
        "\t\t\tm3 : mult(m1, m2)\n\n",
        { "mult", "multmatrice", NULL, },
    },

    [CM_MULS] =
    {
        CM_MULS,
        "\tmuls, mulscalaire\n"
        "\t\tmuls(<matrice>,<flottant>)\n\n"
        "\t\tMultiplication d'une matrice par un scalaire.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6])\n"
        "\t\t\ta : 4\n"
        "\t\t\tm2 : muls(m1, a)\n"
        "\t\t\tm3 : muls(m1, 3)\n\n",
        { "muls", "mulscalaire", NULL, },
    },

    [CM_EXP] =
    {
        CM_EXP,
        "\texpo, exponentiation\n"
        "\t\texpo(<matrice>,<entier>)\n\n"
        "\t\tExponentiation d'une matrice.\n"
        "\t\tL'exposant doit être positif. Le résultat de\n"
        "\t\tcette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6])\n"
        "\t\t\tm2 : expo(m1, 2)\n\n",
        { "expo", NULL, },
    },

    [CM_TSP] =
    {
        CM_TSP,
        "\ttrans, transpose\n"
        "\t\ttranspose(<matrice>)\n\n"
        "\t\tTransposition d'une matrice.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6])\n"
        "\t\t\tm2 : transpose(m1)\n\n",
        { "transpose", "trans", NULL, },
    },

    [CM_DET] =
    {
        CM_DET,
        "\tdet, determinant\n"
        "\t\tdeterminant(<matrice>)\n\n"
        "\t\tCalcul du déterminant d'une matrice carrée.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2], [4, 5])\n"
        "\t\t\td : determinant(m1)\n\n",
        { "determinant", "det", NULL, },
    },

    [CM_INV] =
    {
        CM_INV,
        "\tinvert, inversion\n"
        "\t\tinvert(<matrice>)\n\n"
        "\t\tInversion d'une matrice carrée.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2], [4, 5])\n"
        "\t\t\tm2 : invert(m1)\n\n",
        { "invert", "inversion", NULL, },
    },

    [CM_SOL] =
    {
        CM_SOL,
        "\tsolve\n"
        "\t\tsolve(<matrice>,<matrice>)\n\n"
        "\t\tRésolution d'un système.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6], [7, 8, 9])\n"
        "\t\t\tm2 : matrix([1], [2], [3])\n"
        "\t\t\tm3 : solve(m1, m2)\n\n",
        { "solve", "resolution", NULL, },
    },

    [CM_RK] =
    {
        CM_RK,
        "\trank\n"
        "\t\trank(<matrice>)\n\n"
        "\t\tCalcul du rang d'une matrice.\n"
        "\t\tLe résultat de cette commande doit être affecté à une variable.\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6], [7, 8, 9])\n"
        "\t\t\tr : rank(m1)\n\n",
        { "rank", "rang", NULL, },
    },

    [CM_LU] =
    {
        CM_LU,
        "\tdecomposition\n"
        "\t\tdecomposition(<matrice>)\n\n"
        "\t\tDécomposition LU d'une matrice.\n"
        "\t\tLe résultat de cette commande ne doit pas être affecté à une\n"
        "\t\tvariable. Les résultats seront disponibles dans les variables\n"
        "\t\tspéciales \"L\" et \"U\".\n\n"
        "\t\tExemple :\n"
        "\t\t\tm1 : matrix([1, 2, 3], [4, 5, 6], [7, 8, 9])\n"
        "\t\t\tdecomposition(m1)\n\n",
        { "decomposition", NULL, },

    },

    [CM_SPD] =
    {
        CM_SPD,
        "\tspeedtest <commande> <taille_min> <taille_max> <pas> [secondes]\n"
        "\t\tLancement du speedtest d'une commande sur deux matrices.\n"
        "\t\t- commande : add | sub | mult (commande sur deux matrices).\n"
        "\t\t- taille_min : Taille de départ des matrices.\n"
        "\t\t- taille_max : Taille maximale des matrices.\n"
        "\t\t- pas : Incrément des tailles.\n"
        "\t\t- secondes : (Optionnel) Le programme quitera si le test est trop long.\n\n",
        { "speedtest", NULL, },
    },

    [CM_AIDE] =
    {
        CM_AIDE,
        "\taide [commande]\n"
        "\t\tAfficher l'aide d'une commande, si donnée en argument, ou\n"
        "\t\tafficher l'aide du programme.\n\n",
        { "aide", NULL, },
    },

    [CM_QUIT] =
    {
        CM_QUIT,
        "\tquit, quitter\n"
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
    printf("%s", INTROAIDE);
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

void afficherDonnee(const Donnee * d)
{
    if (d != NULL)
    {
        if (estE(d))
            printf("\t%f\n", eDonnee(d));
        else
            displayMatrix(matriceDonnee(d));
    }
}

Matrix * traiterCommande(Commande c, char * arguments, const Variables * v)
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
                fprintf(stderr, "%s : matrice non valide.\n", arguments);
            break;

        case CM_ADD :

        case CM_SUB :

        case CM_MULM :

        case CM_SOL :
            /* Partie commune aux quatres commandes CM_ADD, CM_SUB, CM_MULM,
             * CM_SOL.
             */
            if (sscanf(arguments, " %63[^,]%*[,]%63s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        fprintf(stderr, "%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        fprintf(stderr, "%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estMatrice(d2))
                {
                    if (!estMatrice(d1))
                        fprintf(stderr, "%s n'est pas une matrice.\n", buffer1);
                    if (!estMatrice(d2))
                        fprintf(stderr, "%s, n'est pas une matrice.\n", buffer2);
                }
                else
                {
                    const Matrix * m1 = matriceDonnee(d1);
                    const Matrix * m2 = matriceDonnee(d2);

                    /* Addition et soustraction. */
                    if (c == CM_ADD || c == CM_SUB)
                    {
                        if (nbLignes(m1) == nbLignes(m2) && nbColonnes(m1) == nbColonnes(m2))
                            m = c == CM_ADD ? addition(m1, m2) : soustraction(m1, m2);
                        else
                            fprintf(stderr, "Les matrices n'ont pas la même taille.\n");
                    }
                    /* Multiplication. */
                    else if (c == CM_MULM)
                    {
                        if (nbColonnes(m1) == nbLignes(m2))
                            m = multiplication(m1, m2);
                        else
                            fprintf(stderr, "Les matrices n'ont pas les bonnes tailles.\n");
                    }
                    /* Résolution. */
                    else
                    {
                        if (nbLignes(m1) == nbLignes(m2) && nbColonnes(m2) == 1)
                        {
                            Matrix * m0 = copieMatrice(m1);
                            Matrix * b0 = copieMatrice(m2);
                            Matrix * solution = newMatrix(nbLignes(m1), 1);

                            gauss(m0, b0, solution);
                            deleteMatrix(m0);
                            deleteMatrix(b0);

                            m = solution;
                        }
                        else
                            fprintf(stderr, "Les matrices n'ont pas les bonnes tailles.\n");
                    }
                }
            }
            break;

        case CM_MULS :
            /* L'utilisateur a donné une variable et un flottant. */
            if (sscanf(arguments, " %63[^,]%*[,]%f", buffer1, &buffer3) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                if (d1 == NULL)
                    fprintf(stderr, "%s n'existe pas.\n", buffer1);
                else if (!estMatrice(d1))
                    fprintf(stderr, "%s n'est pas une matrice.\n", buffer1);
                else
                    m = multiplierScalaire(matriceDonnee(d1), buffer3);
            }
            /* L'utilisateur a donné deux variables. */
            else if (sscanf(arguments, " %63[^,]%*[,]%31s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);
                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        fprintf(stderr, "%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        fprintf(stderr, "%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estE(d2))
                {
                    if (!estMatrice(d1))
                        fprintf(stderr, "%s n'est pas une matrice.\n", buffer1);
                    if (!estE(d2))
                        fprintf(stderr, "%s n'est pas un flottant.\n", buffer2);
                }
                else
                    m = multiplierScalaire(matriceDonnee(d1), eDonnee(d2));
            }
            else
                printf("???\n");
            break;

        case CM_EXP :
            if (sscanf(arguments, " %63[^,]%*[,]%d", buffer1, &buffer4) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);

                if (d1 == NULL)
                    fprintf(stderr, "%s n'existe pas.\n", buffer1);
                else if (!estMatrice(d1))
                    fprintf(stderr, "%s n'est pas une matrice.\n", buffer1);
                else if (buffer4 < 0)
                    fprintf(stderr, "L'exposant doit être positif.\n");
                else if (nbLignes(matriceDonnee(d1)) != nbColonnes(matriceDonnee(d1)))
                    fprintf(stderr, "La matrice n'est pas carrée.\n");
                else
                    m = exponentiation(matriceDonnee(d1), buffer4);
            }
            else if (sscanf(arguments, " %63[^,]%*[,]%31s", buffer1, buffer2) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                const Donnee * d2 = obtenirDonnee(v, buffer2);

                if (d1 == NULL || d2 == NULL)
                {
                    if (d1 == NULL)
                        fprintf(stderr, "%s n'existe pas.\n", buffer1);
                    if (d2 == NULL)
                        fprintf(stderr, "%s n'existe pas.\n", buffer2);
                }
                else if (!estMatrice(d1) || !estE(d2))
                {
                    if (!estMatrice(d1))
                        fprintf(stderr, "%s n'est pas une matrice.\n", buffer1);
                    if (!estE(d2))
                        fprintf(stderr, "%s n'est pas une matrice.\n", buffer2);
                }
                else if (eDonnee(d2) < 0)
                    fprintf(stderr, "L'exposant doit être positif.\n");
                else if (nbLignes(matriceDonnee(d1)) != nbColonnes(matriceDonnee(d1)))
                    fprintf(stderr, "La matrice n'est pas carrée.\n");
                else
                    m = exponentiation(matriceDonnee(d1), eDonnee(d2));
            }
            break;

        case CM_TSP :

        case CM_INV :
            if (sscanf(arguments, " %63[^,]", buffer1) == 1)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);

                if (d1 == NULL)
                    fprintf(stderr, "%s n'existe pas.\n", buffer1);
                else if (!estMatrice(d1))
                    fprintf(stderr, "%s n'est pas une matrice.\n", buffer1);
                else
                    m = c == CM_TSP ? transpose(matriceDonnee(d1)) : inverseM(matriceDonnee(d1));
            }
            break;

        default :
            break;
    }

    return m;
}

static Variables * lancerDecomposition(Variables * v, char * copie, char * morceaux[2])
{
    Commande c = CM_INCONNU;
    Donnee *d;
    supprimerEspaces(copie);
    c = rechercherCommande(copie);

    if (c == CM_LU)
    {
        char variable[32] = { '\0' };
        if (sscanf(morceaux[0], "%31s", variable) == 1
            && (d = obtenirDonnee(v, variable)) != NULL
            && estMatrice(d)
            )
        {
            LUM * lu = decomposition(matriceDonnee(d));
            v = ajouterMatrice(v, "L", copieMatrice(lu[0]));
            v = ajouterMatrice(v, "U", copieMatrice(lu[1]));
            afficheLU(lu);
            libererLU(lu);
        }
    }
    else if (c != CM_INCONNU)
        fprintf(stderr, "%s : Mauvaise utilisation.\n", copie);
    else
        fprintf(stderr, "%s : Commande inconnue.\n", copie);

    return v;
}

static Bool lancerSpeedtest(const char * buffer, const char * commande)
{
    Bool continuer = VRAI;
    char fonction[32] = { '\0' };
    int min, max, pas, sec;

    if (sscanf(buffer, "%*s %31s %d %d %d %d", fonction, &min, &max, &pas, &sec) == 5)
    {
        struct timeval tv1, tv2;
        unsigned long long temps;

        Commande c = rechercherCommande(fonction);
        if ((c == CM_ADD || c == CM_SUB || c == CM_MULM)
            && min > 0 && min <= max && pas > 0
           )
        {
            gettimeofday(&tv1, NULL);
            speedtest(c, min, max, pas);
            gettimeofday(&tv2, NULL);

            temps = (tv2.tv_sec - tv1.tv_sec);
            if (temps > sec)
                continuer = FAUX;
        }
    }
    else if (sscanf(buffer, "%*s %31s %d %d %d", fonction, &min, &max, &pas) == 4)
    {
        Commande c = rechercherCommande(fonction);
        if ((c == CM_ADD || c == CM_SUB || c == CM_MULM)
            && min > 0 && min <= max && pas > 0
           )
            speedtest(c, min, max, pas);
    }
    else
        fprintf(stderr, "%s : Arguments invalides.\n", commande);

    return continuer;
}

static Variables * ligneDeuxParties(Variables * v, char * parties[4], Commande c)
{
    supprimerEspaces(parties[0]);
    c = rechercherCommande(parties[0]);

    if (c != CM_INCONNU || rechercherMot(parties[0], (const char * []) { "L", "U", NULL, }))
        fprintf(stderr, "%s : Mot-clé réservé.\n", parties[0]);
    else
    {
        char variable_1[32];
        E valeur;
        Donnee * d;

        /* Ligne de la forme "variable : flottant" ? */
        if (sscanf(parties[1], "%f\n", &valeur) == 1)
        {
            char variable[32];

            if (sscanf(parties[0], "%31s", variable) == 1)
            {
                v = ajouterE(v, variable, valeur);
                printf("\t%f\n", valeur);
            }
        }
        /* Ligne de la forme "variable_2 : variable_1" ? */
        else if (sscanf(parties[1], "%31s", variable_1) == 1
                 && (d = obtenirDonnee(v, variable_1)) != NULL
                )
        {
            char variable[32];

            if (sscanf(parties[0], "%31s", variable) == 1)
            {
                /* Copie de la variable_1 dans la variable_2 */
                if (estE(d))
                {
                    v = ajouterE(v, variable, eDonnee(d));
                    printf("\t%f\n", eDonnee(d));
                }
                else
                {
                    v = ajouterMatrice(v, variable, copieMatrice(matriceDonnee(d)));
                    displayMatrix(matriceDonnee(d));
                }
            }
        }
        else
            fprintf(stderr, "%s : Variable non affectée.\n", parties[1]);
    }

    return v;
}

static Variables * ligneTroisParties(Variables * v, char * parties[4], Commande c)
{
    supprimerEspaces(parties[0]);
    c = rechercherCommande(parties[0]);

    /* Utilisation d'un mot-clé comme nom de variable ? */
    if (c != CM_INCONNU || rechercherMot(parties[0], (const char * []) { "L", "U", NULL, }))
        fprintf(stderr, "%s : mot-clé réservé.\n", parties[0]);
    else
    {
        c = rechercherCommande(parties[1]);

        /* Commandes non valides sous cette forme. */
        if (c == CM_SPD || c == CM_QUIT || c == CM_AIDE)
            fprintf(stderr, "Incorrect.\n");
        /* Cas particuliers, commandes prenant une seule matrice en argument. */
        else if (c == CM_DET || c == CM_RK)
        {
            char buffer[32];

            if (sscanf(parties[2], " %63[^,]", buffer) == 1)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer);

                if (d1 == NULL)
                    fprintf(stderr, "%s n'existe pas.\n", buffer);
                else if (!estMatrice(d1))
                    fprintf(stderr, "%s n'est pas une matrice.\n", buffer);
                /* Calcul du déterminant. */
                else if (c == CM_DET)
                {
                    if (nbLignes(matriceDonnee(d1)) == nbColonnes(matriceDonnee(d1)))
                    {
                        Matrix * m0 = copieMatrice(matriceDonnee(d1));
                        E det = determinant_opt(m0);
                        m0 = deleteMatrix(m0);

                        v = ajouterE(v, parties[0], det);
                        printf("\t%f\n", det);
                    }
                    else
                        fprintf(stderr, "La matrice n'est pas carrée.\n");
                }
                /* Calcul du rang. */
                else if (c == CM_RK)
                {
                    Matrix * m0 = copieMatrice(matriceDonnee(d1));
                    triangulaireDet(m0);

                    int rk = rang(m0);
                    v = ajouterE(v, parties[0], rk);
                    printf("\t%d\n", rk);

                    deleteMatrix(m0);
                }
            }
        }
        else if (c == CM_INCONNU)
            fprintf(stderr, "%s : Commande inconnue.\n", parties[1]);
        /* Autres commandes. */
        else
        {
            Matrix * m = traiterCommande(c, parties[2], v);
            if (m != NULL)
            {
                v = ajouterMatrice(v, parties[0], m);
                displayMatrix(m);
            }
        }
    }

    return v;
}

void prompt(FILE * fichier)
{
    FILE * entree = fichier == NULL ? stdin : fichier;

    struct stat statBuffer;
    fstat(fileno(entree), &statBuffer);
    Bool terminal = S_ISCHR(statBuffer.st_mode);

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

        if (terminal)
        {
            printf("> ");
            fflush(stdout);
        }

        /* Lecture des entrées. */
        succes = fscanf(entree, " %511[^\n]%*[^\n]", buffer);
        if (terminal)
            getchar();

        if (succes == 1)
        {
            char commande[64] = { '\0' };

            /* Pré-traitement pour détecter certaines commandes particulières. */
            char * copie = copierChaine(buffer);
            char * morceaux[2];
            int sousparties = preparerCommande(copie, morceaux);

            /* decomposition(), seule fonction sur les matrices à s'utiliser sous
             * la forme "fonction(argument)".
             * (Toutes les autres sont de la forme "variable : fonction(arguments)").
             */
            if (sousparties == 1 && strchr(buffer, ':') == NULL)
            {
                /* Fonction statique. */
                v = lancerDecomposition(v, copie, morceaux);
            }
            /* speedtest(), autre fonction dont l'appel est particulier. */
            else if (sscanf(buffer, "%63s", commande) == 1
                    && rechercherCommande(commande) == CM_SPD)
            {
                /* Fonction statique. */
                continuer = lancerSpeedtest(buffer, commande);
            }
            /* Autres lignes de commandes classiques, de la forme
             * "variable : <fonction, variable...>"
             */
            else
            {
                Commande c = CM_INCONNU;
                Donnee * d = NULL;

                /* Découpage de la ligne de commande. */
                char * parties[4];
                int ok = preparerLigneCommmande(buffer, parties);

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
                                fprintf(stderr, "Commande inconnue ou variable non affectée.\n");
                            else if (c == CM_AIDE)
                                afficherPromptAide();
                            else if (c != CM_QUIT)
                                fprintf(stderr, "Mauvaise utilisation de %s.\n", parties[0]);
                        }
                        break;

                    case 2 :
                        /* Fonction statique. */
                        v = ligneDeuxParties(v, parties, c);
                        break;

                    case 3 :
                        /* Fonction statique. */
                        v = ligneTroisParties(v, parties, c);
                        break;

                    case 4 :

                    default :
                        fprintf(stderr, "Syntaxe non valide.\n");
                }

                if ((c == CM_QUIT && terminal
                        && verifier("de vouloir quitter le programme "))
                    || (c == CM_QUIT && !terminal)
                   )
                {
                    continuer = FAUX;
                }
            }

            free(copie);
        }
        else if (succes == EOF)
            continuer = FAUX;
    }
    while (continuer);

    v = libererVariables(v);
}

void speedtest(Commande c, int min, int max, int pas)
{
    static const char * fichier = "/tmp/minicas";
    Bool erreur = FAUX;

    /* Pointeur sur fonction. */
    Matrix * (*fun) (const Matrix *, const Matrix *);

    /* Choix de la comande. */
    switch (c)
    {
        case CM_ADD :
            fun = addition;
            break;
        case CM_SUB :
            fun = soustraction;
            break;
        case CM_MULM :
            fun = multiplication;
            break;

        default :
            break;
    }

    FILE * const output = fopen(fichier, "w");

    if (output == NULL)
    {
        perror("fopen");
        erreur = VRAI;
    }

    if (erreur != VRAI)
    for (int i = min; i <= max; i += pas)
    {
        struct timeval tv1, tv2;
        unsigned long long temps;

        Matrix * m1 = aleatoire(newMatrix(i, i), ALEA_MIN, ALEA_MAX);
        Matrix * m2 = aleatoire(newMatrix(i, i), ALEA_MIN, ALEA_MAX);

        gettimeofday(&tv1, NULL);
        Matrix * m3 = fun(m1, m2);
        gettimeofday(&tv2, NULL);

        temps = ((tv2.tv_sec * 1000000 + tv2.tv_usec) - (tv1.tv_sec * 1000000 + tv1.tv_usec));

        fprintf(output, "%d %llu\n", i, temps);
        fflush(output);

        m1 = deleteMatrix(m1);
        m2 = deleteMatrix(m2);
        m3 = deleteMatrix(m3);
    }

    fclose(output);

    FILE * const gnuplot = popen("gnuplot -persistent", "w");

    if (gnuplot == NULL || gnuplot == (FILE *)-1)
    {
        perror("popen");
        erreur = VRAI;
    }
    else
    {
        fprintf(gnuplot,
                "set style data histogram\n"
                "set style fill solid border\n"
                "set xlabel \"Taille\"\n"
                "set ylabel \"Temps (µsecondes)\"\n"
                "plot '%s' u 2:xtic(1) ti \"\"\n",
                fichier);
        fflush(gnuplot);
        fclose(gnuplot);
    }
}
