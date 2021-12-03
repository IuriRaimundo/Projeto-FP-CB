#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "registos.h"
#include "mensagens.h"

// Funcao recebe o vetor das Bicicletas, o contador de Bicicletas. Se a bicicleta nao estiver
// requisita vai pedir ao utilizador a data do registo, o tipo e a descri��o e alterar o estado da bicicleta
// e no final registar num ficheiro log
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
        printf(MENSAGEM_BICICLETA_NAO_EXISTE);
    }
    else
    {
        // Apenas � permitido alterar  estado de uma bicicleta nao requisitada, pelo que deve ser
        // efetuada a devolucao antes de se efetuar um registo de avaria e disponibilidade
        if (vetorBicicletas[pos].estado != ESTADO_REQ)
        {
            printf("\n\tInsira a data de registo (%s): ", FORMATO_DATA);
            data = lerData();
            printf("\n\tInsira o tipo de registo: \n");
            tipoRegisto = escolhaMultipla(opcoesRegisto, 2);
            printf("\n\tInsira a descricao: ");
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
            // Caso n�o consiga abrir o ficheiro, pedir ao utilizador se pretende tentar novamente
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
        else
        {
            printf("\nEfetue o registo de devolucao da bicicleta antes de registar uma avaria / disponibilidade.\n");
        }
    }
}

// Recebe os dados do registo e acrescenta-os em um ficheiro de texto
// Devolve 1 se guardar com sucesso, 0 se n�o conseguir abrir o ficheiro.
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
        fprintf(fich, "Registo da Bicicleta N�mero: %d \"%s\"\n", bicicleta.id, bicicleta.nome);
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
        fprintf(fich, "\tDist�ncia total percorrida: %.2fkm\n", bicicleta.distanciaPercorrida);
        fprintf(fich, "\tDescri��o: %s\n\n", desc);
        printf("\nRegisto efetuado com sucesso.\n");
        controlo = 1;
    }
    fclose(fich);
    return controlo;
}

// Recebe o vetor de bicicletas, o numero de elementos, o vetor de registos e um ponteiro para o seu contador de elementos
// Cria um registo de requisi��o caso a introdu��o dos campos seja v�lida
void registarReq(tipoBicicleta vetorBicicletas[], int contBicicletas, tipoRegReq vetorRegReq[], int *contRegReq)
{
    int pos, id, controlo;

    printf("\n\n\tREGISTO DE REQUISICAO\n\n");
    id = lerIdBicicleta();
    pos = procuraBicicleta(vetorBicicletas, id, contBicicletas);
    if (pos != -1)
    {
        // Apenas criar registo de a bicicleta selecionada estiver disponivel
        if (vetorBicicletas[pos].estado == ESTADO_DISP)
        {
                // Ler dados e inserir estrutura no vetor
                controlo = criarReq(vetorRegReq, contRegReq, vetorBicicletas[pos]);
                if (controlo != 0)
                {
                    // Alterar dados da bicicleta
                    vetorBicicletas[pos].requisicoes++;
                    vetorBicicletas[pos].estado = ESTADO_REQ;
                    printf("\nRegisto de requisicao efetuado com sucesso.\n");
                }
        }
        else
        {
            printf("\nA Bicicleta selecionada nao se encontra disponivel.\n");
        }
    }
    else
    {
        printf(MENSAGEM_BICICLETA_NAO_EXISTE);
    }
}

// Recebe o vetor de registos de requisicao, um ponteiro para o contador de registos de req e a bicicleta a ser requisitada
// Devolve 1 se criar, 0 se n�o
int criarReq(tipoRegReq vetorRegReq[], int *contRegReq, tipoBicicleta bic)
{
    tipoRegReq novoReg; int i, controlo, comparacaoDatas;
    novoReg.idBic = bic.id;
    // Ler dados
    novoReg = lerDadosRegReq(novoReg);
    // Apenas criar registo se a bicicleta selecionada estiver no campus de origem escolhido
    controlo = 0; // Apenas sera alterado no caso de sucesso
    if (novoReg.campusOrigem == bic.campus)
    {
        comparacaoDatas = compararDatas(novoReg.dataReq, bic.dAquisicao);
        // Apenas criar registo se a data de requisicao for depois ou igual � data de aquisi��o da bicicleta
        if (comparacaoDatas == 1 || comparacaoDatas == 0)
        {
            // Inserir registo no vetor
            if (*contRegReq != MAX_REGISTOS)
            {
                novoReg.idReq = *contRegReq + 1;
                vetorRegReq[*contRegReq] = novoReg;
                (*contRegReq)++;
            }
            else // Se estiver no limite do vetor
            {
                // Apagar a primeira requisicao ( a mais antiga) e deslocar todos os elementos do vetor
                // para a esquerda, o id das requisicoes ap�s o limite original ser atingido � o id do elemento
                // anterior + 1
                for (i = 1; i < *contRegReq; i++)
                {
                    vetorRegReq[i - 1] = vetorRegReq[i];
                }
                novoReg.idReq = vetorRegReq[i - 1].idReq + 1;
                vetorRegReq[i] = novoReg;
            }
            controlo = 1;
        }
        else
        {
            printf("\nA data de requisicao nao pode ser antes da data de aquisicao da bicicleta.\n");
            printf("Data de aquisicao da bicicleta: %d/%d/%d\n", bic.dAquisicao.dia, bic.dAquisicao.mes, bic.dAquisicao.ano);
        }
    }
    else
    {
        printf("\nA Bicicleta selecionada nao se encontra no campus de origem selecionado.\nCampus da bicicleta atual: ");
        switch (bic.campus)
        {
            case RESIDENCIAS: printf("Residencias"); break;
            case CAMPUS1: printf("Campus 1"); break;
            case CAMPUS2: printf("Campus 2"); break;
        }
    }
    return controlo;
}

// Recebe uma estrutura do tipoRegReq e devolve outra com os dados lidos
tipoRegReq lerDadosRegReq(tipoRegReq dadosReg)
{
    int controlo;

    printf("\n\tInsira o nome do requisitante: ");
    do
    {
        lerString(dadosReg.nomeReq, LIM_NOME_REQ);
        controlo = verificarNome(dadosReg.nomeReq);
        if (!controlo)
        {
            printf("\n\tNome invalido, repita a insercao: ");
        }
    }
    while (!controlo);

    printf("\n\tInsira o campus de origem\n");
    dadosReg.campusOrigem = escolhaCampus();
    printf("\n\tInsira o campus de destino\n");
    dadosReg.campusDestino = escolhaCampus();
    printf("\n\tInsira a data de requisicao (%s): ", FORMATO_DATA);
    dadosReg.dataReq = lerData();
    printf("\n\tInsira a hora de emprestimo (%s): ", FORMATO_HORA);
    dadosReg.horaEmprestimo = lerHora();
    return dadosReg;
}

// Recebe uma estrutura do tipoRegReq e mostra os dados de uma requisicao
void mostrarRequisicao(tipoRegReq dados)
{
    char hora[CARATERES_HORA], data[CARATERES_DATA];
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
    dataParaString(data, dados.dataReq, '/');
    horaParaString(hora, dados.horaEmprestimo);
    printf("\tData de requisicao: %s %s\n", data, hora);
}

// Recebe o vetor de requisi��es e o contador de elementos, mostra os dados do vetor
void mostrarRequisicoes(tipoRegReq vetorReq[], int contRegReq)
{
    int i;
    for (i = 0; i < contRegReq; i++)
    {
        mostrarRequisicao(vetorReq[i]);
    }
}

// Recebe o vetor de requisi��es, o contador de elementos do vetor e um id de requisi��o
// Devolve a posi��o de uma requisi��o com esse id ou -1 se n�o existir
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

// Recebe o vetor de requisi��es, o contador de elementos do vetor, o vetor de bicicleta e o seu contador
// A fun��o vai mostrar os dados das requisi��es de uma determinada bicicleta
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
// Regista uma devolu��o
void registarDev(tipoBicicleta vetorBicicletas[], int contBicicletas, tipoRegReq vetorRegReq[], int contRegReq)
{
    int id, pos, i;
    printf("\n\nREGISTO DE DEVOLUCAO\n\n");

    id = lerIdBicicleta();
    pos = procuraBicicleta(vetorBicicletas, id, contBicicletas);

    if (pos == -1)
    {
        printf(MENSAGEM_BICICLETA_NAO_EXISTE);
    }
    else
    {
        // Apenas efetuar o registo de devolu��o caso a bicicleta esteja requisitada
        if (vetorBicicletas[pos].estado == ESTADO_REQ)
        {
            printf("\n\tInsira a distancia percorrida (KM): ");
            vetorBicicletas[pos].distanciaPercorrida += lerFloat(0, LIM_KM);
            printf("\tInsira o tempo de utilizacao em horas: ");
            vetorBicicletas[pos].tempoUtilizacao += lerInteiro(0, LIM_TEMP_UTIL);
            printf("\tNumero de cargas efetuadas: ");
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

            // Atualizar campus da bicicleta com o campus de destino da sua ultima requisicao
            for (i = contRegReq; i > 0; i--)
            {
                if (vetorRegReq[i].idBic == vetorBicicletas[pos].id)
                {
                    vetorBicicletas[pos].campus = vetorRegReq[i].campusDestino;
                }
            }
            printf("\nRegisto efetuado com sucesso\n");
        }
        else
        {
            printf("\nEsta bicicleta nao se encontra requisitada.\n");
        }
    }
}

// Esta fun��o recebe um vetor de estruturas tipoRegReq e o numero de
// elementos do vetor e grava os dados em um ficheiro binario.
// Retorna 1 se gravar com sucesso, 0 se n�o gravar.
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

// Esta fun��o recebe um vetor de estruturas tipoRegReq e
// ir� adicionar a esse vetor os dados lidos do ficheiro de registos.
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
    fclose(fich);
    return elem;
}
