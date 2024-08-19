/**
 * @file Jogador.cpp
 * @brief Implementação da classe Jogador responsável por armazenar e gerenciar os dados de um jogador.
 */

#include "Jogador.hpp"
#include <iostream>  // Para std::endl
#include <fstream>   // Para std::ofstream e std::ifstream

using namespace std;

/**
 * @brief Construtor da classe Jogador.
 * 
 * @param apelido Apelido do jogador.
 * @param nome Nome do jogador.
 */
Jogador::Jogador(const string& apelido, const string& nome) : apelido(apelido), nome(nome) {}

/**
 * @brief Obtém o apelido do jogador.
 * 
 * @return string Apelido do jogador.
 */
string Jogador::getApelido() const {
    return apelido;
}

/**
 * @brief Obtém o nome do jogador.
 * 
 * @return string Nome do jogador.
 */
string Jogador::getNome() const {
    return nome;
}

/**
 * @brief Obtém as estatísticas de um jogo específico.
 * 
 * @param jogo Nome do jogo cujas estatísticas são solicitadas.
 * @return tuple<int, int, int> Tupla contendo o número de vitórias, derrotas e empates do jogador no jogo especificado.
 */
tuple<int, int, int> Jogador::getEstatisticas(const string& jogo) const {
    auto it = estatisticas.find(jogo);
    if (it != estatisticas.end()) {
        return it->second;
    }
    return make_tuple(0, 0, 0);
}

/**
 * @brief Adiciona uma vitória ao jogador em um jogo específico.
 * 
 * @param jogo Nome do jogo em que a vitória deve ser registrada.
 */
void Jogador::adicionarVitoria(const string& jogo) {
    auto& stats = estatisticas[jogo];
    get<0>(stats)++;
}

/**
 * @brief Adiciona uma derrota ao jogador em um jogo específico.
 * 
 * @param jogo Nome do jogo em que a derrota deve ser registrada.
 */
void Jogador::adicionarDerrota(const string& jogo) {
    auto& stats = estatisticas[jogo];
    get<1>(stats)++;
}

/**
 * @brief Adiciona um empate ao jogador em um jogo específico.
 * 
 * @param jogo Nome do jogo em que o empate deve ser registrado.
 */
void Jogador::adicionarEmpate(const string& jogo) {
    auto& stats = estatisticas[jogo];
    get<2>(stats)++;
}

/**
 * @brief Salva os dados do jogador em um arquivo.
 * 
 * @param arquivo Referência para o stream de saída onde os dados do jogador serão salvos.
 */
void Jogador::salvar(ofstream& arquivo) const {
    arquivo << apelido << " " << nome << endl;
    for (const auto& pair : estatisticas) {
        const string& jogo = pair.first;
        const auto& stats = pair.second;
        arquivo << jogo << " " << get<0>(stats) << " " << get<1>(stats) << " " << get<2>(stats) << endl;
    }
    arquivo << "END" << endl;
}

/**
 * @brief Carrega os dados do jogador de um arquivo.
 * 
 * @param arquivo Referência para o stream de entrada de onde os dados do jogador serão carregados.
 */
void Jogador::carregar(ifstream& arquivo) {
    string jogo;
    int vitorias, derrotas, empates;
    while (arquivo >> jogo && jogo != "END") {
        arquivo >> vitorias >> derrotas >> empates;
        estatisticas[jogo] = make_tuple(vitorias, derrotas, empates);
    }
}
