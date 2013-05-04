/**
 * \file operations.c
 * \brief Opérations sur les matrices (code)
 * \author Harenome RAZANAJATO
 */
#include "operations.h"

Matrix * addition(const Matrix * m1, const Matrix * m2)
{
    Matrix * m = newMatrix(nbColonnes(m1), nbLignes(m1));

    if (m != NULL)
        for (int i = 1; i <= nbLignes(m1); i++)
            for (int j = 1; j <= nbColonnes(m1); j++)
                setElt(m, i, j, getElt(m1, i, j) + getElt(m2, i, j));

    return m;
}

Matrix * soustraction(const Matrix * m1, const Matrix * m2)
{
    Matrix * m = newMatrix(nbColonnes(m1), nbLignes(m1));

    if (m != NULL)
        for (int i = 1; i <= nbLignes(m1); i++)
            for (int j = 1; j <= nbColonnes(m1); j++)
                setElt(m, i, j, getElt(m1, i, j) - getElt(m2, i, j));

    return m;
}

Matrix * multiplication(const Matrix * m1, const Matrix * m2)
{
    Matrix * m = newMatrix(nbLignes(m1), nbColonnes(m2));

    if (m != NULL)
        for (int i = 1; i <= nbLignes(m); i++)
            for (int j = 1; j <= nbColonnes(m); j++)
            {
                setElt(m, i, j, 0.);
                for (int k = 1; k <= nbColonnes(m1); k++)
                    setElt(m, i, j, getElt(m, i, j) + getElt(m1, i, k) * getElt(m2, k, j));
            }

    return m;
}

Matrix * exponentiation(const Matrix * m, int n)
{
    Matrix * mp = (Matrix *)m;
    Matrix * ms;

    for (int i = 0; i < n; i++)
    {
        ms = multiplication(mp, m);
        mp = deleteMatrix(mp);

        if (ms != NULL)
            mp = ms;
        else
            return NULL;
    }

    return ms;
}

Matrix * transpose(const Matrix * m)
{
    Matrix * mt = newMatrix(nbColonnes(m), nbLignes(m));

    if (mt != NULL)
        for (int i = 0; i <= nbLignes(mt); i++)
            for (int j = 1; j <= nbColonnes(mt); j++)
                setElt(mt, i, j, getElt(m, j, i));

    return mt;
}

Matrix * multiplierScalaire(const Matrix * m, E k)
{
    Matrix * m0 = newMatrix(nbColonnes(m), nbLignes(m));

    if (m0 != NULL)
        for (int i = 0; i <= nbLignes(m0); i++)
            for (int j = 0; i <= nbColonnes(m0); j++)
                setElt(m0, i, j, getElt(m, i, j) * k);
                
    return m0;
}
