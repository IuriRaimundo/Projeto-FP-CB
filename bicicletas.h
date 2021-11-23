#ifndef BICICLETAS_H_INCLUDED
#define BICICLETAS_H_INCLUDED

#include "datas.h"

#define NOME_FICH_BICICLETAS "bicicletas.tio"
#define MAX_BICICLETAS 20
#define LIM_ID 20
#define LIM_NOME 50
// Capacidades de bateria
#define CAP_BAT1 "10"
#define CAP_BAT2 "15"
#define CAP_BAT3 "20"
// Estados da bicicleta
#define ESTADO_DISP 1
#define ESTADO_REQ 2
#define ESTADO_AVAR 3
#define ESTADO_DESAT 4
// Campus
#define RESIDENCIAS 1
#define CAMPUS1 2
#define CAMPUS2 3

typedef struct {
	int id; // Identificacao unica da bicicleta
	char nome[LIM_NOME]; // Designacao da bicicleta
	int estado; // Estado da bicicleta (1 - Dispon�vel, 2 - Requisitada, 3 - Avariada, 4 - Desativada)
	int campus; // Campus (1 - Residencias, 2 - Campus1, 3 - Campus2)
	int capacidade; // Capacidade da bateria 10 Ah, 15 Ah ou 20 Ah
	int cargas;
	float distanciaPercorrida;
	tipoData dAquisicao; // Data de aquisicao da bicicleta
} tipoBicicleta;

void criarBicicleta(tipoBicicleta vetorBicicletas[], int* contBicicletas);
int lerIdBicicleta(void);
int verificarUnicidadeIdBic(tipoBicicleta vetor[], int contBicicletas, int id);
tipoBicicleta lerDadosBicicleta(tipoBicicleta bicicleta);
int procuraBicicleta(tipoBicicleta vetorBicicletas[], int id, int numeroBicicletas);
int gravarFichBicicleta(tipoBicicleta dadosBic[], int elem);
int lerFichBicicleta(tipoBicicleta dadosBic[]);

#endif // BICICLETAS_H_INCLUDED
