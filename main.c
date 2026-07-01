// Importa interfaces públicas
#include "ui.h"
#include "bd_partidas.h"
#include "bd_times.h"
#include "classificacao.h"

#include<locale.h>

int main(){
    setlocale(LC_ALL, ""); // Adicione esta linha como a primeiríssima do programa

    // Define quais arquivos serão utilizados
    const char* arquivo_p = "partidas_completo.csv";
    const char* arquivo_t = "times.csv";
    const char* arquivo_bd_p = "bd_partidas.csv";
    const char* arquivo_c = "bd_classificacao.csv";

    // Aloca dinamicamente bancos de dados
    BDTime* bd_t = criar_bd_time();
    BDPartidas* bd_p = criar_bd_partidas();

    // Carrega os arquivos acima
    carregar_times_csv(bd_t, arquivo_t);
    carregar_partidas_csv(bd_p, arquivo_p);
    salvar_arquivo_classificacao(bd_t, bd_p, arquivo_c);
    
    // Imprime o menu principal
    imprimir_menu(bd_t, bd_p, arquivo_bd_p);

    atualizar_partidas_csv(bd_t, bd_p, arquivo_p);

    // Libera a memória dos bancos de dados alocados dinamicamente
    destruir_bd_time(bd_t);
    destruir_bd_partidas(bd_p);
    
    // Encerra o programa
    return 0;
}

