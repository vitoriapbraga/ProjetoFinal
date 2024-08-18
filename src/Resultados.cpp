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
