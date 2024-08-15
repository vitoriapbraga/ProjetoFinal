#include "JogadorLig4.h"

JogadorLig4::JogadorLig4(const std::string& apelido, char simbolo) : Jogador(apelido, apelido), simbolo(simbolo) {}


char JogadorLig4::getSimbolo() const {
    return simbolo;
}