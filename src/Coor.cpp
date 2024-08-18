#include "Table.hpp"
#include "Coor.hpp"
#include "Constantes.hpp"



/**
 Este método é útil em um jogo ou aplicação que requer entrada do usuário para selecionar posições em um tabuleiro, 
 garantindo que apenas posições válidas sejam aceitas.
 */
coor Table::userPlays()
{
    coor c;
    do
    {
        cout << "linha e coluna\n";
        cin >> c.row >> c.col;

        // para corresponder ao índice do array
        c.row--;
        c.col--;
        if (getBoard(c) == LEGAL)
            return c;

        cout << "\nPosicao invalida!!!" << endl
             << "Insira novamente\n\n";
    } while (true);
}

/**
 Este código simula um jogador de CPU em um jogo de tabuleiro. 
 A CPU verifica todas as posições do tabuleiro para encontrar movimentos legais, 
 escolhe um desses movimentos aleatoriamente e realiza o movimento com um atraso para simular o 
 tempo de pensamento da CPU. 
 As coordenadas do movimento escolhido são impressas para o usuário ver.
 */
coor Table::randomMoves()
{
    int random;
    vector<vector<int>> moves;
    for (int row = 0; row < SIZE; row++) // tenta todas as casas no tabuleiro se elas são legais
    {
        for (int col = 0; col < SIZE; col++)
        {
            // se elas são legais, elas são salvas
            if (getBoard({row, col}) == LEGAL)
                moves.push_back({row, col});
        }
    }
    srand(time(NULL));
    random = rand() % moves.size(); // gera números aleatórios [0, count)
    coor c;
    c.row = moves[random][0];
    c.col = moves[random][1];
    return c;
}

/**
o parâmetro delay, atrasa em milissegundos
 
 */
coor Table::cpuPlays()
{
    coor c(randomMoves());
    // para uma melhor experiência de jogo, imprime os movimentos da CPU
    cout << "row: " << c.row + 1 << endl;
    cout << "col: " << c.col + 1 << endl;
    return c;
}



/**
fileMoves(): Retorna o próximo movimento a partir de um arquivo de movimentos.

filePlays(unsigned delayInMs): Retorna o próximo movimento a partir de um arquivo de movimentos, 
com atrasos antes e depois de imprimir as coordenadas do movimento.

Essas funções são úteis para automatizar movimentos em um jogo de tabuleiro, possivelmente 
para simular jogadas de um adversário de IA ou para carregar uma sequência predefinida de movimentos.
 */
coor Table::fileMoves()
{
	// retorna movimentos dos arquivos
	return moves[moveCount++];
}

/**
 O parâmetro delay, atrasa em milissegundos
 */
coor Table::filePlays()
{
	coor c = fileMoves();
	// para uma melhor experiência de jogo, imprime os movimentos da CPU
	cout << "linha: " << moves[moveCount].row + 1 << endl;
	cout << "coluna: " << moves[moveCount].col + 1 << endl;
	return c;
}


////////////////// load from file //////////////////

// o tabuleiro tem elementos de tamanho SIZE x SIZE
// 4 deles são inicializados
// isso resulta em SIZE * SIZE - 4
// os movimentos são salvos no formato linha.coluna
// portanto, é multiplicado por 4

#define LENGTH (SIZE * SIZE - 4) * 4

/**
 
 Em resumo, este código lê movimentos de um arquivo, onde cada movimento está 
 no formato linha.coluna, e retorna esses movimentos como um vetor de coordenadas.

 */
vector<coor> Table::loadFromFile(string fileName)
{
    std::vector<coor> moves;
    coor c;
    ifstream file;
    char text[LENGTH];
    // copia os movimentos do arquivo para uma string
    file.open(fileName);
    file.getline(text, LENGTH);
    file.close();
    char *ptr;
    // o delimitador é um ponto (.)
    // porque as linhas terminam com um ponto
    // usa a função strtok() para separar a string usando o delimitador
    ptr = strtok(text, ".");
    while (ptr != NULL)
    {
        // usa a função stoi() para converter string em inteiro
        c.row = stoi(ptr);
        // o delimitador é uma vírgula (,)
        // porque as colunas terminam com uma vírgula
        ptr = strtok(NULL, ",");
        c.col = stoi(ptr);
        moves.push_back(c);
        ptr = strtok(NULL, ".");
    }
    return moves;
}
