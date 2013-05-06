/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file main.c
 * \brief Main
 * \author Harenome RAZANAJATO
 */
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <time.h>

#include "base.h"
#include "matrix.h"
#include "operations.h"
#include "decompo.h"
#include "resol.h"
#include "prompt.h"

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 */
int main(int argc, char ** argv)
{
    //~ afficherPrompt();

	Matrix * m = newMatrix(3,3);
	setElt(m,1,1,1.);
	setElt(m,1,2,2.);
	setElt(m,1,3,1.);
	setElt(m,2,1,4.);
	setElt(m,2,2,2.);
	setElt(m,2,3,6.);
	setElt(m,3,1,2.);
	setElt(m,3,2,3.); 
	setElt(m,3,3,1.);
	displayMatrix(m);
	printf("\n\n");

	/* /1* setElt(m,1,1,4.); *1/ */
	/* /1* setElt(m,1,2,-9.); *1/ */
	/* /1* setElt(m,1,3,2.); *1/ */
	/* /1* setElt(m,2,1,2.); *1/ */
	/* /1* setElt(m,2,2,-4.); *1/ */
	/* /1* setElt(m,2,3,4.); *1/ */
	/* /1* setElt(m,3,1,-1.); *1/ */
	/* /1* setElt(m,3,2,2.); *1/ */
	/* /1* setElt(m,3,3,2.); *1/ */

	LUM* test = decomposition(m);
	afficheL(test);
	printf("\n\n");
	afficheU(test);
	printf("\n");

	Matrix * mprime = inverseL(test[0]);
	printf("\n\n");
	displayMatrix(mprime);
	printf("\n");
	libererLU(test);

    return 0;
}
