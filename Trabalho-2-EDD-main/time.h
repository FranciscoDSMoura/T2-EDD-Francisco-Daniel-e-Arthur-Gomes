#ifndef TIME_H
#define TIME_H

// Estrutura que armazena as informações dos times
typedef struct Time Time;

// Remove , ao ler o arquivo times.csv
Time remove_caracteres_especiais_timecsv(char *linha_csv);

// Imprime as informações do time (ID, nome, vitórias, ...)
void imprimir_time(Time t);

#endif