#ifndef JOGADORIA_H
#define JOGADORIA_H

#include "JogadorLig4.h"
#include "Tabuleiro.h"
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class JogadorIA : public JogadorLig4 {
public:
    JogadorIA(const std::string& nome, char simbolo);
    
    int obterJogada(Tabuleiro& tabuleiro) override; 

private:
    int minimax(Tabuleiro& tabuleiro, int profundidade, bool maximizando, int alpha, int beta);
    bool temVencedor(const Tabuleiro& tabuleiro, char simbolo) const;
    int avaliarTabuleiro(const Tabuleiro& tabuleiro) const; 
};

#endif 


