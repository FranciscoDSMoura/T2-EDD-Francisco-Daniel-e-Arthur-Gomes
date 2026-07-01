#ifndef CLASSIFICACAO_H
#define CLASSIFICACAO_H

// Importa interfaces públicas
#include "time.h"
#include "bd_partidas.h"
#include "partidas.h"

// Registra no banco de dados de time a pontuação completa de cada um dos times
void classificacao_completa(void* bd_t, void* bd_p);

// Salva a pontuação completa dos times no arquivo bd_classificacao.csv
void salvar_arquivo_classificacao(void *bd_t, void *bd_p, const char* caminho_arquivo);

#endif