/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file memoire.h
 * \brief Gestion des variables utilisateur (header)
 */
#ifndef __MEMOIRE_H
#define __MEMOIRE_H

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "matrix.h"

#define VAR_TAILLE 50

/**
 * \brief Type de donnée sauvegardée par dans une Donnee
 * \enum donnee_t
 */
typedef enum donnee_t
{
    VAR_FLOTTANT,   /**<- La donnée est un flottant. */
    VAR_MATRICE,    /**<- La donnée est une matrice. */
} donnee_t;

/**
 * \brief Donnée sauvegardée.
 * \struct Donnee
 */
typedef struct Donnee
{
    const char * nom;       /**<- Nom de la donnée. */
    union
    {
        E flottant;         /**<- Membre flottant de l'union. */
        Matrix * matrice;   /**<- Membre matrice de l'union. */
    } u_var;                /**<- Union contenant la donnée sauvegardée. */
    donnee_t type;          /**<- Type de donnée sauvegardée. */
} Donnee;

/**
 * \brief Variables sauvegardées.
 * \struct Variables
 */
typedef struct Variables
{
    Donnee ** donnees;      /**<- Ensemble des Donnee sauvegardées. */
    Nat taille;             /**<- Taille maximale du tableau. */
    Nat position;           /**<- Pösition courante. */
} Variables;

/**
 * \brief Créer une nouvelle donnée contenant un E.
 * \relatesalso Donnee
 * \param nom Nom de la donnée.
 * \param e E à sauvegarder.
 * \return Donnee.
 */
Donnee * nouveauE(const char * nom, E e);

/**
 * \brief Créer une nouvelle donnée contenant une matrice
 * \relatesalso Donnee
 * \param nom Nom de la donnée.
 * \param m Matrice à sauvegarder.
 * \return Donnee.
 */
Donnee * nouvelleMatrice(const char * nom, const Matrix * m);

/**
 * \brief Test vérifiant si la donnée est un E.
 * \relatesalso Donnee
 * \param d Donnee
 * \return #VRAI si la donnée est un E, #FAUX sinon.
 */
Bool estE(const Donnee * d);

/**
 * \brief Test vérifiant si la donnée est une matrice.
 * \relatesalso Donnee
 * \param d Donnee
 * \return #VRAI si la donnée est une matrice, #FAUX sinon.
 */
Bool estMatrice(const Donnee * d);

/**
 * \brief Obtenir le E stocké dans une donnée.
 * \relatesalso Donnee
 * \param d Donnee
 * \pre estE(d)
 * \return E stocké.
 */
E eDonnee(const Donnee * d);

/**
 * \brief Obtenir la matrice stockée dans une donnée.
 * \relatesalso Donnee
 * \param d Donnee
 * \pre estMatrice(d)
 * \return Matrice stockée.
 */
Matrix * matriceDonnee(const Donnee * d);

/**
 * \brief Libérer la mémoire occuppée par une Donnee.
 * \relatesalso Donnee
 * \param d Donnee
 * \return \a NULL
 */
Donnee * libererDonnee(Donnee * d);

/**
 * \brief Initialiser les variables.
 * \relatesalso Variables
 * \return Variables
 */
Variables * initVariables(void);

/**
 * \brief Test d'existence d'une variable.
 * \relatesalso Variables
 * \param v Variables.
 * \param nomVariables variable recherchée.
 * \return #VRAI si la variable existe, #FAUX sinon.
 */
Bool existeVariable(const Variables * v, const char * nomVariable);

/**
 * \brief Obtenir la Donnee \a nomVariable.
 * \relatesalso Variables
 * \relatesalso Donnees
 * \param v Variables.
 * \param nomVariable variable recherchée
 */
Donnee * obtenirDonnee(const Variables * v, const char * nomVariable);

/**
 * \brief Sauvegarder un E.
 * \relatesalso Variables
 * \param v Variables.
 * \param nomVariable Nom du E.
 * \param e E à sauvegarder.
 * \return Variables
 */
Variables * ajouterE(Variables * v, const char * nomVariable, E e);

/**
 * \brief Sauvegarder une matrice
 * \relatesalso Variables
 * \param v Variables.
 * \param nomVariable Nom de la matrice.
 * \param m Matrice à sauvegarder.
 * \return Variables
 */
Variables * ajouterMatrice(Variables * v, const char * nomVariable, const Matrix * m);

/**
 * \brief Supprimer une variable.
 * \relatesalso Variables
 * \param v Variables.
 * \param nomVariable Nom de la variable à supprimer.
 * \return Variables.
 */
Variables * supprimerVariable(Variables * v, const char * nomVariable);

/**
 * \brief Libérer la mémoire occuppée par les variables.
 * \relatesalso Variables
 * \param v Variables
 * \return NULL
 */
Variables * libererVariables(Variables * v);

#endif /* __MEMOIRE_H */
