#ifndef JOGADORHUMANO_H
#define JOGADORHUMANO_H

#include "JogadorLig4.h"

class JogadorHumano : public JogadorLig4 {
public:
    JogadorHumano(const std::string& apelido, char simbolo);
    int obterJogada(Tabuleiro& tabuleiro) override;
};

#endif