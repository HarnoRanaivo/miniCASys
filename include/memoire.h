/**
 * \file memoire.h
 * \brief Gestion des variables utilisateur
 */
#ifndef __MEMOIRE_H
#define __MEMOIRE_H

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "matrix.h"

typedef enum donnee_t
{
    VAR_FLOTTANT,
    VAR_MATRIX,
} donnee_t;

typedef struct Variables
{
    char * nom;
    union
    {
        E reka;
        Matrix matrice;
    } u_var;
    donnee_t type;
} Donnee;

typedef struct Variables
{
    Donnee * donnees;
    Nat taille;
    Nat position;
} Variables;

Bool estE(const Donnee * d);

Bool estMatrice(const Donnee * d);

E eDonnee(const Donnee * d);

Matrix * matriceDonnee(const Donnee * d);

Variables * initVariables(Nat taille);

Donnee * obtenirDonnee(const Variables * v, const char * nomVariable);

Variables * ajouterE(Variables * v, const char * nomVariable, E e);

Variables * ajouterMatrice(Variables * v, const char * nomVariable, Matrix m);

Variables * supprimerVariable(Variables * v, const char * nomVariable);

#endif /* __MEMOIRE_H */
