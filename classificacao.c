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

int comparar_times(const void *a, const void *b);

void imprimir_tabela_classificacao_ordenada(void *bd_time, void* bd_partida){
    BDTime *bd_t = (BDTime *)bd_time;
    BDPartidas *bd_p = (BDPartidas *)bd_partida;
    
    classificacao_completa(bd_t, bd_p);

    int num_times = 0;
    NoTime *atual = recebe_BDTime_inicio(bd_t);
    while (atual) {
        num_times++;
        atual = recebe_NoTime_proximo(atual);
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
    atual = recebe_BDTime_inicio(bd_t);
    for (int i = 0; i < num_times; i++) {
        vetor_times[i] = recebe_time_do_no(atual);
        atual = recebe_NoTime_proximo(atual);
    }
    
    qsort(vetor_times, num_times, sizeof(Time *), comparar_times);

    printf("Pos  ID   Time            V    E    D    GM   GS   S    PG\n");
    for (int i = 0; i < num_times; i++) {
        Time *t = vetor_times[i];
        imprimir_time_com_classificacao(t, i);
    }
    
    free(vetor_times);
}

void salvar_tabela_ordenada_arquivo(void *bd_time, void *bd_partida, const char* caminho_arquivo){
    // Abre o arquivo para escrita
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo);
        return;
    }

    BDTime *bd_t = (BDTime *)bd_time;
    BDPartidas *bd_p = (BDPartidas *)bd_partida;
    
    classificacao_completa(bd_t, bd_p);

    int num_times = 0;
    NoTime *atual = recebe_BDTime_inicio(bd_t);
    while (atual) {
        num_times++;
        atual = recebe_NoTime_proximo(atual);
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
    atual = recebe_BDTime_inicio(bd_t);
    for (int i = 0; i < num_times; i++) {
        vetor_times[i] = recebe_time_do_no(atual);
        atual = recebe_NoTime_proximo(atual);
    }
    
    qsort(vetor_times, num_times, sizeof(Time *), comparar_times);

    fprintf(arquivo, "Pos  ID   Time            V    E    D    GM   GS   S    PG\n");
    for (int i = 0; i < num_times; i++) {
        Time *t = vetor_times[i];
        salvar_time_com_classificacao(t, i, arquivo);
    }
    
    free(vetor_times);
    fclose(arquivo);
}
