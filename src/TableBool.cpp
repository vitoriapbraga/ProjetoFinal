#include "Table.hpp"



/**
Verifica se um lado possui alguma peça para virar, algum movimento legal.
 
 */
bool Table::hasTileToFlip()
{
	// todas as posições são verificadas
	for (int linha = 0; linha < SIZE; linha++)
	{
		for (int coluna = 0; coluna < SIZE; coluna++)
		{
			if (getBoard({linha, coluna}) == LEGAL)
				return true;
		}
	}
	return false;
}

/**
 * @brief Verifica se um movimento é legal em uma direção.
 *
 coordenada dos movimentos de direção
 */
bool Table::isLegal(coor c)
{
    coor curr(c);
    bool flip = false;

    // se a coordenada não está no tabuleiro, então não é um movimento legal
    if (!this->isOnBoard(c))
        return false;

    // quadrados não vazios não podem ser preenchidos, portanto não é um movimento legal
    if (getBoard(c) != EMPTY && getBoard(c) != LEGAL)
        return false;

    // para cada direção
    for (auto dir : DIRS)
    {
        flip = false;
        for (int i = 1;; i++)
        {
            // multiplicando por "i" para mover ao longo das direções
            curr.row = c.row + dir[0] * i;
            curr.col = c.col + dir[1] * i;

            // se o quadrado não está no tabuleiro, então não é um movimento legal
            if (!isOnBoard(curr))
                break;

            // se o quadrado está vazio, interrompe
            if (getBoard(curr) == EMPTY || getBoard(curr) == LEGAL)
                break;

            // se o quadrado não é do mesmo jogador, atribui flip como verdadeiro e continua
            if (getBoard(curr) == getOpponent())
            {
                flip = true;
                continue;
            }

            // se o quadrado é do jogador atual e pelo menos uma peça foi virada
            // então é um movimento legal
            if (getBoard(curr) == getTurn())
            {
                if (flip)
                    return true;
                else
                    break;
            }
        }
    }
    // se nenhum movimento legal for encontrado, então não é um movimento legal
    return false;
}

/**
 Verifica se a coordenada está dentro do alcance do tamanho, que são coordenadas válidas
 * coor c: coordenada dos movimentos
 */
bool Table::isOnBoard(coor c)
{
    if (c.row >= 0 && c.row < SIZE && c.col >= 0 && c.col < SIZE)
        return true;
    else
        return false;
}

/**
Este código verifica se os movimentos em um arquivo são válidos simulando o jogo. 
Ele lê cada movimento, verifica sua legalidade, aplica o movimento se for legal, alterna os turnos e, no final, 
reconstrói o tabuleiro ao seu estado original.
 */

bool Table::checkFile()
{
    // Verifica se o arquivo está vazio
    if (moves.size() == 0)
    {
        return false;
    }
    // Simulando o jogo
    coor c;
    marker();
    while (true)
    {
        if (!hasTileToFlip())
            break;
        c = fileMoves();
        // Se algum movimento ilegal for encontrado, o arquivo não é válido
        if (!isLegal(c))
            return false;
        // Telhas legais são viradas aqui
        flipTiles(c);
        // Alterna o lado quando um movimento é feito
        switchTurn();
        // Caso não haja movimento legal para o próximo usuário, o lado é alternado
        if (!hasTileToFlip())
        {
            switchTurn();
        }
    }
    // Reconstruindo o tabuleiro
    constructor(); // void type function
    return true;
}