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

//Aloca e retorna as 3 diagonais nos ponteiros que recebe
void tridiagonaliza(real_t** matriz, real_t* termos,  uint n, real_t* vetC, real_t* vetD, real_t* vetA){

	vetD[0]=matriz[0][0];
	vetC[0]=matriz[0][1];
	for(uint i=1; i<n-1; i++){
		vetC[i]=matriz[i][i+1];
		vetD[i]=matriz[i][i];
		vetA[i-1]=matriz[i][i-1];
	}
	vetD[n-1]=matriz[n-1][n-1];
	vetA[n-2]=matriz[n-1][n-2];

}