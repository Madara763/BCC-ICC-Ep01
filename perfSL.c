#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "EliminacaoGauss.h"

#define uint unsigned int
#define real_t double

void imprimeMatriz(real_t **M, real_t *B, unsigned int n);
real_t* isola_variaveis(real_t **M, real_t *B, unsigned int n);
int main(){
	//Lê o tamanho da matriz
	uint n;
	scanf("%d", &n);
	
	//Aloca e verifica matriz
	real_t **matriz;
	matriz=malloc(sizeof(real_t*)*n);
	if(!matriz){
		perror("Erro de alocação.\n");
		return 1;
	}
	for(uint i=0; i<n; i++){
		matriz[i]=malloc(sizeof(real_t)*n);
		if(!matriz[i]){
			perror("Erro de alocação.\n");
			return 1;
		}
	}	
	
	//Aloca e testa os termos independentes
	real_t *termos_ind=malloc(sizeof(real_t)*n);
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
	/*eliminacaoGauss_Piv(matriz, termos_ind, n);
	*/
	real_t* variaveis=isola_variaveis(matriz, termos_ind, n);
	if(!variaveis){
		perror("Erro de alocação.\n");
        return 1;
	}
	

	imprimeGauss(matriz, termos_ind, variaveis, n);
	//imprimeMatriz(matriz, termos_ind, n);
	

	//libera memória e encerra o programa
	for(unsigned int i=0; i<n; i++)
		free(matriz[i]);
	free(matriz);
	free(termos_ind);
	free(variaveis);
	return 0;
}//Main



//Imprime a matriz e os termos
void imprimeMatriz(real_t **M, real_t *B, unsigned int n){
	for(uint l=0; l<n; l++){
		for(uint c=0; c<n; c++){
        	printf("%.2lf ", M[l][c]);
    	}
    	printf("%.2lf\n", B[l]);
    }
	printf("\n");
}

//Aloca e retorna um vetor com as variaveis do SL já triangularizado
real_t* isola_variaveis(real_t **M, real_t *B, unsigned int n){
	//Aloca e testa o vetor de variaveis
	real_t *variaveis=calloc(n, sizeof(real_t));
	if(!variaveis)
        return NULL;
	real_t linha;
	uint c;
	//Isola as variaveis e salva em variaveis
	for(uint l=n; l>0; l--){
		linha=0.0;
		for(c=n; c>l; c--)
			linha+= (M[l-1][c-1] * variaveis[c-1]);

		variaveis[c-1]=((B[l-1] - linha) / M[l-1][c-1] );
	}
	return variaveis;
}