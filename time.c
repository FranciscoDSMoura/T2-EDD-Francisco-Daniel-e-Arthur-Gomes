// Importa a própria interface pública
#include "time.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Importa uma outra interface pública
#include "partidas.h"
#include "bd_partidas.h"
#include "bd_times.h"

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

// Função de comparação seguindo os critérios do TP2
int comparar_times(const void *a, const void *b){
    Time *timeA = *(Time **)a;
    Time *timeB = *(Time **)b;

    // 1º Critério
    if (timeA->pontos_ganhos != timeB->pontos_ganhos) {
        return timeB->pontos_ganhos - timeA->pontos_ganhos;
    }
    // 2º Critério
    if (timeA->vitorias != timeB->vitorias) {
        return timeB->vitorias - timeA->vitorias;
    }
    // 2º Critério
    if (timeA->saldo_gols != timeB->saldo_gols) {
        return timeB->saldo_gols - timeA->saldo_gols;
    }
    // 3º Critério
    if (timeA->gols_m != timeB->gols_m) {
        return timeB->gols_m - timeA->gols_m;
    }

    return timeA->id - timeB->id;
}

void imprimir_time_com_classificacao(Time* t, int i){
        //inicializa variáveis para calcular o espaçamento da tabela, considerando a possibilidade de acentos nos nomes dos times
        wchar_t w_nome[50];

        //a função converte e retorna a quantidade exata de letras visíveis
        int qtd_letras = mbstowcs(w_nome, t->nome, 50);

        //atribui a base de 16 e 12 espaços, respectivamente
        int pad = 14;

        //se tiver acento, o strlen (bytes) vai ser maior que o mbstowcs (letras)
        if(qtd_letras != -1)
            pad += (strlen(t->nome) - qtd_letras); //soma essa diferença no tamanho da coluna
            
    printf("%-3d  %-3d  %-*s  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d\n",
            i + 1, t->id, pad, t->nome, t->vitorias, t->empates, t->derrotas, 
            t->gols_m, t->gols_s, t->saldo_gols, t->pontos_ganhos);
}

void salvar_time_com_classificacao(Time* t, int i, FILE* arquivo){
        //inicializa variáveis para calcular o espaçamento da tabela, considerando a possibilidade de acentos nos nomes dos times
        wchar_t w_nome[50];

        //a função converte e retorna a quantidade exata de letras visíveis
        int qtd_letras = mbstowcs(w_nome, t->nome, 50);

        //atribui a base de 16 e 12 espaços, respectivamente
        int pad = 14;

        //se tiver acento, o strlen (bytes) vai ser maior que o mbstowcs (letras)
        if(qtd_letras != -1)
            pad += (strlen(t->nome) - qtd_letras); //soma essa diferença no tamanho da coluna
            
    fprintf(arquivo, "%-3d  %-3d  %-*s  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d\n",
            i + 1, t->id, pad, t->nome, t->vitorias, t->empates, t->derrotas, 
            t->gols_m, t->gols_s, t->saldo_gols, t->pontos_ganhos);
}


int recebe_id_do_time(Time* t){ return t->id; }
char* recebe_nome_do_time(Time* t){ return t->nome; }
