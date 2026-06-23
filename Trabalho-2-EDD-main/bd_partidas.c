// Importa a própria interface pública
#include "bd_times.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Importa outra interface pública
#include "bd_partidas.h"

struct NoPartida{
    Partidas* partidas;
    NoPartida *proximo;
};

struct bd_partidas{
    int quantidade;           
    NoPartida *inicio;  
} ;

BDPartidas* criar_bd_partidas() 
{
    BDPartidas* bdp = (BDPartidas*) malloc(sizeof(BDPartidas)); // Aloca um vetor dinamicamente
    if (bdp != NULL) {
        bdp->quantidade = 0;
        bdp->inicio = NULL;
    }
    return bdp; // Retorna um vetor vazio
}

void inserir_partida(BDPartidas* bd, Partidas* p)
{
    NoPartida *novo = malloc(sizeof(NoPartida));
    novo->partidas = p;
    novo->proximo = bd->inicio;
    bd->inicio = novo;
}

void destruir_bd_partidas(BDPartidas *bd)
{
    if (bd == NULL) return;

    NoPartida *atual = bd->inicio;
    while (atual != NULL) {
        NoPartida *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    free(bd);
}

void carregar_partidas_csv(BDPartidas *bd, const char *caminho_arquivo)
{
    NoPartida *atual = bd->inicio;
    while (atual) {
        NoPartida *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    bd->inicio = NULL;
    bd->quantidade = 0;

    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", caminho_arquivo);
        return;
    }

    char linha[100];
    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo)) {
        Partidas* p = remove_caracteres_especiais_partidascsv(linha);
        inserir_partida(bd, p);
    }
    fclose(arquivo);
}

void imprimir_cabecalho_partidas(void)
{
    printf("%-3s  %-20s  %-12s\n", "ID", "Time1", "Time2");
}

void imprimir_partidas(BDTime *bd_times, Partidas p){
    void *mandante = buscar_por_id(bd_times, p.id_time1);
    void *visitante = buscar_por_id(bd_times, p.id_time2);

    const char *nome_m = mandante ? time_get_nome(mandante) : "Desconhecido";
    const char *nome_v = visitante ? time_get_nome(visitante) : "Desconhecido";

    printf("%-3d  %-10s  %-1d  x  %-2d  %-10s\n",
           p.id, nome_m, p.gols_time1, p.gols_time2, nome_v);
}

void buscar_por_mandante(void *bd_t, BDPartidas *bd_p, int paginacao){
    printf("\nDigite o nome:\n");
    char prefixo[100];
    scanf("%99s", prefixo);
    getchar();

    NoPartida *atual = bd_p->inicio;
    int cont = 0;
    int encontrou = 0;
    int tamanho_prefixo = strlen(prefixo);

    while (atual) {
        Partidas p = atual->partidas;
        
        void *mandante = buscar_por_id(bd_t, p.id_time1); // Busca o ID do time que seja o mesmo ID do time1

        const char *nome_m = mandante ? time_get_nome(mandante) : ""; // Recebe o nome do time atravé do ID dele

        int verifica_mandante = (strncasecmp(nome_m, prefixo, tamanho_prefixo) == 0); // Verifica se o nome ou prefixo bate com o nome do time1

        if (verifica_mandante) {
            if (encontrou == 0) {
                imprimir_cabecalho_partidas();
                encontrou = 1;
            }

            imprimir_partidas(bd_t, p);
            cont++;

            if (cont % paginacao == 0) {
                char op;
                printf("\n-- Página %d -- ENTER p/ continuar, Q p/ sair: ", cont / paginacao);
                op = getchar();
                if (op == 'Q' || op == 'q') break;
                imprimir_cabecalho_partidas();
            }
        }
        atual = atual->proximo;
    }

    if (!encontrou) {
        printf("Nenhuma partida encontrada envolvendo o time com o prefixo informado.\n");
    }
}

void buscar_por_visitante(void *bd_t, BDPartidas *bd_p, int paginacao){
    printf("\nDigite o nome:\n");
    char prefixo[100];
    scanf("%99s", prefixo);
    getchar();

    NoPartida *atual = bd_p->inicio;
    int cont = 0;
    int encontrou = 0;
    int tamanho_prefixo = strlen(prefixo);

    while (atual) {
        Partidas p = atual->partidas;
        
        void *visitante = buscar_por_id(bd_t, p.id_time2); // Busca o ID do time que seja o mesmo ID do time2

        const char *nome_v = visitante ? time_get_nome(visitante) : ""; // Recebe o nome do time atravé do ID dele

        int verifica_visitante = (strncasecmp(nome_v, prefixo, tamanho_prefixo) == 0); // Verifica se o nome ou prefixo bate com o nome do time2

        if (verifica_visitante) {
            if (encontrou == 0) {
                imprimir_cabecalho_partidas();
                encontrou = 1;
            }

            imprimir_partidas(bd_t, p);
            cont++;

            if (cont % paginacao == 0) {
                char op;
                printf("\n-- Página %d -- ENTER p/ continuar, Q p/ sair: ", cont / paginacao);
                op = getchar();
                if (op == 'Q' || op == 'q') break;
                imprimir_cabecalho_partidas();
            }
        }
        atual = atual->proximo;
    }

    if (!encontrou) {
        printf("Nenhuma partida encontrada envolvendo o time com o prefixo informado.\n");
    }
}

void buscar_por_m_ou_v(void *bd_t, BDPartidas *bd_p, int paginacao){
    // Recebe o nome digitado pelo usu[ario]
    printf("\nDigite o nome:\n");
    char prefixo[100];
    scanf("%99s", prefixo);
    getchar();

    NoPartida *atual = bd_p->inicio;
    int cont = 0;
    int encontrou = 0;
    int tamanho_prefixo = strlen(prefixo);

    // Busca as partidas
    while (atual) {
        Partidas p = atual->partidas;
        
        void *mandante = buscar_por_id(bd_t, p.id_time1); // Busca o ID do time que seja o mesmo ID do time1
        void *visitante = buscar_por_id(bd_t, p.id_time2); // Busca o ID do time que seja o mesmo ID do time2

        const char *nome_m = mandante ? time_get_nome(mandante) : ""; // Recebe o nome do time atravé do ID dele
        const char *nome_v = visitante ? time_get_nome(visitante) : ""; // Recebe o nome do time atravé do ID dele

        int verifica_mandante = (strncasecmp(nome_m, prefixo, tamanho_prefixo) == 0); // Verifica se o nome ou prefixo bate com o nome do time1
        int verifica_visitante = (strncasecmp(nome_v, prefixo, tamanho_prefixo) == 0); // Verifica se o nome ou prefixo bate com o nome do time2

        // Se o nome existir, imprime o cabeçalho e as infos das partidas
        if (verifica_mandante || verifica_visitante) {
            if (encontrou == 0) {
                imprimir_cabecalho_partidas();
                encontrou = 1;
            }

            imprimir_partidas(bd_t, p);
            cont++;
            // Divide as partidas em páginas
            if (cont % paginacao == 0) {
                char op;
                printf("\n-- Página %d -- ENTER p/ continuar, Q p/ sair: ", cont / paginacao);
                op = getchar();
                if (op == 'Q' || op == 'q') break;
                imprimir_cabecalho_partidas();
            }
        }
        atual = atual->proximo;
    }
    // Se nehuma partida for encontrada, apresenta uma mensagem de erro
    if (!encontrou) {
        printf("Nenhuma partida encontrada envolvendo o time com o prefixo informado.\n");
    }
}

void salvar_arquivo_partidas(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo_escrever){
    // Abre o arquivo para escrita
    FILE *arquivo = fopen(caminho_arquivo_escrever, "w");
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo_escrever);
        return;
    }

    fprintf(arquivo, "%-1s %6s %21s\n", "ID", "Time1", "Time2"); // Escreve o cabeçalho no arquivo
    NoPartida *atual = bd_p->inicio;
    BDTime *bd = (BDTime *)bd_t;

    while(atual){
        Partidas* p_atual = atual->partidas;
        
        void *mandante = buscar_por_id(bd, p_atual->id_time1); // Busca o ID do time que seja o mesmo ID do time1
        void *visitante = buscar_por_id(bd, p_atual->id_time2); // Busca o ID do time que seja o mesmo ID do time2

        const char *nome_m = mandante ? time_get_nome(mandante) : "Desconhecido"; // Recebe o nome do time atravé do ID dele
        const char *nome_v = visitante ? time_get_nome(visitante) : "Desconhecido";  // Recebe o nome do time atravé do ID dele
        
        fprintf(arquivo, "%-2d  %-10s  %-1d  x  %-2d  %-10s\n", // Escreve as partidas no arquivo
                p_atual->id, nome_m, p_atual->gols_time1, p_atual->gols_time2, nome_v);
                
        atual = atual->proximo;
    }
    fclose(arquivo);
}

NoPartida* recebe_primeira_partida(BDPartidas *bd_p){
    return bd_p->inicio;
}


NoPartida* recebe_proxima_partida(NoPartida *atual){
    return atual->proximo;
}


Partidas* recebe_NoPartida_partida(NoPartida *atual){
    return atual->partidas;
}