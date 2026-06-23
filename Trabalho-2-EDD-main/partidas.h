#ifndef PARTIDAS_H
#define PARTIDAS_H

// Estrutura com as informações das partidas
typedef struct Partidas Partidas;

// Remove , ao ler algum dos arquivos de partidas
Partidas remove_caracteres_especiais_partidascsv(char *linha_csv);

#endif