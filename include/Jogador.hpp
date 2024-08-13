#ifndef JOGADOR_HPP
#define JOGADOR_HPP

#include <string>
#include <tuple>
#include <map>

using namespace std;

class Jogador {
protected:   //permite que as classes filhas tenham acesso
    string apelido;
    string nome;
    map<string, tuple<int, int, int>> estatisticas; // NomedoJogo (Vitórias, Derrotas, Empates)

public:
    Jogador(const string& apelido, const string& nome);

    virtual string getApelido() const;
    string getNome() const;
    tuple<int, int, int> getEstatisticas(const string& jogo) const;

    virtual void adicionarVitoria(const string& jogo);
    virtual void adicionarDerrota(const string& jogo);
    virtual void adicionarEmpate(const string& jogo);

    void salvar(ofstream& arquivo) const;
    void carregar(ifstream& arquivo);
};

#endif