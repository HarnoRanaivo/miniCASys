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

enum var_t
{
    VAR_FLOTTANT,
    VAR_MATRIX,
};

struct var
{
    char * nom;
    union
    {
        E reka;
        Matrix m;
    } u_var;
    enum var_t type;
};

typedef struct
{
    struct var * vartab;
    Nat taille;
    Nat position;
} Variables;

Variables * initVariables(Nat taille);

#endif /* __MEMOIRE_H */
