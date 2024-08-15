#include "Tabuleiro.h"
#include <iostream>

Tabuleiro::Tabuleiro() {
    // Inicializa o tabuleiro com espaços vazios
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            grid[i][j] = ' ';
        }
    }
}

bool Tabuleiro::fazerJogada(int coluna, char simbolo) {
    // Tenta inserir a jogada na coluna digitada
    if (coluna < 0 || coluna >= 7 || grid[0][coluna] != ' ') {
        return false; // Jogada inválida
    }
    
    for (int i = 5; i >= 0; --i) {
        if (grid[i][coluna] == ' ') {
            grid[i][coluna] = simbolo;
            return true;
        }
    }
    return false;
}

void Tabuleiro::desfazerJogada(int coluna) {
 
    for (int i = 0; i < 6; ++i) {
        if (grid[i][coluna] != ' ') {
            grid[i][coluna] = ' ';
            break;
        }
    }
}

void Tabuleiro::exibir() const {
    // Exibe o estado atual do tabuleiro
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            std::cout << "|" << grid[i][j];
        }
        std::cout << "|\n";
    }
    std::cout << " 1 2 3 4 5 6 7 \n";
}

bool Tabuleiro::verificarVitoria(char simbolo) const {
    // Verifica todas as direções possíveis para uma vitória

    // Verifica linhas
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j] == simbolo && grid[i][j+1] == simbolo &&
                grid[i][j+2] == simbolo && grid[i][j+3] == simbolo) {
                return true;
            }
        }
    }

    // Verifica colunas
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (grid[i][j] == simbolo && grid[i+1][j] == simbolo &&
                grid[i+2][j] == simbolo && grid[i+3][j] == simbolo) {
                return true;
            }
        }
    }

    // Verifica diagonais (cima para baixo)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j] == simbolo && grid[i+1][j+1] == simbolo &&
                grid[i+2][j+2] == simbolo && grid[i+3][j+3] == simbolo) {
                return true;
            }
        }
    }

    // Verifica diagonais (baixo para cima)
    for (int i = 3; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (grid[i][j] == simbolo && grid[i-1][j+1] == simbolo &&
                grid[i-2][j+2] == simbolo && grid[i-3][j+3] == simbolo) {
                return true;
            }
        }
    }

    return false;
}

bool Tabuleiro::estaCheio() const {
    // Verifica se o tabuleiro está cheio
    for (int j = 0; j < 7; ++j) {
        if (grid[0][j] == ' ') {
            return false;
        }
    }
    return true;
}

bool Tabuleiro::colunaValida(int coluna) const {
    // Verifica se a coluna está disponível para jogada
    return grid[0][coluna] == ' ';
}
