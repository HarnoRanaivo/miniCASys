/**
 * \file lu.h
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
 * \brief Libération de la mémoire utilisée dans une décompositon en LU.
 * \param lum (Matrix L et Matrix U)
 * \relatesalso LUM
 * \return \b void
 */
void libererLU(LUM* lum);

#endif /* __DECOMPO_H */
