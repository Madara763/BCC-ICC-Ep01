#include "funcSL.h"


//Imprime a matriz e os termos
void imprimeMatriz(real_t **M, real_t *B, unsigned int n){
	for(uint l=0; l<n; l++){
		for(uint c=0; c<n; c++){
        	printf("%.5lf ", M[l][c]);
    	}
    	printf("%.5lf\n", B[l]);
    }
	printf("\n");
}

//Copia matriz para matriz_copia e os termos para termos_copia
void copiaSL(real_t** matriz, real_t* termos, real_t** matriz_copia, real_t* termos_copia, uint n){
	for(uint l=0; l<n; l++){
		for(uint c=0; c<n; c++)
			matriz_copia[l][c] = matriz[l][c];
		termos_copia[l]=termos[l];
	}
}