#ifndef PARTIDAS_H
#define PARTIDAS_H

// Estrutura com as informações das partidas
typedef struct Partidas Partidas;

//
Partidas* criar_nova_partida(int id_novo, int id_time1, int id_time2, int placar1, int placar2);

// Recebe o id da partida
int recebe_id_partida(Partidas* p);

// Recebe o id do time1
int recebe_id_time1(Partidas* p);

// Recebe o id do time2
int recebe_id_time2(Partidas* p);

// Recebe os gols que o time1 fez em uma partida
int recebe_gols_time1(Partidas* p);

// Recebe os gols que o time2 fez em uma partida
int recebe_gols_time2(Partidas* p);

// Remove , ao ler algum dos arquivos de partidas
Partidas* remove_caracteres_especiais_partidascsv(char* linha_csv);

// Imprime o cabeçalho das partidas
void imprimir_cabecalho_partidas();

// Insere uma partida no banco de dados
void imprimir_partidas(void* bd_times, Partidas* p);

// Atualiza uma partida
int atualizar_bd_partida(void* bd_p, int id_p, int placar1_novo, int placar2_novo);

#endif