#include <stdlib.h>

#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "mensagens.h"

// Esta funcao cria uma estrutura bicicleta e adiciona-lhe ao vetor das bicicletas,
// recebe o ponteiro para o vetor e o contador de bicicletas
void criarBicicleta(tipoBicicleta vetorBicicletas[], int *contBicicletas)
{
    tipoBicicleta bicicleta; int idUnico;
    if (*contBicicletas == MAX_BICICLETAS)
    {
        printf("\n\nLimite de bicicletas atingido.\n\n");
    }
    else
    {
        printf("\n\nNOVA BICICLETA\n\n");
        bicicleta.id = lerIdBicicleta();
        idUnico = verificarUnicidadeIdBic(vetorBicicletas, *contBicicletas, bicicleta.id);
        // Ler dados da bicicleta e adicionar ao vetor caso tenha sido inserido um id válido.
        if (idUnico)
        {
            // Ler dados restantes
            bicicleta = lerDadosBicicleta(bicicleta);
            // Adicionar bicicleta ao vetor
            vetorBicicletas[*contBicicletas] = bicicleta;
            (*contBicicletas)++;
            printf("\n\nBicicleta adicionada com sucesso!\n\n");
        }
        else
        {
            printf("\n\nJa existe uma bicicleta com este id.\n\n");
        }
    }
}

// Verifica a unicidade de um id de bicicleta, devolve 1 se for unico, 0 se não.
int verificarUnicidadeIdBic(tipoBicicleta vetor[], int contBicicletas, int id)
{
    int pos, unico;
    pos = procuraBicicleta(vetor, id, contBicicletas);
    if (pos == -1)
    {
        unico = 1;
    }
    else
    {
        unico = 0;
    }
    return unico;
}

// Le um id da bicicleta e devolve-o
int lerIdBicicleta(void)
{
    int id;
    printf("Identificacao da bicicleta: ");
    id = lerInteiro(1, LIM_ID);
    return id;
}

// Le dados e devolve uma estrutura do tipoBicicleta
tipoBicicleta lerDadosBicicleta(tipoBicicleta bicicleta)
{
    int escolhaEstado, escolhaCampus;
    // Opcoes para as funcoes de escolha multipla
    char estados[LIM_OPCOES][LIM_CHAR_OPCAO] = { "Disponivel", "Requisitada", "Avariada", "Desativada" };
    char campus[LIM_OPCOES][LIM_CHAR_OPCAO]= { "Residencias", "Campus 1", "Campus 2" };
    char baterias[LIM_OPCOES][LIM_CHAR_OPCAO] = {{CAP_BAT1}, {CAP_BAT2}, {CAP_BAT3}};

    // Designação de bicicleta
    printf("\nNome: ");
    lerString(bicicleta.nome, LIM_NOME_BIC);

    // Solicitar estado e associar valor das contantes de estado à estrutura bicicleta
    printf("\nEstado da bicicleta\n");
    escolhaEstado = escolhaMultipla(estados, 4);
    switch (escolhaEstado)
    {
        case 1: bicicleta.estado = ESTADO_DISP; break;
        case 2: bicicleta.estado = ESTADO_REQ; break;
        case 3: bicicleta.estado = ESTADO_AVAR; break;
        case 4: bicicleta.estado = ESTADO_DESAT; break;
    }

    // Solicitar campus e associar valor das contantes de campus à estrutura bicicleta
    printf("\nCampus\n");
    escolhaCampus = escolhaMultipla(campus, 3);
    switch (escolhaCampus)
    {
        case 1: bicicleta.campus = RESIDENCIAS; break;
        case 2: bicicleta.campus = CAMPUS1; break;
        case 3: bicicleta.campus = CAMPUS2; break;
    }

    // O valor das baterias 1, 2 e 3 é definido em constantes
    printf("\nCapacidade da bateria (%sAh, %sAh ou %sAh)\n", CAP_BAT1, CAP_BAT2, CAP_BAT3);
    bicicleta.capacidade = escolhaMultipla(baterias, 3);

    // Data de aquisição
    printf("\nData de aquisicao (DD/MM/YY): ");
    bicicleta.dAquisicao = lerData();

    // Inicializar o contador de cargas a 0 por defeito
    bicicleta.cargas = 0;

    return bicicleta;
}

// Recebe o vetor de bicicletas, um id e o contador de bicicletas e procura uma bicicleta com esse id
// Retorna -1 se não encontrar nenhuma bicicleta com id correspondente ou a posição da bicicleta no vetor.
int procuraBicicleta(tipoBicicleta vetorBicicletas[], int id, int contBicicletas)
{
    int i, pos;
    pos = -1;
    for (i = 0; i < contBicicletas; i++)
    {
        if (vetorBicicletas[i].id == id)
        {
            pos = i;
            i = contBicicletas;
        }
    }
    return pos;
}

// Esta função recebe um vetor de estruturas tipoBicicletas e o numero de
// elementos do vetor e grava os dados em um ficheiro binario.
// Retorna 1 se gravar com sucesso, 0 se não gravar.
int gravarFichBicicleta(tipoBicicleta dadosBic[], int elem)
{
    FILE *fich; int controlo;
    fich = fopen(NOME_FICH_BICICLETAS, "wb");
    if (fich != NULL)
    {
        fwrite(&elem, sizeof(int), 1, fich);
        fwrite(dadosBic, sizeof(tipoBicicleta), elem, fich);
        controlo = 1;
    }
    else
    {
        controlo = 0;
    }
    fclose(fich);
    return controlo;
}

// Esta função recebe um vetor de estruturas tipoBicicletas e
// irá adicionar a esse vetor os dados lidos do ficheiro de bicicletas.
// Retorna o numero de elementos lidos.
int lerFichBicicleta(tipoBicicleta dadosBic[])
{
    FILE *fich; int elem;
    fich = fopen(NOME_FICH_BICICLETAS, "rb");
    elem = 0;
    if (fich != NULL)
    {
        fread(&elem, sizeof(int), 1, fich);
        fread(dadosBic, sizeof(tipoBicicleta), elem, fich);
    }
    else
    {
        printf(MENSAGEM_ERRO_LER);
    }
    fclose(fich);
    return elem;
}
