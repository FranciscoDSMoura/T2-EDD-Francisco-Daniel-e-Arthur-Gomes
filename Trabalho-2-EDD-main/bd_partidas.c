// Importa a própria interface pública
#include "bd_partidas.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Importa outra interface pública
#include "bd_times.h"
#include "time.h"

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
        Partidas* p = atual->partidas;
        
        void *mandante = buscar_time_por_id(bd_t, recebe_id_time1(p)); // Busca o ID do time que seja o mesmo ID do time1

        const char *nome_m = mandante ? procura_nome_do_no(mandante) : ""; // Recebe o nome do time atravé do ID dele

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
        Partidas* p = atual->partidas;
        
        void *visitante = buscar_time_por_id(bd_t, recebe_id_time2(p)); // Busca o ID do time que seja o mesmo ID do time2

        const char *nome_v = visitante ? procura_nome_do_no(visitante) : ""; // Recebe o nome do time atravé do ID dele

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
        Partidas* p = atual->partidas;
        
        void *mandante = buscar_time_por_id(bd_t, recebe_id_time1(p)); // Busca o ID do time que seja o mesmo ID do time1
        void *visitante = buscar_time_por_id(bd_t, recebe_id_time2(p)); // Busca o ID do time que seja o mesmo ID do time2

        const char *nome_m = mandante ? procura_nome_do_no(mandante) : ""; // Recebe o nome do time atravé do ID dele
        const char *nome_v = visitante ? procura_nome_do_no(visitante) : ""; // Recebe o nome do time atravé do ID dele

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

void salvar_arquivo_partidas(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo){
    // Abre o arquivo para escrita
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo);
        return;
    }

    fprintf(arquivo, "%-1s %6s %21s\n", "ID", "Time1", "Time2"); // Escreve o cabeçalho no arquivo
    NoPartida *atual = bd_p->inicio;
    BDTime *bd = (BDTime *)bd_t;

    while(atual){
        Partidas* p_atual = atual->partidas;
        
        void *mandante = buscar_time_por_id(bd, recebe_id_time1(p_atual)); // Busca o ID do time que seja o mesmo ID do time1
        void *visitante = buscar_time_por_id(bd, recebe_id_time2(p_atual)); // Busca o ID do time que seja o mesmo ID do time2

        const char *nome_m = mandante ? procura_nome_do_no(mandante) : "Desconhecido"; // Recebe o nome do time atravé do ID dele
        const char *nome_v = visitante ? procura_nome_do_no(visitante) : "Desconhecido";  // Recebe o nome do time atravé do ID dele
        
        fprintf(arquivo, "%-2d  %-10s  %-1d  x  %-2d  %-10s\n", // Escreve as partidas no arquivo
                recebe_id_partida(p_atual), nome_m, recebe_gols_time1(p_atual), recebe_gols_time2(p_atual), nome_v);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void* recebe_proxima_partida(NoPartida *atual){
    return (void*)atual->proximo;
}

void* recebe_partida_do_no(NoPartida *atual_partida){
    return (void*)atual_partida->partidas; 
}

void* recebe_BDPartidas_inicio(BDPartidas* bd_p){
    return (void*)bd_p->inicio;
}

/*
int atualizar_estatisticas_time(BDTime *bd, int id, Time novo) {
    printf("Digite o ID do registro a ser atualizado: \n");

    int id;
    scanf("%d", &id);

    // identificar a partida pelo ID dela

    printf("Digite o novo valor para os campos Placar1 e Placar2 (para manter o valor atual de um campo, digite '-')");

    // registrar os novos valores pra atualizar la embaixo

    printf("Confirma os novos valores para o registro abaixo? (S/N)");

    // Printar a partida que vai alterar

    // resposta do usuário

    // atualizar o registro no arquivo

    printf("Registro atualizado com sucesso.");

    NoTime *n = buscar_time_por_id(bd, id); // Busca nó por ID
    if (!n) return 0; // Não encontrou
    n->time = novo; // Atualiza dados
    return 1; // Sucesso
}*/

NoPartida* buscar_partida_por_id(BDPartidas *bd, int id){
    NoPartida *atual = bd->inicio;
    while (atual) {
        if (atual->partidas == id) // Verifica ID
            return atual;
        atual = atual->proximo;
    }
    return NULL; // Não achou
}

/*
int remover_partida(BDTime *bd, int id){
    BDPartidas* bd_p;

    printf("Digite o ID do registro a ser removido: \n");

    int id;
    scanf("%d", &id);

    // registrar os novos valores pra remover la embaixo

    printf("Tem certeza que deseja excluir o registro abaixo? (S/N)");

    // Printar a partida que vai deletar
    Partidas* p = atual->partida;
    imprimir_cabecalho_partidas();

    // resposta do usuário
    char conf;
    scanf(" %c", conf);

    // deletar o registro
    switch(conf){
        case 'S' : case 's' :
            NoPartida* atual = bd->inicio, *anterior = NULL;
            while(atual){
                if(buscar_partida_por_id(atual->time) == id) { // Achou a partida
                    if (anterior)
                        anterior->proximo = atual->proximo; // Remove do meio/fim
                    else
                        bd->inicio = atual->proximo; // Remove do inicio
                    free(atual); // Libera a memória
                    printf("Registro removido com sucesso.\n");
                    return 1; // Sucesso
                }
                anterior = atual;
                atual = atual->proximo;
            
            }
            printf("Time não encontrado.\n");
            return 0; // Não encontrou o time
        case 'N' : case 'n' : printf("Remoção do registro cancelada.\n"); break;
        default : printf("Digite uma opção válida.\n"); break;
    
}
*/