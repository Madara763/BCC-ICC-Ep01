#include "EliminacaoGauss.h"

/*FUNÇÕES AUXILIARES*/

//Recebe a matriz, o vetor de t.i, as linhas a serem trocadas e o tamanho da matriz 
//Retorna 1 se deu certo e 0 se deu errado
int trocaLinha(real_t **M, real_t *B, uint pivo, uint i, uint n){
    if(pivo >= n || i >= n )
        return 0;
    
    //Troca as linhas na matriz
    real_t *aux=M[pivo];
    M[pivo]=M[i];
    M[i]=aux;

    //Troca os t.i
    real_t aux_ti=B[pivo];
    B[pivo]=B[i];
    B[i]=aux_ti;

    return 1;
}   

//Recebe a MAtriz e o numero da coluna
//Retorna a linha onde há o maior valor na coluna recebida
uint encontraMax(real_t **M, uint c){
    uint max=M[0][c], linha=0;
    for(uint i=1; i<c; ++i){
        if(M[i][c] > max){
            max=M[i][c];
            linha=i;
        }
    }
    return linha;
}

//Garante que a diagonal principal esteja com os maiores valores de cada coluna
void pivoteamento(real_t **M, real_t *B, uint n){
    uint pivo;
    for(uint i=0; i<n; ++i){
        pivo=encontraMax(M, i);
        if(pivo != i)
            trocaLinha(M, B, pivo, i, n);
    }
}


/*MÉTODOS DE ELIMINAÇÃO*/

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial
void eliminacaoGauss_Piv(real_t **M, real_t *B, uint n){
    pivoteamento(M, B, n);
    eliminacaoGauss(M, B, n);
}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem qualquer pivoteamento
void eliminacaoGauss(real_t **M, real_t *B, uint n){
    real_t mult;
    
    for(uint i=0; i<n; i++){
        for(uint k=i+1; k<n; k++){
            mult=M[k][i] / M[i][i];
            M[k][i]=0.0;
            for(uint j=i+1; j<n; j++)
                M[k][j] -= M[i][j] * mult;
            B[k]-=B[i]*mult;
        }
    }   
}

//IMPRESSÂO 
//Recebe a matriz, o vetor de t.i e o vetor de variaveis
void imprimeGauss(real_t **M, real_t *B, real_t *variaveis, uint n){
    printf("EG Clássico:\n");
    printf("<Tempo_em_MS> ms\n");
    for(uint i=0; i<n; i++)
        printf("%.5lf ", variaveis[i]);
    
    printf("\n");
    real_t linha;
    uint c;
    
    //calcula o erro e salva em erros
    real_t *erros=malloc(sizeof(real_t)*n);
    if(!erros){
        perror("Erro de Alocação!!!\n");
        exit(1);
    }

    for(uint l=n; l>0; l--){
        linha=0.0;
		for(c=n; c>l; c--)
			linha+= (M[l-1][c-1] * variaveis[c-1]);

        linha=fabs((B[c-1]-linha)/M[l-1][c-1]);
        erros[c-1]=fabs(linha-variaveis[c-1]);
    }
    //imprime os erros
    for(uint i=0; i<n; i++)
        printf("%.5lf ", erros[i]);
    
    //Libera memória
    free(erros);
    printf("\n");
}
