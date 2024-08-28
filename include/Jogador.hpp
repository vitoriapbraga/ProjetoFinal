#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <tuple>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

class Jogador {
protected:   
    string apelido;
    string nome;
    map<string, tuple<int, int, int>> estatisticas; // NomedoJogo (Vitórias, Derrotas, Empates)

public:
    Jogador(const string& apelido, const string& nome);

    virtual string getApelido() const;
    string getNome() const;
    tuple<int, int, int> getEstatisticas(const string& jogo) const;

    void adicionarVitoria(const string& jogo);
    void adicionarDerrota(const string& jogo);
    void adicionarEmpate(const string& jogo);

    void salvar(ofstream& arquivo) const;
    void carregar(ifstream& arquivo);
};

#endif