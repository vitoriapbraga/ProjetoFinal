#ifndef MENUJOGADORES_HPP
#define MENUJOGADORES_HPP

#include <string>

#include "CadastroJogadores.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MenuJogadores {
private:
    //Variáveis
    bool endMenu;
    CadastroJogadores* _jogadores;
    bool isCapturingText;
    std::string inputBuffer;

    //Janela
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Posições do mouse
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Recursos
    sf::Font buttonsFont;
    sf::Font listaDeJogadoresFont;

    //Textos que irão aparecer sobre cada botão
    sf::Text addPlayerButtonText;
    sf::Text removePlayerButtonText;
    sf::Text listPlayersByNameButtonText;
    sf::Text listPlayersByNicknameButtonText;
    sf::Text returnButtonText;
    sf::Text listaDeJogadores;
    sf::Text exitButtonText;
    sf::Text inputText;

    //Botões para captar a escolha do usuário
    sf::RectangleShape addPlayerButton;
    sf::RectangleShape removePlayerButton;
    sf::RectangleShape listPlayersByNameButton;
    sf::RectangleShape listPlayersByNicknameButton;
    sf::RectangleShape returnButton;
    sf::RectangleShape exitButton;

    //Funções Privadas
    void initVariables();
    void initWindow();
    void initFonts();
    void initTexts();
    void initButtons();

public:
    MenuJogadores();
    MenuJogadores(CadastroJogadores&);
    ~MenuJogadores();

    const bool isRunning() const;

    void pollEvents();
    void updateMousePositions();
    void updateExitButton(sf::RenderWindow&);
    void updateButtons();
    void update();

    void renderText(sf::RenderTarget&);
    void renderButtons(sf::RenderTarget&);
    void render();
};

#endif
