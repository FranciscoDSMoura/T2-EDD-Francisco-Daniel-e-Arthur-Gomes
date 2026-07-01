// Importa a própria interface pública
#include "time.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Importa uma outra interface pública
#include "partidas.h"

struct Time{
    int id;
    char nome[50];
    int vitorias;
    int empates;
    int derrotas;
    int gols_m;
    int gols_s;
    int saldo_gols;
    int pontos_ganhos;
};

void time_zerar_estatisticas(Time *t) {
    t->vitorias = 0;
    t->empates = 0;
    t->derrotas = 0;
    t->gols_m = 0;
    t->gols_s = 0;
    t->saldo_gols = 0;
    t->pontos_ganhos = 0;
}

// Converte uma linha CSV em um struct Time
Time* remove_caracteres_especiais_timecsv(char *linha_csv)
{
    Time* t = malloc(sizeof(Time));
    if(!t) return NULL;
    
    char *token;

    token = strtok(linha_csv, ","); // ID
    t->id = token ? atoi(token) : 0;

    token = strtok(NULL, ","); // Nome
    strncpy(t->nome, token ? token : "", sizeof(t->nome));
    t->nome[sizeof(t->nome) - 1] = '\0';

    t->nome[strcspn(t->nome, "\r\n")] = '\0';

    return t;
}

// Imprime dados do paciente formatado em tabela
void imprimir_time(Time* t){
    printf("%-3d  %-10s  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d\n", // Imprime os dados formatados
           t->id, t->nome, t->vitorias, t->empates, t->derrotas, t->gols_m, t->gols_s, t->saldo_gols, t->pontos_ganhos);
}

// Salva em arquivo dados do paciente formatado em tabela
void salvar_time_arquivo(Time* t, FILE* arquivo){
    fprintf(arquivo, "%-3d  %-10s  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d\n", // Imprime os dados formatados
           t->id, t->nome, t->vitorias, t->empates, t->derrotas, t->gols_m, t->gols_s, t->saldo_gols, t->pontos_ganhos);
}

void calcula_pontuacoes_time(Time *t, void* p){
    int id_time1 = recebe_id_time1(p);
    int id_time2 = recebe_id_time2(p);
    int gols_time1 = recebe_gols_time1(p);
    int gols_time2 = recebe_gols_time2(p);

    // Calcula as pontuações que o time fez em casa
    if (t->id == id_time1){
        if(gols_time1 > gols_time2){
            t->vitorias += 1;
        } else if(gols_time1 < gols_time2){
            t->derrotas += 1;
        } else {
            t->empates += 1;
        }
        t->gols_m += gols_time1;
        t->gols_s += gols_time2;

    // Calcula as pontuações que o time fez fora de casa
    } else if (t->id == id_time2){
        if(gols_time1 < gols_time2){
            t->vitorias += 1;
        } else if(gols_time1 > gols_time2){
            t->derrotas += 1;
        } else {
            t->empates += 1;
        }
        t->gols_m += gols_time2;
        t->gols_s += gols_time1;
    }

    t->pontos_ganhos = t->vitorias * 3 + t->empates; // Calucla os pontos ganhos do time em todo o campeonato (V * 3 + E)
    t->saldo_gols = t->gols_m - t->gols_s; // Calcula o saldo final de gols
}

int recebe_id_do_time(Time* t){ return t->id; }
char* recebe_nome_do_time(Time* t){ return t->nome; }