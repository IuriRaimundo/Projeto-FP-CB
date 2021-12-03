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
    printf("____________________________________________________________________\n");
    printf("\n\t\tGESTAO DE BICICLETAS PARTILHADAS\n");
    printf("____________________________________________________________________\n\n");
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
    printf("\t8. Exportar dados para CSV\n");
    printf("\t0. Sair\n");
    printf("\t\tSelecione a opcao: ");
    op = lerInteiro(0, 8);
    printf("\n");
    return op;
}

// Esta função recebe vetores de estruturas e o numero de elementos em
// cada e grava esses dados em ficheiros
void gravarDadosFich(tipoBicicleta dadosBic[], int totBic, tipoRegReq dadosReg[], int totReg)
{
    int controlo, escolha;
    // Se controlo for 2, os dados foram gravados com sucesso
    // Se não for, perguntar de o utilizador pretende tentar novamente para evitar perca de dados involuntária
    do
    {
        controlo = 0;
        controlo += gravarFichBicicleta(dadosBic, totBic);
        controlo += gravarFichReq(dadosReg, totReg);
        if (controlo != CONTROLO_SUCESSO_GRAVAR_FICH)
        {
            escolha = escolhaSimOuNao("Falha ao gravar ficheiros, pretende tentar novamente?");
        }
        else
        {
            printf(MENSAGEM_SUCESSO_GRAVAR);
        }
    } while (controlo != CONTROLO_SUCESSO_GRAVAR_FICH && escolha == 1);
}

// Esta função recebe os vetores de estrutura e um ponteiro para os seus contadores
// Irá executar as funções de leitura e atualizar o valor dos contadores passados por referencia
void lerDadosFich(tipoBicicleta vetorBic[], int *totalBic, tipoRegReq vetorReg[], int *totalReg)
{
    *totalBic = lerFichBicicleta(vetorBic);
    *totalReg = lerFichReg(vetorReg);
    if (*totalBic == 0)
    {
        printf(MENSAGEM_ERRO_LER_BICICLETAS);
    }
    if (*totalReg == 0)
    {
        printf(MENSAGEM_ERRO_LER_REQUISICOES);
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
                printf(MENSAGEM_0_BICICLETAS);
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
                    printf("\nDados da bicicleta requisitada\n");
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

// Esta funcao recebe o vetor de bicicletas, o seu contador de elementos, o vetor dos registos e o seu contador de elementos
// Apresenta um menu para o utilizador escolher que informações sobre as bicicletas e requisições ver
// e apresenta a informacao escolhida
void informacoes(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq)
{
    int escolha, campus, quantidadeReqAposData, nenhumaEncontrada, i, j;
    tipoData data;

    escolha = menuInformacoes();

    switch (escolha)
    {
        // 1 - Informações gerais
        case 1: informacoesGerais(vetorBic, contBic, vetorReq, contRegReq); break;
        case 2: // 2 - Quantidade de requisicoes apos uma data
            printf("\nInsira uma data (%s): ", FORMATO_DATA);
            data = lerData();
            quantidadeReqAposData = 0;
            for (i = 0; i < contRegReq; i++)
            {
                // Se a data de requisicao for mais adiante do que a data inserida, incrementar contador
                if (compararDatas(vetorReq[i].dataReq, data) == 1)
                {
                    quantidadeReqAposData++;
                }
            }
            printf("\nRequisicoes apos essa data: %d\n", quantidadeReqAposData);
            break;

        case 3: // 3 - Bicicletas que ja se deslocaram a um campus
            campus = escolhaCampus();
            printf("\nBicicletas que ja se deslocaram a esse campus: ");
            nenhumaEncontrada = 1;
            // Por cada bicicleta, percorrer as requisicoes e comparar o id. Apos corresponder ao id comparar o campus inserido
            // com o campus de destino da requisicao. Se for igual escrever o nome da bicicleta e parar o ciclo.
            // Isto evita a repeticao de
            for (i = 0; i < contBic; i++)
            {
                for (j = 0; j < contRegReq; j++)
                {
                    // Se o campus inserido corresponder a um campus de destino, escrever id da bicicleta
                    if (vetorBic[i].id == vetorReq[j].idBic)
                    {
                        if (campus == vetorReq[j].campusDestino)
                        {
                            printf("Bicicleta %d; ", vetorReq[i].idBic);
                            nenhumaEncontrada = 0;
                            j = contRegReq;
                        }
                    }
                }
            }
            // Se nao houver correspondencia, escrever nenhuma
            if (nenhumaEncontrada)
            {
                printf("Nenhuma");
            }
            printf("\n\n");
            break;
    }
}

// Apresenta o menu das informações e devolve a escolha
int menuInformacoes(void)
{
    int escolha;
    char opcoes[LIM_OPCOES][LIM_CHAR_OPCAO] = {"Informacoes gerais", "Quantidade de requisicoes apos uma data", "Bicicletas que ja se deslocaram a um campus"};
    printf("\n\n\tINFORMACOES\n\n");
    escolha = escolhaMultipla(opcoes, 3);
    return escolha;
}

// Apresenta informacoes sobre as bicicletas e requisicoes
// Recebe o vetor de bicicletas, o contador de bicicletas, o vetor de requisicoes e o contador de requisicoes
void informacoesGerais(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq)
{
    float percEstadoDisp, percEstadoAvar, percEstadoReq, percEstadoDesat;
    int contEstadoDisp, contEstadoAvar, contEstadoReq, contEstadoDesat;
    float tempoUtilizacaoMedio, somaTempoUtilizacaoMedio;
    int maximoReq, contadoresReq[3] = {0}; // Contadores de requisicao por campuss: 0 - Residencias, 1 - Campus 1, 2 - Campus 2
    int bicicletasComSubstituicao;
    int i;
    // Contar numero de bicicletas em cada estado, contar bicicletas com substituicoes e calcular tempo medio de utilizacao
    contEstadoDisp = contEstadoAvar = contEstadoReq = contEstadoDesat = 0;
    bicicletasComSubstituicao = 0;
    somaTempoUtilizacaoMedio = 0;
    for (i = 0; i < contBic; i++)
    {
        // Estados
        switch (vetorBic[i].estado)
        {
            case ESTADO_DISP: contEstadoDisp++; break;
            case ESTADO_AVAR: contEstadoAvar++; break;
            case ESTADO_REQ: contEstadoReq++; break;
            case ESTADO_DESAT: contEstadoDesat++; break;
        }
        // Substituicoes
        if (vetorBic[i].substituicoes)
        {
            bicicletasComSubstituicao++;
        }
        // Tempo medio de utilizacao
        if (vetorBic[i].requisicoes != 0) // Evitar divisão por zero
        {
            // Para efetuar o correto calculo da media, deve-se retirar uma requisicao das bicicletas requisitadas
            // porque os valores de tempo de utilizacao da atual requisicao não estão armazenados.
            // Se o contador de requisições for 1, causa divisão por zero.
            if (vetorBic[i].estado == ESTADO_REQ && vetorBic[i].requisicoes != 1)
            {
                somaTempoUtilizacaoMedio += vetorBic[i].tempoUtilizacao / vetorBic[i].requisicoes - 1;
            }
            else
            {
                somaTempoUtilizacaoMedio += vetorBic[i].tempoUtilizacao / vetorBic[i].requisicoes;
            }

        }
    }

    // Calcular percentagem de cada estado
    if (contBic != 0) // Evitar divisao por zero
    {
        percEstadoDisp = (float) contEstadoDisp / contBic * 100;
        percEstadoAvar = (float) contEstadoAvar / contBic * 100;
        percEstadoReq = (float) contEstadoReq / contBic * 100;
        percEstadoDesat = (float) contEstadoDesat / contBic * 100;
    }
    else
    {
        percEstadoDisp = percEstadoAvar = percEstadoReq = percEstadoDesat = 0;
    }

    // Calculcar tempo medio de utilizacao
    if (contBic != 0) // Evitar divisao por zero
    {
        tempoUtilizacaoMedio = somaTempoUtilizacaoMedio / contBic;
    }

    // Determinar campus de origem com maior numero de requisicoes
    // Contar requisicoes por campus
    for (i = 0; i < contRegReq; i++)
    {
        switch (vetorReq[i].campusOrigem)
        {
            case RESIDENCIAS: contadoresReq[0]++; break;
            case CAMPUS1: contadoresReq[1]++; break;
            case CAMPUS2: contadoresReq[2]++; break;
        }
    }

    // Obter maior valor de requisicoes
    maximoReq = 0;
    for (i = 0; i < 3; i++)
    {
        if (contadoresReq[i] > maximoReq)
        {
            maximoReq = contadoresReq[i];
        }
    }

    // Apresentar informações
    printf("\n\n\tINFORMACOES\n\n");
    printf("Bicicletas disponiveis: %.1f%%\t", percEstadoDisp);
    printf("Bicicletas avariadas: %.1f%%\n", percEstadoAvar);
    printf("Bicicletas requisitadas: %.1f%%\t", percEstadoReq);
    printf("Bicicletas desativadas: %.1f%%\n", percEstadoDesat);
    printf("\nTempo de utilizacao medio: %.1f horas\n", tempoUtilizacaoMedio);
    printf("\nBicicletas em que foram substituidas baterias: %d\n", bicicletasComSubstituicao);
    // Para apresentar vários campus de origem no caso de empate, é comparado cada contador com o maximo e apresentado o correspondente campus se for igual
    printf("\nCampus de origem com mais requisicoes: ");
    if (maximoReq != 0) // Se for zero apresentar que não houveram requisições em vez de apresentar todos os campus
    {
        for (i = 0; i < 3; i++)
        {
            if (contadoresReq[i] == maximoReq)
            {
                switch (i)
                {
                    case 0: printf("Residencias "); break;
                    case 1: printf("Campus 1 "); break;
                    case 3: printf("Campus 2 "); break;
                }
                printf("(%d requisicoes); ", maximoReq);
            }
        }
    }
    else
    {
        printf("Nao houveram requisicoes");
    }
    printf("\n");
}

