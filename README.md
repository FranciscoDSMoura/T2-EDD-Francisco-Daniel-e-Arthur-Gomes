# Trabalho-2-EDD

Este projeto consiste em um sistema de gerenciamento de dados de um campeonato de futebol simplificado, desenvolvido em Linguagem C como parte do trabalho prático da disciplina estrutura de dados.

## 1 - Requisitos para executar

GCC 11

Linux Ubuntu V24.04

## 2 - Como Executar

`make` - _Compila automaticamente todos os módulos e executa o programa

`clear` - _Limpa o terminal

## 3 - Arquivos

`main.c`: Ponto de entrada que gerencia o fluxo principal e inicialização dos bancos de dados.

`time.h` / `time.c`: TAD que modela uma equipe individual e suas estatísticas (V, E, D, GM, GS, etc.).

`ui.c / .h`: Gerencia a Interface de Usuário, menus e interações de entrada.

`bd_times.h` / `bd_times.c`: TAD responsável por gerenciar a coleção de times e carregar o arquivo times.csv.

`partida.h` / `partida.c`: TAD que representa as informações de um jogo específico.

`bd_partidas.h` / `bd_partidas.c`: TAD que gerencia o histórico de jogos e carrega o arquivo partidas.csv.

`classificacao.h` / `classificacao.c`: TAD que calcula as pontuações/classificação dos times após todo o campeonato

`Makefile`: Arquivo de automação da compilação.

## 4 - Estruturas utilizadas

**BDTime (Lista Encadeada Simples):** Armazena os nós contendo a estrutura `Time` de cada equipe (ID, Nome, V, E, D, GM, GS, S, PG). As inserções ocorrem de forma dinâmica.

**BDPartidas (Lista Encadeada Simples):** Armazena os nós contendo a estrutura `Partidas` (ID do jogo, ID do Mandante, ID do Visitante, Gols do Mandante, Gols do Visitante). Suporta inserções e remoções dinâmicas de nós através de manipulação de ponteiros (`proximo`).

## 5 - Regras de pontuação:

+ Vitória: +3 pontos.

+ Empate: +1 ponto.

+ Derrota: 0 pontos.

## 6 - Descrição das Funcionalidades (Parte I)

* 6.1 **Consulta de Times:** Busca por nome ou prefixo (case-insensitive).

Exemplo de Busca por Prefixo
Se o usuário desejar buscar os times que começam com "SE":
- **Entrada:** `se`
- **Saída:**
  
| ID | Time | V | E | D | GM | GS | S | PG |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **2** | SemCTRL | 3 | 1 | 0 | 10 | 4 | 6 | 10 |
     
  
  | ID    | Time     | V | E | D | GM | GS | S  | PG |
  | :---: | :---:    |:-:|:-:|:-:|:-: |:-: |:-: |:-: |
  | **5** | SeQueLas | 6 | 2 | 5 | 25 | 12 | 13 | 10 | 

* 6.2 **Consulta de Partidas:** Filtros por mandante, visitante ou ambos.

| ID    | Time1   |    -    |  Time 2  |
| :---: | :----:  |  :----: | :------: |
| **0** | JAVAlis |  5 x 4  | NETunos  |
| **4** | PYthons |  2 x 2  | SEquelas |

* 6.3 **Atualizar Partida:** Permite modificar o placar (gols do mandante e do visitante) de um jogo existente através do seu ID. O sistema recalcula automaticamente as estatísticas de classificação dos times envolvidos.

* 6.4 **Remover Partida:** Exclui uma partida do banco de dados usando o ID do jogo, ajustando e subtraindo os pontos correspondentes dos times na memória.

* 6.5 **Inserir Partida:** Registra um novo confronto entre dois times informando os IDs e os gols marcados, inserindo o nó dinamicamente na lista encadeada de partidas.

6.6 **Imprimir Tabela de Classificação (Ordenada):** Gera o ranking atualizado do campeonato. Os times são ordenados através do algoritmo `qsort`, utilizando os os critérios de desempate.

Ao selecionar a **opção 6** no menu, o sistema gera o seguinte relatório de desempenho dos times:

| ID | Time | Vitórias | Empates | Derrotas | GM | GS | Saldo | PG |
| :---: | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **0** | JAVAlis | 3 | 1 | 0 | 10 | 4 | +6 | **10** |
| **4** | PYthons | 2 | 2 | - | - | - | - | **-** |

## 7 - Lógica de Ordenação e Desempate (Opção 6)

1. **Pontos Ganhos (PG):** Maior pontuação fica acima (Decrescente).
2. **Vitórias (V):** Maior número de vitórias (Decrescente).
3. **Saldo de Gols (S):** Maior saldo (Decrescente).
4. **Gols Marcados (GM):** Maior quantidade de gols pró (Decrescente).
5. **ID do Time:** Caso todos os critérios anteriores sejam idênticos, o time com o menor ID tem preferência (Crescente).
