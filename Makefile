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
TARGET := server

# Diretórios
BIN := ./bin/
INC := ./include/*
# Server ./include/Client
OBJ := ./obj/
SRC := ./src/**

# INCLUDES
LIST_INC := $(wildcard $(INC))
LIST_INC_FLAG := $(patsubst %, -I %, $(LIST_INC))
# SOURCE FILES
LIST_SRC_C := $(wildcard $(SRC)*.c)
LIST_OBJ := $(patsubst $(SRC)%.c, $(OBJ)%.o, $(LIST_SRC_C))

SOURCES := $(shell find $(SOURCEDIR) -name '*.c')

$(OBJ)%.o: $(SRC)%.c
	$(C) -c $< -o $@ $(LIST_INC_FLAG)
	
all: $(LIST_OBJ)
	@echo $(SOURCES)
	$(C) -o $(TARGET) $(LIST_OBJ)

clean:
	rm $(BIN) $(LIST_OBJ) 

proof:
	gprof $(BIN)$(TARGET) ./bin/gmon.out > ./tmp/analise.txt

rod:	
	rm ./rodadas/*.txt