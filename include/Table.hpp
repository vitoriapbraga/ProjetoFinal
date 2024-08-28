#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "Constantes.hpp"
#include "Coor.hpp"
#include "Jogador.hpp"
#include "Resultados.hpp"
#include "CadastroJogadores.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


using namespace std;

int JogarReversi(CadastroJogadores& cadastro);
class Table
{
private:
    std::vector<coor> moves;
    GameMode gameMode = CPU_VS_CPU;
    char board[SIZE][SIZE];
    bool guidance = true;
    int moveCount;
    char turn;
    char opponent;
    char userSide = BLACK;
    string jogador1;
    string jogador2; 

public:
    // Constructor
    Table();

    // bool return type functions in TableBool.cpp
    bool hasTileToFlip();
    bool isLegal(coor);
    bool isOnBoard(coor);
    bool checkFile();

    // game functions in JogarReversi.cpp
    int settings(CadastroJogadores& cadastro);
    void game(CadastroJogadores& cadastro);

    // void return type functions in TableVoid.cpp
    void printBoard();
    void flipTiles(coor);
    void marker();
    void saveMoves(string);
    void constructor();

    // int coor(user-defined) type functions in Coor.cpp
    coor userPlays();
    coor randomMoves();
    coor cpuPlays();
    coor fileMoves();
    coor filePlays();

    std::vector<coor> loadFromFile(string);
    GameMode getGameMode(); // getter function

    // getter functions
    char getBoard(coor);
    bool getGuidance();
    char getTurn();
    char getOpponent();
    char getUserSide();
                        //gets e sets definidos em Table.cpp
    // setter functions
    void setBoard(coor, char value);
    void setGuidance(bool);
    void setGameMode(GameMode);
    void setTurn(char);
    void switchTurn();
    void setUserSide(char);
};
#endif