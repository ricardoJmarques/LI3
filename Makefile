# source files.
SRC =  main.c API-Utils.c avl-strings.c API-Produtos.c API-Clientes.c API-Faturacao.c API-Filiais.c API-Ficheiros.c

OBJ = $(SRC:.cpp=.o)

OUT = GereVendas

# include directories
#INCLUDES = -I. 
 
# C compiler flags 
CCFLAGS = -I -Wall -pedantic --ansi -g

# compiler
CCC = gcc 

# libraries
#LIBS = -lm -lpapi

# dependencias
DEPS = API-Utils.h avl-strings.h API-Produtos.h API-Clientes.h API-Faturacao.h API-Filiais.h API-Ficheiros.c

.SUFFIXES: .cpp .c 

default: $(OUT)

.cpp.o:
	$(CCC) $(CCFLAGS) $(INCLUDES)  -c $< -o $@

.c.o:
	$(CCC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

$(OUT): $(OBJ)
	$(CCC) -o $(OUT) $(CCFLAGS) $(OBJ) $(LIBS) 

clean:
	rm -f *.o .a *~ Makefile.bak $(OUT)
