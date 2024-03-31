/*
Biblioteca que implementa o algoritmo de
Eliminação de Gauss com pivoteamento parcial
Davi Lazzarin - 29/03/2024
*/

#ifndef _ELIMINA_GAUSS_
#define _ELIMINA_GAUSS_

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial
void eliminacaoGauss_PivoteamentoParcial(double **M, double *B, unsigned int n);

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem qualquer pivoteamento
void eliminacaoGauss(double **M, double *B, unsigned int n);


#endif