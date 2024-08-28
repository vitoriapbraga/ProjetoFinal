#ifndef CADASTRO_JOGADORES_HPP
#define CADASTRO_JOGADORES_HPP

#include "Jogador.hpp"
#include <vector>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class CadastroJogadores {
private:
    vector<Jogador> jogadores;
    void carregarCadastro();
    void salvarCadastro() const;

public:
    CadastroJogadores();
    ~CadastroJogadores();

    bool cadastrarJogador(const string& apelido, const string& nome);
    bool removerJogador(const string& apelido);
    stringstream listarJogadores(char criterio) const;
    bool jogadorExiste(const string& apelido) const;
    Jogador* obterJogador(const string& apelido); 
};

#endif
