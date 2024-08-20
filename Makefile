CC = g++
CFLAGS = -std=c++11 -I$(SFML_DIR)/include
SFML_DIR = third-parties/SFML-2.6.1
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Detectar o sistema operacional
ifeq ($(OS),Windows_NT)
    UNAME_S := Windows
else
    UNAME_S := $(shell uname -s)
endif

# Definir flags e bibliotecas específicas para Raylib
ifeq ($(UNAME_S),Linux)
    CFLAGS += -Ithirdy_party -Iinclude
    LDFLAGS += -Llib/Linux -lraylib -lGL -lm -lpthread -ldl -lrt -lgcov
endif

ifeq ($(UNAME_S),Darwin)
    CFLAGS += -Ithirdy_party -Iinclude
    LDFLAGS += -Llib/macOS -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
endif

ifeq ($(UNAME_S),Windows)
    CFLAGS += -Ithirdy_party -Iinclude
    LDFLAGS += -Llib/Windows -lraylib -lopengl32 -lgdi32 -lwinmm
endif

# Objetos comuns a todos os sistemas operacionais
OBJ_FILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/CadastroJogadores.o $(OBJ_DIR)/Jogador.o \
            $(OBJ_DIR)/JogadorHumanoLig4.o $(OBJ_DIR)/JogadorIA.o $(OBJ_DIR)/JogadorLig4.o \
            $(OBJ_DIR)/Jogo.o $(OBJ_DIR)/Resultados.o $(OBJ_DIR)/Tabuleiro.o $(OBJ_DIR)/MenuInicial.o \
            $(OBJ_DIR)/MenuJogadores.o $(OBJ_DIR)/MenuJogos.o $(OBJ_DIR)/Coor.o \
             $(OBJ_DIR)/Table.o $(OBJ_DIR)/JogarReversi.o $(OBJ_DIR)/TableVoid.o \
             $(OBJ_DIR)/TableBool.o

# Adicionar mancala.o apenas se for Linux ou macOS
ifeq ($(UNAME_S),Linux)
    OBJ_FILES += $(OBJ_DIR)/mancala.o
endif

ifeq ($(UNAME_S),Darwin)
    OBJ_FILES += $(OBJ_DIR)/mancala.o
endif

all: $(BIN_DIR)/main

# Compilar mancala apenas se for Linux ou macOS
ifeq ($(UNAME_S),Linux)
$(OBJ_DIR)/mancala.o: $(INCLUDE_DIR)/mancala.hpp $(SRC_DIR)/mancala.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mancala.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/mancala.o
endif

ifeq ($(UNAME_S),Darwin)
$(OBJ_DIR)/mancala.o: $(INCLUDE_DIR)/mancala.hpp $(SRC_DIR)/mancala.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/mancala.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/mancala.o
endif

# Compilação do main
$(BIN_DIR)/main: $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(BIN_DIR)/main $(LDFLAGS)

# Outras regras de compilação
$(OBJ_DIR)/CadastroJogadores.o: $(INCLUDE_DIR)/CadastroJogadores.hpp $(SRC_DIR)/CadastroJogadores.cpp $(INCLUDE_DIR)/Jogador.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CadastroJogadores.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/CadastroJogadores.o

$(OBJ_DIR)/Jogador.o: $(INCLUDE_DIR)/Jogador.hpp $(SRC_DIR)/Jogador.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Jogador.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/Jogador.o

$(OBJ_DIR)/JogadorHumanoLig4.o: $(INCLUDE_DIR)/JogadorHumanoLig4.h $(SRC_DIR)/JogadorHumanoLig4.cpp $(INCLUDE_DIR)/JogadorLig4.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/JogadorHumanoLig4.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/JogadorHumanoLig4.o

$(OBJ_DIR)/JogadorIA.o: $(INCLUDE_DIR)/JogadorIA.h $(SRC_DIR)/JogadorIA.cpp $(INCLUDE_DIR)/JogadorLig4.h $(INCLUDE_DIR)/Tabuleiro.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/JogadorIA.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/JogadorIA.o

$(OBJ_DIR)/JogadorLig4.o: $(INCLUDE_DIR)/JogadorLig4.h $(SRC_DIR)/JogadorLig4.cpp $(INCLUDE_DIR)/Jogador.hpp $(INCLUDE_DIR)/Tabuleiro.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/JogadorLig4.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/JogadorLig4.o

$(OBJ_DIR)/Jogo.o: $(INCLUDE_DIR)/Jogo.h $(SRC_DIR)/Jogo.cpp $(INCLUDE_DIR)/JogadorLig4.h $(INCLUDE_DIR)/Tabuleiro.h $(INCLUDE_DIR)/CadastroJogadores.hpp $(INCLUDE_DIR)/JogadorHumanoLig4.h $(INCLUDE_DIR)/JogadorIA.h $(INCLUDE_DIR)/Resultados.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Jogo.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/Jogo.o

$(OBJ_DIR)/Resultados.o: $(INCLUDE_DIR)/Resultados.hpp $(SRC_DIR)/Resultados.cpp $(INCLUDE_DIR)/Jogador.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Resultados.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/Resultados.o

$(OBJ_DIR)/Tabuleiro.o: $(INCLUDE_DIR)/Tabuleiro.h $(SRC_DIR)/Tabuleiro.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Tabuleiro.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/Tabuleiro.o

$(OBJ_DIR)/MenuInicial.o: $(SRC_DIR)/MenuInicial.cpp $(INCLUDE_DIR)/MenuInicial.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MenuInicial.cpp -o $(OBJ_DIR)/MenuInicial.o

$(OBJ_DIR)/MenuJogadores.o: $(SRC_DIR)/MenuJogadores.cpp $(INCLUDE_DIR)/MenuJogadores.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MenuJogadores.cpp -o $(OBJ_DIR)/MenuJogadores.o

$(OBJ_DIR)/MenuJogos.o: $(SRC_DIR)/MenuJogos.cpp $(INCLUDE_DIR)/MenuJogos.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/MenuJogos.cpp -o $(OBJ_DIR)/MenuJogos.o

$(OBJ_DIR)/Coor.o: $(SRC_DIR)/Coor.cpp $(INCLUDE_DIR)/Coor.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Coor.cpp -o $(OBJ_DIR)/Coor.o

$(OBJ_DIR)/JogarReversi.o: $(SRC_DIR)/JogarReversi.cpp $(INCLUDE_DIR)/Table.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/JogarReversi.cpp -o $(OBJ_DIR)/JogarReversi.o

$(OBJ_DIR)/Table.o: $(SRC_DIR)/Table.cpp $(INCLUDE_DIR)/Table.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Table.cpp -o $(OBJ_DIR)/Table.o

$(OBJ_DIR)/TableBool.o: $(SRC_DIR)/TableBool.cpp $(INCLUDE_DIR)/Table.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/TableBool.cpp -o $(OBJ_DIR)/TableBool.o

$(OBJ_DIR)/TableVoid.o: $(SRC_DIR)/TableVoid.cpp $(INCLUDE_DIR)/Table.hpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/TableVoid.cpp -o $(OBJ_DIR)/TableVoid.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Constantes.hpp $(INCLUDE_DIR)/settings.hpp $(INCLUDE_DIR)/Coor.hpp $(INCLUDE_DIR)/Table.hpp $(INCLUDE_DIR)/MenuInicial.hpp $(INCLUDE_DIR)/MenuJogadores.hpp $(INCLUDE_DIR)/MenuJogos.hpp $(INCLUDE_DIR)/CadastroJogadores.hpp $(INCLUDE_DIR)/Jogador.hpp  $(INCLUDE_DIR)/JogadorHumanoLig4.h $(INCLUDE_DIR)/JogadorIA.h $(INCLUDE_DIR)/JogadorLig4.h $(INCLUDE_DIR)/Jogo.h $(INCLUDE_DIR)/Resultados.hpp $(INCLUDE_DIR)/Tabuleiro.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

run:
	./$(BIN_DIR)/main

clean:
ifeq ($(UNAME_S),Linux)
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/main
endif

ifeq ($(UNAME_S),Darwin)
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/main
endif

ifeq ($(UNAME_S),Windows)
	del /Q $(OBJ_DIR)\*.o $(BIN_DIR)\main.exe
endif
