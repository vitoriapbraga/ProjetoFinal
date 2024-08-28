#ifndef JOGADORHUMANO_H
#define JOGADORHUMANO_H

#include "JogadorLig4.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class JogadorHumano : public JogadorLig4 {
public:
    JogadorHumano(const std::string& apelido, char simbolo);
    int obterJogada(Tabuleiro& tabuleiro) override;
};

#endif