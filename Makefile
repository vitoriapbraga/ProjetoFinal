CC = g++
CFLAGS = -std=c++11 -I$(SFML_DIR)/include
LDFLAGS = -L$(SFML_DIR)/lib -lsfml-system -lsfml-window -lsfml-graphics

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SFML_DIR = third-parties/SFML-2.6.1
INCLUDE_DIR = include

all: $(BIN_DIR)/main

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

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/CadastroJogadores.hpp $(INCLUDE_DIR)/Jogador.hpp  $(INCLUDE_DIR)/JogadorHumanoLig4.h $(INCLUDE_DIR)/JogadorIA.h $(INCLUDE_DIR)/JogadorLig4.h $(INCLUDE_DIR)/Jogo.h $(INCLUDE_DIR)/Resultados.hpp $(INCLUDE_DIR)/Tabuleiro.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/CadastroJogadores.o $(OBJ_DIR)/Jogador.o $(OBJ_DIR)/JogadorHumanoLig4.o $(OBJ_DIR)/JogadorIA.o $(OBJ_DIR)/JogadorLig4.o $(OBJ_DIR)/Jogo.o $(OBJ_DIR)/Resultados.o $(OBJ_DIR)/Tabuleiro.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o -o $(BIN_DIR)/main $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/main

.PHONY: all clean
