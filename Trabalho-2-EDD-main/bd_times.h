#ifndef TIMES_H
#define TIMES_H

// Importa uma interface pública
#include "time.h"

#include <stdio.h>

// Nó da linked list, contendo um time e o ponteiro para o próximo
typedef struct no_time NoTime;

// Aponta para o início da lista de times
typedef struct bd_time BDTime;

// Cria uma lista vazia (banco de dados dos times)
BDTime *criar_bd_time(void);

// Libera toda a memória alocada pelo banco
void destruir_bd_time(BDTime *bd); 

// Insere as informações de um time no banco de dados
void inserir_time(BDTime *bd, Time* t);

// Carrega os times do arquivo times.csv
void carregar_times_csv(BDTime *bd, const char *caminho_arquivo);

// Imprime o cabeçalho de time
void imprimir_cabecalho();

// Salva o cabeçalho de time em arquivo
void salvar_cabecalho_arquivo(FILE* arquivo);

// Busca o time pelo nome ou por seu prefixo
void buscar_por_nome(BDTime *bd_t, void *bd_p, char *prefixo, int paginacao);

// Encontra um time através de seu ID
NoTime* buscar_time_por_id(BDTime *bd, int id);

// Salva todas as partidas em um arquivo
void bd_salvar_arquivo(BDTime *bd, const char *caminho_arquivo);

void* recebe_BDTime_inicio(BDTime* bd_t);

void* recebe_NoTime_proximo(NoTime* atual);

void* recebe_time_do_no(NoTime* atual_time);

const char* procura_nome_do_no(NoTime *n);

// Atualiza as estatísticas de um time no banco de dados
//int atualizar_estatisticas_time(BDTime *bd, int id, Time novo);

// Remove um time do banco de dados
//int remover_bd_times(BDTime *bd, int id);

#endif