/**
 * \file operations.c
 * \brief Opérations sur les matrices (code)
 * \author Harenome RAZANAJATO
 */
#include "operations.h"

Matrix addition(Matrix m1, Matrix m2)
{
    Matrix m = newMatrix(nbColonnes(m1), nbLignes(m1));

    for (int i = 1; i <= nbLignes(m1); i++)
        for (int j = 1; j <= nbColonnes(m1); j++)
            setElt(m, i, j, getElt(m1, i, j) + getElt(m2, i, j));

    return m;
}

Matrix soustraction(Matrix m1, Matrix m2)
{
    Matrix m = newMatrix(nbColonnes(m1), nbLignes(m1));

    for (int i = 1; i <= nbLignes(m1); i++)
        for (int j = 1; j <= nbColonnes(m1); j++)
            setElt(m, i, j, getElt(m1, i, j) - getElt(m2, i, j));

    return m;
}

Matrix multiplication(Matrix m1, Matrix m2)
{
    Matrix m = newMatrix(nbLignes(m1), nbColonnes(m2));

    for (int i = 1; i <= nbLignes(m); i++)
        for (int j = 1; j <= nbColonnes(m); j++)
        {
            setElt(m, i, j, 0.);
            for (int k = 1; k <= nbColonnes(m1); k++)
                setElt(m, i, j, getElt(m, i, j) + getElt(m1, i, k) * getElt(m2, k, j));
        }

    return m;
}

Matrix exponentiation(Matrix m, int n)
{
    Matrix mp = m;
    Matrix ms;

    for (int i = 0; i < n; i++)
    {
        ms = multiplication(mp, m);
        deleteMatrix(mp);
        mp = ms;
    }

    return ms;
}

Matrix transpose(Matrix m)
{
    Matrix mt = newMatrix(nbColonnes(m), nbLignes(m));

    for (int i = 0; i <= nbLignes(mt); i++)
        for (int j = 1; j <= nbColonnes(mt); j++)
            setElt(mt, i, j, getElt(m, j, i));

    return mt;
}

Matrix multiplierScalaire(Matrix m, E k)
{
    Matrix m0 = newMatrix(nbColonnes(m), nbLignes(m));

    for (int i = 0; i <= nbLignes(m0); i++)
        for (int j = 0; i <= nbColonnes(m0); j++)
            setElt(m0, i, j, getElt(m, i, j) * k);
}
