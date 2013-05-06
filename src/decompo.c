/**
 * \file lu.c
 * \brief Décomposition en LU (code source)
 * \author Jérémy Meyer
 */
 
#include "decompo.h"

LUM* decomposition(Matrix *m)
{
	int n = nbLignes(m);
	E somme=0.;
	E somme2=0.;
	LUM* raiponce = MALLOCN(LUM, 2);
	
	raiponce[0] = newMatrix(n,n); // L
	raiponce[1] = newMatrix(n,n); // U
	
	setElt(raiponce[0],1,1,getElt(m,1,1));
	
	for (int j = 2 ; j<=n ; j++)
	{
		setElt(raiponce[0],1,j,getElt(m,1,j));
		setElt(raiponce[1],j,1,getElt(m,j,1)/getElt(m,1,1));
	}
	
	for (int i = 2 ; i<n ; i++)
	{
		for (int k = 1 ; k<=i ; k++)
		{
			somme += getElt(raiponce[1],i,k)*getElt(raiponce[0],k,i);
		}
		
		setElt(raiponce[0],i,i,getElt(m,i,i)-somme);
		somme=0.;
		
		for (int j = i+1 ; j<=n ; j++)
		{
			for (int k = 1 ; k<=i ; k++)
			{
				somme += getElt(raiponce[0],i,k)*getElt(raiponce[1],k,j);
				somme2 += getElt(raiponce[0],j,k)*getElt(raiponce[1],k,j);
			}
			
			setElt(raiponce[1],i,j,getElt(m,i,j)-somme);
			setElt(raiponce[0],j,i,1/getElt(raiponce[1],i,i)*(getElt(m,j,i)-somme2));
		}
	}
	
	for (int k = 1 ; k<n ; k++)
	{
		somme += getElt(raiponce[0],n,k)*getElt(raiponce[1],k,n);
	}
	
	setElt(raiponce[1],n,n,getElt(m,n,n)-somme);
	
	return raiponce;
}

void afficheL(LUM* lum)
{
	displayMatrix(lum[0]);
	return;
}

void afficheU(LUM* lum)
{
	displayMatrix(lum[1]);
	return;
}

void libererLU(LUM* lum)
{
	deleteMatrix(lum[0]);
	deleteMatrix(lum[1]);
	return;
}
