/**
 * \file memoire.c
 * \brief Gestion des variables utilisateur (code)
 */
#include "memoire.h"

Donnee * nouveauE(const char * nom, E e)
{
    Donnee * d = MALLOC(d);

    if (d != NULL)
    {
        d->nom = copierChaine(nom);
        d->u_var.flottant = e;
        d->type = VAR_FLOTTANT;
    }
    else
        perror("malloc");

    return d;
}

Donnee * nouvelleMatrice(const char * nom, const Matrix * m)
{
    Donnee * d = MALLOC(d);

    if (d != NULL)
    {
        d->nom = copierChaine(nom);
        d->u_var.matrice = (Matrix *) m;
        d->type = VAR_MATRICE;
    }
    else
        perror("malloc");

    return d;
}

Bool estE(const Donnee * d)
{
    return d->type == VAR_FLOTTANT;
}

Bool estMatrice(const Donnee * d)
{
    return d->type == VAR_MATRICE;
}

char * nomDonnee(const Donnee * d)
{
    return (char *)d->nom;
}

E eDonnee(const Donnee * d)
{
    return d->u_var.flottant;
}

Donnee * libererDonnee(Donnee * d)
{
    if (estMatrice(d))
        deleteMatrix(d->u_var.matrice);
    free(d);

    return NULL;
}

Matrix * matriceDonnee(const Donnee * d)
{
    return d->u_var.matrice;
}

Variables * initVariables(void)
{
    Variables * v = MALLOC(v);

    if (v != NULL)
    {
        v->donnees = MALLOCN(v->donnees, VAR_TAILLE);

        if (v->donnees != NULL)
        {
            v->taille = VAR_TAILLE;
            v->position = 0;
        }
        else
        {
            perror("malloc");
            free(v);
            v = NULL;
        }
    }
    else
        perror("malloc");

    return v;
}

Variables * agrandirVariables(Variables * v)
{
    Donnee ** d0 = REALLOC(v->donnees, v->taille + VAR_TAILLE);

    if (d0 != NULL)
    {
        v->donnees = d0;
        v->taille += VAR_TAILLE;
    }
    else
        perror("realloc");

    return v;
}

Bool existeVariable(const Variables * v, const char * nomVariable)
{
    for (int i = 0; i < v->position; i++)
        if (strcmp(nomDonnee(v->donnees[i]), nomVariable) == 0)
            return VRAI;

    return FAUX;
}

Donnee * obtenirDonnee(const Variables * v, const char * nomVariable)
{
    for (int i = 0; i < v->position; i++)
        if (strcmp(nomDonnee(v->donnees[i]), nomVariable) == 0)
            return v->donnees[i];

    return NULL;
}

Variables * ajouterE(Variables * v, const char * nomVariable, E e)
{
    Donnee * d = obtenirDonnee(v, nomVariable);

    if (d != NULL)
    {
        if (!estE(d))
        {
            d->u_var.matrice = deleteMatrix(d->u_var.matrice);
            d->type = VAR_FLOTTANT;
        }
        d->u_var.flottant = e;
    }
    else
    {
        if (v->taille == v->position)
            v = agrandirVariables(v);
        v->donnees[v->position] = nouveauE(nomVariable, e);
        v->position++;
    }

    return v;
}

Variables * ajouterMatrice(Variables * v, const char * nomVariable, const Matrix * m)
{
    Donnee * d = obtenirDonnee(v, nomVariable);

    if (d != NULL)
    {
        if (!estMatrice(d))
        {
            d->type = VAR_MATRICE;
        }
        d->u_var.matrice = (Matrix *) m;
    }
    else
    {
        if (v->taille == v->position)
            v = agrandirVariables(v);
        v->donnees[v->position] = nouvelleMatrice(nomVariable, m);
        v->position++;
    }

    return v;
}

Variables * supprimerVariable(Variables * v, const char * nomVariable)
{
    Donnee * d = NULL;

    for (int i = 0; i < v->position; i++)
        if (strcmp(nomDonnee(v->donnees[i]), nomVariable) == 0)
        {
            d = v->donnees[i];
            v->donnees[i] = v->donnees[v->position - 1];
            break;
        }

    if (d != NULL)
    {
        if (!estE(d))
            d->u_var.matrice = deleteMatrix(d->u_var.matrice);
        free(d);
        free((char *) d->nom);
        v->position--;
    }

    return v;
}

Variables * libererVariables(Variables * v)
{
    for (int i = 0; i < v->position; i++)
        libererDonnee(v->donnees[i]);

    return NULL;
}
