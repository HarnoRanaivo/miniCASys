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
 * \brief Soustraction de matrices
 * \relatesalso matrix
 * \param m1 matrice 1
 * \param m2 matrice 2
 * \pre nbColonnes(m1) == nbLignes(m2)
 * \return pointeur vers la différence
 */
Matrix soustraction(Matrix m1, Matrix m2);

/**
 * \brief Exponentiation d'une matrice
 * \relatesalso matrix
 * \param m matrice
 * \param n exposant
 * \return m^n
 */
Matrix exponentiation(Matrix m, int n);

/**
 * \brief Transposition d'une matrice
 * \relatesalso matrix
 * \param m
 * \return pointeur vers la transposée
 */
Matrix transpose(Matrix m);

/**
 * \brief Multiplication d'une matrice par un scalaire
 * \relatesalso matrix
 * \param m1 matrice 1
 * \param k scalaire
 * \return pointeur vers le produit
 */
Matrix multiplierScalaire(Matrix m, E k);

#endif /* __OPERATIONS_H */
