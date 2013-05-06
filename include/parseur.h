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

Bool contientMatriceValide(const char * chaine);

int compterLignes(const char * chaine);

int compterColonnes(const char * chaine);

char ** recupererLignesMatrice(char * chaine);

Matrix * recupererMatrice(char * chaine, const Variables * v);

#endif /* __PARSEUR_H */
