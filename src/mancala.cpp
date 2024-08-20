#include "mancala.hpp"
#include <stdio.h>

Mancala::Mancala() {}

Mancala::~Mancala() {
}

void Mancala::_initialize() {
    // Inicializa a janela do jogo e estabelece o FPS
    SetTargetFPS(FPS);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    // Inicializa o estado do jogo com 4 sementes em cada nicho e 0 sementes em cada mancala
    _game_state = std::vector<int>(TAMANHO_MANCALA, 4);
    _game_state[MANCALA_0] = 0;
    _game_state[MANCALA_1] = 0;

    // winner
    _winner = DRAW;

    _text = "Turno: Jogador 0";
    _text_color = RAY_RED;

    _reset = false;
    _stop = false;


    // events
    _hover_nichos = std::vector<bool>(NICHOS_COUNT, false);
    _click_nichos = std::vector<bool>(NICHOS_COUNT, false);

    _mouse_down = false;
    _click_processed = false;
    _end_game = false;

    // Define o jogador inicial como Jogador 0
    _player = false;
    _mouse_position = Vector2 {};

    // Textura do jogo
    _wood_texture = LoadTexture(WOOD_TEXTURE);
    _seed_texture = LoadTexture(SEED_TEXTURE);


    // Constroi objetos do jogo: nichos e mancala
    _build_objects();
}


void Mancala::_run_loop(CadastroJogadores& cadastro) {
    // Loop principal do jogo
 
     while(!WindowShouldClose()) {
        _process_input();
        _update_game(cadastro);
        _draw_game();
    }
}

void Mancala::_process_input() {
    _mouse_position = GetMousePosition();

    // Check hover for nichos
    for (int i = 0; i < NICHOS_COUNT; i++) {
        _hover_nichos[i] = CheckCollisionPointCircle(_mouse_position, _nichos[i], NICHOS_RADIUS);
    }
    
 // Check for mouse button down event
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        _mouse_down = true;
        if (!_click_processed) {
            for (int i = 0; i < NICHOS_COUNT; ++i) {
                if (_hover_nichos[i]) {
                    _click_nichos[i] = true;
                    _click_processed = true;
                    break;
                }
            }
        }

        // Check for reset button click
        Rectangle reset_button = {SCREEN_WIDTH - 120, SCREEN_HEIGHT - 50, 100, 40};
        if (CheckCollisionPointRec(_mouse_position, reset_button)) {
            _reset = true;
        }
}

    // Check for mouse button up event
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
        _mouse_down = false;
        _click_processed = false;
        
        // Perform reset action
        if (_reset) {
            _reset_game();
        }
    }
}


void Mancala::_move_seeds_end() {
    for (int i = 0; i <= 5; ++i) {
        _game_state[6] += _game_state[i]; // Adiciona à Mancala 0
        _game_state[i] = 0; // Remove as sementes da casa
        }

    // Movendo sementes do Jogador 1 (casas 7 a 12) para a Mancala 1 (índice 13)
    for (int i = 7; i <= 12; ++i) {
        _game_state[13] += _game_state[i]; // Adiciona à Mancala 1
        _game_state[i] = 0; // Remove as sementes da casa
    }
}


void Mancala::_update_game(CadastroJogadores& cadastro) {
    if (end_game() && !_stop) {
        _end_game = true;
        get_winner(cadastro);
        _stop = true;

        return;
    }
    // atualiza se houver evento de click
    for (int i = 0; i < NICHOS_COUNT; i++) {
        if (_click_nichos[i]) {
            // se action retorna true altera o jogador
            _player = action(i <= 5 ? i : i + 1) ? !_player : _player;
            _click_nichos[i] = false;
        }
    }
}

void Mancala::_draw_game() {
    BeginDrawing();
    
    ClearBackground(RAY_RAYWHITE);


    // Desenho do fundo de madeira
    Rectangle source = { 0, 0, (float)_wood_texture.width, (float)_wood_texture.height };
    Rectangle dest = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(_wood_texture, source, dest, origin, 0.0f, RAY_WHITE);


    // Draw mancalas with hover effect
    for (int i = 0; i < 2; i++) {
        // Desenha o retângulo da mancala com a cor de preenchimento
        DrawRectangleRec(_mancalas[i], MANCALA_COLOR);

        // Desenha o contorno da mancala
        Color borderColor = (i == 0) ? RAY_RED : RAY_BLUE;
        DrawRectangleLinesEx(_mancalas[i], 2, borderColor); // O valor 2 é a espessura da borda
    }


    // Draw nichos with hover effect
    for (int i = 0; i < NICHOS_COUNT; i++) {
        Color color = _hover_nichos[i] ? RAY_DARKGRAY : NICHOS_COLOR;
        DrawCircleV(_nichos[i], NICHOS_RADIUS, color);

        // Verifica se é um círculo superior ou inferior
        if (i < NICHOS_COUNT / 2) {
            // Desenha "X" AZUL no centro dos círculos superiores
            DrawLine(_nichos[i].x - 5, _nichos[i].y - 5, _nichos[i].x + 5, _nichos[i].y + 5, RAY_RED);
            DrawLine(_nichos[i].x + 5, _nichos[i].y - 5, _nichos[i].x - 5, _nichos[i].y + 5, RAY_RED);
        } else {
            // Desenha "X" VERMELHO no centro dos círculos inferiores
            DrawLine(_nichos[i].x - 5, _nichos[i].y - 5, _nichos[i].x + 5, _nichos[i].y + 5, RAY_BLUE);
            DrawLine(_nichos[i].x + 5, _nichos[i].y - 5, _nichos[i].x - 5, _nichos[i].y + 5, RAY_BLUE);
        }
    }
    

    _draw_seeds();

    const char* player_text = "";
    Color color = RAY_BLUE; // Cor padrão

    
    if (!_end_game) {
        // Exibe de quem é a vez de jogar
        _text = _player ? ("Turno: " + _jogador1->getNome()).c_str() : ("Turno: " + _jogador0->getNome()).c_str();
        _text_color = _player ? RAY_BLUE : RAY_RED; // Cor de acordo com o jogador da vez
    }

    // Calcula a posição para centralizar o texto na parte superior da tela
    int screenWidth = GetScreenWidth();
    int textWidth = MeasureText(_text, 20); // Largura do texto
    int xPosition = (screenWidth / 2) - (textWidth / 2); // Centraliza horizontalmente
    int yPosition = 10; // Distância do topo

    // Desenha o texto na tela
    DrawText(_text, xPosition, yPosition, 20, _text_color);

    // Desenha o botão de reset
    Rectangle reset_button = {SCREEN_WIDTH - 120, SCREEN_HEIGHT - 50, 100, 40};
    DrawRectangleRec(reset_button, NICHOS_COLOR);
    DrawText("Reset", reset_button.x + 20, reset_button.y + 10, 20, RAY_BLACK);

    EndDrawing();
}

void Mancala::_draw_seeds() {

    // Draw Seeds
    for (int i = 0; i <= MANCALA_1; i++) {
        Vector2 position;
        int seeds_in_nicho = _game_state[i]; // Número de sementes no nicho i
        
        if (i == MANCALA_0 || i == MANCALA_1) {
            // Mancala is a rectangle, so we need a different approach
            Rectangle mancala_rect = _mancalas[i == MANCALA_0 ? 0 : 1];
            float mancala_width = mancala_rect.width;
            float mancala_height = mancala_rect.height;

            // Calculate the number of rows and columns for the seeds
            int rows = std::max(1, (int)std::sqrt(seeds_in_nicho)); 
            int cols = std::max(1, (int)std::ceil((float)seeds_in_nicho / rows));

            float seed_size = std::min(mancala_width / cols, mancala_height / rows); // Redimensiona o tamanho da semente

            // Adjust the seed_size to leave some padding
            seed_size *= 0.8f;
            float x_spacing = (mancala_width - seed_size * cols) / (cols + 1);
            float y_spacing = (mancala_height - seed_size * rows) / (rows + 1);

            for (int j = 0; j < seeds_in_nicho; j++) {
                // Calculate the row and column for the seed
                int row = j / cols;
                int col = j % cols;

                Vector2 seed_position = {
                    mancala_rect.x + x_spacing * (col + 1) + seed_size * col + seed_size / 2,
                    mancala_rect.y + y_spacing * (row + 1) + seed_size * row + seed_size / 2
                };

                // Desenha a pequena textura (semente) na posição calculada com o tamanho escalado
                Rectangle source = { 0, 0, (float)_seed_texture.width, (float)_seed_texture.height };
                Rectangle dest = { seed_position.x, seed_position.y, seed_size, seed_size };
                Vector2 origin = { seed_size / 2, seed_size / 2 };

                DrawTexturePro(_seed_texture, source, dest, origin, 0.0f, RAY_WHITE);
            }
        } else {
            // Nicho is a circle, so we can use the existing logic
            Vector2 nicho_position = _nichos[i > MANCALA_0 ? i-1 : i];

            // Calcula o fator de escala baseado no número de sementes
            float scale_factor = std::max(1.0f - 0.05f * (seeds_in_nicho - 1), 0.7f);
            float seed_size = SEED_RADIUS * scale_factor; // Redimensiona o tamanho da semente

            for (int j = 0; j < seeds_in_nicho; j++) {
                // Calculando a posição das sementes dentro do nicho
                float angle = (PI * 2 / seeds_in_nicho) * j; // Distribui uniformemente ao redor do centro
                Vector2 seed_position = {
                    nicho_position.x + cos(angle) * (NICHOS_RADIUS - seed_size),
                    nicho_position.y + sin(angle) * (NICHOS_RADIUS - seed_size)
                };

                // Desenha a pequena textura (semente) na posição calculada com o tamanho escalado
                Rectangle source = { 0, 0, (float)_seed_texture.width, (float)_seed_texture.height };
                Rectangle dest = { seed_position.x, seed_position.y, seed_size, seed_size };
                Vector2 origin = { seed_size / 2, seed_size / 2 };

                DrawTexturePro(_seed_texture, source, dest, origin, 0.0f, RAY_WHITE);
            }
        }
    }
}


void Mancala::_shutdown() {
    UnloadTexture(_wood_texture);
    UnloadTexture(_seed_texture);
    CloseWindow();
}


void Mancala::print_state() {
    // Primeira linha: indices 12 a 7
    printf("                ");
    for (int i = 12; i >= 7; i--) {
        printf("%d ", _game_state[i]);
    }
    printf("\n");

    // Linha central: Mancala 1 e Mancala 0
    printf("%d", _game_state[MANCALA_1]);
    printf("                                      ");
    printf("%d\n", _game_state[MANCALA_0]);

    // Segunda linha: indices 0 a 5
    printf("                ");
    for (int i = 0; i <= 5; i++) {
        printf("%d ", _game_state[i]);
    }
    printf("\n");
}


bool Mancala::action(int position) {
    // Verifica se a posição é válida e se há sementes para ação
    if (!_valid_interval(position) || _game_state[position] == 0) {
        return false;
    }

    // Executa a ação do jogo para a posição fornecida
    return _loop_capture_seeds(position);
}


bool Mancala::_loop_capture_seeds(int start) {
    int position = start;
    int seeds = _game_state[position];
    _game_state[position] = 0;
    
    // Distribui as sementes
    while (seeds != 0) {
        position = (position + 1) % TAMANHO_MANCALA;
        bool mancala_adv = (!_player && position == MANCALA_1) || (_player && position == MANCALA_0);

        if (!mancala_adv) {
            --seeds;
            ++_game_state[position]; // update game_state
        }
    }

    // se o loop termina na mancala do jogador: nunca termina na mancala adversária
    if (_check_mancala_player(position)) {
        return false; // jogador joga novamente
    }

    // Realiza captura se aplicável: não pode ser mancala do jogador a posicao final
    else if (_game_state[position] == 1 && _valid_interval(position)) {
        _capture(position);
    }

    return true;
}

void Mancala::_capture(int position) {
    int mancala = !_player ? MANCALA_0 : MANCALA_1;
    int position_op = ((mancala - position) + mancala) % TAMANHO_MANCALA;

    // Captura as sementes da posição oposta e adiciona na mancala do jogador
    _game_state[mancala] += _game_state[position_op];
    _game_state[position_op] = 0;
}


void Mancala::set_state(int position, int value) {
    // Define o valor da posição especificada no estado do jogo
    _game_state[position] = value;
}

bool Mancala::end_game() {
    int sum1 = 0;
    int sum2 = 0;
    
    // Calcula a soma das sementes para Jogador 1 e Jogador 2
    for (int i = 0; i <= 5; ++i) {
        sum1 += _game_state[i];
        sum2 += _game_state[i + 7];
    }

    // Verifica se o jogo terminou (se um dos jogadores não tiver mais sementes)
    if (sum1 == 0 || sum2 == 0) {
        _move_seeds_end();
    }
    return sum1 == 0 || sum2 == 0;
}

void Mancala::get_winner(CadastroJogadores& cadastro) {
    static char buffer[256];  // Buffer to hold the text

    if (_game_state[MANCALA_0] == _game_state[MANCALA_1]) {
        //Empate atribuído
        ResultadoJogador(*cadastro.obterJogador(_jogador0->getApelido()), "MANCALA", 1);
        ResultadoJogador(*cadastro.obterJogador(_jogador1->getApelido()), "MANCALA", 1);
        _winner = DRAW;
        _text = "Empate";
        _text_color = RAY_GRAY;

    } else if (_game_state[MANCALA_0] > _game_state[MANCALA_1]) {
        //jogador 0 venceu e jogador 1 perdeu
        ResultadoJogador(*cadastro.obterJogador(_jogador0->getApelido()), "MANCALA", 3);
        ResultadoJogador(*cadastro.obterJogador(_jogador1->getApelido()), "MANCALA", 0);
        _winner = PLAYER_0;
        snprintf(buffer, sizeof(buffer), "%s venceu!", _jogador0->getNome().c_str());
        _text = buffer;
        _text_color = RAY_RED;

    } else {
        //jogador 0 perdeu e jogador 1 venceu
        ResultadoJogador(*cadastro.obterJogador(_jogador0->getApelido()), "MANCALA", 0);
        ResultadoJogador(*cadastro.obterJogador(_jogador1->getApelido()), "MANCALA", 3);
        _winner = PLAYER_1;
        snprintf(buffer, sizeof(buffer), "%s venceu!", _jogador1->getNome().c_str());
        _text = buffer;
        _text_color = RAY_BLUE;
    }

    printf("%s\n", _text);  // For debugging, prints the winner's text
}



bool Mancala::_valid_interval(int position) {
    // Verifica se a posição está no intervalo válido para o jogador atual
    return _player ? (position <= 12) && (position >= 7) : (position <= 5) && (position >= 0);
}


void Mancala::_build_objects() {
    // mancala do jogador 1
    _mancalas[1] = Rectangle{MARGIN_H, MARGIN_V, MANCALA_WIDTH, MANCALA_HEIGHT};

    // coordenada dos centos dos nichos
    for (int i=0; i < NICHOS_COUNT; ++i) {
        // nichos inferiores
        if (i >=0 && i <= 5) {
            float x = (float)(MARGIN_H + MANCALA_WIDTH + (i+1) * NICHOS_SPACING_H + i * 2 * NICHOS_RADIUS + NICHOS_RADIUS);
            float y = (float)(MARGIN_V + 2 * NICHOS_RADIUS + NICHOS_SPACING_V + NICHOS_RADIUS);
            _nichos[i] = Vector2{x, y};
        }

        // nichos superiores
        else if (i >= 6 && i <= 11) {
            float x = (float)(MARGIN_H + MANCALA_WIDTH + ((i%6)+1) * NICHOS_SPACING_H + (i%6) * 2 * NICHOS_RADIUS + NICHOS_RADIUS);
            float y = (float)(MARGIN_V + NICHOS_RADIUS);
            _nichos[(11-i)+6] = Vector2{x, y};            
        }
    }

    // mancala do jogador 0
    _mancalas[0] = Rectangle{_nichos[5].x + NICHOS_RADIUS + NICHOS_SPACING_H, MARGIN_V, MANCALA_WIDTH, MANCALA_HEIGHT};


}

bool Mancala::_check_mancala_player(int position) {
    return (_player && position == MANCALA_1) || (!_player && position == MANCALA_0);
}


void Mancala::_reset_game() {
    // Reinicializa o estado do jogo
    _game_state = std::vector<int>(TAMANHO_MANCALA, 4);
    _game_state[MANCALA_0] = 0;
    _game_state[MANCALA_1] = 0;

    // Define o jogador inicial como Jogador 0
    _player = false;

    // Define o estado do jogo para não terminado
    _end_game = false;

    // Atualiza o texto do turno
    _text = "Turno: Jogador 0";
    _text_color = RAY_RED;

    // Reseta o botão de reset
    _reset = false;
    _stop = false;
}

bool Mancala::_validation(CadastroJogadores& cadastro) {
    std::cout << "Bem-vindo ao Jogo Mancala!\n\n";  

    std::string apelido0, apelido1;
    std::cout << "Digite o apelido do Jogador 0: ";
    std::cin >> apelido0;
    if(cadastro.jogadorExiste(apelido0)){
        std::cout << "Digite o apelido do Jogador 1: ";
        std::cin >> apelido1;

        if(cadastro.jogadorExiste(apelido1)){
            //jogo pode acontecer
            _jogador0 = cadastro.obterJogador(apelido0);
            _jogador1 = cadastro.obterJogador(apelido1);
        } else {
            std::cerr << "Jogador 1 inexistente.\n";
            return false;
        }

    } else {
            std::cerr << "Jogador 0 inexistente.\n";
            return false;
    }

    return true;
}

void Mancala::run(CadastroJogadores& cadastro) {
    if (_validation(cadastro)) {
        _initialize();
        _run_loop(cadastro);
        _shutdown();
    }
}