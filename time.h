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

// Recebe o ID de um time
int recebe_id_do_time(Time* t);

// Recebe o nome de um time
char* recebe_nome_do_time(Time* t);

// Compara diferente pontuações de 2 times para não haver empates
int comparar_times(const void* a, const void* b);

// Imprime a tabela ordenada
void imprimir_time_com_classificacao(Time* t, int i);

// Escreve a tabela ordenada no arquivo
void salvar_time_com_classificacao(Time* t, int i, FILE* arquivo);

#endif
