// Importa interfaces públicas
#include "ui.h"
#include "bd_partidas.h"
#include "bd_times.h"
#include "classificacao.h"

int main()
{
    // Define quais arquivos serão utilizados
    const char *arquivo_p = "partidas_completo.csv";
    const char *arquivo_t = "times.csv";

    // Aloca dinamicamente bancos de dados
    BDTime *bd_t = criar_bd_time();
    BDPartidas *bd_p = bd_partidas_criar();

    // Carrega os arquivos acima
    bd_carregar_times_csv(bd_t, arquivo_t);
    carregar_partidas_csv(bd_p, arquivo_p);
    
    // Imprime o menu principal
    imprimir_menu(bd_t, bd_p);

    // Libera a memória dos bancos de dados alocados dinamicamente
    destruir_bd_time(bd_t);
    destruir_bd_partidas(bd_p);
    
    // Encerra o programa
    return 0;
}

