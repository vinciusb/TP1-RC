#-------------------------------------------------------------------------------
# Arquivo      : Makefile
# Conteudo     : Implementação de campo minado server-client
# Autor        : Vinícius Braga Freire (vinicius.braga@dcc.ufmg.br)
# Historico    : 2023-09-19 - arquivo criado
#-------------------------------------------------------------------------------
# Opções	: make all - compila tudo
#			: make clean - remove objetos e executável
#-------------------------------------------------------------------------------
#-pg for gprof
CPP := g++ -g -std=c++17
TARGET := tp01

# Diretórios
BIN := ./bin/
INC := ./include/
OBJ := ./obj/
SRC := ./src/

LIST_SRC_CPP := $(wildcard $(SRC)*.cpp)
LIST_OBJ := $(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(LIST_SRC_CPP))

$(OBJ)%.o: $(SRC)%.cpp
	$(CPP) -c $< -o $@ -I $(INC)
	
all: $(LIST_OBJ)
	$(CPP) -o $(TARGET) $(LIST_OBJ)

clean:
	rm $(BIN) $(LIST_OBJ) 

proof:
	gprof $(BIN)$(TARGET) ./bin/gmon.out > ./tmp/analise.txt

rod:	
	rm ./rodadas/*.txt