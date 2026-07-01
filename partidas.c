// Importa a própria interface pública
#include "partidas.h"
#include "bd_times.h"
#include "bd_partidas.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Partidas{
    int id;           
    int id_time1;     
    int id_time2;     
    int gols_time1;   
    int gols_time2;   
};

Partidas* criar_nova_partida(int id_novo, int id_time1, int id_time2, int placar1, int placar2){
    Partidas *p = malloc(sizeof(Partidas));
    if (!p) return NULL;

    p->id = id_novo;
    p->id_time1 = id_time1;
    p->id_time2 = id_time2;
    p->gols_time1 = placar1;
    p->gols_time2 = placar2;

    return p;
}

int recebe_id_partida(Partidas* p){ return p->id; }
int recebe_id_time1(Partidas *p) { return p->id_time1; }
int recebe_id_time2(Partidas *p) { return p->id_time2; }
int recebe_gols_time1(Partidas *p) { return p->gols_time1; }
int recebe_gols_time2(Partidas *p) { return p->gols_time2; }

// Remove , e lixos
Partidas* remove_caracteres_especiais_partidascsv(char *linha_csv)
{
    Partidas* p = malloc(sizeof(Partidas));
    if (!p) return NULL;

    char *token;

    token = strtok(linha_csv, ",");
    p->id = token ? atoi(token) : 0; // ID da partida

    token = strtok(NULL, ",");
    p->id_time1 = token ? atoi(token) : 0; // ID do time1

    token = strtok(NULL, ",");
    p->id_time2 = token ? atoi(token) : 0; // ID do time2

    token = strtok(NULL, ",");
    p->gols_time1 = token ? atoi(token) : 0; // Qtd de gols do time1

    token = strtok(NULL, ",\n\r");
    p->gols_time2 = token ? atoi(token) : 0; // Qtd de gols do time2

    return p;
}

void imprimir_cabecalho_partidas(){
    printf("\n%-3s  %-16s  %-12s  %-10s  %-5s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
}

void imprimir_partidas(void* bd_times, Partidas* p){
    void *mandante = buscar_time_por_id(bd_times, p->id_time1);
    void *visitante = buscar_time_por_id(bd_times, p->id_time2);

    const char* nome_m = mandante ? procura_nome_do_no(mandante) : "Desconhecido";
    const char* nome_v = visitante ? procura_nome_do_no(visitante) : "Desconhecido";

    printf("\n%-3d  %-16s  %-12s  %-10d  %-2d\n",
           p->id, nome_m, nome_v, p->gols_time1, p->gols_time2);
}

int atualizar_bd_partida(void* bd_p, int id_p, int placar1_novo, int placar2_novo){
    NoPartida* atual = recebe_BDPartidas_inicio(bd_p);

    while(atual){
        Partidas* p = recebe_partida_do_no(atual);
        if(p->id == id_p){
            p->gols_time1 = placar1_novo;
            p->gols_time2 = placar2_novo;
            return 1;
        }
        atual = recebe_proxima_partida(atual);
    }
    return 0; // Partida não encontrada
}