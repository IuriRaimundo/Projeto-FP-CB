#include "csv.h"

// Gravar os dados do vetor bicicletas e escreve um ficheiro CSV
// Recebe o vetor de bicicletas e o número de elementos do vetor
void gravarBicicletasCSV(tipoBicicleta dadosBic[], int elem)
{
    tipoBicicleta dados;
    FILE *fich;
    int i;
    fich = fopen(NOME_CSV_BIC, "w");

    if (fich != NULL)
    {
        fprintf(fich, "%s\n", CABECALHO_CSV_BIC); // Escrever cabeçalhos do ficheiro CSV
        // Percorrer vetor de bicicletas e escrever os dados
        for (i = 0; i < elem; i++)
        {
            dados = dadosBic[i];
            fprintf(fich, "%d; ", dados.id);
            fprintf(fich, "%s; ", dados.nome);
            switch (dados.estado)
            {
                case ESTADO_AVAR: fprintf(fich, "%s; ", "Avariada"); break;
                case ESTADO_DISP: fprintf(fich, "%s; ", "Disponível"); break;
                case ESTADO_REQ: fprintf(fich, "%s; ", "Requisitada"); break;
                case ESTADO_DESAT: fprintf(fich, "%s; ", "Desativada"); break;
            }
            switch (dados.campus)
            {
                case RESIDENCIAS: fprintf(fich, "%s; ", "Residências"); break;
                case CAMPUS1: fprintf(fich, "%s; ", "Campus 1"); break;
                case CAMPUS2: fprintf(fich, "%s; ", "Campus 2"); break;
            }
            switch (dados.capacidade)
            {
                case 1: fprintf(fich, "%s; ", CAP_BAT1); break;
                case 2: fprintf(fich, "%s; ", CAP_BAT2); break;
                case 3: fprintf(fich, "%s; ", CAP_BAT3); break;
            }
            fprintf(fich, "%.2f; ", dados.distanciaPercorrida);
            fprintf(fich, "%.2f; ", dados.tempoUtilizacao);
            fprintf(fich, "%d; ", dados.cargas);
            fprintf(fich, "%d; ", dados.requisicoes);
            fprintf(fich, "%d; ", dados.avarias);
            fprintf(fich, "%d/%d/%d\n", dados.dAquisicao.dia, dados.dAquisicao.mes, dados.dAquisicao.ano);
        }
        printf("\n\nDados exportados para ficheiro CSV.\n\n");
    }
    else
    {
        printf("\n\nDados exportados para ficheiro CSV.\n\n");
    }

    fclose(fich);
}

void gravarRequisicoesCSV(tipoRegReq dadosReg[], int elem)
{
    tipoRegReq dados;
    FILE *fich;
    int i;
    fich = fopen(NOME_CSV_REG_REQ, "w");

    if (fich != NULL)
    {
        fprintf(fich, "%s\n", CABECALHO_CSV_REG_REQ); // Escrever cabeçalhos do ficheiro CSV
        // Percorrer vetor de registos e escrever os dados
        for (i = 0; i < elem; i++)
        {
            dados = dadosReg[i];
            fprintf(fich, "%d; ", dados.idBic);
            fprintf(fich, "%s; ", dados.nomeReq);
            switch (dados.campusOrigem)
            {
                case RESIDENCIAS: fprintf(fich, "%s; ", "Residências"); break;
                case CAMPUS1: fprintf(fich, "%s; ", "Campus 1"); break;
                case CAMPUS2: fprintf(fich, "%s; ", "Campus 2"); break;
            }
            switch (dados.campusDestino)
            {
                case RESIDENCIAS: fprintf(fich, "%s; ", "Residências"); break;
                case CAMPUS1: fprintf(fich, "%s; ", "Campus 1"); break;
                case CAMPUS2: fprintf(fich, "%s; ", "Campus 2"); break;
            }
            fprintf(fich, "%d/%d/%d %d:%d\n", dados.dataReq.dia, dados.dataReq.mes, dados.dataReq.ano, dados.horaEmprestimo.hora, dados.horaEmprestimo.minuto);
        }

    }
}
