CFLAGS = -Wall -g -O0 # gerar "warnings" detalhados e infos de depuração
 
objs = perfSL.o EliminacaoGauss.o EliminacaoGaussSidel.o funcSL.o utils.o

# regra default (primeira regra)
all: perfSL
 
# regras de ligacao
perfSL:	$(objs)
 
# regras de compilação
perfSL.o:	perfSL.c
funcSL.o:	funcSL.c
EliminacaoGauss.o:	EliminacaoGauss.c
EliminacaoGaussSidel.o:	EliminacaoGaussSidel.c
utils.o:	utils.c

# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f perfSL
