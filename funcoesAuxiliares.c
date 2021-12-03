#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcoesAuxiliares.h"

void limpaBufferStdin(void)
{
    char lixo;
    do
    {
        lixo = getchar();
    } while (lixo != '\n' && lixo != EOF);
}

int lerInteiro(int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        controlo = scanf("%d", &numero); // scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin();

        if (numero<minimo || numero>maximo)
        {
            printf("\n Numero invalido. Insira novamente: ");
        }
        if (controlo == 0) {
            printf("\n Nao foi inserido um valor (numerico) valido. Insira novamente: ");
        }

    } while (numero<minimo || numero>maximo || controlo == 0);

    return numero;
}

float lerFloat(float minimo, float maximo)
{
    float numero;
    int controlo;

    do
    {
        controlo = scanf("%f", &numero);
        limpaBufferStdin();

        if (numero<minimo || numero>maximo)
        {
            printf("\n Numero invalido. Insira novamente: ");
        }
        if (controlo == 0) {
            printf("\n Nao foi inserido um valor (numerico) valido. Insira novamente: ");
        }
    } while (numero<minimo || numero>maximo || controlo == 0);

    return numero;
}

void lerString(char vetorCaracteres[], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (vetorCaracteres[tamanhoString - 1] != '\n')  // ficaram caracteres no buffer....
        {
            limpaBufferStdin();  // apenas faz sentido limpar buffer se la ficarem caracteres
        }
        else {
            vetorCaracteres[tamanhoString - 1] = '\0';  // Elimina \n da string
        }

        if (tamanhoString == 1)
        {
            printf("\nNao foram introduzidos caracteres!\nRepita a insercao: ");
        }
    } while (tamanhoString == 1);
}

// Recebe uma matriz de carateres com o texto para as diferentes opções e o número de opções
// Devolve a escolha do utilizador
int escolhaMultipla(char textoOpcoes[LIM_OPCOES][LIM_CHAR_OPCAO], int nOpcoes)
{
    int op, i;
    for (i = 0; i < nOpcoes; i++)
    {
        printf("\t%d. %s\n", i + 1, textoOpcoes[i]);
    }
    printf("\n\t\tEscolha: ");
    op = lerInteiro(1, nOpcoes);
    return op;
}

// Recebe o texto para apresentar na solicitação de carater
// Devolve 1 se for escolhido Sim, 0 se for escolhido não.
int escolhaSimOuNao(char texto[])
{
    char escolha; int retorno;
    printf("%s (S/N): ", texto);
    do
    {
        scanf("%c", &escolha);
        escolha = tolower(escolha);
        if (escolha != 's' && escolha != 'n')
        {
            printf("\tEscolha inválida, insira 'S' ou 'N': ");
        }
    }
    while (escolha != 's' && escolha != 'n');
    if (escolha == 's')
    {
        retorno = 1;
    }
    else
    {
        retorno = 0;
    }
    limpaBufferStdin();
    return retorno;
}

// Verifica se uma string é um nome, se a string tiver menos de 3 carateres consideramos inválida
// Se conter digitos também consideramos inválida.
int verificarNome(char nome[])
{
    int valido, n, i;
    valido = 1;
    n = strlen(nome);
    if (n < 3)
    {
        valido = 0;
    }
    for (i = 0; i < n; i++)
    {
        if (isdigit(nome[i]))
        {
            valido = 0;
        }
    }
    return valido;
}
