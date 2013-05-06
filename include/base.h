/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file base.h
 * \brief Base (header)
 * \author Harenome RAZANAJATO
 * \version 1.5
 */

#ifndef __BASE_H
#define __BASE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * \enum Bool
 * \brief Simulation des booléens.
 */
enum Bool
{
    FAUX,   /**<- Faux. */
    VRAI    /**<- Vrai. */
};

/**
 * \brief Simulation des booléens.
 */
typedef enum Bool Bool;

/**
 * \brief Entiers naturels.
 */
typedef unsigned int Nat;

/**
 * \brief Entiers relatifs.
 */
typedef int Ent;

/**
 * \brief Nombres réels.
 */
typedef float Reel;

/**
 * \brief Nombres rationnels.
 */
typedef float Rat;

/**
 * \brief Caractères.
 */
typedef char Car;

/* Simplement pour différencier un Caractère d'une Chaîne.
 * Pas de pointeur dans le typedef : pouvoir utiliser le mot-clé const correctement.
 */
/**
 * \brief Chaîne de caractères
 */
typedef Car Chaine;

/**
 * \typedef E
 */
typedef float E;

/**
 * \brief Opérations de base pour un type donné.
 * \param T Type.
 */
#define OP(T) \
static inline Bool T ## _eq(T a, T b) { return a == b ? VRAI : FAUX; } \
static inline Bool T ## _neq(T a, T b) { return !T ## _eq(a, b); } \
static inline Bool T ## _inf(T a, T b) { return a < b ? VRAI : FAUX; } \
static inline Bool T ## _supT(T a, T b) { return !T ## _inf(a, b); } \
static inline Bool T ## _infeq(T a, T b) { return a <= b ? VRAI : FAUX; } \
static inline Bool T ## _supeq(T a, T b) { return a >= b ? VRAI : FAUX; } \
static inline T T ## _min(T a, T b) { return a <= b ? a : b; } \
static inline T T ## _max(T a, T b) { return a >= b ? a : b; }

OP(int)
OP(float)
OP(Nat)
OP(Ent)
OP(Reel)
OP(Rat)
OP(E)

#undef OP

/**
 * \brief Allouer de la mémoire.
 * \param P Pointeur.
 */
#define MALLOC(P) malloc(sizeof *(P))

/**
 * \brief Allouer un tableau de taille N.
 * \param P Pointeur.
 * \param N Taille du tableau.
 */
#define MALLOCN(P, N) malloc((N) * sizeof *(P))

/**
 * \brief Allouer un tableau de taille N et l'initialiser à 0.
 * \param P Pointeur.
 * \param N Taille du tableau.
 */
#define CALLOC(P, N) calloc((N), sizeof *(P))

/**
 * \brief Réallouer un tableau.
 * \param P Pointeur.
 * \param N Nouvelle taille du tableau.
 */
#define REALLOC(P, N) realloc((P), (N) * sizeof *(P))

/**
 * \brief Copie d'une chaîne de caractères.
 * \param chaine Chaîne à copier.
 * \pre \a chaine est une chaîne de caractères valide.
 * \return copie de la chaîne.
 */
static inline char * copierChaine(const char * chaine)
{
    char * copie = MALLOCN(copie, strlen(chaine) + 1);

    if (copie != NULL)
        copie = strcpy(copie, chaine);
    else
        perror("malloc");

    return copie;
}

/**
 * \brief Recherche d'un mot dans un tableau de chaînes de caractères valide.
 * \param mot Mot.
 * \param tableau Tableau.
 * \pre \a tableau doit être terminé par NULL.
 * \return #VRAI si le mot se trouve dans le tableau, #FAUX sinon.
 */
static inline Bool rechercherMot(const char * mot, const char * const * tableau)
{
    for (int i = 0; tableau[i] != NULL; i++)
        if (strcmp(mot, tableau[i]) == 0) return VRAI;

    return FAUX;
}

static inline int compterTokens(const char * chaine, char c)
{
    int n = 0;

    for (const char * s = chaine; s != NULL; s = strchr(s, c))
    {
        n++;
        s++;
    }

    return n;
}

/**
 * \brief Compter le nombre de mots dans une chaîne de caractères.
 * \param chaine Chaîne de caractères.
 * \pre \a chaine est une chaîne de caractères valide terminée par \c '\0'.
 * \return Nombre de mots.
 */
static inline int compterMots(const char * chaine)
{
    return compterTokens(chaine, ' ');
}

/**
 * \brief Changer la casse en minuscules d'une chaine de caractères.
 * \param chaine Chaîne de caractères.
 * \pre \a chaine est une chaîne de caractères valide terminée par \c '\0'.
 */
static inline void chaineEnMinuscules(char * chaine)
{
    for (int i = 0; chaine[i] != '\0'; i++)
        chaine[i] = tolower(chaine[i]);
}

static inline void supprimerEspaces(char * chaine)
{
    for (int i = 0; chaine[i] != '\0'; i++)
        if (isspace(chaine[i]))
            chaine[i] = '\0';
}

#endif /* __BASE_H */
