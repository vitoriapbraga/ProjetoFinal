#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Tabuleiro {
private:
    char grid[6][7]; 
public:
    Tabuleiro();
    bool fazerJogada(int coluna, char simbolo); // Realiza uma jogada
    void desfazerJogada(int coluna); // Reverte a jogada
    void exibir() const; // Exibe o tabuleiro
    bool verificarVitoria(char simbolo) const; // Verifica vitória
    bool estaCheio() const; // Verifica se o tabuleiro está cheio
    bool colunaValida(int coluna) const; // Verifica se a coluna está disponível para jogada
};

#endif 
