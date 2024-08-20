#include "MenuInicial.hpp"
#include "MenuJogadores.hpp"
#include "MenuJogos.hpp"
#include <sstream>

void MenuInicial::initVariables() {
    this->window = nullptr;
    this->_jogadores = nullptr;
    this->endMenu = false;
}

void MenuInicial::initWindow() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    if (desktopMode.width > 0 && desktopMode.height > 0) {
        this->videoMode.width = desktopMode.width;
        this->videoMode.height = desktopMode.height;
    } else {

        this->videoMode.width = 800;
        this->videoMode.height = 600;
    }

    this->window = new sf::RenderWindow(this->videoMode, "Menu inicial", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}


void MenuInicial::initFonts() {
    this->buttonsFont.loadFromFile("fonts/historical/historical.ttf");

    this->welcomingFont.loadFromFile("fonts/times.ttf");
}

void MenuInicial::initTexts() {
    this->welcomingText.setFont(this->welcomingFont);
    this->welcomingText.setCharacterSize(45);
    this->welcomingText.setFillColor(sf::Color::White);
    this->welcomingText.setString("Bem vindo a nossa HUD de jogos.\n"
                                  "Para avancar ao menu de jogadores clique no botao JOGADORES.\n"
                                  "Nesse menu voce podera fazer as acoes referentes ao cadastro de jogadores.\n"
                                  "Para avancar ao menu de jogos clique no botao JOGOS.\n"
                                  "Nesse menu voce podera escolher diferentes opcoes de jogos.\n"
                                  "Para jogar e necessario que o jogador esteja CADASTRADO.\n"
                                  "Para encerrar o programa pressione ESC ou feche a janela.");

    this->playersButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.67f, this->videoMode.height * 0.5f));
    this->gamesButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.7f , this->videoMode.height * 0.8f));
    this->playersButtonText.setFont(this->buttonsFont);
    this->gamesButtonText.setFont(this->buttonsFont);
    this->playersButtonText.setCharacterSize(50);
    this->gamesButtonText.setCharacterSize(50);
    this->playersButtonText.setFillColor(sf::Color::Red);
    this->gamesButtonText.setFillColor(sf::Color::Red);
    this->playersButtonText.setString("JOGADORES");
    this->gamesButtonText.setString("JOGOS");
}

void MenuInicial::initButtons() {
    this->playersButton.setPosition(sf::Vector2f(this->videoMode.width * 0.6f, this->videoMode.height * 0.5f));
    this->playersButton.setSize(sf::Vector2f(this->videoMode.width * 0.3f, this->videoMode.height * 0.1f));
    this->playersButton.setFillColor(sf::Color::White);
    this->playersButton.setOutlineColor(sf::Color::Red);
    this->playersButton.setOutlineThickness(this->videoMode.width * 0.005f);

    this->gamesButton.setPosition(sf::Vector2f(this->videoMode.width * 0.6f, this->videoMode.height * 0.8f));
    this->gamesButton.setSize(sf::Vector2f(this->videoMode.width * 0.3f, this->videoMode.height * 0.1f));
    this->gamesButton.setFillColor(sf::Color::White);
    this->gamesButton.setOutlineColor(sf::Color::Red);
    this->gamesButton.setOutlineThickness(this->videoMode.width  * 0.005f);
}

MenuInicial::MenuInicial() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initButtons();
}

MenuInicial::MenuInicial(CadastroJogadores& jogadores) {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initButtons();
    this->_jogadores = &jogadores;
}

MenuInicial::~MenuInicial() {
    delete this->window;
}

const bool MenuInicial::isRunning() const {
    return this->window->isOpen();
}

char MenuInicial::getEscolhaDeJogo() {
    return this->escolhaDoJogo;
}

void MenuInicial::pollEvents() {
    while(this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed: {
                this->window->close();
                break;
            }
            case sf::Event::KeyPressed: {
                if(this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
            }
        }
    }
}

void MenuInicial::updateMousePositions() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void MenuInicial::updateButtons() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(this->playersButton.getGlobalBounds().contains(this->mousePosView)) {
            MenuJogadores menuJogadores(*this->_jogadores);

            while(menuJogadores.isRunning()) {
                menuJogadores.update();

                menuJogadores.render();
            }
        }
        if(this->gamesButton.getGlobalBounds().contains(this->mousePosView)) {
            MenuJogos menuJogos(*this->_jogadores);

            while(menuJogos.isRunning()) {
                menuJogos.update();

                menuJogos.render();
            }
            this->escolhaDoJogo = menuJogos.getEscolhaDeJogo();
            this->window->close();
        }
    }
}

void MenuInicial::update() {
    this->pollEvents();

    if(!this->endMenu) {
        this->updateMousePositions();

        this->updateButtons();
    }
}

void MenuInicial::renderText(sf::RenderTarget& target) {
    target.draw(this->welcomingText);
    target.draw(this->playersButtonText);
    target.draw(this->gamesButtonText);
}

void MenuInicial::renderButtons(sf::RenderTarget& target) {
    target.draw(this->playersButton);
    target.draw(this->gamesButton);
}

void MenuInicial::render() {
    this->window->clear(sf::Color(0, 0, 0, 255));

    this->renderButtons(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
