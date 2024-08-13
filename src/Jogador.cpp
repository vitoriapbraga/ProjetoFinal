#include "Jogador.hpp"
#include <iostream>  // Para std::endl
#include <fstream>   // Para std::ofstream e std::ifstream

using namespace std;


Jogador::Jogador(const string& apelido, const string& nome) : apelido(apelido), nome(nome) {}


string Jogador::getApelido() const {
    return apelido;
}


string Jogador::getNome() const {
    return nome;
}


tuple<int, int, int> Jogador::getEstatisticas(const string& jogo) const {
    auto it = estatisticas.find(jogo);
    if (it != estatisticas.end()) {
        return it->second;
    }
    return make_tuple(0, 0, 0);
}


void Jogador::adicionarVitoria(const string& jogo) {
    auto& stats = estatisticas[jogo];
    get<0>(stats)++;
}


void Jogador::adicionarDerrota(const string& jogo) {
    auto& stats = estatisticas[jogo];
    get<1>(stats)++;
}


void Jogador::adicionarEmpate(const string& jogo) {
    auto& stats = estatisticas[jogo];
    get<2>(stats)++;
}

// Salva os dados do jogador no arquivo
void Jogador::salvar(ofstream& arquivo) const {
    arquivo << apelido << " " << nome << endl;
    for (const auto& pair : estatisticas) {
        const string& jogo = pair.first;
        const auto& stats = pair.second;
        arquivo << jogo << " " << get<0>(stats) << " " << get<1>(stats) << " " << get<2>(stats) << endl;
    }
    arquivo << "END" << endl;
}

// Carrega os dados do jogador do arquivo
void Jogador::carregar(ifstream& arquivo) {
    string jogo;
    int vitorias, derrotas, empates;
    while (arquivo >> jogo && jogo != "END") {
        arquivo >> vitorias >> derrotas >> empates;
        estatisticas[jogo] = make_tuple(vitorias, derrotas, empates);
    }
}
