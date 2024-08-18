#include "Table.hpp"

/**
 Imprime o tabuleiro com dois loops for aninhados
 
 */
void Table::printBoard()
{
    int row, col;

    // Limpa a tela (comando específico para Windows)
    system("cls");
    cout << " ";

    // Imprimindo os números das colunas para uma melhor compreensão das coordenadas
    for (row = 0; row < SIZE; row++)
        cout << " " << row + 1;

    cout << endl;

    // Loop externo para percorrer as linhas do tabuleiro
    for (row = 0; row < SIZE; row++)
    {
        // Imprime o número da linha atual no início de cada linha
        cout << row + 1 << " ";

        // Loop interno para percorrer as colunas do tabuleiro
        for (col = 0; col < SIZE; col++)
        {
            // Se a orientação do usuário estiver desativada
            // os quadrados legais são escondidos e substituídos por EMPTY
            if (!getGuidance())
            {
                if (getBoard({row, col}) == LEGAL)
                {
                    cout << EMPTY << " ";
                    continue; // Pula para a próxima iteração do loop
                }
            }
            // Imprime o valor atual do tabuleiro (peça ou espaço vazio)
            cout << getBoard({row, col}) << " ";
        }
        // Imprime o número da linha novamente no final de cada linha
        cout << row + 1;
        cout << endl;
    }

    // Imprime novamente os números das colunas no final do tabuleiro
    cout << " ";
    for (row = 0; row < SIZE; row++)
        cout << " " << row + 1;
}




/**
 Em resumo, a função flipTiles verifica se um movimento feito pelo jogador é válido, e se for, 
 vira as peças do oponente que foram cercadas pelo movimento do jogador, 
 alterando-as para a cor do jogador atual. Se o movimento não for válido, a função lança uma exceção.
 */
void Table::flipTiles(coor move)
{
    coor curr(move), toFlip(move);
    bool isFlipped = false;
    // guarda de movimento válido caso haja um problema com a função isLegal
    bool isValid = false;

    // para cada direção
    for (auto dir : DIRS)
    {
        isFlipped = false;
        for (int i = 1;; i++)
        {
            // multiplicando por 'i' para mover ao longo das direções
            curr.row = move.row + dir[0] * i;
            curr.col = move.col + dir[1] * i;

            // se a casa não está no tabuleiro, então não é um movimento legal
            if (!isOnBoard(curr))
                break;

            // se a casa está vazia, o objetivo não foi alcançado
            if (getBoard(curr) == EMPTY || getBoard(curr) == LEGAL)
                break;

            // isFlipped muda para true se houver uma peça a ser virada
            // quando a casa do jogador é encontrada, deve haver pelo menos uma peça a ser virada
            if (getBoard(curr) == getOpponent())
                isFlipped = true;

            // quando uma casa da mesma cor do jogador é encontrada
            if (getBoard(curr) == getTurn())
            {
                // se isFlipped não for true, então não é um movimento legal
                if (!isFlipped)
                    break;
                isValid = true;

                // toFlip recebe os números ao longo da direção legal
                // para virar as peças entre curr e move, não incluindo curr e move
                // [curr]-----[toFlip]-----[move]
                toFlip.row = move.row + dir[0];
                toFlip.col = move.col + dir[1];

                // atribuindo as casas, quando a direção é horizontal
                if (dir[0] == 0)
                {
                    // atribuir até curr.col
                     while (toFlip.col != curr.col)
                    {
                        // aumentar o número pelo delta
                        setBoard(toFlip, getTurn());
                        toFlip.col += dir[1];
                    }
                }

                // atribuindo as casas, quando a direção é vertical
                else if (dir[1] == 0)
                {
                    // atribuir até curr.row
                    while (toFlip.row != curr.row)
                    {
                        // aumentar o número pelo delta
                        setBoard(toFlip, getTurn());
                        toFlip.row += dir[0];
                    }
                }

                // atribuindo as casas, quando a direção é diagonal
                else
                {
                    // atribuir até curr.row e curr.col
                    while (toFlip.row != curr.row && toFlip.col != curr.col)
                    {
                        // aumentar os números pelo delta
                        setBoard(toFlip, getTurn());
                        toFlip.row += dir[0];
                        toFlip.col += dir[1];
                    }
                }
                break;
            }
        }
    }
    try
    {
        if (isValid)
        {
            this->moves.push_back(move);
            // a casa escolhida é atribuída à cor do jogador atual
            setBoard(move, getTurn());
        }
        else
        {
            throw "flipTiles: Movimento ilegal\n";
        }
    }
    catch (const char *msg)
    {
        std::cerr << msg;
    }
}



/**
 * @brief Movimentos legais são marcados com LEGAL
 *
 * @param nenhum
 *
 * @return nada
 */
void Table::marker()
{
    // Desmarca todos os quadrados previamente marcados como LEGAL
    /////////////////////////////////////////////////////
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (getBoard(coor(row, col)) == LEGAL) // Verifica se a célula está marcada como LEGAL
                setBoard({row, col}, EMPTY); // Redefine a célula para EMPTY
        }
    }
    /////////////////////////////////////////////////////

    // Marca todos os quadrados legais para o jogador atual
    /////////////////////////////////////////////////////
    // Todos os quadrados são verificados
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (isLegal(coor(row, col))) // Verifica se a célula é um movimento legal
                setBoard({row, col}, LEGAL); // Marca a célula como LEGAL
        }
    }
    /////////////////////////////////////////////////////
}


/**

Salva movimentos em um arquivo no formato linha.coluna,
 
 */
void Table::saveMoves(string fileName)
{
    ofstream file;
    file.open(fileName);
    for (size_t i = 0; i < moves.size(); i++)
    {
        file << moves[i].row << "." << moves[i].col << ",";
    }
    file.close();
}



/**
 Em resumo, o código inicializa o estado do jogo, 
 configurando um tabuleiro vazio, posicionando as peças iniciais e marcando os movimentos legais.
 */
void Table::constructor()
{
    this->moveCount = 0;

    // o jogador preto começa o jogo
    setTurn(BLACK);

    // criando um tabuleiro em branco
    for (int row = 0; row < SIZE; row++)
        for (int col = 0; col < SIZE; col++)
            setBoard({row, col}, EMPTY);

    // adicionando as casas iniciais
    setBoard({SIZE/2 - 1, SIZE/2},     BLACK);
    setBoard({SIZE/2, SIZE/2 - 1},     BLACK);
    setBoard({SIZE/2 - 1, SIZE/2 - 1}, WHITE);
    setBoard({SIZE/2, SIZE/2},         WHITE);

    // marcar movimentos legais inicialmente
    marker();
}
