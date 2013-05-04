/**
 * \file main.c
 * \brief Main
 * \author Harenome RAZANAJATO
 */
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <time.h>
#include "matrix.h"
#include "operations.h"
#include "decompo.h"
#include "resol.h"

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 */
int main(int argc, char ** argv)
{
	Matrix * m = newMatrix(3,3);
	setElt(m,0,0,1.);
	setElt(m,0,1,2.);
	setElt(m,0,2,1.);
	setElt(m,1,0,4.);
	setElt(m,1,1,2.);
	setElt(m,1,2,6.);
	setElt(m,2,0,2.);
	setElt(m,2,1,3.);
	setElt(m,2,2,1.);
	
	LUM* test = decomposition(m);
	afficheL(test);
	printf("\n\n");
	afficheU(test);
	printf("\n");
	libererLU(test);
	
    return 0;
}
