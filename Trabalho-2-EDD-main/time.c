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

// Converte uma linha CSV em um struct Time
Time remove_caracteres_especiais_timecsv(char *linha_csv)
{
    Time t;
    char *token;

    token = strtok(linha_csv, ","); // ID
    t.id = token ? atoi(token) : 0;

    token = strtok(NULL, ","); // Nome
    strncpy(t.nome, token ? token : "", sizeof(t.nome));
    t.nome[sizeof(t.nome) - 1] = '\0';

    t.nome[strcspn(t.nome, "\r\n")] = '\0';

    return t;
}

// Imprime dados do paciente formatado em tabela
void imprimir_time(Time t)
{
    
    printf("%-3d  %-10s  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d\n", // Imprime os dados formatados
           t.id, t.nome, t.vitorias, t.empates, t.derrotas, t.gols_m, t.gols_s, t.saldo_gols, t.pontos_ganhos);
}
