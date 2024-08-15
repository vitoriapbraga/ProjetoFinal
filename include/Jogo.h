#ifndef JOGO_H
#define JOGO_H
#include "JogadorLig4.h"
#include "Tabuleiro.h"
#include "CadastroJogadores.hpp"

class Jogo {
private:
    JogadorLig4* jogador1;
    JogadorLig4* jogador2;
    Tabuleiro tabuleiro;
    
    char simbolo; // 'X' ou 'O'

public:
    Jogo(JogadorLig4* j1, JogadorLig4* j2);
    ~Jogo();

    void jogar(CadastroJogadores& cadastro);
};

int JogarLigue4(CadastroJogadores& cadastro);

#endif 
