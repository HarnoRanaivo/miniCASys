/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file resol.c
 * \brief Résolution (code)
 * \author Harenome RAZANAJATO
 */
#include "resol.h"

Matrix * sousMatrice(const Matrix * m, int i, int j)
{
    int n = nbLignes(m);
    Matrix * m0 = newMatrix(n-1, n-1);

    if (m0 != NULL)
    {
        /* Carré supérieur gauche. */
        for (int k = 1; k <= i-1; k++)
            for (int l = 1; l <= j-1; l++)
                setElt(m0, k, l, getElt(m, k, l));

        /* Carré supérieur droit. */
        for (int k = 1; k <= i-1; k++)
            for (int l = j+1; l <= n; l++)
                setElt(m0, k, l-1, getElt(m, k, l));

        /* Carré inférieur gauche. */
        for (int k = i+1; k <= n; k++)
            for (int l = 1; l <= j-1; l++)
                setElt(m0, k-1, l, getElt(m, k, l));

        /* Carré inférieur droit. */
        for (int k = i+1; k <= n; k++)
            for (int l = j+1; l <= n; l++)
                setElt(m0, k-1, l-1, getElt(m, k, l));
    }

    return m0;
}

E determinant_naif(const Matrix * m)
{
    if (nbLignes(m) == 1)
        return getElt(m, 1, 1);
    else
    {
        int n = nbLignes(m);
        E d = 0.;
        int c = 1;

        for (int i = 1; i <= n; i++)
        {
            Matrix * m0 = sousMatrice(m, i, 1);
            if (m0 != NULL)
            {
                d += c * getElt(m, i, 1) * determinant_naif(m0);
                c *= -1;
                m0 = deleteMatrix(m0);
            }
        }

        return d;
    }
}

Matrix * permutLigne(Matrix * m, int i, int j)
{
    for (int k = 1; k <= nbColonnes(m); k++)
    {
        E tmp = getElt(m, i, k);
        setElt(m, i, k, getElt(m, j, k));
        setElt(m, j, k, tmp);
    }

    return m;
}

void permutLigneSysteme(Matrix * m, Matrix * b, int i, int j)
{
    /* Matrice b. */
    E tmp = getElt(b, i, 1);
    setElt(b, i, 1, getElt(b, j, 1));
    setElt(b, j, 1, tmp);

    /* Matrice m. */
    m = permutLigne(m, i, j);

    return;
}

void addMultLigneSysteme(Matrix * m, Matrix * b, int i, int j, E k)
{
    /* Matrice b. */
    setElt(b, i, 1, getElt(b, i, 1) + getElt(b, j, 1) * k);

    /* Matrice m. */
    addMultLigne(m, i, j, k);

    return;
}

int choixPivotPartiel(const Matrix * m, int i)
{
    int p = i;
    E v = valeurAbsolueE(getElt(m, i, i));

    for (int j = i+1; j <= nbLignes(m); j++)
        if (valeurAbsolueE(getElt(m, j, i)) > v)
        {
            p = j;
            v = valeurAbsolueE(getElt(m, j, i));
        }

    return p;
}

void triangulaireSysteme(Matrix * m, Matrix * b)
{
    for (int i = 1; i <= nbLignes(m)-1; i++)
    {
        permutLigneSysteme(m, b, i, choixPivotPartiel(m, i));

        for (int k = i+1; k <= nbLignes(m); k++)
            addMultLigneSysteme(m, b, k, i, -getElt(m, k, i) / getElt(m, i, i));
    }
}

int triangulaireDet(Matrix * m)
{
    int c = 1;
    int n = nbLignes(m);

    for (int i = 1; i <= n-1; i++)
    {
        int pivot = choixPivotPartiel(m, i);

        if (pivot != i)
        {
            permutLigne(m, i, pivot);
            c *= -1;
        }
        for (int j = i+1; j <= n; j++)
            addMultLigne(m, j, i, -getElt(m, j, i) / getElt(m, i, i));
    }

    return c;
}

int rang(const Matrix * m)
{
    int n = 0;
    for (int i = 1; i <= nbLignes(m); i++)
    {
        Bool zeros = VRAI;
        for (int j= 1; j <= nbColonnes(m); j++)
            if (getElt(m, i, j) != 0.)
            {
                zeros = FAUX;
                break;
            }
        if (zeros == VRAI)
            return n;
        else
            n++;
    }

    return n;
}

E determinant_opt(Matrix * m)
{
    int c = triangulaireDet(m);

    for (int i = 1; i <= nbLignes(m); i++)
        c *= getElt(m, i, i);

    return c;
}

void remontee(Matrix * m, Matrix * b, Matrix * x)
{
    int n = nbLignes(m);

    for (int i = n; i >= 1; i--)
    {
        setElt(x, i, 1, getElt(b, i, 1));

        for (int j = i+1; j <= n; j++)
            setElt(x, i, 1, getElt(x, i, 1) - getElt(m, i, j) * getElt(x, j, 1));
        setElt(x, i, 1, getElt(x, i, 1) / getElt(m, i, i));

    }
}

void gauss(Matrix * m, Matrix * b, Matrix * x)
{
    triangulaireSysteme(m, b);
    remontee(m, b, x);
}

void multLigne(Matrix * m, Matrix * b, int i, E k)
{
    /* Matrice b. */
    setElt(b, i, 1, getElt(b, i, 1) * k);

    /* Matrice m. */
    for (int j = 1; j <= nbColonnes(m); j++)
        setElt(m, i, j, getElt(m, i, j) * k);

    return;
}

Matrix * addMultLigne(Matrix * m, int i, int j, E k)
{
    for (int l = 1; l <= nbColonnes(m); l++)
        setElt(m, i, l, getElt(m, i, l) + getElt(m, j, l) * k);

    return m;
}
