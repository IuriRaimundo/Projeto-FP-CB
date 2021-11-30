#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "registos.h"
#include "mensagens.h"

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

// Recebe o vetor de bicicletas, o numero de elementos, o vetor de registos e um ponteiro para o seu contador de elementos
// Cria um registo de requisição caso a introdução dos campos seja válida
void registarReq(tipoBicicleta vetorBicicletas[], int contBicicletas, tipoRegReq vetorRegReq[], int *contRegReq)
{
    tipoRegReq novoReg;
    int pos;

    if (*contRegReq < 100)
    {
        printf("\n\n\tREGISTO DE REQUISICAO\n\n");
        novoReg.idBic = lerIdBicicleta();
        pos = procuraBicicleta(vetorBicicletas, novoReg.idBic, contBicicletas);
        if (pos != -1)
        {
            // Apenas criar registo de a bicicleta selecionada estiver disponivel
            if (vetorBicicletas[pos].estado == ESTADO_DISP)
            {
                // Ler dados
                novoReg = lerDadosRegReq(novoReg);

                // Apenas criar registo se a bicicleta selecionada estiver no campus de origem escolhido
                if (novoReg.campusOrigem == vetorBicicletas[pos].campus)
                {
                    // Inserir registo no vetor
                    novoReg.idReq = *contRegReq + 1; // O id da requisição será a sua posição no vetor + 1, apenas estético, não é usado como localizador
                    vetorRegReq[*contRegReq] = novoReg;
                    (*contRegReq)++;
                    // Alterar bicicleta
                    vetorBicicletas[pos].requisicoes++;
                    vetorBicicletas[pos].estado = ESTADO_REQ;
                    printf("\n\nRegisto de requisicao efetuado com sucesso.\n\n");
                }
                else
                {
                    printf("\n\nA Bicicleta selecionada nao se encontra no campus de origem selecionado.\n\n");
                }
            }
            else
            {
                printf("\n\nA Bicicleta selecionada nao se encontra disponivel.\n\n");
            }
        }
        else
        {
            printf("\n\nNao existe uma bicicleta com esse id.\n\n");
        }
    }
    else
    {
        printf("\n\nMaximo de registos atingido.\n\n");
    }
}

// Recebe uma estrutura do tipoRegReq e devolve outra com os dados lidos
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

// Recebe uma estrutura do tipoRegReq e mostra os dados de uma requisicao
void mostrarRequisicao(tipoRegReq dados)
{
    printf("\nRequisicao n. %d\n", dados.idReq);
    printf("\tBicicleta requisitada: %d\n", dados.idBic);
    printf("\tNome do requisitante: %s\n", dados.nomeReq);
    printf("\tCampus de origem: ");
    switch (dados.campusOrigem)
    {
        case RESIDENCIAS: printf("%s\n", "Residencias"); break;
        case CAMPUS1: printf("%s\n", "Campus 1"); break;
        case CAMPUS2: printf("%s\n", "Campus 2"); break;
    }
    printf("\tCampus de destino: ");
    switch (dados.campusDestino)
    {
        case RESIDENCIAS: printf("%s\n", "Residencias"); break;
        case CAMPUS1: printf("%s\n", "Campus 1"); break;
        case CAMPUS2: printf("%s\n", "Campus 2"); break;
    }
    printf("\tData de requisicao: %d/%d/%d %d:%d", dados.dataReq.dia, dados.dataReq.mes, dados.dataReq.ano, dados.horaEmprestimo.hora, dados.horaEmprestimo.minuto);
}

// Recebe o vetor de requisições e o contador de elementos, mostra os dados do vetor
void mostrarRequisicoes(tipoRegReq vetorReq[], int contRegReq)
{
    int i;
    for (i = 0; i < contRegReq; i++)
    {
        mostrarRequisicao(vetorReq[i]);
    }
}

// Recebe o vetor de requisições, o contador de elementos do vetor e um id de requisição
// Devolve a posição de uma requisição com esse id ou -1 se não existir
int procuraRequisicaoPorId(tipoRegReq vetorReg[], int contRegReq, int id)
{
    int pos, i;
    pos = -1;
    for (i = 0; i < contRegReq; i++)
    {
        if (vetorReg[i].idReq == id)
        {
            pos = i;
            i = contRegReq;
        }
    }
    return pos;
}

// Recebe o vetor de requisições, o contador de elementos do vetor, o vetor de bicicleta e o seu contador
// A função vai mostrar os dados das requisições de uma determinada bicicleta
void mostrarRequisicoesDeUmaBicicleta(tipoRegReq vetorReg[], int contRegReq)
{
    int id, i, mostradas;
    printf("\n");
    id = lerIdBicicleta();
    for (i = 0, mostradas = 0; i < contRegReq; i++)
    {
        if (vetorReg[i].idBic == id)
        {
            mostrarRequisicao(vetorReg[i]);
            mostradas++;
        }
    }
    if (mostradas == 0)
    {
        printf("\n\nEssa bicicleta nao teve requisicoes.\n\n");
    }
}

// Recebe o vetor de bicicletas e o numero de elementos
// Regista uma devolução
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
        // Apenas efetuar o registo de devolução caso a bicicleta esteja requisitada
        if (vetorBicicletas[pos].estado == ESTADO_REQ)
        {
            printf("Insira a distância percorrida (KM): ");
            vetorBicicletas[pos].distanciaPercorrida += lerFloat(0, LIM_KM);
            printf("Insira o tempo de utilizacao (%s): ", FORMATO_HORA);
            hora = lerHora();
            vetorBicicletas[pos].tempoUtilizacao += tipoHoraParaFloat(hora);
            printf("Numero de cargas efetuadas: ");
            vetorBicicletas[pos].cargas += lerInteiro(0, LIM_CARGAS);
            // Se a bicicleta exceder as 1000 cargas deve ser desativada
            if (vetorBicicletas[pos].cargas >= LIM_CARGAS)
            {
                vetorBicicletas[pos].estado = ESTADO_DESAT;
            }
            else
            {
                vetorBicicletas[pos].estado = ESTADO_DISP;
            }
            printf("\n\nRegisto efetuado com sucesso\n");
        }
        else
        {
            printf("\n\nEsta bicicleta nao se encontra requisitada.\n\n");
        }
    }
}

// Esta função recebe um vetor de estruturas tipoRegReq e o numero de
// elementos do vetor e grava os dados em um ficheiro binario.
// Retorna 1 se gravar com sucesso, 0 se não gravar.
int gravarFichReq(tipoRegReq dadosReq[], int elem)
{
    FILE *fich; int controlo;
    fich = fopen(NOME_FICH_REG, "wb");
    if (fich != NULL)
    {
        fwrite(&elem, sizeof(int), 1, fich);
        fwrite(dadosReq, sizeof(tipoRegReq), elem, fich);
        controlo = 1;
    }
    else
    {
        controlo = 0;
    }
    fclose(fich);
    return controlo;
}

// Esta função recebe um vetor de estruturas tipoRegReq e
// irá adicionar a esse vetor os dados lidos do ficheiro de registos.
// Retorna o numero de elementos lidos.
int lerFichReg(tipoRegReq dadosReq[])
{
    FILE *fich; int elem;
    fich = fopen(NOME_FICH_REG, "rb");
    elem = 0;
    if (fich != NULL)
    {
        fread(&elem, sizeof(int), 1, fich);
        fread(dadosReq, sizeof(tipoRegReq), elem, fich);
    }
    else
    {
        printf("\nNao foi possivel abrir o ficheiro dos registos.\n");
    }
    fclose(fich);
    return elem;
}
