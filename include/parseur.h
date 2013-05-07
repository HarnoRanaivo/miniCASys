/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file parseur.h
 * \brief Parseur (header)
 * \author Harenome RAZANAJATO
 */
#ifndef __PARSEUR_H
#define __PARSEUR_H

#include <stdio.h>
#include <string.h>

#include "base.h"
#include "memoire.h"

/**
 * \brief Vérifie qu'une définition de matrice contient des lignes complètes.
 * \param chaine Matrice à analyser
 * \return #VRAI si les lignes sont correctes, #FAUX sinon.
 *
 * Chaque '[' doit avoir son ']', les lignes ne doivent pas être imbriquées.
 */
Bool contientMatriceValide(const char * chaine);

/**
 * \brief Compter le nombre de lignes d'une définition de matrice.
 * \param chaine Matrice à analyser.
 * \return nombre de lignes.
 */
int compterLignes(const char * chaine);

/**
 * \brief Compter le nombre de colonnes d'une définition de matrice.
 * \param chaine Matrice à analyser.
 * \return nombre de colonnes.
 */
int compterColonnes(const char * chaine);

/**
 * \brief Récupérer un tableau de pointeurs sur les lignes.
 * \param chaine Matrice à analyser.
 * \return lignes de la matrice.
 *
 * Chaque élément du tableau pointe vers le début d'une sous-chaîne
 * correspondant à une ligne de la matrice.
 */
char ** recupererLignesMatrice(char * chaine);

/**
 * \brief Obtenir une matrice à partir de sa définition.
 * \param chaine Matrice à analyser.
 * \param v Variables déjà définies.
 * \return Matrice.
 */
Matrix * recupererMatrice(char * chaine, const Variables * v);

/**
 * \brief Préparer la ligne de commande entrée par l'utilisateur.
 * \param chaine Ligne de commande utilisateur.
 * \param decomposition Tableau destiné aux pointeurs vers les sous-chaînes.
 * \return Nombre de parties.
 *
 * Les parties délimitées par cette fonction sont de la forme :
 * <partie 1> : <partie 2> ( <partie 3> ) <partie 4>
 *
 * Les parties 1 et 2 ne doivent contenir qu'un seul mot.
 */
int preparerLigneCommmande(char * chaine, char * decomposition[4]);

/**
 * \brief Préparer la commande entrée par l'utilisateur.
 * \param chaine Ligne de commande utilisateur.
 * \param decomposition Tableau destiné aux pointeurs vers les sous-chaînes.
 * \return Nombre de parties.
 *
 * Les parties délimitées par cette fonction sont de la forme :
 * <partie 1> ( <partie 2> )
 *
 * La partie 1 ne doit contenir qu'un seul mot.
 */
int preparerCommande(char * chaine, char * decomposition[2]);

#endif /* __PARSEUR_H */
