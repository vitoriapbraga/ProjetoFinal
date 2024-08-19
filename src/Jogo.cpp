#include <iostream>
#include "Jogo.h"
#include "JogadorHumanoLig4.h"
#include "JogadorIA.h"

#include "CadastroJogadores.hpp"
#include "Resultados.hpp"


//função principal do jogo
int JogarLigue4(CadastroJogadores& cadastro) {
    
    std::cout << "Bem-vindo ao Ligue 4!\n\n";  
    std::cout << "Escolha o modo de jogo:\n\n"; 
    std::cout << "1: Jogador 1 vs Jogador 2\n";
    std::cout << "2: Jogador vs IA\n\n";
    
        char escolha;
    std::cin >> escolha;

    JogadorLig4* jogador1;
    JogadorLig4* jogador2;

    if (escolha == '1') {
        std::string nome1, nome2;
        std::cout << "Digite o nome do Jogador 1: ";
        std::cin >> nome1;
        if(cadastro.jogadorExiste(nome1)){
        std::cout << "Digite o nome do Jogador 2: ";
        std::cin >> nome2;
        if(cadastro.jogadorExiste(nome2)){
        //jogo pode acontecer
        jogador1 = new JogadorHumano(nome1, 'X');
        jogador2 = new JogadorHumano(nome2, 'O');
        } else {
            std::cerr << "Jogador 2 inexistente.\n";
            return 1;
        }
        } else {
            std::cerr << "Jogador 1 inexistente.\n";
            return 1;
        }


    } else if (escolha == '2') {
        std::string nome;
        std::cout << "Digite seu nome: ";
        std::cin >> nome;
        if(cadastro.jogadorExiste(nome)){
        //jogo pode acontecer

        jogador1 = new JogadorHumano(nome, 'X');
        jogador2 = new JogadorIA("IA", 'O');
        } else {
            std::cerr << "Jogador inexistente.\n";
            return 1;
        }
    } else {
        std::cerr << "Escolha invalida.\n";
        return 0;
    }

    Jogo jogo(jogador1, jogador2);
    jogo.jogar(cadastro);

    return 0;
}

Jogo::Jogo(JogadorLig4* j1, JogadorLig4* j2) : jogador1(j1), jogador2(j2) {}

Jogo::~Jogo() {
    delete jogador1;
    delete jogador2;
}

void Jogo::jogar(CadastroJogadores& cadastro) {
    bool jogoEmAndamento = true;
    JogadorLig4* jogadorAtual = jogador1;

    while (jogoEmAndamento) {
        tabuleiro.exibir();
        int coluna = jogadorAtual->obterJogada(tabuleiro);
        

        while (!tabuleiro.fazerJogada(coluna, jogadorAtual->getSimbolo())) {
            std::cout << "Jogada inválida. Tente novamente.\n";
            coluna = jogadorAtual->obterJogada(tabuleiro);
        }

        if (tabuleiro.verificarVitoria(jogadorAtual->getSimbolo())) {
            tabuleiro.exibir();

            //verifica se não é o jogador IA
            if(cadastro.jogadorExiste(jogadorAtual->getApelido())){
            ResultadoJogador(*cadastro.obterJogador(jogadorAtual->getApelido()), "LIG4", 3);
            std::cout << "Parabens, " << jogadorAtual->getApelido() << "! Voce venceu!\n\n";
            }else{
                //vitória da IA
                std::cout << "A " << jogadorAtual->getNome() << " venceu o jogo!\n\n";
            }

            //alterna o jogador para derrota
            jogadorAtual = (jogadorAtual == jogador1) ? jogador2 : jogador1;

            //verifica se não é o jogador IA
            if(cadastro.jogadorExiste(jogadorAtual->getApelido()))
            ResultadoJogador(*cadastro.obterJogador(jogadorAtual->getApelido()), "LIG4", 0);
            jogoEmAndamento = false;

        } else if (tabuleiro.estaCheio()) {
            tabuleiro.exibir();
            std::cout << "Empate! O tabuleiro está cheio.\n";

            if(cadastro.jogadorExiste(jogadorAtual->getApelido()))
            ResultadoJogador(*cadastro.obterJogador(jogadorAtual->getApelido()), "LIG4", 0);

            //alterna o jogador para derrota
            jogadorAtual = (jogadorAtual == jogador1) ? jogador2 : jogador1;

            if(cadastro.jogadorExiste(jogadorAtual->getApelido()))
            ResultadoJogador(*cadastro.obterJogador(jogadorAtual->getApelido()), "LIG4", 0);


            jogoEmAndamento = false;
        } else {
            jogadorAtual = (jogadorAtual == jogador1) ? jogador2 : jogador1;
        }
    }
    
   
}
