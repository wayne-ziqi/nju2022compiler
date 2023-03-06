# GNU make: http://www.gnu.org/software/make/manual/make.html
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -g -std=c99

# 
CFILES = $(shell find ./ -name "*.c")
#CFILES = $(filter-out ./test/testlib.c, $(ALLCFILES))
LIBS = $(shell find ./src/lib -name "*.c")
# CMAIN = $(shell find ./ -name "main.c")
# CLIB = $(shell find ./src/lib -name "*.c") # data structures
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntex.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: syntax $(filter-out  $(LFO),$(OBJS))
	$(CC) -g -o parser $(filter-out $(LFO),$(OBJS)) -ly

# parser: syntax $(filter-out $(LFO),$(OBJS))
# 	$(CC) ${CMAIN} ${YFC} ${CLIB} -lfl -ly -o compiler

testlib:
	$(CC) $(LIBS) ./test/testlib.c -o testlib

syntax: lexical syntax-c
	$(CC) -g -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

.PHONY: clean test

test:
	./compiler ./test/01undefVar.cmm
clean:
	rm -f parser testlib lex.yy.c syntax.tab.c y.tab.h y.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f $(shell find ./ -name "*.o")
	rm -f *~