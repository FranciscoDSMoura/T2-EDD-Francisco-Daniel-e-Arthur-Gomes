#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

// Importa interfaces públicas
#include "partidas.h"

#define MAX_PARTIDAS 90

typedef struct NoPartida NoPartida;

typedef struct bd_partidas BDPartidas;

// Cria um banco de dados para as partidas
BDPartidas* criar_bd_partidas();

int remover_partida(BDPartidas *bd_p, int id);

// Libera a memória do banco de dados de partidas
void destruir_bd_partidas(BDPartidas *bd);

// Encontra a partida através de seu ID
NoPartida* buscar_partida_por_id(BDPartidas *bd, int id);

//int bd_partidas_carregar(BDPartidas* bd_p, const char* caminho_arquivo);
void carregar_partidas_csv(BDPartidas *bd, const char *caminho_arquivo);

// Atualiza o arquivo partidas_completo.csv
void atualizar_partidas_csv(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo);

// Busca e imprime as partidas do time mandante escolhido
void buscar_por_mandante(void *bd_t, BDPartidas *bd_p, int paginacao);

// Busca e imprime as partidas do time visitante escolhido
void buscar_por_visitante(void *bd_t, BDPartidas *bd_p, int paginacao);

// Busca e imprime as partidas do time escolhido, seja ele mandante ou visitante
void buscar_por_m_ou_v(void *bd_t, BDPartidas *bd_p, int paginacao);

// Salva todas as partidas atuais em arquivo
void salvar_arquivo_partidas(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo_escrever);

// Recebe a última partida da lista
void* recebe_BDPartidas_inicio(BDPartidas* bd_p);

// Retorna o ponteiro para a estrutura interna de dados de uma partida de forma genérica
void* recebe_partida_do_no(NoPartida *atual_partida);

// Recebe a proxima partida da lista
void* recebe_proxima_partida(NoPartida *atual);

// Insere uma nova partida na lista encadeada e reescreve o arquivo com essa nova partida
void salvar_nova_partida(void* bd_time, BDPartidas* bd_p, const char* caminho_arquivo);

// // Atualiza uma partida na lista encadeada e reescreve o arquivo com essa partida já atualizada
void atualizar_partida(void* bd_time, BDPartidas* bd_p, const char* caminho_arquivo);

// Remove uma partida na lista encadeada e reescreve o arquivo sem essa partida
void remover_partida_arquivo(void* bd_time, BDPartidas* bd_p, const char* caminho_arquivo);

#endif
