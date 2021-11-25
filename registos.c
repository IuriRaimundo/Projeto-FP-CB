#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "registos.h"

// Funcao recebe o vetor das Bicicletas, o contador de Bicicletas e não retorna nada, no entanto vai pedir ao utilizador
// a data do registo, o tipo e a descrição, depois vai verificar o estado da bicicleta.
void registarAvariaDisponibilidade(tipoBicicleta vetorBicicletas[], int contBicicletas)
{
    char opcoesRegisto[LIM_OPCOES][LIM_CHAR_OPCAO] = { "Avaria", "Disponibilidade" };
    char descReg[LIM_DESC];
    int id, pos, tipoRegisto, controloFich, repetir;
    tipoData data;

    printf("\n\nREGISTO DE AVARIA / DISPONIBILIDADE\n\n");
    id = lerIdBicicleta();
    pos = procuraBicicleta(vetorBicicletas, id, contBicicletas);

    if (pos == -1)
    {
        printf("\n\nEssa bicicleta nao existe.\n\n");
    }
    else
    {
        printf("\nInsira a data de registo: ");
        data = lerData();
        printf("\nInsira o tipo de registo: \n");
        tipoRegisto = escolhaMultipla(opcoesRegisto, 2);
        printf("\nInsira a descricao: ");
        lerString(descReg, LIM_DESC);

        // Alterar estado da bicicleta com a escolha do utilizador com o valor definido em constantes
        if (tipoRegisto == 1)
        {
            vetorBicicletas[pos].estado = ESTADO_AVAR;
            vetorBicicletas[pos].avarias++;
        }
        else
        {
            vetorBicicletas[pos].estado = ESTADO_DISP;
        }

        // Acrescentar registo a um ficheiro de texto.
        // Caso não consiga abrir o ficheiro, pedir ao utilizador se pretende tentar novamente
        // Caso falhe novamente, volte a solicitar.
        do
        {
            controloFich = escreverLogAvariaDisponibilidade(vetorBicicletas[pos], data, tipoRegisto, descReg);
            if (!controloFich)
            {
                repetir = escolhaSimOuNao("Pretende tentar guardar o registo novamente?");
            }
        }
        while (!controloFich && repetir);
    }
}

// Recebe os dados do registo e acrescenta-os em um ficheiro de texto
// Devolve 1 se guardar com sucesso, 0 se não conseguir abrir o ficheiro.
int escreverLogAvariaDisponibilidade(tipoBicicleta bicicleta, tipoData data, int tipoRegisto, char desc[])
{
    int controlo; FILE *fich;
    fich = fopen(NOME_FICH_LOG, "a");
    if (fich == NULL)
    {
        printf("\n\nErro ao abrir o ficheiro log.\n\n");
        controlo = 0;
    }
    else
    {
        fprintf(fich, "\nRegisto da Bicicleta Número: %d \"%s\"\n", bicicleta.id, bicicleta.nome);
        fprintf(fich, "\n\tRegisto efetuado em %d/%d/%d\n", data.dia, data.mes, data.ano);
        fprintf(fich, "\tTipo de registo: ");
        if (tipoRegisto == 1)
        {
            fprintf(fich, "Avaria\n");
        }
        else
        {
            fprintf(fich, "Disponibilidade\n");
        }
        fprintf(fich, "\tDistância total percorrida: %.2fkm\n", bicicleta.distanciaPercorrida);
        fprintf(fich, "\tDescrição: %s", desc);
        printf("\n\nRegisto efetuado com sucesso.\n\n");
        controlo = 1;
    }
    fclose(fich);
    return controlo;
}

tipoRegReq lerDadosRegReq(void)
{
    tipoRegReq dadosReg;
    char campus[LIM_OPCOES][LIM_CHAR_OPCAO]= { "Residencias", "Campus 1", "Campus 2" };

    printf("\n\n\tREGISTO DE REQUISIÇÃO\n\n");
    printf("\nInsira o ID da Bicicleta: ");
    dadosReg.idBic = lerIdBicicleta();
    printf("\nInsira o nome do requisitante: ");
    lerString(dadosReg.nomeReq, LIM_NOME_REQ);
    printf("\nInsira o campus de origem\n");
    dadosReg.campusOrigem = escolhaMultipla(campus, 3);
    switch (dadosReg.campusOrigem)
    {
        case 1: dadosReg.campusOrigem= RESIDENCIAS; break;
        case 2: dadosReg.campusOrigem = CAMPUS1; break;
        case 3: dadosReg.campusOrigem = CAMPUS2; break;
    }
    printf("\n Insira o campus de destino\n");
    dadosReg.campusDestino = escolhaMultipla(campus, 3);
    switch (dadosReg.campusDestino)
    {
        case 1: dadosReg.campusOrigem= RESIDENCIAS; break;
        case 2: dadosReg.campusOrigem = CAMPUS1; break;
        case 3: dadosReg.campusOrigem = CAMPUS2; break;
    }
    printf("\n Insira a data de requisicao: ");
    dadosReg.dataReq = lerData();
    printf("\n Insira a hora de emprestimo: ");
    dadosReg.horaEmprestimo.hora = lerInteiro(0, 24);
    dadosReg.horaEmprestimo.minuto = lerInteiro(0, 60);

    return dadosReg;
}
