#include<stdio.h>
#include<stdlib.h>

#include "EliminacaoGauss.h"

#define uint unsigned int

void imprimeMatriz(double **M, double *B, unsigned int n);
int main(){
	//Lê o tamanho da matriz
	uint n;
	scanf("%d", &n);
	
	//Aloca e verifica matriz
	double **matriz;
	matriz=malloc(sizeof(double*)*n);
	if(!matriz){
		perror("Erro de alocação.\n");
		return 1;
	}
	for(uint i=0; i<n; i++){
		matriz[i]=malloc(sizeof(double)*n);
		if(!matriz[i]){
			perror("Erro de alocação.\n");
			return 1;
		}
	}	
	
	//Aloca e testa os termos independentes
	double *termos_ind=malloc(sizeof(double)*n);
	if(!termos_ind){
		perror("Erro de alocação.\n");
        return 1;
	}
	
	//Lê a matriz e os termos do stdin
	for(uint l=0; l<n; l++){
		for(uint c=0; c<n; c++){
			scanf("%lf", &matriz[l][c]);
		}
		scanf("%lf", &termos_ind[l]);
	}	
	
	imprimeMatriz(matriz, termos_ind, n);	
	eliminacaoGauss_PivoteamentoParcial(matriz, termos_ind, n);
	imprimeMatriz(matriz, termos_ind, n);
	

	//libera memória e encerra o programa
	for(unsigned int i=0; i<n; i++)
		free(matriz[i]);
	free(matriz);
	free(termos_ind);
	return 0;
}

//Imprime a matriz e os termos
void imprimeMatriz(double **M, double *B, unsigned int n){
	for(uint l=0; l<n; l++){
		for(uint c=0; c<n; c++){
        	printf("%.2lf ", M[l][c]);
    	}
    	printf("%.2lf\n", B[l]);
    }
	
	printf("\n");
}