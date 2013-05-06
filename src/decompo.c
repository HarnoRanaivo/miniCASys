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
	LUM* raiponce = MALLOCN(raiponce, 2);
	
	raiponce[0] = newMatrix(n,n); // L
	raiponce[1] = newMatrix(n,n); // U
	
	setElt(raiponce[0],0,0,getElt(m,0,0));
	
	for (int j = 1 ; j<n ; j++)
	{
		setElt(raiponce[0],0,j,getElt(m,0,j));
		setElt(raiponce[1],j,0,getElt(m,j,0)/getElt(m,0,0));
	}
	
	for (int i = 1 ; i<n-1 ; i++)
	{
		for (int k = 0 ; k<i ; k++)
		{
			somme += getElt(raiponce[1],i,k)*getElt(raiponce[0],k,i);
		}
		
		setElt(raiponce[0],i,i,getElt(m,i,i)-somme);
		somme=0.;
		
		for (int j = i+1 ; j<n ; j++)
		{
			for (int k = 0 ; k<i ; k++)
			{
				somme += getElt(raiponce[0],i,k)*getElt(raiponce[1],k,j);
				somme2 += getElt(raiponce[0],j,k)*getElt(raiponce[1],k,j);
			}
			
			setElt(raiponce[1],i,j,getElt(m,i,j)-somme);
			setElt(raiponce[0],j,i,1/getElt(raiponce[1],i,i)*(getElt(m,j,i)-somme2));
		}
	}
	
	for (int k = 0 ; k<n-1 ; k++)
	{
		somme += getElt(raiponce[0],n,k)*getElt(raiponce[1],k,n);
	}
	
	setElt(raiponce[1],n-1,n-1,getElt(m,n-1,n-1)-somme);
	
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
