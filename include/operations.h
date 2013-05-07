/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
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
 * \relatesalso Matrix
 * \param m1 matrice 1
 * \param m2 matrice 2
 * \pre nbColonnes(m1) == nbColonnes(m2) && nbLignes(m1) == nbLignes(m2)
 * \return pointeur vers la somme
 */
Matrix * addition(const Matrix * m1, const Matrix * m2);

/**
 * \brief Multiplication de matrices
 * \relatesalso Matrix
 * \param m1 matrice 1
 * \param m2 matrice 2
 * \pre nbColonnes(m1) == nbLignes(m2)
 * \return pointeur vers le produit
 */
Matrix * multiplication(const Matrix * m1, const Matrix * m2);

/**
 * \brief Soustraction de matrices
 * \relatesalso Matrix
 * \param m1 matrice 1
 * \param m2 matrice 2
 * \pre nbColonnes(m1) == nbLignes(m2)
 * \return pointeur vers la différence
 */
Matrix * soustraction(const Matrix * m1, const Matrix * m2);

/**
 * \brief Exponentiation d'une matrice
 * \relatesalso Matrix
 * \param m matrice
 * \param n exposant
 * \return m^n
 */
Matrix * exponentiation(const Matrix * m, int n);

/**
 * \brief Transposition d'une matrice
 * \relatesalso Matrix
 * \param m
 * \return pointeur vers la transposée
 */
Matrix * transpose(const Matrix * m);

/**
 * \brief Multiplication d'une matrice par un scalaire
 * \relatesalso Matrix
 * \param m1 matrice 1
 * \param k scalaire
 * \return pointeur vers le produit
 */
Matrix * multiplierScalaire(const Matrix * m, E k);

#endif /* __OPERATIONS_H */
