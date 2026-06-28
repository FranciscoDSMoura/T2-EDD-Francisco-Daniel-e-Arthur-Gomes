#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

// Importa interfaces públicas
#include "partidas.h"

#define MAX_PARTIDAS 90

typedef struct NoPartida NoPartida;

typedef struct bd_partidas BDPartidas;

// Cria um banco de dados para as partidas
BDPartidas* criar_bd_partidas();

// Libera a memória do banco de dados de partidas
void destruir_bd_partidas(BDPartidas *bd);

// 
NoPartida* buscar_partida_por_id(BDPartidas *bd, int id);

//int bd_partidas_carregar(BDPartidas* bd_p, const char* caminho_arquivo);
void carregar_partidas_csv(BDPartidas *bd, const char *caminho_arquivo);

// Busca e imprime as partidas do time mandante escolhido
void buscar_por_mandante(void *bd_t, BDPartidas *bd_p, int paginacao);

// Busca e imprime as partidas do time visitante escolhido
void buscar_por_visitante(void *bd_t, BDPartidas *bd_p, int paginacao);

// Busca e imprime as partidas do time escolhido, seja ele mandante ou visitante
void buscar_por_m_ou_v(void *bd_t, BDPartidas *bd_p, int paginacao);

//
void salvar_arquivo_partidas(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo_escrever);

//
void* recebe_BDPartidas_inicio(BDPartidas* bd_p);

// Retorna o ponteiro para a estrutura interna de dados de uma partida de forma genérica
void* recebe_partida_do_no(NoPartida *atual_partida);

//
void* recebe_proxima_partida(NoPartida *atual);

#endif
