#ifndef MENUINICIAL_HPP
#define MENUINICIAL_HPP

#include "CadastroJogadores.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MenuInicial {
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
    sf::Font welcomingFont;

    //Textos que irão aparecer sobre cada botão
    sf::Text playersButtonText;
    sf::Text gamesButtonText;

    //Texto introdutório
    sf::Text welcomingText;

    //Botões para captar a escolha inicial do usuário
    sf::RectangleShape playersButton;
    sf::RectangleShape gamesButton;

    //Funções Privadas
    void initVariables();
    void initWindow();
    void initFonts();
    void initTexts();
    void initButtons();

public:
    MenuInicial();
    MenuInicial(CadastroJogadores&);
    ~MenuInicial();

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
