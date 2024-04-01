#include "EliminacaoGaussSidel.h"

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


/*METODOS DE ELIMINAÇÃO*/

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial 
void eliminacaoGaussSidel_Piv(real_t **M, real_t *B, uint n, real_t erro){
    
    pivoteamento(M, B, n);
    eliminacaoGaussSidel(M, B, n, erro);

}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem nenhum pivoteamento 
void eliminacaoGaussSidel(real_t **M, real_t *B, uint n, real_t erro){
    real_t erro_atual=0;
    uint max_itr=1000000, itr=0;
    while(erro_atual > erro){
        
        itr++;
    }
}