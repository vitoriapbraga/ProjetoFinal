#include "MenuJogos.hpp"
#include <sstream>

void MenuJogos::initVariables() {
    this->window = nullptr;
    this->endMenu = false;
    this->_jogadores = nullptr;
}

void MenuJogos::initWindow() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    if (desktopMode.width > 0 && desktopMode.height > 0) {
        this->videoMode.width = desktopMode.width;
        this->videoMode.height = desktopMode.height;
    } else {

        this->videoMode.width = 800;
        this->videoMode.height = 600;
    }

    this->window = new sf::RenderWindow(this->videoMode, "Menu de Jogos", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}


void MenuJogos::initFonts() {
    this->buttonsFont.loadFromFile("fonts/historical/historical.ttf");
}

void MenuJogos::initTexts() {
    this->lig4ButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.17f, this->videoMode.height * 0.3f));
    this->lig4ButtonText.setFont(this->buttonsFont);
    this->lig4ButtonText.setCharacterSize(50);
    this->lig4ButtonText.setFillColor(sf::Color::Red);
    this->lig4ButtonText.setString("LIGUE QUATRO");

    this->reversiButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.18f , this->videoMode.height * 0.7f));
    this->reversiButtonText.setFont(this->buttonsFont);
    this->reversiButtonText.setCharacterSize(50);
    this->reversiButtonText.setFillColor(sf::Color::Red);
    this->reversiButtonText.setString("REVERSI");

    this->mancalaButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.6f , this->videoMode.height * 0.3f));
    this->mancalaButtonText.setFont(this->buttonsFont);
    this->mancalaButtonText.setCharacterSize(50);
    this->mancalaButtonText.setFillColor(sf::Color::Red);
    this->mancalaButtonText.setString("MANCALA");

    this->returnButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.6f , this->videoMode.height * 0.7f));
    this->returnButtonText.setFont(this->buttonsFont);
    this->returnButtonText.setCharacterSize(50);
    this->returnButtonText.setFillColor(sf::Color::Red);
    this->returnButtonText.setString("RETORNAR");
}

void MenuJogos::initButtons() {
    this->lig4Button.setPosition(sf::Vector2f(this->videoMode.width * 0.1f, this->videoMode.height * 0.3f));
    this->lig4Button.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->lig4Button.setFillColor(sf::Color::White);
    this->lig4Button.setOutlineColor(sf::Color::Red);
    this->lig4Button.setOutlineThickness(this->videoMode.width * 0.005f);

    this->reversiButton.setPosition(sf::Vector2f(this->videoMode.width * 0.1f, this->videoMode.height * 0.7f));
    this->reversiButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->reversiButton.setFillColor(sf::Color::White);
    this->reversiButton.setOutlineColor(sf::Color::Red);
    this->reversiButton.setOutlineThickness(this->videoMode.width  * 0.005f);

    this->mancalaButton.setPosition(sf::Vector2f(this->videoMode.width * 0.55f, this->videoMode.height * 0.3f));
    this->mancalaButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->mancalaButton.setFillColor(sf::Color::White);
    this->mancalaButton.setOutlineColor(sf::Color::Red);
    this->mancalaButton.setOutlineThickness(this->videoMode.width  * 0.005f);

    this->returnButton.setPosition(sf::Vector2f(this->videoMode.width * 0.55f, this->videoMode.height * 0.7f));
    this->returnButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->returnButton.setFillColor(sf::Color::White);
    this->returnButton.setOutlineColor(sf::Color::Red);
    this->returnButton.setOutlineThickness(this->videoMode.width  * 0.005f);
}

MenuJogos::MenuJogos() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initButtons();
}

MenuJogos::MenuJogos(CadastroJogadores& jogadores) {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initButtons();
    this->_jogadores = &jogadores;
}

MenuJogos::~MenuJogos() {
    delete this->window;
}

const bool MenuJogos::isRunning() const {
    return this->window->isOpen();
}

char MenuJogos::getEscolhaDeJogo() {
    return this->escolhaDoJogo;
}

void MenuJogos::pollEvents() {
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

void MenuJogos::updateMousePositions() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void MenuJogos::updateButtons() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(this->lig4Button.getGlobalBounds().contains(this->mousePosView)) {
            this->escolhaDoJogo = 'L';
            this->window->close();
        }
        if(this->reversiButton.getGlobalBounds().contains(this->mousePosView)) {
            this->escolhaDoJogo = 'R';
            this->window->close();
        }
        if(this->mancalaButton.getGlobalBounds().contains(this->mousePosView)) {
            this->escolhaDoJogo = 'M';
            this->window->close();
        }
        if(this->returnButton.getGlobalBounds().contains(this->mousePosView)) {
            this->escolhaDoJogo = 'E';
            this->window->close();
        }
    }
}

void MenuJogos::update() {
    this->pollEvents();

    if(!this->endMenu) {
        this->updateMousePositions();

        this->updateButtons();
    }
}

void MenuJogos::renderText(sf::RenderTarget& target) {
    target.draw(this->lig4ButtonText);
    target.draw(this->reversiButtonText);
    target.draw(this->mancalaButtonText);
    target.draw(this->returnButtonText);
}

void MenuJogos::renderButtons(sf::RenderTarget& target) {
    target.draw(this->lig4Button);
    target.draw(this->reversiButton);
    target.draw(this->mancalaButton);
    target.draw(this->returnButton);
}

void MenuJogos::render() {
    this->window->clear(sf::Color(0, 0, 0, 255));

    this->renderButtons(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
