#include "JogadorIA.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

JogadorIA::JogadorIA(const std::string& nome, char simbolo) : JogadorLig4(nome, simbolo) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int JogadorIA::obterJogada(Tabuleiro& tabuleiro) {
    int melhorJogada = -1;
    int melhorValor = std::numeric_limits<int>::min();

    // Percorre todas as colunas para encontrar a melhor jogada
    for (int coluna = 0; coluna < 7; ++coluna) {
        if (tabuleiro.colunaValida(coluna)) {
            tabuleiro.fazerJogada(coluna, simbolo);
            int valor = minimax(tabuleiro, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            tabuleiro.desfazerJogada(coluna);
            if (valor > melhorValor) {
                melhorValor = valor;
                melhorJogada = coluna;
            }
        }
    }

    // Se não houver jogadas válidas, escolha a primeira coluna válida
    if (melhorJogada == -1) {
        for (int coluna = 0; coluna < 7; ++coluna) {
            if (tabuleiro.colunaValida(coluna)) {
                melhorJogada = coluna;
                break;
            }
        }
    }

    std::cout << apelido << " (" << simbolo << ") joga na coluna " << melhorJogada + 1 << std::endl;
    return melhorJogada;
}

int JogadorIA::minimax(Tabuleiro& tabuleiro, int profundidade, bool maximizando, int alpha, int beta) {
    // Verifica as condições de término
    int avaliacao = avaliarTabuleiro(tabuleiro);
    if (avaliacao == 10 || avaliacao == -10 || tabuleiro.estaCheio() || profundidade == 5) {
        return avaliacao;
    }

    if (maximizando) {
        int melhorValor = std::numeric_limits<int>::min();
        for (int coluna = 0; coluna < 7; ++coluna) {
            if (tabuleiro.colunaValida(coluna)) {
                tabuleiro.fazerJogada(coluna, simbolo);
                int valor = minimax(tabuleiro, profundidade + 1, false, alpha, beta);
                tabuleiro.desfazerJogada(coluna);
                melhorValor = std::max(melhorValor, valor);
                alpha = std::max(alpha, valor);
                if (beta <= alpha) {
                    break; // Poda beta
                }
            }
        }
        return melhorValor;
    } else {
        int melhorValor = std::numeric_limits<int>::max();
        char oponenteSimbolo = simbolo == 'X' ? 'O' : 'X';
        for (int coluna = 0; coluna < 7; ++coluna) {
            if (tabuleiro.colunaValida(coluna)) {
                tabuleiro.fazerJogada(coluna, oponenteSimbolo);
                int valor = minimax(tabuleiro, profundidade + 1, true, alpha, beta);
                tabuleiro.desfazerJogada(coluna);
                melhorValor = std::min(melhorValor, valor);
                beta = std::min(beta, valor);
                if (beta <= alpha) {
                    break; // Poda alpha
                }
            }
        }
        return melhorValor;
    }
}

bool JogadorIA::temVencedor(const Tabuleiro& tabuleiro, char simbolo) const {
    return tabuleiro.verificarVitoria(simbolo);
}

int JogadorIA::avaliarTabuleiro(const Tabuleiro& tabuleiro) const {
    // Avalia a posição atual do tabuleiro para o jogador IA
    if (temVencedor(tabuleiro, simbolo)) {
        return 10; // Vitória do IA
    } else if (temVencedor(tabuleiro, simbolo == 'X' ? 'O' : 'X')) {
        return -10; // Vitória do oponente
    } else {
        return 0; // Nenhuma vitória
    }
}
