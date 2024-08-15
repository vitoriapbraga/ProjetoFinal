#include "Resultados.hpp"

//Para adcionar apenas 1 jogador
void ResultadoJogador(Jogador& jogador1, const std::string& jogo, int resultado) {
    if (resultado == 3) {
        jogador1.adicionarVitoria(jogo);
    } else if (resultado == 0) {
        jogador1.adicionarDerrota(jogo);
    } else if (resultado == 1) {
        jogador1.adicionarEmpate(jogo);
    }
}

void ResultadoHumanoHumano(Jogador& jogador1, Jogador& jogador2, const std::string& jogo, int resultado) {
    if (resultado == 3) {
        jogador1.adicionarVitoria(jogo); //jogador 1 ganha
        jogador2.adicionarDerrota(jogo);
    } else if (resultado == 0) {
        jogador1.adicionarDerrota(jogo); //jogador 1 perde
        jogador2.adicionarVitoria(jogo);
    } else if (resultado == 1) {
        jogador1.adicionarEmpate(jogo);
        jogador2.adicionarEmpate(jogo);
    }
}