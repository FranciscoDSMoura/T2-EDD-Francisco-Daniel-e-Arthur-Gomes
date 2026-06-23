#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

// Importa interfaces públicas
#include "partidas.h"

#define MAX_PARTIDAS 90

typedef struct NoPartida NoPartida;

typedef struct bd_partidas BDPartidas;

// Cria um banco de dados para as partidas
BDPartidas* criar_bd_partidas() ;

// Libera a memória do banco de dados de partidas
void destruir_bd_partidas(BDPartidas *bd);

//int bd_partidas_carregar(BDPartidas* bd_p, const char* caminho_arquivo);
void carregar_partidas_csv(BDPartidas *bd, const char *caminho_arquivo);

// Insere uma partida no banco de dados
void inserir_partida(BDPartidas *bd, Partidas p);

// Imprime o cabeçalho das partidas
void imprimir_cabecalho();

// Busca e imprime as partidas do time mandante escolhido
void buscar_por_mandante(void *bd_t, BDPartidas *bd_p, int paginacao);

// Busca e imprime as partidas do time visitante escolhido
void buscar_por_visitante(void *bd_t, BDPartidas *bd_p, int paginacao);

// Busca e imprime as partidas do time escolhido, seja ele mandante ou visitante
void buscar_por_m_ou_v(void *bd_t, BDPartidas *bd_p, int paginacao);

void salvar_arquivo_partidas(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo_escrever);


NoPartida* recebe_primeira_partida(BDPartidas *bd_p);


NoPartida* recebe_proxima_partida(NoPartida *atual);


Partidas* recebe_NoPartida_partida(NoPartida *atual);

#endif
