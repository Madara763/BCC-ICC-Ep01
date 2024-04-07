#include "EliminacaoGaussSidel.h"

/*FUNÇÕES AUXILIARES*/

//Recebe a matriz, o vetor de t.i, as linhas a serem trocadas e o tamanho da matriz 
//Retorna 1 se deu certo e 0 se deu errado
int trocaLinha_sidel(real_t **M, real_t *B, int pivo, int i, uint n){
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
int encontraMax_sidel(real_t **M, uint c){
    int max=M[0][c], linha=0;
    for(int i=1; i<c; ++i){
        if(M[i][c] > max){
            max=M[i][c];
            linha=i;
        }
    }
    return linha;
}

//Garante que a diagonal principal esteja com os maiores valores de cada coluna
void pivoteamento_sidel(real_t **M, real_t *B, uint n){
    int pivo;
    for(int i=0; i<n; ++i){
        pivo=encontraMax_sidel(M, i);
        if(pivo != i)
            trocaLinha_sidel(M, B, pivo, i, n);
    }
}


/*METODOS DE ELIMINAÇÃO*/

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Implementa pivoteamento parcial 
real_t* eliminacaoGaussSidel_Piv(real_t **M, real_t *B, uint n, real_t erro, uint *itr, rtime_t *tempo){
    //pivoteamento_sidel(M, B, n);
    return eliminacaoGaussSidel(M, B, n, erro, itr, tempo);    
}

//Matriz M, Vetor B de termos independentes, Tamnaho da matriz n
//Sem nenhum pivoteamento
//Retorna o vetor com as variaveis e não altera a matriz e os T.I
real_t* eliminacaoGaussSidel(real_t **M, real_t *B, uint n, real_t erro, uint *itr, rtime_t *tempo){
   
    real_t erro_atual=DBL_MAX, linha=0.0;
    //Aloca o vetor de variaveis e o vetor de variaveis da execução anterior
    real_t *variaveis=calloc(n, sizeof(real_t));
    real_t *variaveis_ante=calloc(n, sizeof(real_t));
    real_t *erros=calloc(n, sizeof(real_t));
    if(!variaveis || !variaveis_ante || !erros ){
        perror("Erro de Alocação!!!\n");
        exit(1);
    }
    //Execução do LIKWID
    (*tempo)=timestamp();
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
    (*tempo)=(timestamp() - (*tempo));
    //Execução do LIKWID
    free(variaveis_ante);
    free(erros);
    return variaveis;
}


//Algoritmo que implementa o GS para matrizes tridiagonais
//Recebe o vetor de T.I, os 3 vetores tridiagonais, o erro maximo e o tamanho
real_t* eliminacaoGaussSidel_tri(real_t *B, real_t *c, real_t *d, real_t *a, uint n, real_t erro_max, uint *itr, rtime_t *tempo){
    real_t erro_atual=1.0+erro_max;
    real_t *variaveis=calloc(n,sizeof(real_t));
    real_t *variaveis_ante=calloc(n, sizeof(real_t));
    real_t *erros=calloc(n, sizeof(real_t));
    if(!variaveis || !variaveis_ante || !erros ){
        perror("Erro de Alocação!!!\n");
        exit(1);
    }

    //Execução do LIKWID
    (*tempo)=timestamp();
    *itr=0;
    while (erro_atual > erro_max && (*itr)<MAX_ITR) {
        variaveis[ 0 ] = (B[ 0 ] - c[ 0 ] * variaveis[ 1 ]) / d[ 0 ];
        erros[0]=fabs(variaveis[0]);
        variaveis_ante[0]=variaveis[0];

        for (int i=1; i < n-1; ++i){
            variaveis[ i ] = (B[ i ] - a[ i-1 ] * variaveis[ i-1] - c[ i ] * variaveis[ i+1 ]) / d[ i ];
            erros[i]=fabs(variaveis[i]-variaveis_ante[i]);
            variaveis_ante[i]=variaveis[i];
        }   
        variaveis[n-1] = (B[n-1] - a[n-2] * variaveis[n-2] ) / d[n-1];

        erros[n-1]=fabs(variaveis[n-1]-variaveis_ante[n-1]);
        variaveis_ante[n-1]=variaveis[n-1];

        erro_atual=erros[n-1];
        for(uint i=0; i<n-1; i++)
            if(erros[i]>erro_atual)
                erro_atual=erros[i];
        
        (*itr)++;
    }
    (*tempo)=(timestamp() - (*tempo));
    //Execução do LIKWID

    free(erros);
    free(variaveis_ante);
    return variaveis;
}

//IMPRESSÂO 
//Recebe a matriz, o vetor de t.i e o vetor de variaveis
void imprimeGaussSidel(real_t **M, real_t *B, real_t *variaveis, uint n, uint *itr, rtime_t *tempo){
    printf("\nGS Clássico [%d]\n", *itr);
    printf("%.8lf ms\n", (*tempo));
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
        printf("%.12lf ", erros[i]);
    
    //Libera memória
    free(erros);
    printf("\n");
}

//Recebe o vetor de T.i, os 3 vetores e as variaveis
void imprimeGaussSidel_tri(real_t *B, real_t *vetC, real_t *vetD, real_t *vetA, real_t *variaveis, uint n, uint *itr, rtime_t *tempo){
    printf("\nGS 3-Diagonal [%d]\n", *itr);
    printf("%.8lf ms\n", (*tempo));
    for(uint i=0; i<n; i++)
        printf("%.5lf ", variaveis[i]);

    printf("\n");

    //calcula o erro e salva em erros
    real_t *erros=malloc(sizeof(real_t)*n);
    if(!erros){ perror("Erro de Alocação!!!\n"); exit(1); }

    erros[n-1]=fabs(variaveis[n-1] - (B[n-1]/vetD[n-1]));
    for(int linha=n-2; linha>=0; linha--)
        erros[linha]= fabs( variaveis[linha] - ( (B[linha] - (vetC[linha] * B[linha+1])) / vetD[linha] ) );
    
    //imprime os erros
    for(uint i=0; i<n; i++)
        printf("%.12lf ", erros[i]);
    
    //Libera memória
    free(erros);
    printf("\n");
}