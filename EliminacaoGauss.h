/*
Biblioteca que implementa o algoritmo de
Eliminação de Gauss com pivoteamento parcial
Davi Lazzarin - 29/03/2024
GRR - 20204398
*/

#ifndef _ELIMINA_GAUSS_
#define _ELIMINA_GAUSS_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <likwid.h>
#include "utils.h"

#define real_t double
#define uint unsigned int

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial
real_t* eliminacaoGauss_Piv(real_t **M, real_t *B, uint n, rtime_t *tempo);

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem qualquer pivoteamento
real_t* eliminacaoGauss(real_t **M, real_t *B, uint n, rtime_t *tempo);

//Algoritmo implementa a EG para matrizes tri-diagonais
real_t* eliminacaoGauss_tri(real_t *B, real_t *c, real_t *d, real_t *a, uint n, rtime_t *tempo);

//Recebe a matriz o vetor de t.i e o vetor de variaveis
void imprimeGauss(real_t **M, real_t *B, real_t *variaveis, uint n, rtime_t *tempo);

//Recebe os 3 vetores e o vetor de t.i
void imprimeGauss_tri(real_t* B, real_t* vetC, real_t* vetD, real_t* vetA, real_t* variaveis, uint n, rtime_t *tempo);


#endif
