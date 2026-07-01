// Importa a própria interface pública
#include "classificacao.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Importa interfaces públicas
#include "bd_times.h"
#include "bd_partidas.h"

void classificacao_completa(void* bd_t, void* bd_p)
{
    NoTime *atual_time = recebe_BDTime_inicio(bd_t);

    // Percorre enqunto ainda tiver informações a obter de um único time
    while (atual_time) {
        time_zerar_estatisticas(recebe_time_do_no(atual_time));

        NoPartida *atual_partida = recebe_BDPartidas_inicio(bd_p); 
        // Calcula as informações de um time por partida
        while (atual_partida) {
            calcula_pontuacoes_time(recebe_time_do_no(atual_time), recebe_partida_do_no(atual_partida)); 
            atual_partida = recebe_proxima_partida(atual_partida);
        }

        atual_time = recebe_NoTime_proximo(atual_time);
    }
}

void salvar_arquivo_classificacao(void* bd_t, void* bd_p, const char* caminho_arquivo){
    FILE *arquivo = fopen(caminho_arquivo, "w"); // Abre arquivo para escrita
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo); // Mensagem de erro
        return;
    }
    classificacao_completa(bd_t, bd_p);

    salvar_cabecalho_arquivo(arquivo);
    NoTime *atual = recebe_BDTime_inicio(bd_t);
    while (atual) {
        salvar_time_arquivo(recebe_time_do_no(atual), arquivo);
        atual = recebe_NoTime_proximo(atual);
    }
    fclose(arquivo); // Fecha arquivo
}

// NOVAS FUNÇÕES:

// Função de comparação seguindo os critérios do TP2
int comparar_times(const void *a, const void *b) {
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

void bd_imprimir_tabela_ordenada(void *bd_t, BDPartidas *bd_p) {
    BDTime *bd = (BDTime *)bd_t;
    
    classificacao_completa(bd_t, bd_p);

    int num_times = 0;
    NoTime *atual = bd->inicio;
    while (atual) {
        num_times++;
        atual = atual->proximo;
    }
    if (num_times == 0) {
        printf("\nNenhum time cadastrado.\n");
        return;
    }
    Time **vetor_times = (Time **)malloc(num_times * sizeof(Time *));
    if (!vetor_times) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    atual = bd->inicio;
    for (int i = 0; i < num_times; i++) {
        vetor_times[i] = &(atual->time);
        atual = atual->proximo;
    }
    
    qsort(vetor_times, num_times, sizeof(Time *), comparar_times);

    printf("Pos  ID   Time            V    E    D    GM   GS   S    PG\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < num_times; i++) {
        Time *t = vetor_times[i];
        printf("%-3d  %-3d  %-14s  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d  %-3d\n",
               i + 1, t->id, t->nome, t->vitorias, t->empates, t->derrotas, 
               t->gols_m, t->gols_s, t->saldo_gols, t->pontos_ganhos);
    }
    
    free(vetor_times);
}

