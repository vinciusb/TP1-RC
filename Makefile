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
C := gcc -g
TARGET_SERVER := server
TARGET_CLIENT := client

# Diretórios
BIN := ./bin/
INC := ./include/
OBJ := ./obj/
SRC := ./src/

# INCLUDES
LIST_INC := $(wildcard $(INC))
LIST_INC_FLAG := -I $(INC) -I $(INC)Server -I $(INC)Client
	
all:
	$(C) -c $(SRC)MineSweeper.c -o $(OBJ)MineSweeper.o $(LIST_INC_FLAG)
	$(C) -c $(SRC)Communication.c -o $(OBJ)Communication.o $(LIST_INC_FLAG)
	$(C) -c $(SRC)Server/Server.c -o $(OBJ)Server.o $(LIST_INC_FLAG)
	$(C) -c $(SRC)Server/main.c -o $(OBJ)main_server.o $(LIST_INC_FLAG)
	$(C) -c $(SRC)Client/Client.c -o $(OBJ)Client.o $(LIST_INC_FLAG)
	$(C) -c $(SRC)Client/main.c -o $(OBJ)main_client.o $(LIST_INC_FLAG)

	$(C) -o $(BIN)$(TARGET_SERVER) $(OBJ)MineSweeper.o $(OBJ)Communication.o $(OBJ)Server.o $(OBJ)main_server.o
	$(C) -o $(BIN)$(TARGET_CLIENT) $(OBJ)MineSweeper.o $(OBJ)Communication.o $(OBJ)Client.o $(OBJ)main_client.o

clean:
	rm $(BIN)* $(OBJ)*

proof:
	gprof $(BIN)$(TARGET) ./bin/gmon.out > ./tmp/analise.txt

rod:	
	rm ./rodadas/*.txt