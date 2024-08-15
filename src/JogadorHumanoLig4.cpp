#include "JogadorHumanoLig4.h"
#include <iostream>

JogadorHumano::JogadorHumano(const std::string& apelido, char simbolo) : JogadorLig4(apelido, simbolo) {}

int JogadorHumano::obterJogada(Tabuleiro& tabuleiro) {
    int jogada;
    std::cout << apelido << " sua vez (" << simbolo << "), digite sua jogada (1-7): ";
    std::cin >> jogada;
    return jogada - 1; 
}