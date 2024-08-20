#ifndef MENUJOGOS_HPP
#define MENUJOGOS_HPP

#include "CadastroJogadores.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MenuJogos {
private:
    //Variáveis
    bool endMenu;
    CadastroJogadores* _jogadores;
    char escolhaDoJogo;

    //Janela
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Posições do mouse
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Recursos
    sf::Font buttonsFont;

    //Textos que irão aparecer sobre cada botão
    sf::Text lig4ButtonText;
    sf::Text reversiButtonText;
    sf::Text mancalaButtonText;
    sf::Text returnButtonText;

    //Botões para captar a escolha do usuário
    sf::RectangleShape lig4Button;
    sf::RectangleShape reversiButton;
    sf::RectangleShape mancalaButton;
    sf::RectangleShape returnButton;

    //Funções Privadas
    void initVariables();
    void initWindow();
    void initFonts();
    void initTexts();
    void initButtons();

public:
    MenuJogos();
    MenuJogos(CadastroJogadores&);
    ~MenuJogos();

    const bool isRunning() const;
    char getEscolhaDeJogo();

    void pollEvents();
    void updateMousePositions();
    void updateButtons();
    void update();

    void renderText(sf::RenderTarget&);
    void renderButtons(sf::RenderTarget&);
    void render();
};

#endif
