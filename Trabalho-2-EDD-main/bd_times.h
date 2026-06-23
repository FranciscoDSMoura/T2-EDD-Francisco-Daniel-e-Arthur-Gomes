#ifndef TIMES_H
#define TIMES_H

// Importa uma interface pública
#include "time.h"

// Nó da linked list, contendo um time e o ponteiro para o próximo
typedef struct no_time NoTime;

// Aponta para o início da lista de times
typedef struct bd_time BDTime;

// Cria uma lista vazia (banco de dados dos times)
BDTime *criar_bd_time(void);

// Libera toda a memória alocada pelo banco
void destruir_bd_time(BDTime *bd); 

// Insere as informações de um time no banco de dados
void inserir_time(BDTime *bd, Time t);

// Carrega os times do arquivo times.csv
void bd_carregar_times_csv(BDTime *bd, const char *caminho_arquivo);

// Imprime o cabeçalho de time
void imprimir_cabecalho();

// Busca o time pelo nome ou por seu prefixo
void buscar_por_nome(BDTime *bd_t, void *bd_p, char *prefixo, int paginacao);

// Encontra um time através de seu ID
NoTime* buscar_por_id(BDTime *bd, int id);

// Busca o nome do time
const char* recebe_nome_time(NoTime *n);

// Salva todas as partidas em um arquivo
void bd_salvar_arquivo(BDTime *bd, const char *caminho_arquivo);

// Calcula a pontuação de um time após todas as partidas
void calcula_pontuacoes_time(Time *t, Partidas p);

// Registra no banco de dados de time a pontuação completa de cada um dos times
void classificacao_completa(void *bd_t, BDPartidas *bd_p);

// Salva a pontuação completa dos times no arquivo bd_classificacao.csv
void bd_salvar_arquivo_classificacao(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo);

// Atualiza as estatísticas de um time no banco de dados
//int atualizar_estatisticas_time(BDTime *bd, int id, Time novo);

// Remove um time do banco de dados
//int remover_bd_times(BDTime *bd, int id);

#endif