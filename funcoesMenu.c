#include <stdio.h>

#include "funcoesAuxiliares.h"
#include "funcoesMenu.h"
#include "bicicletas.h"
#include "mensagens.h"

int menu(int totalBicicletas, float distancia, int registos, int bicicletasDisponiveis)
{
    int op;
    printf("\n\t\tGestao de Bicicletas Partilhadas\n\n");
    printf("Total de Bicicletas: %2d", totalBicicletas);
    printf("\t\tDistancia percorrida(kms): %3.1f\n", distancia);
    printf("Registos de deslocacao: %2d", registos);
    printf("\tBicicletas disponiveis: %2d\n", bicicletasDisponiveis);
    printf("\n");
    printf("\t1. Nova Bicicleta\n");
    printf("\t2. Registo de Avaria/Disponibilidade\n");
    printf("\t3. Registo de Requisicao\n");
    printf("\t4. Registo de Devolucao\n");
    printf("\t5. Listagens\n");
    printf("\t6. Informacoes\n");
    printf("\t7. Gravar\n");
    printf("\t0. Sair\n");
    printf("\t\tSelecione a opcao: ");
    op = lerInteiro(0, 7);
    return op;
}

// Esta função recebe vetores de estruturas e o numero de elementos em
// cada e grava esses dados em ficheiros
void gravarDados(tipoBicicleta dadosBic[], int totBic)
{
    int controlo;
    controlo = gravarFichBicicleta(dadosBic, totBic);
    if (controlo == 0)
    {
        printf(MENSAGEM_ERRO_GRAVAR);
    }
    else
    {
        printf(MENSAGEM_SUCESSO_GRAVAR);
    }
}

