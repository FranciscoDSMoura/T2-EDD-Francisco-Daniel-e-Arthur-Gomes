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

void bd_salvar_arquivo_classificacao(void* bd_t, void* bd_p, const char* caminho_arquivo){
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