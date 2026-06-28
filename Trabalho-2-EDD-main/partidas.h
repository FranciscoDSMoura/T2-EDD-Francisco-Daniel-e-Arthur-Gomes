#ifndef PARTIDAS_H
#define PARTIDAS_H

// Estrutura com as informações das partidas
typedef struct Partidas Partidas;

int recebe_id_partida(Partidas* p);
int recebe_id_time1(Partidas* p);
int recebe_id_time2(Partidas* p);
int recebe_gols_time1(Partidas* p);
int recebe_gols_time2(Partidas* p);

// Remove , ao ler algum dos arquivos de partidas
Partidas* remove_caracteres_especiais_partidascsv(char* linha_csv);

// Imprime o cabeçalho das partidas
void imprimir_cabecalho_partidas();

// Insere uma partida no banco de dados
void imprimir_partidas(void* bd_times, Partidas* p);

#endif