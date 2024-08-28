
#ifndef JOGADORLIG4_H
#define JOGADORLIG4_H

#include "Jogador.hpp"
#include "Tabuleiro.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class JogadorLig4 : public Jogador {
protected:
    char simbolo;

public:
    JogadorLig4(const std::string& apelido, char simbolo);
    virtual ~JogadorLig4() = default;
    char getSimbolo() const;
    virtual int obterJogada(Tabuleiro& tabuleiro) = 0;

};

#endif
