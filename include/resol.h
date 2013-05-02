/**
 * \file resol.h
 * \brief Résolution (header)
 * \author Harenome RAZANAJATO
 */
#ifndef __RESOL_H
#define __RESOL_H

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "operations.h"

/**
 * \brief Sous-matrice.
 * \param m Matrice.
 * \param i Ligne.
 * \param j Colonne.
 * \pre nbLignes(m) == nbColonnes(m).
 * \return Sous-matrice.
 */
Matrix * sousMatrice(const Matrix * m, int i, int j);

/**
 * \brief Déterminant d'une matrice (calcul récursif).
 * \param m Matrice.
 * \pre nbLignes(m) == nbColonnes(m).
 * \return det(m).
 */
E determinant_naif(const Matrix * m);

/**
 * \brief Permuter les lignes i et j d'une matrice.
 * \param m Matrice.
 * \param i Indice de la première ligne.
 * \param j Indice de la deuxième ligne.
 * \pre nbLignes(m) == nbLignes(b) && nbColonnes(m) == 1.
 */
Matrix * permutLigne(Matrix * m, int i, int j);

/**
 * \brief Permuter les lignes i et j d'un système.
 * \param m Matrice.
 * \param b Matrice colonne.
 * \param i Indice de la première ligne.
 * \param j Indice de la deuxième ligne.
 * \pre nbLignes(m) == nbLignes(b) && nbColonnes(m) == 1.
 */
void permutLigneSysteme(Matrix * m, Matrix * b, int i, int j);

/**
 * \brief Additionner à la ligne i la ligne j multipliée par k.
 * \param m Matrice.
 * \param b Matrice colonne.
 * \param i Indice de la première ligne.
 * \param j Indice de la deuxième ligne.
 * \param k Facteur.
 * \pre nbLignes(m) == nbLignes(b) && nbColonnes(m) == 1.
 */
void addMultLigneSysteme(Matrix * m, Matrix * b, int i, int j, E k);

/**
 * \brief Valeur absolue d'un élément E.
 * \param x Élément.
 * \return valeur absolue de x.
 */
static inline E valeurAbsolueE(E x)
{
    return x < 0. ? -x : x;
}

/**
 * \brief Choix pivot partiel.
 * \param m Matrice.
 * \param i Indice de la colonne.
 * \pre nbLignes(m) == nbLignes(b).
 */
int choixPivotPartiel(const Matrix * m, int i);

/**
 * \brief Met le système sous forme triangulaire.
 * \param m Matrice.
 * \param b Matrice colonne.
 * \pre nbLignes(m) == nbLignes(b) && nbColonnes(m) == 1.
 */
void triangulaireSysteme(Matrix * m, Matrix * b);

/**
 * \brief Mise sous forme triangulaire d'une matrice.
 * \param m Matrice
 * \return permutations.
 */
int triangulaireDet(Matrix * m);

/**
 * \brief Calcul efficace du déterminant d'une matrice.
 * \param m Matrice
 * \return déterminant de m.
 */
E determinant_opt(Matrix * m);

/**
 * \brief Remontée d'un système.
 * \param m Matrice.
 * \param b Matrice colonne.
 * \param x Inconnues.
 * \pre nbLignes(m) == nbLignes(b) == nbLignes(x) && nbColonnes(b) == nbColonnes(x) == 1
 */
void remontee(Matrix * m, Matrix * b, Matrix * x);

/**
 * \brief Pivot de Gauss.
 * \param m Matrice.
 * \param b Matrice colonne.
 * \param x Inconnues.
 * \pre nbLignes(m) == nbLignes(b) == nbLignes(x) && nbColonnes(b) == nbColonnes(x) == 1
 */
void gauss(Matrix * m, Matrix * b, Matrix * x);

/**
 * \brief Multiplier la ligne i d'un système par un facteur k.
 * \param m Matrice.
 * \param b Matrice colonne.
 * \param i Indice de la ligne.
 * \param k Facteur.
 * \pre nbLignes(m) == nbLignes(b) && nbColonnes(m) == 1.
 */
void multLigne(Matrix * m, Matrix * b, int i, E k);

/**
 * \brief Additionner à la ligne i la ligne j multipliée par k.
 * \param m Matrice.
 * \param i Indice de la première ligne.
 * \param j Indice de la deuxième ligne.
 * \param k Facteur.
 */
Matrix * addMultLigne(Matrix * m, int i, int j, E k);

#endif /* __RESOL_H */
