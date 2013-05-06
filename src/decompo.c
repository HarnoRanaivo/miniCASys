/* This program is free software. It comes WITHOUT ANY WARRANTY, to
* the extent permitted by applicable law. You can redistribute it
* and/or modify it under the terms of the Do What The Fuck You Want
* To Public License, Version 2, as published by Sam Hocevar. See
* http://wtfpl.net for more details. */
/**
 * \file decompo.c
 * \brief Décomposition en LU (code source)
 * \author Jérémy Meyer
 */
 
#include "decompo.h"

LUM* decomposition(Matrix *m)
{
	int n = nbLignes(m);
	E somme=0.;
	E somme2=0.;
	LUM* raiponce = MALLOCN(raiponce, 2);
	
	if (raiponce != NULL)
    {
        Matrix * l = newMatrix(n,n); // L
        Matrix * u = newMatrix(n,n); // U

        setElt(u,1,1,getElt(m,1,1));


        for (int j = 2 ; j<=n ; j++)
        {
            setElt(u,1,j,getElt(m,1,j));
            setElt(l,j,1,getElt(m,j,1)/getElt(m,1,1));
        }

        for (int i = 2 ; i<n ; i++)
        {
            for (int k = 1 ; k<i ; k++)
            {
                somme += getElt(l,i,k)*getElt(u,k,i);
            }

            setElt(u,i,i,getElt(m,i,i)-somme);
            somme=0.;

            for (int j = i+1 ; j<=n ; j++)
            {
                for (int k = 1 ; k<i ; k++)
                {
                    somme += getElt(l,i,k)*getElt(u,k,j);
                    somme2 += getElt(l,j,k)*getElt(u,k,i);
                }

                setElt(u,i,j,getElt(m,i,j)-somme);
                setElt(l,j,i,1./getElt(u,i,i)*(getElt(m,j,i)-somme2));
            }

            somme=0.;
            somme2=0.;
        }

        for (int k = 1 ; k<n ; k++)
        {
            somme += getElt(l,n,k)*getElt(u,k,n);
        }

        setElt(u,n,n,getElt(m,n,n)-somme);

        for (int i = 1; i <= n; i++)
            setElt(l,i,i,1.);

        raiponce[0]= l;
        raiponce[1] = u;
    }
    else
        perror("malloc");
		
	return raiponce;
}

void afficheL(LUM* lum)
{
    printf("\tL :\n");
	displayMatrix(lum[0]);
	return;
}

void afficheU(LUM* lum)
{
    printf("\tU :\n");
	displayMatrix(lum[1]);
	return;
}

void afficheLU(LUM* lum)
{
    afficheL(lum);
    printf("\n\n");
    afficheU(lum);
}

void libererLU(LUM* lum)
{
	deleteMatrix(lum[0]);
	deleteMatrix(lum[1]);
	free(lum);
	return;
}

Matrix * inverseL (LUM * l)
{
	int n = nbLignes(l[0]);
	Matrix * lprime = copieMatrice(l[0]);
	Matrix * solve = identite(n);
	
	for (int i = 2 ; i<=n ; i++) // pour toutes lignes en dehors de la diagonale
	{
		for (int j = 1 ; j<i ; j++) // pour toutes colonnes en dehors de la diagonale
		{
			if (getElt(lprime,i,j) != 0) // On cherche à mettre l'élément à 0 donc ce test réduit les calculs
			{
				E multiple = -1.*getElt(lprime,i,j); // multiple permettant de mettre à 0 car il n'y a que des 1 sur la diagonale de L
				lprime = addMultLigne(lprime, i, j, multiple);
				solve = addMultLigne(solve, i, j, multiple);
				/*On fait les mêmes opérations sur les deux matrices,
				 * permettant ainsi d'avoir la solution
				 */
			}
		}
	}
	deleteMatrix(lprime);
	
	return solve;
}

Matrix * inverseU (LUM * l)
{
	int n = nbLignes(l[1]);
	Matrix * lprime = copieMatrice(l[1]);
	Matrix * solve = identite(n);
	
	for (int i = 1 ; i<=n ; i++) // Pour toute la diagonale
	{
		if (getElt(lprime,i,i) != 1) // si l'élément de la diagonale est différent de 1 on le met à 1
		{
			E multiple = 1./getElt(lprime,i,i);
			for (int j = 1 ; j<=n ; j++) // on oublie pas de modifier le reste de la ligne en conséquence
			{
				E element = getElt(lprime,i,j);
				element*=multiple;
				setElt(lprime,i,j,element);
				element = getElt(solve,i,j);
				element*=multiple;
				setElt(solve,i,j,element);
			}
		}
	}
	
	for (int i = n-1 ; i>0 ; i--) // Même algorithme que pour L
	{
		for (int j = n ; j>i ; j--)
		{
			if (getElt(lprime,i,j) != 0)
			{
				E multiple = -1.*getElt(lprime,i,j);
				lprime = addMultLigne(lprime, i, j, multiple);
				solve = addMultLigne(solve,i ,j ,multiple);
			}
		}
	}
	deleteMatrix(lprime);
		
	return solve;
}

Matrix * inverseM (Matrix * m)
{
	LUM * decompo = decomposition(m);
	Matrix * solve;
	
	solve = multiplication(inverseU(decompo),inverseL(decompo)); // l'inverse d'une matrice m = inv(U).inv(L)
	libererLU(decompo);
	
	return solve;
}
