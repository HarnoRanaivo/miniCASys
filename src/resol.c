/**
 * \file resol.c
 * \brief Résolution (code)
 * \author Harenome RAZANAJATO
 */
#include "resol.h"

Matrix sousMatrice(Matrix m, int i, int j)
{
    int n = nbLignes(m);
    Matrix m0 = newMatrix(n-1, n-1);

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

    return m0;
}

E determinant_naif(Matrix m)
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
            Matrix m0 = sousMatrice(m, i, 1);
            d += c * getElt(m, i, 1) * determinant_naif(m0);
            c *= -1;
            deleteMatrix(m0);
        }

        return d;
    }
}

void permutLigne(Matrix m, int i, int j)
{
    for (int k = 1; k <= nbColonnes(m); k++)
    {
        E tmp = getElt(m, i, k);
        setElt(m, i, k, getElt(m, j, k));
        setElt(m, j, k, tmp);
    }

}

void permutLigneSysteme(Matrix m, Matrix b, int i, int j)
{
    /* Matrice b. */
    E tmp = getElt(b, i, 0);
    setElt(b, i, 0, getElt(b, j, 0));
    setElt(b, j, 0, tmp);

    /* Matrice m. */
    permutLigne(m, i, j);

    return;
}

void addMultLigneSysteme(Matrix m, Matrix b, int i, int j, E k)
{
    /* Matrice b. */
    setElt(b, i, 0, getElt(b, i, 0) + getElt(b, j, 0) * k);

    /* Matrice m. */
    addMultLigne(m, i, j, k);

    return;
}

int choixPivotPartiel(Matrix m, int i)
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

void triangulaireSysteme(Matrix m, Matrix b)
{
    for (int i = 1; i <= nbLignes(m)-1; i++)
    {
        permutLigneSysteme(m, b, i, choixPivotPartiel(m, i));

        for (int k = i+1; k < nbLignes(m); k++)
            addMultLigneSysteme(m, b, k, i, -getElt(m, k, i) / getElt(m, i, i));
    }
}

int triangulaireDet(Matrix m)
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

E determinant_opt(Matrix m)
{
    int c = triangulaireDet(m);

    for (int i = 1; i <= nbLignes(m); i++)
        c *= getElt(m, i, i);

    return c;
}

void remontee(Matrix m, Matrix b, Matrix x)
{
    int n = nbLignes(m);

    for (int i = n; i >= 1; i--)
    {
        setElt(x, i, 1, getElt(b, i, 1));

        for (int j = i+1; j <= n; i++)
            setElt(x, i, 1, getElt(x, i, 1) - getElt(m, i, j) * getElt(x, j, 1));
        setElt(x, i, 1, getElt(x, i, 1) / getElt(m, i, i));

    }
}

void gauss(Matrix m, Matrix b, Matrix x)
{
    triangulaireSysteme(m, b);
    remontee(m, b, x);
}

void multLigne(Matrix m, Matrix b, int i, E k)
{
    /* Matrice b. */
    setElt(b, i, 1, getElt(b, i, 0) * k);

    /* Matrice m. */
    for (int j = 1; j <= nbColonnes(m); j++)
        setElt(m, i, j, getElt(m, i, j) * k);

    return;
}

void addMultLigne(Matrix m, int i, int j, E k)
{
    for (int l = 1; l <= nbColonnes(m); l++)
        setElt(m, i, l, getElt(m, i, l) + getElt(m, j, l) * k);
}
