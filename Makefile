# source files.
SRC =  main.c API-Utils.c avl-strings.c API-Clientes.c API-Produtos.c API-Facturacao.c
#API-Vendas.c 

OBJ = $(SRC:.cpp=.o)

OUT = GereVendas

# include directories
#INCLUDES = -I. 
 
# C compiler flags 
CCFLAGS = -I -Wall -pedantic --ansi

# compiler
CCC = gcc 

# libraries
#LIBS = -lm -lpapi

# dependencias
DEPS = API-Utils.h avl-strings.h API-Clientes.h API-Produtos.h API-Facturacao.h
#API-Vendas.h

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
