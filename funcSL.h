/*
Biblioteca com funções auxiliares de manipulação de SL
Davi Lazzarin 04/04/2024
*/
#include <stdio.h>

#define uint unsigned int
#define real_t double

//Copia matriz para matriz_copia e os termos para termos_copia
void copiaSL(real_t** matriz, real_t* termos, real_t** matriz_copia, real_t* termos_copia, uint n);

//Imprime a matriz e os termos
void imprimeMatriz(real_t **M, real_t *B, unsigned int n);