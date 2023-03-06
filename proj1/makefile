# GNU make: http://www.gnu.org/software/make/manual/make.html
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 
CFILE = $(shell find ./ -name "*.c")
CMAIN = $(shell find ./ -name "main.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntex.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

# parser: syntax $(filter-out $(LFO),$(OBJS))
# 	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) ${CMAIN} ${YFC} ./src/tree.c -lfl -ly -o parser 

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test
test:
	./src/parser ./test/test1.cmm
clean:
	rm -f parser lex.yy.c syntax.tab.c y.tab.h y.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f $(shell find ./ -name "*.o")
	rm -f $(shell find ./ -name "*.output")
	rm -f *~