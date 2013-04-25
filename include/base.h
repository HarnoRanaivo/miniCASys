/**
 * \file base.h
 * \brief Base (header)
 * \author Harenome RAZANAJATO
 * \version 1.2
 */

#ifndef __BASE_H
#define __BASE_H

#include <stdlib.h>
#include <stdio.h>

/**
 * \enum Bool
 * \brief Simulation des booléens.
 */
/**
 * \typedef Bool
 * \brief Simulation des booléens.
 */
typedef enum
{
    FAUX,   /**<- Faux. */
    VRAI    /**<- Vrai. */
} Bool;

/**
 * \typedef Nat
 * \brief Entiers naturels.
 */
typedef unsigned int Nat;
/**
 * \typedef Ent
 * \brief Entiers relatifs.
 */
typedef int Ent;
/**
 * \typedef Reel
 * \brief Nombres réels.
 */
typedef float Reel;
/**
 * \typedef Rat
 * \brief Nombres rationnels.
 */
typedef float Rat;
/**
 * \typedef Car
 * \brief Caractères.
 */
typedef char Car;
/**
 * \typedef Chaine
 * \brief Chaîne de caractères
 */
typedef Car Chaine;
/* Simplement pour différencier un Caractère d'une Chaîne.
 * Pas de pointeur dans le typedef : pouvoir utiliser le mot-clé const correctement.
 */

/**
 * \def OP(T)
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

#undef OP

/**
 * \def MALLOC(P)
 * \brief Allouer de la mémoire.
 * \param P Pointeur.
 */
#define MALLOC(P) malloc(sizeof *(P))
/**
 * \def MALLOCN(P, N)
 * \brief Allouer un tableau de taille N.
 * \param P Pointeur.
 * \param N Taille du tableau.
 */
#define MALLOCN(P, N) malloc((N) * sizeof *(P))
/**
 * \def CALLOC(P, N)
 * \brief Allouer un tableau de taille N et l'initialiser à 0.
 * \param P Pointeur.
 * \param N Taille du tableau.
 */
#define CALLOC(P, N) calloc((N), sizeof *(P))
/**
 * \def REALLOC(P, N)
 * \brief Réallouer un tableau.
 * \param P Pointeur.
 * \param N Nouvelle taille du tableau.
 */
#define REALLOC(P, N) realloc((P), (N) * sizeof *(P))

#endif /* __BASE_H */
