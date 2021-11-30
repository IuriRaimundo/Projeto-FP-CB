#ifndef FUNCOESMENU_H_INCLUDED
#define FUNCOESMENU_H_INCLUDED

#include <stdio.h>
#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "registos.h"

int menu(int totalBicicletas, float distancia, int registos, int bicicletasDisponiveis);
void gravarDadosFich(tipoBicicleta dadosBic[], int totBic, tipoRegReq dadosReg[], int totReg);
void lerDadosFich(tipoBicicleta vetorBic[], int *totalBic, tipoRegReq vetorReg[], int *totalReg);
void listagens(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq);
int menuListagens(void);

#endif // FUNCOESMENU_H_INCLUDED
