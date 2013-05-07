/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file decompo.h
 * \brief Décomposition en LU (header)
 * \author Jérémy Meyer
 */
#ifndef __DECOMPO_H
#define __DECOMPO_H

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "matrix.h"
#include "operations.h"
#include "resol.h"

/**
 * \typedef LUM
 * \brief Structure d'une décomposition en LU
 */
typedef Matrix* LUM;

/**
 * \brief Décomposition en LU.
 * \param m (Matrix)
 * \relatesalso LUM
 * \pre nbLignes(m) == nbColonnes(m)
 * \return Décomposition de m en LU.
 */
LUM* decomposition(Matrix *m);

/**
 * \brief Affichage de L dans une décomposition en LU.
 * \param lum (Matrix L et Matrix U)
 * \relatesalso LUM
 * \return \b void
 */
void afficheL(LUM* lum);

/**
 * \brief Affichage de U dans une décomposition en LU.
 * \param lum (Matrix L et Matrix U)
 * \relatesalso LUM
 * \return \b void
 */
void afficheU(LUM* lum);

/**
 * \brief Affichage des matrices L et U d'une décomposition en LU.
 * \param lum (Matrix L et Matrix U)
 * \relatesalso LUM
 * \return \b void
 */
void afficheLU(LUM* lum);

/**
 * \brief Libération de la mémoire utilisée dans une décompositon en LU.
 * \param lum (Matrix L et Matrix U)
 * \relatesalso LUM
 * \return \b void
 */
void libererLU(LUM* lum);

/**
 * \brief Inverse une matrice carrée.
 * \param m (Matrix)
 * \relatesalso Matrix
 * \pre nbLignes(m) == nbColonnes(m)
 * \return inverse de m.
 */
Matrix * inverseM (Matrix * m);

#endif /* __DECOMPO_H */
