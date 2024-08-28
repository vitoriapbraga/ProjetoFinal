#include "MenuJogadores.hpp"
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

void MenuJogadores::initVariables() {
    this->window = nullptr;
    this->endMenu = false;
    this->_jogadores = nullptr;
    isCapturingText = false;
}

void MenuJogadores::initWindow() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    if (desktopMode.width > 0 && desktopMode.height > 0) {
        this->videoMode.width = desktopMode.width;
        this->videoMode.height = desktopMode.height;
    } else {

        this->videoMode.width = 800;
        this->videoMode.height = 600;
    }

    this->window = new sf::RenderWindow(this->videoMode, "Menu de Jogadores", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}


void MenuJogadores::initFonts() {
    this->buttonsFont.loadFromFile("fonts/historical/historical.ttf");

    this->listaDeJogadoresFont.loadFromFile("fonts/arial.ttf");
}

void MenuJogadores::initTexts() {
    this->addPlayerButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.15f, this->videoMode.height * 0.2f));
    this->addPlayerButtonText.setFont(this->buttonsFont);
    this->addPlayerButtonText.setCharacterSize(50);
    this->addPlayerButtonText.setFillColor(sf::Color::Red);
    this->addPlayerButtonText.setString("ADICIONAR JOGADOR");

    this->removePlayerButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.15f , this->videoMode.height * 0.5f));
    this->removePlayerButtonText.setFont(this->buttonsFont);
    this->removePlayerButtonText.setCharacterSize(50);
    this->removePlayerButtonText.setFillColor(sf::Color::Red);
    this->removePlayerButtonText.setString("REMOVER JOGADOR");

    this->listPlayersByNameButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.1006f , this->videoMode.height * 0.8f));
    this->listPlayersByNameButtonText.setFont(this->buttonsFont);
    this->listPlayersByNameButtonText.setCharacterSize(40);
    this->listPlayersByNameButtonText.setFillColor(sf::Color::Red);
    this->listPlayersByNameButtonText.setString("LISTAR JOGADORES POR NOME");

    this->listPlayersByNicknameButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.5503f , this->videoMode.height * 0.4f));
    this->listPlayersByNicknameButtonText.setFont(this->buttonsFont);
    this->listPlayersByNicknameButtonText.setCharacterSize(39);
    this->listPlayersByNicknameButtonText.setFillColor(sf::Color::Red);
    this->listPlayersByNicknameButtonText.setString("LISTAR JOGADORES POR APELIDO");

    this->returnButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.60f , this->videoMode.height * 0.7f));
    this->returnButtonText.setFont(this->buttonsFont);
    this->returnButtonText.setCharacterSize(50);
    this->returnButtonText.setFillColor(sf::Color::Red);
    this->returnButtonText.setString("RETORNAR");

    this->exitButtonText.setPosition(sf::Vector2f(this->videoMode.width * 0.73f , this->videoMode.height * 0.8f));
    this->exitButtonText.setFont(this->buttonsFont);
    this->exitButtonText.setCharacterSize(50);
    this->exitButtonText.setFillColor(sf::Color::Red);
    this->exitButtonText.setString("SAIR");

    this->listaDeJogadores.setPosition(sf::Vector2f(this->videoMode.width * 0.05f , this->videoMode.height * 0.05f));
    this->listaDeJogadores.setFont(this->listaDeJogadoresFont);
    this->listaDeJogadores.setCharacterSize(20);
    this->listaDeJogadores.setFillColor(sf::Color::White);
    this->listaDeJogadores.setString("NONE");
}

void MenuJogadores::initButtons() {
    this->addPlayerButton.setPosition(sf::Vector2f(this->videoMode.width * 0.1f, this->videoMode.height * 0.2f));
    this->addPlayerButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->addPlayerButton.setFillColor(sf::Color::White);
    this->addPlayerButton.setOutlineColor(sf::Color::Red);
    this->addPlayerButton.setOutlineThickness(this->videoMode.width * 0.005f);

    this->removePlayerButton.setPosition(sf::Vector2f(this->videoMode.width * 0.1f, this->videoMode.height * 0.5f));
    this->removePlayerButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->removePlayerButton.setFillColor(sf::Color::White);
    this->removePlayerButton.setOutlineColor(sf::Color::Red);
    this->removePlayerButton.setOutlineThickness(this->videoMode.width  * 0.005f);

    this->listPlayersByNameButton.setPosition(sf::Vector2f(this->videoMode.width * 0.1f, this->videoMode.height * 0.8f));
    this->listPlayersByNameButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->listPlayersByNameButton.setFillColor(sf::Color::White);
    this->listPlayersByNameButton.setOutlineColor(sf::Color::Red);
    this->listPlayersByNameButton.setOutlineThickness(this->videoMode.width  * 0.005f);

    this->listPlayersByNicknameButton.setPosition(sf::Vector2f(this->videoMode.width * 0.55f, this->videoMode.height * 0.4f));
    this->listPlayersByNicknameButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->listPlayersByNicknameButton.setFillColor(sf::Color::White);
    this->listPlayersByNicknameButton.setOutlineColor(sf::Color::Red);
    this->listPlayersByNicknameButton.setOutlineThickness(this->videoMode.width  * 0.005f);

    this->returnButton.setPosition(sf::Vector2f(this->videoMode.width * 0.55f, this->videoMode.height * 0.7f));
    this->returnButton.setSize(sf::Vector2f(this->videoMode.width * 0.35f, this->videoMode.height * 0.1f));
    this->returnButton.setFillColor(sf::Color::White);
    this->returnButton.setOutlineColor(sf::Color::Red);
    this->returnButton.setOutlineThickness(this->videoMode.width  * 0.005f);

    this->exitButton.setPosition(sf::Vector2f(this->videoMode.width * 0.7f, this->videoMode.height * 0.8f));
    this->exitButton.setSize(sf::Vector2f(this->videoMode.width * 0.25f, this->videoMode.height * 0.1f));
    this->exitButton.setFillColor(sf::Color::White);
    this->exitButton.setOutlineColor(sf::Color::Red);
    this->exitButton.setOutlineThickness(this->videoMode.width  * 0.005f);
}

MenuJogadores::MenuJogadores() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initButtons();
}

MenuJogadores::MenuJogadores(CadastroJogadores& jogadores) {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
    this->initButtons();
    this->_jogadores = &jogadores;
}

MenuJogadores::~MenuJogadores() {
    delete this->window;
}

const bool MenuJogadores::isRunning() const {
    return this->window->isOpen();
}

void MenuJogadores::pollEvents() {
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

void MenuJogadores::updateMousePositions() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void MenuJogadores::updateExitButton(sf::RenderWindow& exit) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(this->exitButton.getGlobalBounds().contains(this->mousePosView)){
            exit.close();
        }
    }
}

void MenuJogadores::updateButtons() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->addPlayerButton.getGlobalBounds().contains(this->mousePosView)) {
            std::string nome, apelido;
            bool isCapturingApelido = true;
            bool isCapturingNome = false;
            sf::Text inputText;
            inputText.setFont(this->listaDeJogadoresFont);
            inputText.setCharacterSize(30);
            inputText.setFillColor(sf::Color::White);
            inputText.setPosition(this->videoMode.width * 0.1f, this->videoMode.height * 0.3f);

            while (isCapturingApelido || isCapturingNome) {
                this->window->clear(sf::Color::Black);
                this->renderButtons(*this->window);
                this->renderText(*this->window);

                while (this->window->pollEvent(this->ev)) {
                    if (this->ev.type == sf::Event::Closed) {
                        this->window->close();
                        return;
                    }
                    if (this->ev.type == sf::Event::TextEntered) {
                        if (isCapturingApelido) {
                            if (this->ev.text.unicode == '\b' && !apelido.empty()) {
                                apelido.pop_back();
                            } else if (this->ev.text.unicode == '\r') {
                                isCapturingApelido = false;
                                isCapturingNome = true;
                            } else if (this->ev.text.unicode < 128) {
                                apelido += static_cast<char>(this->ev.text.unicode);
                            }
                        } else if (isCapturingNome) {
                            if (this->ev.text.unicode == '\b' && !nome.empty()) {
                                nome.pop_back();
                            } else if (this->ev.text.unicode == '\r') {
                                isCapturingNome = false;
                            } else if (this->ev.text.unicode < 128) {
                                nome += static_cast<char>(this->ev.text.unicode);
                            }
                        }
                    }
                }

                inputText.setString("Apelido: " + apelido + "\nNome: " + nome);
                this->window->draw(inputText);
                this->window->display();
            }

            bool cadastroRealizado = this->_jogadores->cadastrarJogador(apelido, nome);
            if(cadastroRealizado) {
                stringstream ss;
                ss << "Jogador " << apelido << " cadastrado com sucesso!\nPronto para continuar usando!";
                std::string str = ss.str();
                inputText.setString(str);
                this->window->clear(sf::Color::Black);
                this->update();
                this->renderButtons(*this->window);
                this->renderText(*this->window);
                this->window->draw(inputText);
                this->window->display();
                sf::sleep(sf::seconds(5));
            }
            else {
                if(this->_jogadores->jogadorExiste(apelido)) {
                    std::string str = "ERRO: jogador repetido";
                    inputText.setString(str);
                    this->window->clear(sf::Color::Black);
                    this->update();
                    this->renderButtons(*this->window);
                    this->renderText(*this->window);
                    this->window->draw(inputText);
                    this->window->display();
                    sf::sleep(sf::seconds(5));
                }
                else {
                    std::string str = "ERRO: dados incorretos";
                    inputText.setString(str);
                    this->window->clear(sf::Color::Black);
                    this->update();
                    this->renderButtons(*this->window);
                    this->renderText(*this->window);
                    this->window->draw(inputText);
                    this->window->display();
                    sf::sleep(sf::seconds(5));
                }
            }
        }

        if (this->removePlayerButton.getGlobalBounds().contains(this->mousePosView)) {
            std::string apelido;
            bool isCapturingApelido = true;
            sf::Text inputText;
            inputText.setFont(this->listaDeJogadoresFont);
            inputText.setCharacterSize(30);
            inputText.setFillColor(sf::Color::White);
            inputText.setPosition(this->videoMode.width * 0.1f, this->videoMode.height * 0.6f);

            while (isCapturingApelido) {
                this->window->clear(sf::Color::Black);
                this->renderButtons(*this->window);
                this->renderText(*this->window);

                while (this->window->pollEvent(this->ev)) {
                    if (this->ev.type == sf::Event::Closed) {
                        this->window->close();
                        return;
                    }
                    if (this->ev.type == sf::Event::TextEntered) {
                        if (this->ev.text.unicode == '\b' && !apelido.empty()) {
                            apelido.pop_back();
                        } else if (this->ev.text.unicode == '\r') {
                            isCapturingApelido = false;
                        } else if (this->ev.text.unicode < 128) {
                            apelido += static_cast<char>(this->ev.text.unicode);
                        }
                    }
                }

                inputText.setString("Apelido: " + apelido);
                this->window->draw(inputText);
                this->window->display();
            }

            bool jogadorRemovido = this->_jogadores->removerJogador(apelido);

            if(jogadorRemovido) {
                stringstream ss;
                ss << "Jogador " << apelido << " removido com sucesso!\nPronto para continuar usando!";
                std::string str = ss.str();
                inputText.setString(str);
                this->window->clear(sf::Color::Black);
                this->update();
                this->renderButtons(*this->window);
                this->renderText(*this->window);
                this->window->draw(inputText);
                this->window->display();
                sf::sleep(sf::seconds(5));
            }
            else {
                std::string str = "ERRO: jogador inexistente";
                inputText.setString(str);
                this->window->clear(sf::Color::Black);
                this->update();
                this->renderButtons(*this->window);
                this->renderText(*this->window);
                this->window->draw(inputText);
                this->window->display();
                sf::sleep(sf::seconds(5));
            }
        }
        if(this->listPlayersByNameButton.getGlobalBounds().contains(this->mousePosView)) {
            std::string str = this->_jogadores->listarJogadores('A').str();
            this->listaDeJogadores.setString(str);

            sf::RenderWindow listarJogadores(this->videoMode, "Lista de jogadores", sf::Style::Titlebar | sf::Style::Close);
            while(listarJogadores.isOpen()) {

                while(listarJogadores.pollEvent(this->ev)) {
                    switch (this->ev.type) {
                        case sf::Event::Closed: {
                            listarJogadores.close();
                            break;
                        }
                        case sf::Event::KeyPressed: {
                            if(this->ev.key.code == sf::Keyboard::Escape) {
                                listarJogadores.close();
                            }
                            break;
                        }
                    }
                }

                this->updateMousePositions();

                this->updateExitButton(listarJogadores);

                listarJogadores.clear(sf::Color(0, 0, 0, 255));

                listarJogadores.draw(this->exitButton);
                listarJogadores.draw(this->exitButtonText);
                listarJogadores.draw(this->listaDeJogadores);

                listarJogadores.display();
            }
        }
        if(this->listPlayersByNicknameButton.getGlobalBounds().contains(this->mousePosView)) {
            std::string str = this->_jogadores->listarJogadores('N').str();
            this->listaDeJogadores.setString(str);

            sf::RenderWindow listarJogadores(this->videoMode, "Lista de jogadores", sf::Style::Titlebar | sf::Style::Close);
            while(listarJogadores.isOpen()) {

                while(listarJogadores.pollEvent(this->ev)) {
                    switch (this->ev.type) {
                        case sf::Event::Closed: {
                            listarJogadores.close();
                            break;
                        }
                        case sf::Event::KeyPressed: {
                            if(this->ev.key.code == sf::Keyboard::Escape) {
                                listarJogadores.close();
                            }
                            break;
                        }
                    }
                }

                this->updateMousePositions();

                this->updateExitButton(listarJogadores);

                listarJogadores.clear(sf::Color(0, 0, 0, 255));

                listarJogadores.draw(this->exitButton);
                listarJogadores.draw(this->exitButtonText);
                listarJogadores.draw(this->listaDeJogadores);

                listarJogadores.display();
            }
        }
        if(this->returnButton.getGlobalBounds().contains(this->mousePosView)) {
            this->window->close();
        }
    }
}

void MenuJogadores::update() {
    this->pollEvents();

    if(!this->endMenu) {
        this->updateMousePositions();

        this->updateButtons();
    }
}

void MenuJogadores::renderText(sf::RenderTarget& target) {
    target.draw(this->addPlayerButtonText);
    target.draw(this->removePlayerButtonText);
    target.draw(this->listPlayersByNameButtonText);
    target.draw(this->listPlayersByNicknameButtonText);
    target.draw(this->returnButtonText);
}

void MenuJogadores::renderButtons(sf::RenderTarget& target) {
    target.draw(this->addPlayerButton);
    target.draw(this->removePlayerButton);
    target.draw(this->listPlayersByNameButton);
    target.draw(this->listPlayersByNicknameButton);
    target.draw(this->returnButton);
}

void MenuJogadores::render() {
    this->window->clear(sf::Color(0, 0, 0, 255));

    this->renderButtons(*this->window);

    this->renderText(*this->window);

    this->window->display();
}
