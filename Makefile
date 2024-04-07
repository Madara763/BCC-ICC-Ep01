#gerar "warnings" detalhados e infos de depuração
CFLAGS = -O0 -I${LIKWID_HOME}/include -DLIKWID_PERFMON
LDLIBS= -L${LIKWID_HOME}/lib -llikwid
objs = perfSL.o EliminacaoGauss.o EliminacaoGaussSidel.o funcSL.o utils.o

# regra default (primeira regra)
all:	perfSL
 
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
