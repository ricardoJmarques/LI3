# source files.
SRC =  main.c API-Clientes.c API-Produtos.c API-Vendas.c API-Utils.c

OBJ = $(SRC:.cpp=.o)

OUT = geshiper

# include directories
#INCLUDES = -I. 
 
# C compiler flags 
CCFLAGS = -I -Wall -pedantic --ansi

# compiler
CCC = gcc 

# libraries
#LIBS = -lm -lpapi

# dependencias
DEPS = API-Clientes.h API-Produtos.h API-Vendas.h API-Utils.h

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
