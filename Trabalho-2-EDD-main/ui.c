// Importa a própria interface pública
#include "ui.h"

// importa as bibliotecas padrões do C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Importa outras interfaces públicas
#include "bd_times.h"
#include "bd_partidas.h"
#include "partidas.h"
#include "classificacao.h"

void consultar_time(BDTime *bd_t, BDPartidas *bd_p){
  printf("\nDigite o nome ou o prefixo do time:\n");
  char prefixo[100];
  scanf("%99s", prefixo); // Recebe o nome ou prefixo digitado pelo usuário
  buscar_por_nome(bd_t, bd_p, prefixo, 10); 
}

void consultar_partidas(BDTime *bd_t, BDPartidas *bd_p){
    printf("\nEscolha o modo de consulta:\n"
           "1 - Por time mandante\n"
           "2 - Por time visitante\n"
           "3 - Por time mandante ou visitante\n"
           "4 - Retornar ao menu principal\n\n");

    char opcao;
    scanf(" %c", &opcao); getchar(); //recebe a opção que o usuário digitar 

    // Entra em um caso dependeno da opção escolhida pelo usuário
    switch(opcao){
        case '1': buscar_por_mandante(bd_t, bd_p, 10); break;
        case '2': buscar_por_visitante(bd_t, bd_p, 10); break;
        case '3': buscar_por_m_ou_v(bd_t, bd_p, 10); break;
        case '4': imprimir_menu(bd_t, bd_p); break;
        default: printf("Escolha uma opção válida.\n"); break;
    }
}

void imprimir_tabela_classificacao(BDTime *bd_t, BDPartidas *bd_p){
    printf("\nImprimindo classificação...\n\n");

    BDTime *bd = (BDTime *)bd_t;
    classificacao_completa(bd_t, bd_p);

    printf("%-3s  %-10s  %-3s  %-3s  %-3s  %-3s  %-3s  %-3s  %-3s\n",
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG"); // Cabeçalho classificacao CSV
    NoTime *atual = recebe_BDTime_inicio(bd);
    while (atual) {
        Time* t = recebe_time_do_no(atual);
        imprimir_time(t);
        atual = recebe_NoTime_proximo(atual);
    }

}

int imprimir_menu(BDTime *bd_t, BDPartidas *bd_p){
    char opcao;
    
    //continua printando o menu ate que Q ou q seja inserido
    while (opcao != 'Q' && opcao != 'q')  {

        printf("\n1 - Consultar time\n"
               "2 - Consultar partidas\n"
               "3 - Atualizar partida\n"
               "4 - Remover partida\n"
               "5 - Inserir partida\n"
               "6 - Imprimir tabela de classificação\n"
               "Q - Sair\n\n");

        scanf(" %c", &opcao); getchar(); //recebe a opção que o usuário digitar 

        switch(opcao){
            case '1': consultar_time(bd_t, bd_p); break;
            case '2': consultar_partidas(bd_t, bd_p); break;
            case '3': consultar_partidas(bd_t, bd_p); break;
            case '4': consultar_partidas(bd_t, bd_p); break;
            case '5': consultar_partidas(bd_t, bd_p); break;
            case '6': imprimir_tabela_classificacao(bd_t, bd_p); break;
            case 'Q': case 'q': printf("Encerrando...\n"); break;
            default: printf("Escolha uma opção válida.\n"); break;
        }
    }
    return 0;
}

