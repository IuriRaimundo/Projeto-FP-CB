#ifndef BICICLETAS_H_INCLUDED
#define BICICLETAS_H_INCLUDED

#include "datas.h"

#define NOME_FICH_BICICLETAS "bicicletas.tio"
#define MAX_BICICLETAS 20
#define LIM_ID 20
#define LIM_NOME_BIC 50
// Capacidades de bateria
#define CAP_BAT1 "10Ah"
#define CAP_BAT2 "15Ah"
#define CAP_BAT3 "20Ah"
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
	char nome[LIM_NOME_BIC]; // Designacao da bicicleta
	int estado; // Estado da bicicleta (1 - Disponivel, 2 - Requisitada, 3 - Avariada, 4 - Desativada)
	int campus; // Campus (1 - Residencias, 2 - Campus1, 3 - Campus2)
	float distanciaPercorrida; // Acumulador de distância percorrida
	float tempoUtilizacao; // Acumulador do tempo de utilização
	int capacidade; // Capacidade da bateria 10 Ah, 15 Ah ou 20 Ah
	int cargas;      // Contador de cargas
	int requisicoes; // Contador de requisições
	int avarias;     // Contador de avarias
	int substituicoes; // Contador de substituicoes de bateria
	tipoData dAquisicao; // Data de aquisicao da bicicleta
} tipoBicicleta;

int criarBicicleta(tipoBicicleta vetorBicicletas[], int* contBicicletas);
int lerIdBicicleta(void);
int verificarUnicidadeIdBic(tipoBicicleta vetor[], int contBicicletas, int id);
tipoBicicleta lerDadosBicicleta(tipoBicicleta bicicleta);
int procuraBicicleta(tipoBicicleta vetorBicicletas[], int id, int numeroBicicletas);
int escolhaCampus(void);
int gravarFichBicicleta(tipoBicicleta dadosBic[], int elem);
int lerFichBicicleta(tipoBicicleta dadosBic[]);
void mostrarBicicleta(tipoBicicleta dados);
void mostrarDadosBicicletas(tipoBicicleta vetorBicicletas[], int contBicicletas);
void mostrarBicicletasRequisitadas(tipoBicicleta vetorBicicletas[], int contBicicletas);
int contarBicicletasDisponiveis(tipoBicicleta vetorBicicletas[], int contBicicletas);
float contarDistPercorrida(tipoBicicleta vetorBicicletas[], int contBicicletas);

#endif // BICICLETAS_H_INCLUDED
