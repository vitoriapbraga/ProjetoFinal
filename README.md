# Projeto com SFML

Este projeto utiliza a biblioteca gráfica **SFML** (Simple and Fast Multimedia Library), na versão **2.6.1**. Para compilar e executar o programa adequadamente, é necessário que você tenha esta mesma versão da SFML instalada em seu ambiente de desenvolvimento.

## Pré-requisitos

- **SFML 2.6.1**: Certifique-se de que você possui a versão 2.6.1 da SFML instalada. Outras versões podem não ser compatíveis com o código deste projeto.
- **Compilador C++**: Um compilador compatível com C++11 ou superior.

## Instruções de Configuração

1. **Baixe a SFML 2.6.1:**
   - Acesse o [site oficial da SFML](https://www.sfml-dev.org/download.php) e baixe a versão 2.6.1 para o seu sistema operacional.
   - Extraia os arquivos em um local de sua preferência.

2. **Compilação e Execução:**
   - Compile o projeto utilizando o Makefile.
   - As bibliotecas dinâmicas da SFML (como `sfml-graphics`, `sfml-window`, `sfml-system`, etc.) estão acessíveis durante a execução do programa, pois estão arquivadas no diretório `bin/`.

## Estrutura do Projeto

O repositório está organizado da seguinte forma:

- `src/` : Contém o código-fonte do projeto.
- `include/` : Cabeçalhos e arquivos de inclusão.
- `bin/` : Arquivos executáveis gerados após a compilação.
- `obj/` : Arquivos objeto gerados durante a compilação.
- `tests/` : Código relacionado aos testes do projeto.
- `third-parties/` : Bibliotecas de terceiros (incluindo SFML).

## Mancala
As regras do jogo estão no PDF, ou então podem ser acessadas no site: https://brainking.com/pt/GameRules?tp=103


## Observações

- Para garantir que o programa funcione corretamente em diferentes máquinas, é crucial utilizar a versão 2.6.1 da SFML. Outras versões podem causar comportamentos inesperados ou falhas durante a execução.
- Se estiver utilizando uma versão diferente da SFML, é recomendado atualizar para a versão 2.6.1 antes de prosseguir, a fim de evitar erros inesperados.
