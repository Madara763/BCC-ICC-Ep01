/*
Biblioteca que implementa o algoritmo de
Eliminação de Gauss com pivoteamento parcial
Davi Lazzarin - 29/03/2024
*/

#ifndef _ELIMINA_GAUSS_
#define _ELIMINA_GAUSS_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define real_t double
#define uint unsigned int

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial
real_t* eliminacaoGauss_Piv(real_t **M, real_t *B, uint n);

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem qualquer pivoteamento
real_t* eliminacaoGauss(real_t **M, real_t *B, uint n);

//Algoritmo implementa a EG para matrizes tri-diagonais
real_t* eliminacaoGauss_tri(real_t *B, real_t *c, real_t *d, real_t *a, uint n);

//Recebe a matriz o vetor de t.i e o vetor de variaveis
void imprimeGauss(real_t **M, real_t *B, real_t *variaveis, uint n);

//Recebe os 3 vetores e o vetor de t.i
void imprimeGauss_tri(real_t* B, real_t* vetC, real_t* vetD, real_t* vetA,real_t* variaveis, uint n);


#endif