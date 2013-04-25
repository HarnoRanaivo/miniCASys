/**
 * \file matrix.h
 * \brief Matrices (header)
 * \author Harenome RAZANAJATO
 */
#ifndef __MATRIX_H
#define __MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * \typedef E
 */
typedef float E;

/**
 * \struct matrix
 */
typedef struct matrix
{
    E *mat;
    int nrows, ncols;
} *Matrix;

/**
 * \brief Nombre de lignes d'une matrice
 * \relatesalso matrix
 * \param m matrice
 * \return nombre de lignes
 */
static inline int nbLignes(Matrix m)
{
    return m->nrows;
}

/**
 * \brief Nombre de colonnes d'une matrice
 * \relatesalso matrix
 * \param m matrice
 * \return nombre de colonnes
 */
static inline int nbColonnes(Matrix m)
{
    return m->ncols;
}

/**
 * \brief Nouvelle matrice
 * \relatesalso matrix
 * \param nb_rows nombre de lignes
 * \param nb_columns nombre de colonnes
 * \return pointeur vers une nouvelle matrice
 */
Matrix newMatrix(int nb_rows, int nb_columns);

/**
 * \brief Élément à la ligne row et colonne column (row et column commencent à 0.)
 * \relatesalso matrix
 * \param row ligne
 * \param column colonne
 * \return E
 */
E getElt(Matrix m, int row, int column);

/**
 * \brief Changer la valeur de l'élément aux ligne row et colonne column (row et column commencent à 0.)
 * \relatesalso matrix
 * \param m matrice à modifier
 * \param row ligne
 * \param column colonne
 * \param val valeur
 */
void setElt(Matrix m, int row, int column, E val);

/**
 * \brief Effacer une matrice
 * \relatesalso matrix
 * \param m matrice à effacer
 */
void deleteMatrix(Matrix m);

/**
 * \brief Afficher une matrice
 * \relatesalso matrix
 * \param m matrice à afficher
 */
void displayMatrix(Matrix m);

/**
 * \brief Créer une matrice identité
 * \relatesalso matrix
 * \param size taille
 */
Matrix identite(int size);

/*
 * \brief Remplir une matrice aléatoirement
 * \relatesalso matrix
 * \param m matrice à remplir
 * \param min minimum
 * \param max maximum
 * \return pointeur vers la matrice
 */
Matrix aleatoire(Matrix m, float min, float max);

#endif /* __MATRIX_H */
