#include "EliminacaoGauss.h"
#include<stdio.h>

//Recebe a matriz, o vetor de t.i, as linhas a serem trocadas e o tamanho da matriz 
//Retorna 1 se deu certo e 0 se deu errado
int trocaLinha(double **M, double *B, unsigned int pivo, unsigned int i, unsigned int n){
    if(pivo >= n || i >= n )
        return 0;
    
    //Troca as linhas na matriz
    double *aux=M[pivo];
    M[pivo]=M[i];
    M[i]=aux;

    //Troca os t.i
    double aux_ti=B[pivo];
    B[pivo]=B[i];
    B[i]=aux_ti;

    return 1;
}   

//Recebe a MAtriz e o numero da coluna
//Retorna a linha onde há o maior valor na coluna recebida
unsigned int encontraMax(double **M, unsigned int c){
    unsigned int max=M[0][c], linha=0;
    for(unsigned int i=1; i<c; ++i){
        if(M[i][c] > max){
            max=M[i][c];
            linha=i;
        }
    }
    return linha;
}

//Garante que a diagonal principal esteja com os maiores valores de cada coluna
void pivoteamento(double **M, double *B, unsigned int n){
    unsigned int pivo;
    for(unsigned int i=0; i<n; ++i){
        pivo=encontraMax(M, i);
        if(pivo != i)
            trocaLinha(M, B, pivo, i, n);
    }
}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial
void eliminacaoGauss_PivoteamentoParcial(double **M, double *B, unsigned int n){
    double mult;
    pivoteamento(M, B, n);
    
    for(unsigned int i=0; i<n; i++){
        for(unsigned int k=i+1; k<n; k++){
            mult=M[k][i] / M[i][i];
            M[k][i]=0.0;
            for(unsigned int j=i+1; j<n; j++)
                M[k][j] -= M[i][j] * mult;
            B[k]-=B[i]*mult;
        }
    }   
}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem qualquer pivoteamento
void eliminacaoGauss(double **M, double *B, unsigned int n){
    double mult;
    
    for(unsigned int i=0; i<n; i++){
        for(unsigned int k=i+1; k<n; k++){
            mult=M[k][i] / M[i][i];
            M[k][i]=0.0;
            for(unsigned int j=i+1; j<n; j++)
                M[k][j] -= M[i][j] * mult;
            B[k]-=B[i]*mult;
        }
    }   
}