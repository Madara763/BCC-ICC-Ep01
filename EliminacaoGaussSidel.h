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
#define MAX_ITR 100
#define DBL_MAX    1.7976931348623157E+308

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial 
void eliminacaoGaussSidel_Piv(real_t **M, real_t *B, uint n, real_t erro);

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem nenhum pivoteamento 
void eliminacaoGaussSidel(real_t **M, real_t *B, uint n, real_t erro);

#endif