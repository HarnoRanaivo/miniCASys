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
        "\tadd, addition\n"
        "\t\tAddition de matrices\n\n",
        { "add", "addition", NULL, },
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
        succes = scanf("%511[^\n]%*[^\n]%*c", buffer);

        if (succes == 1)
        {
            Commande c = rechercherCommande(buffer);

            v = traiterLigneCommande(buffer, c, v);
            if (c == CM_QUIT && verifier("de vouloir quitter le programme ") == VRAI)
            {
                continuer = FAUX;
            }
        }
    }
    while (continuer);
}
