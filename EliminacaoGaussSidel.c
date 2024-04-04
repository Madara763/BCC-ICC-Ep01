#include "EliminacaoGaussSidel.h"

/*FUNÇÕES AUXILIARES*/

//Recebe a matriz, o vetor de t.i, as linhas a serem trocadas e o tamanho da matriz 
//Retorna 1 se deu certo e 0 se deu errado
int trocaLinha_sidel(real_t **M, real_t *B, uint pivo, uint i, uint n){
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
uint encontraMax_sidel(real_t **M, uint c){
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
void pivoteamento_sidel(real_t **M, real_t *B, uint n){
    uint pivo;
    for(uint i=0; i<n; ++i){
        pivo=encontraMax_sidel(M, i);
        if(pivo != i)
            trocaLinha_sidel(M, B, pivo, i, n);
    }
}


/*METODOS DE ELIMINAÇÃO*/

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial 
real_t* eliminacaoGaussSidel_Piv(real_t **M, real_t *B, uint n, real_t erro, uint *itr){
    pivoteamento_sidel(M, B, n);
    return eliminacaoGaussSidel(M, B, n, erro, itr);    
}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem nenhum pivoteamento
//Retorna o vetor com as variaveis e não altera a matriz e os T.I
real_t* eliminacaoGaussSidel(real_t **M, real_t *B, uint n, real_t erro, uint *itr){
   
    real_t erro_atual=DBL_MAX, linha=0.0;
    //Aloca o vetor de variaveis e o vetor de variaveis da execução anterior
    real_t *variaveis=calloc(n, sizeof(real_t));
    real_t *variaveis_ante=calloc(n, sizeof(real_t));
    real_t *erros=calloc(n, sizeof(real_t));
    if(!variaveis || !variaveis_ante || !erros ){
        perror("Erro de Alocação!!!\n");
        exit(1);
    }
    *itr=0;
    while(erro_atual > erro && (*itr)<MAX_ITR){
        for(uint i=0; i<n; i++){
            linha=B[i];
            for(uint c=0; c<n; c++)
                if(c != i)
                    linha-=(M[i][c] * variaveis[c]);
            
            variaveis[i]=(linha/M[i][i]);
            erros[i]=fabs(variaveis[i]-variaveis_ante[i]);
            variaveis_ante[i]=variaveis[i];
        }
        erro_atual=erros[n-1];
        for(uint i=0; i<n-1; i++)
            if(erros[i]>erro_atual)
                erro_atual=erros[i];
        (*itr)++;
    }
    free(variaveis_ante);
    free(erros);
    return variaveis;
}

//IMPRESSÂO 
//Recebe a matriz, o vetor de t.i e o vetor de variaveis
void imprimeGaussSidel(real_t **M, real_t *B, real_t *variaveis, uint n, uint *itr){
    printf("\nGS Clássico [%d]\n", *itr);
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