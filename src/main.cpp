#include "CadastroJogadores.hpp"
#include "Resultados.hpp"
#include "Jogo.h" // lig4
#include "Table.hpp" // reversi
#include "raylib.h"

#ifndef _WIN32
#include "mancala.hpp" // Incluir apenas se não for Windows
#endif

#include <iostream>
#include <sstream>
#include <algorithm> // para utilizar transform

#include "MenuInicial.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

void ComandosMain() {
    cout << "Comandos:" << endl;
    cout << "CJ <apelido> <nome>    - Cadastrar um novo jogador" << endl;
    cout << "RJ <apelido>           - Remover um jogador" << endl;
    cout << "LJ <A/N>               - Listar jogadores por apelido (A) ou nome (N)" << endl;
    cout << "Lig4                   - Jogar Ligue 4" << endl;
#ifndef _WIN32
    cout << "MANCALA                - Jogar Mancala" << endl;
#endif
    cout << "REVERSI <jogador1> <jogador2> - Jogar Reversi" << endl;
    cout << "FS                     - Fechar o programa\n" << endl;
}

int main() {
    CadastroJogadores cadastro; // inicia o cadastro de jogadores
    MenuInicial menuInicial(cadastro);
    char jogoEscolhido;

    while (menuInicial.isRunning()) {
        menuInicial.update();

        menuInicial.render();

        jogoEscolhido = menuInicial.getEscolhaDeJogo();

        switch (jogoEscolhido) {
            case 'L': {
                JogarLigue4(cadastro);
                break;
            }
            case 'R': {
                JogarReversi(cadastro);
                break;
            }
#ifndef _WIN32
                case 'M': {
            Mancala mancala;
            mancala.run(cadastro);
        }
#endif

            case 'E': {
                break;
            }
        }
    }

    return 0;
}