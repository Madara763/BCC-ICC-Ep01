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

#define real_t double
#define uint unsigned int
#define MAX_ITR 10
#define VLR_INICIAL 0
#define DBL_MAX    1.7976931348623157E+308


//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial 
real_t* eliminacaoGaussSidel_Piv(real_t **M, real_t *B, uint n, real_t erro);

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem nenhum pivoteamento
//Retorna o vetor com as variaveis e não altera a matriz e os T.I
real_t* eliminacaoGaussSidel(real_t **M, real_t *B, uint n, real_t erro);

//IMPRESSÂO 
//Recebe a matriz, o vetor de t.i e o vetor de variaveis
void imprimeGaussSidel(real_t **M, real_t *B, real_t *variaveis, uint n);

#endif