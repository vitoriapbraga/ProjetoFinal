#include "Table.hpp"

/**

Essencialmente, a classe Table gerencia o estado do tabuleiro de um jogo, incluindo a configuração e 
obtenção de valores das células do tabuleiro, alternância de turnos, e
configuração do modo de jogo, orientação e lado do usuário.

 */


Table::Table()
{
    constructor();
}

// bool return type functions ////////////////////////////////////////////////////

//Estão no TableBool.cpp


// Getters
char Table::getBoard(coor c)
{
    try
    {
        if (isOnBoard(c))
            return board[c.row][c.col];
        else
            throw "getBoard: Linha ou coluna inválida\n";
    }
    catch (const char *msg)
    {
        std::cerr << msg;
    }
    return '\0';
}

bool Table::getGuidance()
{
    return this->guidance;
}

GameMode Table::getGameMode()
{
    return this->gameMode;
}

char Table::getTurn()
{
    return this->turn;
}

char Table::getOpponent()
{
    return this->opponent;
}

char Table::getUserSide()
{
    return this->userSide;
}

// Setters
void Table::setBoard(coor c, char value)
{
    try
    {
        if (isOnBoard(c) && (value == BLACK || value == WHITE || value == EMPTY || value == LEGAL))
            board[c.row][c.col] = value;
        else
            throw "setBoard: Linha, coluna ou valor inválido\n";
    }
    catch (const char *msg)
    {
        std::cerr << msg;
    }
}

void Table::setGuidance(bool m)
{
    this->guidance = m;
}

void Table::setGameMode(GameMode gm)
{
    try
    {
        if (gm == HUMANO_VS_HUMANO || gm == HUMANO_VS_CPU || gm == CPU_VS_CPU || gm == LOAD_GAME)
            this->gameMode = gm;
        else
            throw "setGameMode: Modo de jogo inválido\n";
    }
    catch (const char *msg)
    {
        std::cerr << msg;
    }
}

void Table::setTurn(char t)
{
    try
    {
        if (t == BLACK)
        {
            this->turn = BLACK;
            this->opponent = WHITE;
        }
        else if (t == WHITE)
        {
            this->turn = WHITE;
            this->opponent = BLACK;
        }
        else
            throw "setTurn: Turno inválido\n";
    }
    catch (const char *msg)
    {
        std::cerr << msg;
    }
}

void Table::switchTurn()
{
    if (getTurn() == BLACK)
    {
        setTurn(WHITE);
    }
    else
    {
        setTurn(BLACK);
    }
    // atualizar movimentos legais após alternar turnos
    marker();
}

void Table::setUserSide(char s)
{
    try
    {
        if (s == BLACK || s == WHITE)
            this->userSide = s;
        else
            throw "setUserSide: Lado inválido\n";
    }
    catch (const char *msg)
    {
        std::cerr << msg;
    }
}
