#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Limite de opcoes na funcao auxiliar de escolha multipla
#define LIM_OPCOES 10
// Limite de carateres de uma opcao na funcao auxiliar de escolha multipla
#define LIM_CHAR_OPCAO 70

void limpaBufferStdin(void);
int lerInteiro(int minimo, int maximo);
float lerFloat(float minimo, float maximo);
void lerString(char vetorCaracteres[], int maximoCaracteres);
int escolhaMultipla(char textoOpcoes[LIM_OPCOES][LIM_CHAR_OPCAO], int nOpcoes);
int escolhaSimOuNao(char texto[]);
int verificarNome(char nome[]);

#endif // FUNCOESAUXILIARES_H_INCLUDED
