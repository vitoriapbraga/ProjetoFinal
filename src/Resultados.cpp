/**
 * @file Resultados.cpp
 * @brief Implementação da função ResultadoJogador que atualiza os resultados de um jogador em um determinado jogo.
 */

#include "Resultados.hpp"

/**
 * @brief Atualiza as estatísticas de um jogador com base no resultado de um jogo.
 * 
 * @param jogador1 Referência para o objeto Jogador cujas estatísticas serão atualizadas.
 * @param jogo Nome do jogo em que o resultado deve ser registrado.
 * @param resultado Inteiro representando o resultado do jogo: 3 para vitória, 0 para derrota, 1 para empate.
 */
void ResultadoJogador(Jogador& jogador1, const std::string& jogo, int resultado) {
    if (resultado == 3) {
        jogador1.adicionarVitoria(jogo);
    } else if (resultado == 0) {
        jogador1.adicionarDerrota(jogo);
    } else if (resultado == 1) {
        jogador1.adicionarEmpate(jogo);
    }
}
