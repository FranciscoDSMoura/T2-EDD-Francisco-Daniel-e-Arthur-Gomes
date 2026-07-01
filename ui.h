#ifndef UI_H
#define UI_H

// Importa interfaces públicas
#include "bd_times.h"
#include "bd_partidas.h"

// Imprime na tela o menu principal
int imprimir_menu(BDTime *bd_t, BDPartidas *bd_p, const char* caminho_arquivo);

// Imprime na tela um ou mais times e suas pontuações através de uma busca por nome ou prefixo do nome
void consultar_time(BDTime *bd_t, BDPartidas *bd_p);

// Imprime na tela todas as partidas de um time, podendo escolher entre um time mandante, visitante ou ambos
int consultar_partidas(BDTime *bd_t, BDPartidas *bd_p, const char* caminho_arquivo);

// Imprime a classificação final de todos os times
void imprimir_tabela_classificacao(BDTime *bd_t, BDPartidas *bd_p);

#endif