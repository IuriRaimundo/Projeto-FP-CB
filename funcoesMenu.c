#include <stdio.h>

#include "funcoesAuxiliares.h"
#include "funcoesMenu.h"
#include "bicicletas.h"
#include "registos.h"
#include "mensagens.h"
#include "csv.h"

// Recebe os contadores do programa e devolve um inteiro com aescolha do utilizador
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
void gravarDadosFich(tipoBicicleta dadosBic[], int totBic, tipoRegReq dadosReg[], int totReg)
{
    int controlo;
    controlo = 0;
    controlo += gravarFichBicicleta(dadosBic, totBic);
    controlo += gravarFichReq(dadosReg, totReg);
    gravarBicicletasCSV(dadosBic, totBic);
    if (controlo < 2)
    {
        printf(MENSAGEM_ERRO_GRAVAR);
    }
    else
    {
        printf(MENSAGEM_SUCESSO_GRAVAR);
    }
}

// Esta função recebe os vetores de estrutura e um ponteiro para os seus contadores
// Irá executar as funções de leitura e atualizar o valor dos contadores passados por referencia
void lerDadosFich(tipoBicicleta vetorBic[], int *totalBic, tipoRegReq vetorReg[], int *totalReg)
{
    *totalBic = lerFichBicicleta(vetorBic);
    *totalReg = lerFichReg(vetorReg);
    if (*totalBic == 0)
    {
        printf("\nNao foram carregados dados das bicicletas.\n");
    }
    if (*totalReg == 0)
    {
        printf("\nNao foram carregados dados de requisicoes.\n");
    }
}

// Esta funcao recebe o vetor de bicicletas, o seu contador de elementos, o vetor dos registos e o seu contador de elementos
// Apresenta o menu das opcoes de listagens e faz a operacao que o utilizador selecionar
void listagens(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq)
{
    int escolha, idReq, pos;
    escolha = menuListagens();
    switch (escolha) {
        case 1: // Dados de todas as bicicleta
            if (contBic != 0)
            {
                mostrarDadosBicicletas(vetorBic, contBic);             }
            else
            {
                printf("\n\nNao existem bicicletas.\n\n");
            }
            break;
        case 2: mostrarBicicletasRequisitadas(vetorBic, contBic); break;
        case 3: // Dados de todas as requisicoes
            if (contRegReq != 0)
            {
                mostrarRequisicoes(vetorReq, contRegReq);
            }
            else
            {
                printf("\n\nNao foram feitas requisicoes.\n\n");
            }
            break;
        case 4: // Dados das requisicoes de uma determinada bicicleta
            mostrarRequisicoesDeUmaBicicleta(vetorReq, contRegReq); break;
        case 5: // Dados da bicicleta utilizada numa determinada requisição
            printf("\nIdentificacao da requisicao: ");
            idReq = lerInteiro(1, LIM_ID_REG);
            pos = procuraRequisicaoPorId(vetorReq, contRegReq, idReq);
            if (pos != -1 )
            {
                pos = procuraBicicleta(vetorBic, vetorReq[pos].idBic, contBic);
                if (pos != -1)
                {
                    mostrarBicicleta(vetorBic[pos]);
                }
                else
                {
                    printf("\n\nErro, a bicicleta presente na requisicao nao existe.\n\n");
                }
            }
            else
            {
                printf("\n\nNao existe uma requisicao com esse id.\n\n");
            }
            break;
    }
}

// Devolve a escolha do utilizador em inteiro
int menuListagens(void)
{
    int op;
    printf("\n\t\tLISTAGENS\n\n");
    printf("\t1. Ver dados das bicicletas\n");
    printf("\t2. Ver bicicletas atualmente requisitadas\n");
    printf("\t3. Ver todas as requisicoes\n");
    printf("\t4. Procurar requisicoes de uma bicicleta\n");
    printf("\t5. Procurar requisicao\n");
    printf("\n\t\tEscolha: ");
    op = lerInteiro(1, 5);
    return op;
}

