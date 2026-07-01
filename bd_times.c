// Importa a própria interface pública
#include "bd_times.h"

// importa as bibliotecas padrões do C 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Importa interfaces públicas 
#include "time.h"
#include "bd_partidas.h"

// Nó da linked list, contendo um time e o ponteiro para o próximo
struct no_time{
    Time* time;
    NoTime *proximo;
};

// Aponta para o início da lista de times
struct bd_time{
    NoTime *inicio;
};

BDTime *criar_bd_time(void){
    BDTime *bd = malloc(sizeof(BDTime)); // Aloca dinamicamente uma lista de times
    if(bd) bd->inicio = NULL;
    return bd;
}

void destruir_bd_time(BDTime *bd){
    NoTime *atual = bd->inicio;
    // Enquanto faltar nós para serem liberados
    while(atual){
        NoTime *temp = atual;
        atual = atual->proximo;
        free(temp); // Libera nó a nó
    }
    free(bd); // Libera o banco de dados de time
}

void inserir_time(BDTime *bd, Time* t){
    NoTime *novo = malloc(sizeof(NoTime)); // Cria um novo nó
    novo->time = t; // Atribui time
    novo->proximo = bd->inicio; // Insere no início
    bd->inicio = novo;
}

void carregar_times_csv(BDTime *bd, const char *caminho_arquivo){
    FILE *arquivo;
    arquivo = fopen(caminho_arquivo, "r"); // Abre e Lê o arquivo

    // Verifica se realmente há um arquivo com esse nome e caminho
    if(!arquivo){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];
    fgets(linha, sizeof(linha), arquivo); // Pula a primeira linha (cabeçalho)
    while(fgets(linha, sizeof(linha), arquivo)){
        Time* t = remove_caracteres_especiais_timecsv(linha); // Converte uma linha para time
        inserir_time(bd, t); // Insere time no banco de dados
    }
    fclose(arquivo); // Fecha o arquivo
}

void imprimir_cabecalho(){
    printf("\n%-3s  %-10s  %-3s  %-3s  %-3s  %-3s  %-3s  %-3s  %-3s\n", 
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG"); // Imprime o cabeçalho formatado
}

void salvar_cabecalho_arquivo(FILE* arquivo){
    fprintf(arquivo, "\n%-3s  %-10s  %-3s  %-3s  %-3s  %-3s  %-3s  %-3s  %-3s\n", 
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG"); // Imprime o cabeçalho formatado
}

void buscar_por_nome(BDTime *bd_t, void *bd_p, char *prefixo, int paginacao)
{
    NoTime *atual = bd_t->inicio;
    int encontrou = 0;
    int cont = 0;
    while (atual) {
        Time* t = atual->time;
        if (strncasecmp(recebe_nome_do_time(t), prefixo, strlen(prefixo)) == 0){
            imprimir_cabecalho(); 
            time_zerar_estatisticas(t);

            NoPartida *atual_partida = recebe_BDPartidas_inicio(bd_p); 
            // Calcula as informações de um time por partida
            while (atual_partida) {
                calcula_pontuacoes_time(atual->time, recebe_partida_do_no(atual_partida)); 
                atual_partida = recebe_proxima_partida(atual_partida);
            }

            imprimir_time(atual->time); // Imprime se encontrou
            encontrou = 1;
        }
        atual = atual->proximo;
        cont++;

        // Paginação, se imprimir x times passa para a próxima página
        if(cont < 10){
            if (cont % paginacao == 0){
                char op;
                printf("\n-- Página %d -- ENTER p/ continuar, Q p/ sair: ", cont/paginacao);
                op = getchar();
                if (op == 'Q' || op == 'q') break;
            }
        }
    }
    if (!encontrou)
        printf("Nenhum time encontrado com o nome/prefixo informado.\n");
}

NoTime* buscar_time_por_id(BDTime *bd, int id) {
    NoTime *atual = bd->inicio;
    while (atual) {
        if (recebe_id_do_time(atual->time) == id) // Verifica ID
            return atual;
        atual = atual->proximo;
    }
    return NULL; // Não achou
}

void bd_salvar_arquivo(BDTime *bd, const char *caminho_arquivo) 
{
    FILE* arquivo = fopen(caminho_arquivo, "w"); // Abre arquivo para escrita
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo); // Mensagem de erro
        return;
    }

    fprintf(arquivo, "ID\tTime\t\t\tV\tE\tD\tGM\tGS\tS\tPG\n"); // Cabeçalho CSV
    NoTime *atual = bd->inicio;
    while (atual) {
        Time* t = atual->time;
        salvar_time_arquivo(t, arquivo);
        atual = atual->proximo;
    }
    fclose(arquivo); // Fecha arquivo
}

void* recebe_BDTime_inicio(BDTime* bd_t){
    return (void*)bd_t->inicio; // início da lista/último inserido
}

void* recebe_NoTime_proximo(NoTime* atual){
    return (void*)atual->proximo; // Próximo time
}

void* recebe_time_do_no(NoTime* atual_time){
    return (void*)atual_time->time; // Time atual
}

const char* procura_nome_do_no(NoTime *n){
    if (n != NULL) {
        return recebe_nome_do_time(n->time); // Se n não for nulo ele recebe o nome do time
    }
    return "Desconhecido";
}