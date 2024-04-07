Aluno: Davi Garcia Lazzarin 
GRR - 20204398
Trabalho de Introdução a Computação Cientifica EP-01

Divisão de Código:
EliminaçãoGauss (.c/.h) - Implementa os metodos de eliminação de gauss classico e 3-diagonal
EliminaçãoGaussSidel (.c/.h) - Implementa os metodos de eliminação de gaussSidel classico e 3-diagonal
funcSL (.c/.h) - Implementa funções auxiliares de manipulação de SL utilizadas na função main.
utils (.c/.h) - Biblioteca fornecida pelo professor com alterações
pefSL.c - Contem a função main
Makefile - Makefile com regras para o LIKIWID

Script Shell:
perfSL_DGL20.sh - Scrit chama o make com -B, executa o perfSL com o sistema linear de entrada do SL.in
e redireciona a sáida com o LIKWID para FLOPS_DP_perfSL.log eno fim chama o make clean para limpar os .o

Arquivo de entrada:
SL.in: Contém uma entrada no padrão 
n
(0,0) (0,1) (0,2) (0,n-1) B0
(1,0) (1,1) (1,2) (1,n-1) B1
(2,0) (2,1) (2,2) (2,n-1) B2
(n-1,0) (n-1,1) (n-1,2) (n-1,n-1) Bn-1

Arquivo de Saída:
FLOPS_DP_perfSL.log
Arquivo gerado pelo LIKWID com a saída do perfSL e com o mapeamento das regiões configuradas
sendo elas EG_CLASSICO, EG_3_DIAGONAL, GS_CLASSICO, GS_3_CLASSICO


Observações sobre o código:

Sobre os GS: Como os SL dados como exemplo não possuiam as soluções para cada método não consegui verificar se os erros 
dos metodos de GaussSidel convergiam corretamente, em alguns casos que eu criei o resultado era exato
mas o calculo dos erros estavam errados, gerando o residuo errado, mas com o algoritmo convergindo pelo
total de iterações, jé em outros as variaveis e os residuos apresentados estavam corretos.

Sobre o pivoteamento: Ao aplicar EG e GS classicos com pivoteamento parcial em matrizes já tridiagonalizadas o resultado 
gerado era completamente errado, ao retirar o pivoteamento o resultado era correto, não identifiquei o motivo dessa inconsistencia. 

Sobre o LIKWID: Os marcadores de monitoramento foram colocados dentro das funções nas bibliotecas vizando monitorar apenas o trecho 
do algoritmo do método, sem contar coisas como tempo de alocação e chamada de funções.