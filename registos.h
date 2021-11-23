#ifndef REGISTOS_H_INCLUDED
#define REGISTOS_H_INCLUDED

#include "datas.h"
#include "funcoesAuxiliares.h"
#include "bicicletas.h"

#define MAX_REGISTOS 100
#define LIM_KM 10000
#define LIM_DESC 201

// Mensagens de erro/sucesso
#define MENSAGEM_LIMITE_REG "\nLimite de registos atingido.\n"

void registarAvariaDisponibilidade(tipoBicicleta vetorBicicletas[], int contBicicletas);

#endif // REGISTOS_H_INCLUDED

