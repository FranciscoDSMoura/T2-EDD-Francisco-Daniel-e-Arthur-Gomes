#ifndef TIME_H
#define TIME_H

#include <stdio.h>

// Estrutura que armazena as informações dos times
typedef struct Time Time;

// Zera todas as estatísticas de um time passando apenas o ponteiro dele
void time_zerar_estatisticas(Time *t);

// Remove , ao ler o arquivo times.csv
Time* remove_caracteres_especiais_timecsv(char *linha_csv);

// Imprime as informações do time (ID, nome, vitórias, ...)
void imprimir_time(Time* t);

// Salva as informações do time em um arquivo
void salvar_time_arquivo(Time* t, FILE* arquivo);

// Calcula a pontuação de um time após todas as suas partidas
void calcula_pontuacoes_time(Time *t, void* p);

int recebe_id_do_time(Time* t);
char* recebe_nome_do_time(Time* t);

#endif