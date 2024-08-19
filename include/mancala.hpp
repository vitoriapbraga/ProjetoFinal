#ifndef MANCALA_HPP
#define MANCALA_HPP

#include "raylib.h"
#include "math.h"
#include "iostream"
#include "stdlib.h"
#include  "settings.hpp"
#include "CadastroJogadores.hpp"
#include <vector>


// Enumeração para o status do vencedor do jogo
enum WINNER { DRAW, PLAYER_0, PLAYER_1 };

// Classe que representa o jogo de Mancala
class Mancala {
public:
    // Construtor padrão
    Mancala();

    // Destrutor padrão
    ~Mancala();

    // Define o valor de uma posição específica no estado do jogo
    void set_state(int position, int value);

    void set_player(bool player) {
        _player = player;
    }

    // Verifica se o jogo terminou
    bool end_game();

    // Atualiza o vencedor com base no estado do jogo
    void get_winner();

    // Imprime o estado atual do jogo
    void print_state();

    // Executa uma ação baseada na posição fornecida
    bool action(int position);

    void run(CadastroJogadores& cadastro);


private:
    // Verifica se a posição fornecida é válida para o jogador atual
    bool _valid_interval(int position);

    // Captura sementes da posição fornecida e atualiza o estado do jogo
    void _capture(int position);

    // Distribui sementes e verifica se deve ocorrer captura
    bool _loop_capture_seeds(int start);

    void _process_input();

    void _update_game();

    void _draw_game();

    void _draw_seeds();

    void _build_objects();

    bool _check_mancala_player(int position);

    void _move_seeds_end();

    void _reset_game();

        // roda o jogo
    void _run_loop();

    void _shutdown();

    // Inicializa o estado do jogo
    void _initialize();

    bool _validation(CadastroJogadores& cadastro);

    // Vetor que armazena o estado do jogo (semente em cada posição e valores das mancalas)
    std::vector<int> _game_state;

    // Indica o jogador atual (false para Jogador 1, true para Jogador 2)
    bool _player;

    bool _reset;
    bool _stop;

    // Armazena o vencedor do jogo
    WINNER _winner;

    // texto
    const char* _text;
    Color _text_color;

    // Constantes para as posições das mancalas
    static const int MANCALA_0 = 6;
    static const int MANCALA_1 = 13;

    // Tamanho do vetor que representa o estado do jogo
    static const int TAMANHO_MANCALA = 14;


    // Variáveis gráficas
    Vector2 _mouse_position;

    // Vetores para os nichos circulares e mancalas retangulares
    Vector2 _nichos[12];     // 6 nichos circulares para cada jogador
    Rectangle _mancalas[2];  // 2 mancalas retangulares, uma para cada jogador
    

    Texture2D _wood_texture;

    Texture2D _seed_texture;

    std::vector<bool> _hover_nichos;
    std::vector<bool> _click_nichos;

    bool _end_game;

    bool _mouse_down; 
    bool _click_processed; 

    Jogador* _jogador0;
    Jogador* _jogador1;

};

#endif // MANCALA_HPP
