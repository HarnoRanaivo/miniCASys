/**
 * \file operations.h
 * \brief Operations sur les matrices (header)
 * \author Harenome RAZANAJATO
 */
#ifndef __OPERATIONS_H
#define __OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/**
 * \brief Addition de matrices
 * \relatesalso matrix
 * \param m1 matrice 1
 * \param m2 matrice 2
 * \pre nbColonnes(m1) == nbColonnes(m2) && nbLignes(m1) == nbLignes(m2)
 * \return pointeur vers la somme
 */
Matrix addition(Matrix m1, Matrix m2);

/**
 * \brief Multiplication de matrices
 * \relatesalso matrix
 * \param m1 matrice 1
 * \param m2 matrice 2
 * \pre nbColonnes(m1) == nbLignes(m2)
 * \return pointeur vers le produit
 */
Matrix multiplication(Matrix m1, Matrix m2);

/**
 * \brief Transposition d'une matrice
 * \relatesalso matrix
 * \param m
 * \return pointeur vers la transposée
 */
Matrix transpose(Matrix m);

#endif /* __OPERATIONS_H */
