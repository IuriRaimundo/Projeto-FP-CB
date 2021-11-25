#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "registos.h"

// Funcao recebe o vetor das Bicicletas, o contador de Bicicletas e não retorna nada, no entanto vai pedir ao utilizador
// a data do registo, o tipo e a descrição, depois vai verificar o estado da bicicleta.
void registarAvariaDisponibilidade(tipoBicicleta vetorBicicletas[], int contBicicletas)
{
    char opcoesRegisto[LIM_OPCOES][LIM_CHAR_OPCAO] = { "Avaria", "Disponibilidade" };
    char descReg[LIM_DESC];
    int id, pos, tipoRegisto;
    tipoData data;
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
        printf("Insira o tipo de registo: \n");
        tipoRegisto = escolhaMultipla(opcoesRegisto, 2);
        printf("Insira a descricao: \n");
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

        // Acrescentar registo ao ficheiro texto
    }
}
