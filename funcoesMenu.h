#ifndef FUNCOESMENU_H_INCLUDED
#define FUNCOESMENU_H_INCLUDED

#include <stdio.h>
#include "funcoesAuxiliares.h"
#include "bicicletas.h"
#include "registos.h"

// Controlo de ficheiros
#define CONTROLO_SUCESSO_GRAVAR_FICH 2

int menu(int totalBicicletas, float distancia, int registos, int bicicletasDisponiveis);
void gravarDadosFich(tipoBicicleta dadosBic[], int totBic, tipoRegReq dadosReg[], int totReg);
void lerDadosFich(tipoBicicleta vetorBic[], int *totalBic, tipoRegReq vetorReg[], int *totalReg);
void listagens(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq);
int menuListagens(void);
void informacoes(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq);
int menuInformacoes(void);
void informacoesGerais(tipoBicicleta vetorBic[], int contBic, tipoRegReq vetorReq[], int contRegReq);

#endif // FUNCOESMENU_H_INCLUDED
