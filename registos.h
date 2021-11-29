#ifndef REGISTOS_H_INCLUDED
#define REGISTOS_H_INCLUDED

#include "datas.h"
#include "funcoesAuxiliares.h"
#include "bicicletas.h"

#define NOME_FICH_LOG "registos_avarias_disponibilidade.txt"
#define MAX_REGISTOS 100
#define LIM_KM 1000
#define LIM_DESC 201
#define LIM_NOME_REQ 50
#define LIM_ID_REG MAX_REGISTOS
#define LIM_CARGAS 1000

// Mensagens de erro/sucesso
#define MENSAGEM_LIMITE_REG "\nLimite de registos atingido.\n"

typedef struct {
    int idBic;
    char nomeReq[LIM_NOME_REQ];
    int campusOrigem;
    int campusDestino;
    tipoData dataReq;
    tipoHora horaEmprestimo;
} tipoRegReq;


// Registos de avaria disponibilidade
void registarAvariaDisponibilidade(tipoBicicleta vetorBicicletas[], int contBicicletas);
int escreverLogAvariaDisponibilidade(tipoBicicleta bicicleta, tipoData data, int tipoRegisto, char desc[]);

// Registos de requisi��o
void registarReq(tipoBicicleta vetorBicicletas[], int contBicicletas, tipoRegReq vetorRegReq[], int *contRegReq);
tipoRegReq lerDadosRegReq(tipoRegReq reg);

// Registos de Devolu��o
void registarDev(tipoBicicleta vetorBicicletas[], int contBicicletas);

#endif // REGISTOS_H_INCLUDED

