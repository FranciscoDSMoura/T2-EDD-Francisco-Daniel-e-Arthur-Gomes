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

void inserir_partida(BDPartidas *bd_p, Partidas *p) {
    NoPartida *novo = malloc(sizeof(NoPartida));
    novo->partidas = p;
    novo->proximo = NULL;

    if (bd_p->inicio == NULL) {
        bd_p->inicio = novo;
    } else {
        NoPartida *atual = bd_p->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void atualizar_partidas_csv(void *bd_t, BDPartidas *bd_p, const char *caminho_arquivo){
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo);
        return;
    }

    fprintf(arquivo, "ID,Time1,Time2,Placar1,Placar2\n");
    NoPartida *atual = bd_p->inicio;

    while(atual){
        Partidas* p_atual = atual->partidas;
        
        fprintf(arquivo, "%d,%d,%d,%d,%d\n",
                recebe_id_partida(p_atual), 
                recebe_id_time1(p_atual), 
                recebe_id_time2(p_atual), 
                recebe_gols_time1(p_atual), 
                recebe_gols_time2(p_atual));
        atual = atual->proximo;
    }
    fclose(arquivo);
}

int remover_partida(BDPartidas *bd_p, int id){
    NoPartida *atual = bd_p->inicio;
    NoPartida *anterior = NULL;

    while (atual != NULL) {
        if (recebe_id_partida(atual->partidas) == id) {
            if (anterior == NULL) {
                bd_p->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual->partidas);
            free(atual);
            bd_p->quantidade--;
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    return 0;
}

void destruir_bd_partidas(BDPartidas *bd_p)
{
    if (bd_p == NULL) return;

    NoPartida *atual = bd_p->inicio;
    while (atual != NULL) {
        NoPartida *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    free(bd_p);
}

void carregar_partidas_csv(BDPartidas *bd_p, const char *caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de partidas.\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); 

    while (fgets(linha, sizeof(linha), arquivo)) {
        int id, id_t1, id_t2, gols1, gols2;
        
        if (sscanf(linha, "%d,%d,%d,%d,%d", &id, &id_t1, &id_t2, &gols1, &gols2) == 5) {
            Partidas *p = criar_nova_partida(id, id_t1, id_t2, gols1, gols2);
            inserir_partida(bd_p, p);
        }
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
        printf("\nNenhuma partida encontrada envolvendo o time com o prefixo informado.\n");
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

void salvar_arquivo_partidas(void *bd_time, BDPartidas *bd_p, const char *caminho_arquivo){
    // Abre o arquivo para escrita
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao salvar em %s\n", caminho_arquivo);
        return;
    }

    fprintf(arquivo, "%-3s  %-16s  %-12s  %-10s  %-5s\n", "ID", "Time1", "Time2", "Placar1", "Placar2"); // Escreve o cabeçalho no arquivo
    NoPartida *atual = bd_p->inicio;
    BDTime *bd_t = (BDTime *)bd_time;

    while(atual){
        Partidas* p_atual = atual->partidas;

        void *mandante = buscar_time_por_id(bd_t, recebe_id_time1(p_atual));
        void *visitante = buscar_time_por_id(bd_t, recebe_id_time2(p_atual));

        const char* nome_m = mandante ? procura_nome_do_no(mandante) : "Desconhecido";
        const char* nome_v = visitante ? procura_nome_do_no(visitante) : "Desconhecido";

        //inicializa variáveis para calcular o espaçamento da tabela, considerando a possibilidade de acentos nos nomes dos times
        wchar_t w_nome_m[50];
        wchar_t w_nome_v[50];

        //a função converte e retorna a quantidade exata de letras visíveis
        int qtd_letras_m = mbstowcs(w_nome_m, nome_m, 50);
        int qtd_letras_v = mbstowcs(w_nome_v, nome_v, 50);

        //atribui a base de 16 e 12 espaços, respectivamente
        int pad_m = 16;
        int pad_v = 12;

        //se tiver acento, o strlen (bytes) vai ser maior que o mbstowcs (letras)
        if(qtd_letras_m != -1)
            pad_m += (strlen(nome_m) - qtd_letras_m); //soma essa diferença no tamanho da coluna
        if(qtd_letras_v != -1)
            pad_v += (strlen(nome_v) - qtd_letras_v);
        
        fprintf(arquivo, "%-3d  %-*s  %-*s  %-10d  %-2d\n", // Escreve as partidas no arquivo
                recebe_id_partida(p_atual), pad_m, nome_m, pad_v, nome_v, recebe_gols_time1(p_atual), recebe_gols_time2(p_atual));
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void* recebe_proxima_partida(NoPartida *atual){
    return (void*)atual->proximo;
}

void* recebe_partida_do_no(NoPartida *atual){
    return (void*)atual->partidas; 
}

void* recebe_BDPartidas_inicio(BDPartidas* bd_p){
    return (void*)bd_p->inicio;
}

void salvar_nova_partida(void* bd_time, BDPartidas* bd_p, const char* caminho_arquivo){
    printf("\nPara inserir um novo registro, digite os valores para os campos Time1, Time2, Placar1 e Placar2: \n");

    int id_time1;
    scanf("%d", &id_time1);

    int id_time2;
    scanf("%d", &id_time2);

    while(id_time1 == id_time2){
        printf("\nNão é permitido inserir o mesmo time 2 vezes, insira 2 ID's diferentes: \n");
        scanf("%d", &id_time1);
        scanf("%d", &id_time2);
    }

    while(id_time1 < 0 || id_time1 > 9 || id_time2 < 0 || id_time2 > 9){
        printf("\nNão é permitido inserir um time que não existe, insira 2 ID's válidos (de 0 a 9): \n");
        scanf("%d", &id_time1);
        scanf("%d", &id_time2);
    }

    int placar1;
    scanf("%d", &placar1);

    int placar2;
    scanf("%d", &placar2);

    printf("\nConfirma a inserção do registro abaixo? (S/N)\n\n");

    NoPartida *atual = bd_p->inicio;
int maior_id = -1; // Começa com um valor menor que qualquer ID válido

while (atual != NULL) {
    int id_atual = recebe_id_partida(atual->partidas);
    if (id_atual > maior_id) {
        maior_id = id_atual;
    }
    atual = atual->proximo;
}

int p_id_novo = (maior_id == -1) ? 1 : (maior_id + 1);

    BDTime* bd_t = (BDTime *)bd_time;

    void* mandante = buscar_time_por_id(bd_t, id_time1);
    void* visitante = buscar_time_por_id(bd_t, id_time2);

    const char* nome_m = mandante ? procura_nome_do_no(mandante) : "Desconhecido";
    const char* nome_v = visitante ? procura_nome_do_no(visitante) : "Desconhecido";

    // Imprime o registro a ser adicionado
    imprimir_cabecalho_partidas();
    printf("%-3d  %-16s  %-12s  %-10d  %-2d\n",
            p_id_novo, nome_m, nome_v, placar1, placar2);

    char opcao;
    scanf(" %c", &opcao);

    switch(opcao){
        case 'n': case 'N': printf("\nInserção cancelada.\n"); break;
        case 's': case 'S': 
            Partidas* p = criar_nova_partida(p_id_novo, id_time1, id_time2, placar1, placar2);

            inserir_partida(bd_p, p); // Insere a nova partida na lista

            salvar_arquivo_partidas(bd_t, bd_p, caminho_arquivo); // Escreve todos as partidas no arquivo novamente com a partida nova

            printf("\nO registro foi inserido com sucesso.\n"); break;

        default: printf("\nDigite uma opção válida.\n"); break;
    }
}

void atualizar_partida(void* bd_time, BDPartidas* bd_p, const char* caminho_arquivo){
    printf("\nDigite o ID do registro a ser atualizado: \n");

    int id;
    scanf("%d", &id); // Registra o id da partida a ser atualizada

    printf("\nDigite o novo valor para os campos Placar1 e Placar2 (para manter o valor atual de um campo, digite '-'): \n");

    char placar1;
    scanf(" %c", &placar1);

    char placar2;
    scanf(" %c", &placar2);

    while(placar1 == '-' && placar2 == '-'){
        printf("\nNão é possível atualizar a partida se não for informado pelo menos um valor no Placar1 ou no Placar2, digite um valor válido.\n");
        scanf(" %c", &placar1);
        scanf(" %c", &placar2);
    }

    printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n\n");

    NoPartida *atual = bd_p->inicio;
    Partidas* p = atual->partidas;
    BDTime* bd_t = (BDTime *)bd_time;

    int placar1_novo;
    int placar2_novo;
    if(placar1 == '-'){
        placar1_novo = recebe_gols_time1(atual->partidas);
        placar2_novo = placar2 - '0'; // Utiliza do valor do placar2 em ASCII para encontrar o mesmo valor como um inteiro
    } else if(placar2 == '-'){
        placar1_novo = placar1 - '0'; // Utiliza do valor do placar1 em ASCII para encontrar o mesmo valor como um inteiro
        placar2_novo = recebe_gols_time2(atual->partidas);
    } else {
        placar1_novo = placar1 - '0'; // Utiliza do valor do placar1 em ASCII para encontrar o mesmo valor como um inteiro
        placar2_novo = placar2 - '0'; // Utiliza do valor do placar2 em ASCII para encontrar o mesmo valor como um inteiro
    }

    void *mandante = buscar_time_por_id(bd_t, recebe_id_time1(p));
    void *visitante = buscar_time_por_id(bd_t, recebe_id_time2(p));

    const char* nome_m = mandante ? procura_nome_do_no(mandante) : "Desconhecido";
    const char* nome_v = visitante ? procura_nome_do_no(visitante) : "Desconhecido";

    // Imprime o registro a ser atualizado
    imprimir_cabecalho_partidas();
    printf("%-3d  %-16s  %-12s  %-10d  %-2d\n",
            id, nome_m, nome_v, placar1_novo, placar2_novo);

    char opcao;
    scanf(" %c", &opcao);

    switch(opcao){
        case 'n': case 'N': printf("\nInserção cancelada.\n"); break;
        case 's': case 'S':
            atualizar_bd_partida(bd_p, id, placar1_novo, placar2_novo); // Atualiza o time na lista

            salvar_arquivo_partidas(bd_t, bd_p, caminho_arquivo); // Escreve todos as partidas no arquivo novamente com a partida atualizada
        
            printf("\nRegistro atualizado com sucesso.\n"); break;

        default: printf("\nDigite uma opção válida.\n"); break;
    }
}

NoPartida* buscar_partida_por_id(BDPartidas *bd, int id){
    NoPartida *atual = bd->inicio;
    while (atual) {
        if (recebe_id_partida(atual->partidas) == id) // Verifica ID
            return atual;
        atual = atual->proximo;
    }
    return NULL; // Não achou
}


void remover_partida_arquivo(void* bd_time, BDPartidas* bd_p, const char* caminho_arquivo){
    printf("\nDigite o ID do registro a ser removido: \n");

    int id;
    scanf("%d", &id); // Registra o id da partida a ser removida

    printf("\nTem certeza que deseja excluir o registro abaixo? (S/N)");

    NoPartida* atual = bd_p->inicio;
    Partidas* p = atual->partidas;
    BDTime* bd_t = (BDTime *)bd_time;

    void *mandante = buscar_time_por_id(bd_t, recebe_id_time1(p));
    void *visitante = buscar_time_por_id(bd_t, recebe_id_time2(p));

    const char* nome_m = mandante ? procura_nome_do_no(mandante) : "Desconhecido";
    const char* nome_v = visitante ? procura_nome_do_no(visitante) : "Desconhecido";

    // Imprime a partida a excluir
    imprimir_cabecalho_partidas();
    printf("%-3d  %-16s  %-12s  %-10d  %-2d\n",
            id, nome_m, nome_v, recebe_gols_time1(p), recebe_gols_time2(p));

    // resposta do usuário
    char opcao;
    scanf(" %c", &opcao);

    // deletar o registro
    switch(opcao){
        case 'S' : case 's' :
            // Remove a partida do arquivo e escreve todos as partidas no arquivo novamente sem a partida removida
            remover_partida(bd_p, id); salvar_arquivo_partidas(bd_t, bd_p, caminho_arquivo); break;
        case 'N' : case 'n' : printf("Remoção do registro cancelada.\n"); break;
        default : printf("Digite uma opção válida.\n"); break;
    }
}
