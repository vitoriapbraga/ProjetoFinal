#include "Table.hpp"



int JogarReversi(CadastroJogadores& cadastro)
{
    Table t;
    
     if (t.settings(cadastro) == -1) {
        
        return 0;  // Retorna para o menu
    }

    t.game(cadastro);

    return 0;
}
/**
 
 Permite ao usuário configurar a mesa
 
 */
int Table::settings(CadastroJogadores& cadastro) {
    // saudando os usuários
    std::cout << "Bem-vindo ao Jogo Othello :" << endl
         << endl
         << "1 para humano vs cpu" << endl
         << "2 para humano vs humano" << endl
         << "3 para cpu vs cpu" << endl
         << "4 para carregar um jogo de um arquivo" << endl
         << endl
         << "Digite sua escolha: ";

    // obtendo a escolha
    char temp;
    std::cin >> temp;
    GameMode choice = (GameMode)stoi(&temp);
    std::cout << endl;
    // verificando a escolha
    try
    {
        if (choice != HUMANO_VS_HUMANO && choice != HUMANO_VS_CPU && choice != CPU_VS_CPU && choice != LOAD_GAME)
        {
            throw "Modo de jogo invalido\n";
            
        }
    }
    catch (const char *msg)
    {
        std::cerr << msg;
        return -1;
    }
    setGameMode((GameMode)choice);

    if (getGameMode() == HUMANO_VS_CPU || getGameMode() == HUMANO_VS_HUMANO) {
        cout << "Digite o apelido do jogador 1 (PRETO):" << endl;
        cin >> jogador1;

        if(!cadastro.jogadorExiste(jogador1)) {
            cout << "Jogador nao existe" << endl;
            return -1;
        }           


        if (getGameMode() == HUMANO_VS_CPU) {
  
            setUserSide(BLACK);
            jogador2 = "IA";
           


        } else if (getGameMode() == HUMANO_VS_HUMANO) {
            cout << "Digite o apelido do jogador 2 (BRANCO):" << endl;
            cin >> jogador2;

            if(!cadastro.jogadorExiste(jogador2)) {
                cout << "Jogador nao existe" << endl;
                return -1;
            }


        }
    }  


    if (getGameMode() == LOAD_GAME)
    {
        std::cout << "Digite o nome do arquivo: ";
        string fileName;
        std::cin >> fileName;
        fstream file;
        // abrir o arquivo no modo de leitura
        try
        {
            file.open(fileName, ios::in);
            if (!file.is_open())
            {
                throw "Arquivo nao encontrado\n";
                return -1;
            }
        }
        catch (const char *msg)
        {
            std::cerr << msg;
            return -1;
        }
        file.close();
        // verificar se o arquivo possui dados válidos
        this->moves = loadFromFile(fileName);
        try
        {
            if (!checkFile())
            {
                throw "Arquivo invalido\n";
            }
        }
        catch (const char *msg)
        {
            std::cerr << msg;
            return -1;
        }
    }
    char guid;
    std::cout << "Voce gostaria de orientacao? (\'S\' para SIM e \'N\' para NAO): ";
    std::cin >> guid;
    if (guid == 's' || guid == 'S')
        setGuidance(true);
    else
        setGuidance(false);

    return 0;
}

/**

O jogo é processado aqui.

 */
void Table::game(CadastroJogadores& cadastro)
{
    // O jogo começa
    coor c;
    while (true)
    {
        printBoard();

        if (!hasTileToFlip())
            break;

        // imprime o lado para indicar qual lado está jogando
        if (getTurn() == BLACK)
            std::cout << "\n" << jogador1 << " (Black)\n";
        else
            std::cout << "\n" << jogador2 << " (White)\n";

        // obtendo coordenadas dos jogadores
        if (getGameMode() == HUMANO_VS_CPU)
        {
            if (getTurn() == getUserSide())
            {
                c = userPlays();
            }
            else
            {
                c = cpuPlays();
            }
        }
        else if (getGameMode() == HUMANO_VS_HUMANO)
        {
            c = userPlays();
        }
        else if (getGameMode() == CPU_VS_CPU)
        {
            c = cpuPlays();
        }
        else if (getGameMode() == LOAD_GAME)
        {
            c = filePlays();
        }

        // as peças legais são viradas aqui
        flipTiles(c);

        // troca o lado quando uma jogada é feita
        switchTurn();

        // caso não haja jogada legal para o próximo jogador, o lado é trocado
        if (!hasTileToFlip())
        {
            switchTurn();
            if (!hasTileToFlip()) {
                // Se nenhum jogador tiver jogadas legais, o jogo termina
                break;
            }
        }
    }

    // O jogo terminou, contar os quadrados pretos e brancos
    int blacks = 0;
    int whites = 0;

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (getBoard({row, col}) == BLACK)
                blacks++;

            if (getBoard({row, col}) == WHITE)
                whites++;
        }
    }

    // Imprime o resultado final
    if (blacks == whites) {
        if(cadastro.jogadorExiste(jogador1))
        ResultadoJogador(*cadastro.obterJogador(jogador1), "REVERSI", 1);

        if(cadastro.jogadorExiste(jogador2))
        ResultadoJogador(*cadastro.obterJogador(jogador2), "REVERSI", 1);

        cout << "EMPATE";
    } else {

        if (blacks > whites) {
        
        if(cadastro.jogadorExiste(jogador1))
        ResultadoJogador(*cadastro.obterJogador(jogador1), "REVERSI", 3);

        if(cadastro.jogadorExiste(jogador2))
        ResultadoJogador(*cadastro.obterJogador(jogador2), "REVERSI", 0);

        cout << "O jogador " << jogador1 << " (preto) venceu." << endl;

        std::cout << "PONTUACAO" << endl
                  << "Preto: " << blacks << endl
                  << "Branco: " << whites;

        } else {
        
        if(cadastro.jogadorExiste(jogador2))
        ResultadoJogador(*cadastro.obterJogador(jogador2), "REVERSI", 3);

        if(cadastro.jogadorExiste(jogador1))
        ResultadoJogador(*cadastro.obterJogador(jogador1), "REVERSI", 0);

        cout << "O jogador " << jogador2 << " (Branco) venceu." << endl;

        std::cout << "PONTUACAO" << endl
                  << "Preto: " << blacks << endl
                  << "Branco: " << whites;

        }
        
    }

    // Pergunta ao usuário se ele deseja salvar o jogo em um arquivo
    if (getGameMode() != LOAD_GAME)
    {
        char choice;
        std::cout << "\n\nVoce deseja salvar o jogo em um arquivo? (s/n) ";
        std::cin >> choice;
        if (choice == 's' || choice == 'S')
        {
            std::cout << "\nDigite o nome do arquivo: ";
            string fileName;
            std::cin >> fileName;
            saveMoves(fileName);
        }
    }
    cout << "Pressione Enter para voltar ao menu" << endl;
        std::cin.ignore();
        std::cin.get();

}