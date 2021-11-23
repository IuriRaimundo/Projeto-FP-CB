#include "funcoesAuxiliares.h"
#include "registos.h"

// Funcao recebe o vetor das Bicicletas, o contador de Bicicletas e n�o retorna nada, no entanto vai pedir ao utilizador
// a data do registo, o tipo e a descri��o, depois vai verificar o estado da bicicleta.
void registarAvariaDisponibilidade(tipoBicicleta vetorBicicletas[], int contBicicletas)
{
    char tiposRegisto[LIM_OPCOES][LIM_CHAR_OPCAO] = { "Avaria", "Disponibilidade" };
    char descReg[LIM_DESC];
    int id, pos, tipoReg;
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
        tipoReg = escolhaMultipla(tiposRegisto, 2);
        printf("Insira a descricao: \n");
        lerString(descReg, LIM_DESC);
        if (tipoReg == 1)
        {
            vetorBicicletas[pos].estado = 1;
        }
        else
        {
            vetorBicicletas[pos].estado = 3;
        }
    }
}
