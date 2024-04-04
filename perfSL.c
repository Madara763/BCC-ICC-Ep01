#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "funcSL.h"
#include "EliminacaoGauss.h"
#include "EliminacaoGaussSidel.h"

#define uint unsigned int
#define real_t double
#define ERRO_GS 0.005

int main(){
	//Lê o tamanho da matriz
	uint n;
	scanf("%d", &n);
	
	//Aloca e verifica matriz
	real_t **matriz=malloc(sizeof(real_t*)*n);
	real_t **matriz_copia=malloc(sizeof(real_t*)*n);
	if(!matriz || !matriz_copia){
		perror("Erro de alocação.\n");
		return 1;
	}
	for(uint i=0; i<n; i++){
		matriz[i]=malloc(sizeof(real_t)*n);
		matriz_copia[i]=malloc(sizeof(real_t)*n);
		if(!matriz[i] || !matriz_copia[i]){
			perror("Erro de alocação.\n");
			return 1;
		}
	}	
	
	//Aloca e testa os termos independentes
	real_t *termos_ind=malloc(sizeof(real_t)*n);
	real_t *termos_ind_copia=malloc(sizeof(real_t)*n);
	if(!termos_ind || !termos_ind_copia){
		perror("Erro de alocação.\n");
        return 1;
	}
	
	//Lê a matriz e os termos do stdin
	for(uint l=0; l<n; l++){
		for(uint c=0; c<n; c++){
			scanf("%lf", &matriz[l][c]);
			matriz_copia[l][c] = matriz[l][c];
		}
		scanf("%lf", &termos_ind[l]);
		termos_ind_copia[l]=termos_ind[l];
	}	
	

	//INICIO DOS METODOS
	real_t* variaveis;
	uint itr;
	imprimeMatriz(matriz, termos_ind, n);	

	//TESTE EG Clássico
	copiaSL(matriz, termos_ind, matriz_copia, termos_ind_copia, n);
	variaveis=eliminacaoGauss_Piv(matriz_copia, termos_ind_copia, n);
	imprimeGauss(matriz_copia, termos_ind_copia, variaveis, n);	
	free(variaveis);

		
	//Teste GS
	copiaSL(matriz, termos_ind, matriz_copia, termos_ind_copia, n);
	variaveis=eliminacaoGaussSidel_Piv(matriz_copia, termos_ind_copia, n, ERRO_GS, &itr);	
	imprimeGaussSidel(matriz_copia, termos_ind, variaveis, n, &itr);
	free(variaveis);

	
	

	//libera memória e encerra o programa
	for(unsigned int i=0; i<n; i++){
		free(matriz[i]);
		free(matriz_copia[i]);
	}
	free(matriz);
	free(matriz_copia);
	free(termos_ind);
	free(termos_ind_copia);
	
	return 0;
}//Main

