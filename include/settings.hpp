#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#define SCREEN_TITLE "Mancala"
#define FPS 60

// Configurações dos nichos e mancalas
#define NICHOS_RADIUS 48
#define NICHOS_SPACING_H 20
#define NICHOS_SPACING_V (MANCALA_HEIGHT - 4 * NICHOS_RADIUS)
#define MANCALA_WIDTH 80
#define MANCALA_HEIGHT 200
#define MARGIN_H 30
#define MARGIN_V 100
#define NICHOS_COUNT 12

#define SEED_RADIUS (NICHOS_RADIUS/4)

// Configurações de Tela
#define SCREEN_WIDTH (2 * MARGIN_H + 12 * NICHOS_RADIUS + 2 * MANCALA_WIDTH + 7 * NICHOS_SPACING_H)
#define SCREEN_HEIGHT (2 * MARGIN_V + MANCALA_HEIGHT)

// Textura base de madeira
#define WOOD_TEXTURE "textures/nogueira_asti.png"
#define SEED_TEXTURE "textures/seed.png"

// Cores
#define NICHOS_COLOR RAY_BROWN
#define MANCALA_COLOR RAY_BROWN
#define NICHOS_DEPTH_COLOR RAY_DARKBROWN
#define MANCALA_SHADOW_COLOR RAY_DARKBROWN

// Ativar shaders para profundidade
#define ENABLE_SHADERS true

#endif // SETTINGS_HPP
