/**
 * @file CadastroJogadores.cpp
 * @brief Implementação da classe CadastroJogadores responsável pelo cadastro e gerenciamento de jogadores.
 */

#include "CadastroJogadores.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * @brief Construtor da classe CadastroJogadores.
 * 
 * Inicializa a classe carregando os jogadores do arquivo.
 */
CadastroJogadores::CadastroJogadores() {
    carregarCadastro();
}

/**
 * @brief Destrutor da classe CadastroJogadores.
 * 
 * Salva o cadastro de jogadores no arquivo antes de destruir o objeto.
 */
CadastroJogadores::~CadastroJogadores() {
    salvarCadastro();
}

/**
 * @brief Carrega os jogadores a partir de um arquivo.
 * 
 * O método lê o arquivo "cadastro_jogadores.txt" e carrega os jogadores registrados no vetor `jogadores`.
 */
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

/**
 * @brief Salva o cadastro de jogadores no arquivo.
 * 
 * O método escreve os dados dos jogadores no arquivo "cadastro_jogadores.txt".
 */
void CadastroJogadores::salvarCadastro() const {
    ofstream arquivo("cadastro_jogadores.txt");
    if (arquivo.is_open()) {
        for (const auto& jogador : jogadores) {
            jogador.salvar(arquivo);
        }
        arquivo.close();
    }
}

/**
 * @brief Cadastra um novo jogador.
 * 
 * @param apelido Apelido do jogador a ser cadastrado.
 * @param nome Nome do jogador a ser cadastrado.
 * @return true Se o jogador foi cadastrado com sucesso.
 * @return false Se já existe um jogador com o mesmo apelido.
 */
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

/**
 * @brief Remove um jogador do cadastro.
 * 
 * @param apelido Apelido do jogador a ser removido.
 * @return true Se o jogador foi removido com sucesso.
 * @return false Se o jogador não foi encontrado.
 */
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

/**
 * @brief Lista os jogadores cadastrados.
 * 
 * @param criterio Critério de ordenação: 'A' para ordenar por apelido, 'N' para ordenar por nome.
 */
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
        cout << "Apelido: " << jogador.getApelido() << "\tNome: " << jogador.getNome() << "\n" << endl;

        auto REVERSI = jogador.getEstatisticas("REVERSI");
        auto LIG4 = jogador.getEstatisticas("LIG4");
        
        cout << "\t  LIG4  - V: " << get<0>(LIG4) << " D: " << get<1>(LIG4) << " E: " << get<2>(LIG4) << "\n" << endl;
        cout << "\tREVERSI - V: " << get<0>(REVERSI) << " D: " << get<1>(REVERSI) << " E: " << get<2>(REVERSI) << "\n" << endl;
    }
}

/**
 * @brief Verifica se um jogador existe no cadastro.
 * 
 * @param apelido Apelido do jogador a ser verificado.
 * @return true Se o jogador existe.
 * @return false Se o jogador não existe.
 */
bool CadastroJogadores::jogadorExiste(const string& apelido) const {
    for (const auto& jogador : jogadores) {
        if (jogador.getApelido() == apelido) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Obtém um jogador pelo apelido.
 * 
 * @param apelido Apelido do jogador a ser obtido.
 * @return Jogador* Ponteiro para o jogador, ou nullptr se não for encontrado.
 */
Jogador* CadastroJogadores::obterJogador(const string& apelido) {
    for (auto& jogador : jogadores) {
        if (jogador.getApelido() == apelido) {
            return &jogador;
        }
    }
    return nullptr;
}
