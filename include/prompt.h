/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file prompt.h
 * \brief Prompt (header)
 * \author Harenome RAZANAJATO
 */
#ifndef __PROMPT_H
#define __PROMPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sysexits.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base.h"
#include "matrix.h"
#include "memoire.h"
#include "parseur.h"
#include "operations.h"
#include "resol.h"
#include "decompo.h"

#define ALEA_MIN 1.
#define ALEA_MAX 10.

/**
 * \enum Commande
 * \brief Alias pour les commandes du prompt.
 */
typedef enum Commande
{
    CM_NEW,         /**<- Nouvelle matrice. */
    CM_ADD,         /**<- Addition de matrices. */
    CM_SUB,         /**<- Soustraction de matrices. */
    CM_MULM,        /**<- Multiplication de matrices. */
    CM_MULS,        /**<- Multiplication d'une matrice par un scalaire. */
    CM_EXP,         /**<- Exponentiation d'une matrice. */
    CM_TSP,         /**<- Transposition d'une matrice. */
    CM_DET,         /**<- Calcul du déterminant. */
    CM_INV,         /**<- Invcersion d'une matrice. */
    CM_SOL,         /**<- Résolution d'un système. */
    CM_RK,          /**<- Calcul du rang d'une matrice. */
    CM_LU,          /**<- Décomposition LU. */
    CM_SPD,         /**<- Speedtest. */
    CM_QUIT,        /**<- Quitter. */
    CM_AIDE,        /**<- Afficher l'aide. */
    CM_INCONNU,     /**<- Commande inconnue. */
} Commande;
/* CM_INCONNU *DOIT* se trouver en dernier. */

/**
 * \brief Afficher l'aide correspondant à une commande.
 * \relatesalso Commande
 * \param pc Commande.
 */
void afficherAideCommande(Commande c);

/**
 * \brief Afficher l'aide du programme.
 */
void afficherPromptAide(void);

/**
 * \brief Rechercher la commande correspondante.
 * \relatesalso Commande
 * \param ligne Ligne de commande.
 * \return commande correspondante.
 */
Commande rechercherCommande(const char * ligne);

Bool verifier(const char * chaine);

void afficherDonnee(const Donnee * d);

Matrix * traiterCommande(Commande c, char * arguments, const Variables * v);

/**
 * \brief Vérifier l'intention de l'utilisateur.
 * \param chaine Ce que l'utilisateur est sur le point de faire.
 */
Bool verifier(const char * chaine);

/**
 * \brief Afficher un prompt et gérer les entrées de l'utilisateur.
 */
void prompt(FILE * fichier);

void speedtest(Commande c, int min, int max, int pas);

#endif /* __PROMPT_H */
