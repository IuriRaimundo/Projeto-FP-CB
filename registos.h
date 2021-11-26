#ifndef REGISTOS_H_INCLUDED
#define REGISTOS_H_INCLUDED

#include "datas.h"
#include "funcoesAuxiliares.h"
#include "bicicletas.h"

#define NOME_FICH_LOG "registos_avarias_disponibilidade.txt"
#define MAX_REGISTOS 100
#define LIM_KM 10000
#define LIM_DESC 201
#define LIM_NOME_REQ 50
#define LIM_ID_REG MAX_REGISTOS

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

// Registos de requisição
void registarReq(tipoBicicleta vetorBicicletas[], int contBicicletas, tipoRegReq vetorRegReq[], int *contRegReq);
tipoRegReq lerDadosRegReq(tipoRegReq reg);

#endif // REGISTOS_H_INCLUDED

