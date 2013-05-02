/**
 * \file matrix.c
 * \brief Matrices (code)
 * \author Harenome RAZANAJATO
 */
#include "matrix.h"

Matrix * newMatrix(int nb_rows, int nb_columns)
{
    Matrix * m = malloc(sizeof *m);

    if (m != NULL)
    {
        m->nrows = nb_rows;
        m->ncols = nb_columns;
        m->mat = malloc((nb_rows * nb_columns)*(sizeof *m->mat));

        if (m->mat == NULL)
        {
            free(m);
            m = NULL;
        }
        else
            perror("malloc");
    }
    else
        perror("malloc");

    return m;
}

E getElt(const Matrix * m, int row, int column)
{
    return *(m->mat + ((row - 1) * nbColonnes(m)) + (column - 1));
}

void setElt(Matrix * m, int row, int column, E val)
{
    *(m->mat + ((row - 1) * nbColonnes(m)) + (column - 1)) = val;
}

Matrix * deleteMatrix(Matrix * m)
{
    if (m != NULL)
    {
        if (m->mat != NULL)
            free(m->mat);
        free(m);
    }

    return NULL;
}

void displayMatrix(const Matrix * m)
{
    for (int i = 1; i <= nbLignes(m);i++)
    {
        for (int j = 1; j <= nbColonnes(m); j++)
            printf("\t%f", getElt(m, i, j));
        printf("\n");
    }

}

Matrix * identite(int size)
{
    Matrix * m = newMatrix(size, size);

    if (m != NULL)
    {
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
                if (i == j) setElt(m, i, j, 1.);
                else setElt(m, i, j, 0.);
        }
    }

    return m;
}

Matrix * aleatoire(Matrix * m, float min, float max)
{
    /* Au cas-où on oublierait de le faire en début de programme. */
    srand48(time(NULL));

    for (int i = 1; i <= nbLignes(m); i++)
        for (int j = 1; j <= nbColonnes(m); j++)
            setElt(m, i, j, min + (drand48() * (max - min)));

    return m;
}
