#include "CadastroJogadores.hpp"
#include "Resultados.hpp"
#include "Jogo.h"


#include <iostream>
#include <sstream>
#include <algorithm> // para utilizar transform

using namespace std;
void ComandosMain() {
    cout << "Comandos:" << endl;
    cout << "CJ <apelido> <nome>    - Cadastrar um novo jogador" << endl;
    cout << "RJ <apelido>           - Remover um jogador" << endl;
    cout << "LJ <A/N>               - Listar jogadores por apelido (A) ou nome (N)" << endl;
    cout << "Lig4                   - Jogar Ligue 4" << endl;
    cout << "REVERSI <jogador1> <jogador2> - Jogar Reversi" << endl;
    cout << "FS                     - Fechar o programa\n" << endl;
}

int main() {
    
    CadastroJogadores cadastro; //inicia o cadastro de jogadores
    string comando;
    ComandosMain();

    while (true) {
        
        getline(cin, comando);
        if (comando.empty()) {
            continue;
        }

        istringstream iss(comando);
        string cmd;
        iss >> cmd;
        transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper); // transforma todas as letras do comando em maiúsculas

        if (cmd == "CJ") { 
            string apelido, nome;
            iss >> apelido >> nome;
            if (apelido.empty()) {
                cout << "ERRO: dados incorretos" << endl;
                
            } else {
                cadastro.cadastrarJogador(apelido, nome);
            }
        } else if (cmd == "RJ") { 
            string apelido;
            iss >> apelido;
            if (apelido.empty()) {
                cout << "ERRO: jogador inexistente" << endl;
            } else {
                cadastro.removerJogador(apelido);
            }
        } else if (cmd == "LJ") { 
            char criterio;
            iss >> criterio;
            criterio = toupper(criterio);
            if (criterio == 'A' || criterio == 'N') {
                cadastro.listarJogadores(criterio);
            } else {
                cout << "Ordene por 'A' (apelido) ou 'N' (nome)" << endl;
            }
        } else if (cmd == "LIG4") { 
           
            JogarLigue4(cadastro);

        } else if (cmd == "REVERSI") {
            string jogador1, jogador2;
            iss >> jogador1;
            if (cadastro.jogadorExiste(jogador1)) {
                iss >> jogador2;
                if (cadastro.jogadorExiste(jogador2)) {
                    cout << "EMPATE SIMULADO" << endl;
                    ResultadoHumanoHumano(*cadastro.obterJogador(jogador1), *cadastro.obterJogador(jogador2), "REVERSI", 1);
                } else {
                    cout << "ERRO: Jogador << " << jogador2 << " >> inexistente" << endl;
                }
            }else {
                cout << "ERRO: Jogador << " << jogador1 << " >> inexistente" << endl;
            }
        } else if (cmd == "FS") { 
            break;
        } else {
            cout << "ERRO: comando desconhecido" << endl;
        }
        ComandosMain();
    }

    return 0;
}