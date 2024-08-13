#include "CadastroJogadores.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

CadastroJogadores::CadastroJogadores() {
    carregarCadastro();
}

CadastroJogadores::~CadastroJogadores() {
    salvarCadastro();
}


void CadastroJogadores::carregarCadastro() {
    ifstream arquivo("cadastro_jogadores.txt");
    if (arquivo.is_open()) {
        string apelido, nome;
        while (arquivo >> apelido >> nome) {
            Jogador jogador(apelido, nome);
            jogador.carregar(arquivo);
            jogadores.push_back(jogador);
        }
        arquivo.close();
    }
}

// Salva o cadastrono arquivo
void CadastroJogadores::salvarCadastro() const {
    ofstream arquivo("cadastro_jogadores.txt");
    if (arquivo.is_open()) {
        for (const auto& jogador : jogadores) {
            jogador.salvar(arquivo);
        }
        arquivo.close();
    }
}


bool CadastroJogadores::cadastrarJogador(const string& apelido, const string& nome) {
    for (const auto& jogador : jogadores) {
        if (jogador.getApelido() == apelido) {
            cout << "ERRO: apelido ja existente" << endl;
            return false;
        }
    }
    jogadores.push_back(Jogador(apelido, nome));
    cout << "Jogador " << apelido << " cadastrado com sucesso" << endl;
    return true;
}


bool CadastroJogadores::removerJogador(const string& apelido) {
    auto it = find_if(jogadores.begin(), jogadores.end(), [&](const Jogador& jogador) {
        return jogador.getApelido() == apelido;
    });
    if (it != jogadores.end()) {
        jogadores.erase(it);
        cout << "Jogador " << apelido << " removido com sucesso" << endl;
        return true;
    }
    cout << "ERRO: jogador inexistente" << endl;
    return false;
}


void CadastroJogadores::listarJogadores(char criterio) const {
    vector<Jogador> VetorJogadores = jogadores;
    if (criterio == 'A') {
        sort(VetorJogadores.begin(), VetorJogadores.end(), [](const Jogador& a, const Jogador& b) {
            return a.getApelido() < b.getApelido();
        });
    } else if (criterio == 'N') {
        sort(VetorJogadores.begin(), VetorJogadores.end(), [](const Jogador& a, const Jogador& b) {
            return a.getNome() < b.getNome();
        });
    }

    for (const auto& jogador : VetorJogadores) {
        cout << "Apelido: "<<jogador.getApelido() << "\tNome: " << jogador.getNome() << "\n" << endl;

        auto REVERSI = jogador.getEstatisticas("REVERSI");
        auto LIG4 = jogador.getEstatisticas("LIG4");
        
        
        cout << "\t  LIG4  - V: " << get<0>(LIG4) << " D: " << get<1>(LIG4) << " E: " << get<2>(LIG4) << "\n" << endl;
        cout << "\tREVERSI - V: " << get<0>(REVERSI) << " D: " << get<1>(REVERSI) << " E: " << get<2>(REVERSI) << "\n" << endl;
    
    
    
    }
}


bool CadastroJogadores::jogadorExiste(const string& apelido) const {
    for (const auto& jogador : jogadores) {
        if (jogador.getApelido() == apelido) {
            return true;
        }
    }
    return false;
}

// Retorna um ponteiro para um jogador 
Jogador* CadastroJogadores::obterJogador(const string& apelido) {
    for (auto& jogador : jogadores) {
        if (jogador.getApelido() == apelido) {
            return &jogador;
        }
    }
    return nullptr;
} 