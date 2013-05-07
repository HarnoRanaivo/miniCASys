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

    [CM_LU] =
    {
        CM_LU,
        "\tdecomposition\n"
        "\t\tDécomposition LU d'une matrice.\n\n",
        { "decomposition", NULL, },

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

                    /* Partie spécifique. */
                    if (c == CM_ADD || c == CM_SUB)
                    {
                        if (nbLignes(m1) == nbLignes(m2) && nbColonnes(m1) == nbColonnes(m2))
                            m = c == CM_ADD ? addition(m1, m2) : soustraction(m1, m2);
                        else
                            printf("Les matrices n'ont pas la même taille.\n");
                    }
                    else if (c == CM_MULM)
                    {
                        if (nbColonnes(m1) == nbLignes(m2))
                            m = multiplication(m1, m2);
                        else
                            printf("Les matrices n'ont pas les bonnes tailles.\n");
                    }
                    else
                    {
                        if (nbLignes(m1) == nbLignes(m2))
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
                            printf("Les matrices n'ont pas les bonnes tailles.\n");
                    }
                }
            }
            break;

        case CM_MULS :
            if (sscanf(arguments, " %63[^,]%*[,]%f", buffer1, &buffer3) == 2)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);
                if (d1 == NULL)
                {
                    printf("%s n'existe pas.\n", buffer1);
                }
                else if (!estMatrice(d1))
                {
                    printf("%s n'est pas une matrice.\n", buffer1);
                }
                else
                    m = multiplierScalaire(matriceDonnee(d1), buffer3);
            }
            else
                printf("???\n");
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
                    printf("L'exposant doit être positif.\n");
                else if (nbLignes(matriceDonnee(d1)) != nbColonnes(matriceDonnee(d1)))
                    printf("La matrice n'est pas carrée.\n");
                else
                    m = exponentiation(matriceDonnee(d1), buffer4);
            }
            break;

        case CM_TSP :

        case CM_INV :
            if (sscanf(arguments, " %63[^,]", buffer1) == 1)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer1);

                if (d1 == NULL)
                    printf("%s n'existe pas.\n", buffer1);
                else if (!estMatrice(d1))
                    printf("%s n'est pas une matrice.\n", buffer1);
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
        printf("%s : Mauvaise utilisation.\n", copie);
    else
        printf("%s : Commande inconnue.\n", copie);

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
        printf("%s : Arguments invalides.\n", commande);

    return continuer;
}

static Variables * ligneDeuxParties(Variables * v, char * parties[4], Commande c)
{
    supprimerEspaces(parties[0]);
    c = rechercherCommande(parties[0]);

    if (c != CM_INCONNU || rechercherMot(parties[0], (const char * []) { "L", "U", NULL, }))
        printf("%s : Mot-clé réservé.\n", parties[0]);
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
            printf("%s : Variable non affectée.\n", parties[1]);
    }

    return v;
}

static Variables * ligneTroisParties(Variables * v, char * parties[4], Commande c)
{
    supprimerEspaces(parties[0]);
    c = rechercherCommande(parties[0]);

    /* Utilisation d'un mot-clé comme nom de variable ? */
    if (c != CM_INCONNU || rechercherMot(parties[0], (const char * []) { "L", "U", NULL, }))
        printf("%s : mot-clé réservé.\n", parties[0]);
    else
    {
        c = rechercherCommande(parties[1]);

        /* Commandes non valides sous cette forme. */
        if (c == CM_SPD || c == CM_QUIT || c == CM_AIDE)
            printf("Incorrect.\n");
        /* Cas particuliers, commandes prenant une seule matrice en argument. */
        else if (c == CM_DET || c == CM_RK)
        {
            char buffer[32];

            if (sscanf(parties[2], " %63[^,]", buffer) == 1)
            {
                const Donnee * d1 = obtenirDonnee(v, buffer);

                if (d1 == NULL)
                    printf("%s n'existe pas.\n", buffer);
                else if (!estMatrice(d1))
                    printf("%s n'est pas une matrice.\n", buffer);
                /* Calcul du déterminant. */
                else if (c == CM_DET)
                {
                    Matrix * m0 = copieMatrice(matriceDonnee(d1));
                    E det = determinant_opt(m0);
                    m0 = deleteMatrix(m0);

                    v = ajouterE(v, parties[0], det);
                    printf("\t%f\n", det);
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
            printf("%s : Commande inconnue.\n", parties[1]);
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
                                printf("Commande inconnue ou variable non affectée.\n");
                            else if (c == CM_AIDE)
                                afficherPromptAide();
                            else if (c != CM_QUIT)
                                printf("Mauvaise utilisation de %s.\n", parties[0]);
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
                        printf("Syntaxe non valide.\n");
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

    Matrix * (*fun) (const Matrix *, const Matrix *);

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
