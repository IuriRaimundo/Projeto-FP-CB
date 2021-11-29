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
    int controlo;
    FILE *fich;
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

void registarReq(tipoBicicleta vetorBicicletas[], int contBicicletas, tipoRegReq vetorRegReq[], int *contRegReq)
{
    tipoRegReq novoReg;
    int pos;
    printf("\n\n\tREGISTO DE REQUISICAO\n\n");
    novoReg.idBic = lerIdBicicleta();
    pos = procuraBicicleta(vetorBicicletas, novoReg.idBic, contBicicletas);
    if (pos != -1)
    {
        novoReg = lerDadosRegReq(novoReg);
        vetorRegReq[*contRegReq] = novoReg;
        (*contRegReq)++;
        printf("\n\nRegisto de requisicao efetuado com sucesso.\n\n");
        vetorBicicletas[pos].requisicoes++;
    }
    else
    {
        printf("\n\nNao existe uma bicicleta com esse id.\n\n");
    }

}

tipoRegReq lerDadosRegReq(tipoRegReq dadosReg)
{
    int controlo;

    printf("\nInsira o nome do requisitante: ");
    do
    {
        lerString(dadosReg.nomeReq, LIM_NOME_REQ);
        controlo = verificarNome(dadosReg.nomeReq);
        if (!controlo)
        {
            printf("\nNome invalido, repita a insercao: ");
        }
    }
    while (!controlo);

    printf("\nInsira o campus de origem\n");
    dadosReg.campusOrigem = escolhaCampus();
    printf("\n Insira o campus de destino\n");
    dadosReg.campusDestino = escolhaCampus();
    printf("\n Insira a data de requisicao (%s): ", FORMATO_DATA);
    dadosReg.dataReq = lerData();
    printf("\n Insira a hora de emprestimo (%s): ", FORMATO_HORA);
    dadosReg.horaEmprestimo = lerHora();
    return dadosReg;
}

void registarDev(tipoBicicleta vetorBicicletas[], int contBicicletas)
{
    int id, pos;
    tipoHora hora;
    printf("\n\nREGISTO DE DEVOLUCAO\n\n");

    id = lerIdBicicleta();
    pos = procuraBicicleta(vetorBicicletas, id, contBicicletas);

    if (pos == -1)
    {
        printf("\n\nEssa bicicleta nao existe.\n\n");
    }
    else
    {
        printf("Insira a distância percorrida (KM): ");
        vetorBicicletas[pos].distanciaPercorrida += lerFloat(0, LIM_KM);
        printf("Insira o tempo de utilizacao (%s): ", FORMATO_HORA);
        vetorBicicletas[pos].tempoUtilizacao += lerHora();
        printf("Insira o numero de cargas: ");
        vetorBicicletas[pos].cargas = lerInteiro(0,LIM_CARGAS);
        if (vetorBicicletas[pos].cargas > LIM_CARGAS)
        {
        vetorBicicletas[pos].estado = ESTADO_DESAT;
        }
    }
    printf("\n\nRegisto efetuado com sucesso\n");
}
