/**
 * \file memoire.h
 * \brief Gestion des variables utilisateur (header)
 */
#ifndef __MEMOIRE_H
#define __MEMOIRE_H

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "matrix.h"

#define VAR_TAILLE 50

typedef enum donnee_t
{
    VAR_FLOTTANT,
    VAR_MATRICE,
} donnee_t;

typedef struct Donnee
{
    const char * nom;
    union
    {
        E flottant;
        Matrix * matrice;
    } u_var;
    donnee_t type;
} Donnee;

typedef struct Variables
{
    Donnee ** donnees;
    Nat taille;
    Nat position;
} Variables;

Donnee * nouveauE(const char * nom, E e);

Donnee * nouvelleMatrice(const char * nom, const Matrix * m);

Bool estE(const Donnee * d);

Bool estMatrice(const Donnee * d);

E eDonnee(const Donnee * d);

Donnee * libererDonnee(Donnee * d);

Matrix * matriceDonnee(const Donnee * d);

Variables * initVariables(void);

Variables * agrandirVariables(Variables * v);

Bool existeVariable(const Variables * v, const char * nomVariable);

Donnee * obtenirDonnee(const Variables * v, const char * nomVariable);

Variables * ajouterE(Variables * v, const char * nomVariable, E e);

Variables * ajouterMatrice(Variables * v, const char * nomVariable, const Matrix * m);

Variables * supprimerVariable(Variables * v, const char * nomVariable);

Variables * libererVariables(Variables * v);

#endif /* __MEMOIRE_H */
