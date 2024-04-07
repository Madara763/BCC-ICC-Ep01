#include "EliminacaoGauss.h"

/*FUNÇÕES AUvariaveisILIARES*/

//Recebe a matriz, o vetor de t.i, as linhas a serem trocadas e o tamanho da matriz 
//Retorna 1 se deu certo e 0 se deu errado
int trocaLinha(real_t **M, real_t *B, uint pivo, uint i, uint n){
    if(pivo >= n || i >= n )
        return 0;
    
    //Troca as linhas na matriz
    real_t *auvariaveis=M[pivo];
    M[pivo]=M[i];
    M[i]=auvariaveis;

    //Troca os t.i
    real_t auvariaveis_ti=B[pivo];
    B[pivo]=B[i];
    B[i]=auvariaveis_ti;

    return 1;
}   

//Recebe a MAtriz e o numero da coluna
//Retorna a linha onde há o maior valor na coluna recebida
uint encontraMavariaveis(real_t **M, uint c){
    uint mavariaveis=M[0][c], linha=0;
    for(uint i=1; i<c; ++i){
        if(M[i][c] > mavariaveis){
            mavariaveis=M[i][c];
            linha=i;
        }
    }
    return linha;
}

//Garante que a diagonal principal esteja com os maiores valores de cada coluna
void pivoteamento(real_t **M, real_t *B, uint n){
    uint pivo;
    for(uint i=0; i<n; ++i){
        pivo=encontraMavariaveis(M, i);
        if(pivo != i)
            trocaLinha(M, B, pivo, i, n);
    }
}


/*MÉTODOS DE ELIMINAÇÃO*/

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial
real_t* eliminacaoGauss_Piv(real_t **M, real_t *B, uint n, rtime_t *tempo){
    //pivoteamento(M, B, n);
    return eliminacaoGauss(M, B, n, tempo);
}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem qualquer pivoteamento
real_t* eliminacaoGauss(real_t **M, real_t *B, uint n, rtime_t *tempo){
    real_t mult, linha;
    
	//Execução do LIKWID
	LIKWID_MARKER_INIT;
	LIKWID_MARKER_START ("EG_Classico");
    (*tempo)=timestamp();
    for(uint i=0; i<n; i++){
        for(uint k=i+1; k<n; k++){
            mult=M[k][i] / M[i][i];
            M[k][i]=0.0;
            for(uint j=i+1; j<n; j++)
                M[k][j] -= M[i][j] * mult;
            B[k]-=B[i]*mult;
        }
    }
    (*tempo)=(timestamp() - (*tempo));
    
	LIKWID_MARKER_STOP ("EG_Classico");    
  	LIKWID_MARKER_CLOSE;
	//Execução do LIKWID
    
    //Isola as variaveis
    real_t* variaveis=malloc(sizeof(real_t)*n);
    if(!variaveis){ perror("Erro de Alocação!!!\n"); exit(1);}
    
    for(int i=n-1; i>=0; i--){
        linha=0.0;
        for(int k=n-1; k>i; k--)
            linha+=M[i][k]*variaveis[k];
        
        variaveis[i]=(B[i] - linha ) / M[i][i];
    }
    return variaveis;
}

//Algoritmo implementa a EG para matrizes tri-diagonais
real_t* eliminacaoGauss_tri(real_t *B, real_t *c, real_t *d, real_t *a, uint n, rtime_t *tempo){
    real_t mult=0.0;

    //Execução do LIKWID
	LIKWID_MARKER_INIT;
    LIKWID_MARKER_START ("EG_3_Diagonal");

    (*tempo)=timestamp();
    for(uint i=0; i<n-1; i++) {
        mult = a[ i ] / d[ i ];
        a[i] = 0.0;
        d[i+1]-= c[i]*mult;
        B[i+1]-= B[i]*mult;
    }
    (*tempo)=(timestamp() - (*tempo));

	LIKWID_MARKER_STOP ("EG_3_Diagonal");
    LIKWID_MARKER_CLOSE;

    //Execução do LIKWID

    real_t *variaveis=malloc(sizeof(real_t)*n);
    if(!variaveis){ perror("Erro de Alocação!!!\n"); exit(1);}
    
    variaveis[n-1]= B[n-1] / d[n-1];
    for (int i=n-2; i >= 0; i--)
        variaveis[i]= (B[i] - c[i]*variaveis[i+1]) / d[i];
    
    return variaveis;
}

//IMPRESSÂO 
//Recebe a matriz, o vetor de t.i e o vetor de variaveis
void imprimeGauss(real_t **M, real_t *B, real_t *variaveis, uint n, rtime_t *tempo){
    printf("EG Clássico:\n");
    printf("%.8lf ms\n", (*tempo));
    for(uint i=0; i<n; i++)
        printf("%.5lf ", variaveis[i]);
    
    printf("\n");
    real_t linha;
    uint c;
    
    //calcula o erro e salva em erros
    real_t *erros=malloc(sizeof(real_t)*n);
    if(!erros){ perror("Erro de Alocação!!!\n"); exit(1); }

    for(uint l=n; l>0; l--){
        linha=0.0;
		for(c=n; c>l; c--)
			linha+= (M[l-1][c-1] * variaveis[c-1]);

        linha=fabs((B[c-1]-linha)/M[l-1][c-1]);
        erros[c-1]=fabs(linha-variaveis[c-1]);
    }
    //imprime os erros
    for(uint i=0; i<n; i++)
        printf("%.12lf ", erros[i]);
    
    //Libera memória
    free(erros);
    printf("\n");
}

//Recebe os 3 vetores e o vetor de t.i
void imprimeGauss_tri(real_t* B, real_t* vetC, real_t* vetD, real_t* vetA,real_t* variaveis, uint n, rtime_t *tempo){
    printf("\nEG 3-Diagonal:\n");
    printf("%.8lf ms\n", (*tempo));
    for(uint i=0; i<n; i++)
        printf("%.5lf ", variaveis[i]);
    
    printf("\n");

    //calcula o erro e salva em erros
    real_t *erros=malloc(sizeof(real_t)*n);
    if(!erros){ perror("Erro de Alocação!!!\n"); exit(1); }

    erros[n-1]=fabs(variaveis[n-1] - (B[n-1]/vetD[n-1]));
    for(int linha=n-2; linha>=0; linha--)
        erros[linha]= fabs( variaveis[linha] - ( (B[linha] - (vetC[linha] * B[linha+1])) / vetD[linha] ) );
    
    //imprime os erros
    for(uint i=0; i<n; i++)
        printf("%.12lf ", erros[i]);
    
    //Libera memória
    free(erros);
    printf("\n");

}

