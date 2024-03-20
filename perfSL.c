#include<stdio.h>
#include<stdlib.h>

#define uint unsigned int
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
	
	//Imprime a matriz e os termos
	for(uint l=0; l<n; l++){
        for(uint c=0; c<n; c++){
            printf("%.2lf ", matriz[l][c]);
        }
        printf("%.2lf\n", termos_ind[l]);
    }	

	return 0;
}
