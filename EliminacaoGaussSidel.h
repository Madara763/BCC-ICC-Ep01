/*
Biblioteca que implementa o algoritmo de
Eliminação de Gauss com pivoteamento parcial
Davi Lazzarin - 31/03/2024
*/

#ifndef _ELIMINA_GAUSS_SIDEL_
#define _ELIMINA_GAUSS_SIDEL_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utils.h"


#define MAX_ITR 100
#define VLR_INICIAL 0
#define DBL_MAX    1.7976931348623157E+308

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial 
real_t* eliminacaoGaussSidel_Piv(real_t **M, real_t *B, uint n, real_t erro, uint *itr, rtime_t *tempo);

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem nenhum pivoteamento
//Retorna o vetor com as variaveis e não altera a matriz e os T.I
real_t* eliminacaoGaussSidel(real_t **M, real_t *B, uint n, real_t erro, uint *itr, rtime_t *tempo);

//Algoritmo que implementa o GS para matrizes tridiagonais
//Recebe o vetor de T.I, os 3 vetores tridiagonais, o erro maximo e o tamanho
real_t* eliminacaoGaussSidel_tri(real_t *B, real_t *c, real_t *d, real_t *a, uint n, real_t erro_max, uint *itr, rtime_t *tempo);

//IMPRESSÂO 
//Recebe a matriz, o vetor de t.i e o vetor de variaveis
void imprimeGaussSidel(real_t **M, real_t *B, real_t *variaveis, uint n, uint *itr, rtime_t *tempo);

//Recebe o vetor de T.i, os 3 vetores e as variaveis
void imprimeGaussSidel_tri(real_t *B, real_t *c, real_t *d, real_t *a, real_t *variaveis, uint n, uint *itr, rtime_t *tempo);

#endif