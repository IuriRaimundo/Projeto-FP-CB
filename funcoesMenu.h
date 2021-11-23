#ifndef FUNCOESMENU_H_INCLUDED
#define FUNCOESMENU_H_INCLUDED

#include <stdio.h>
#include "funcoesAuxiliares.h"
#include "bicicletas.h"

int menu(int totalBicicletas, float distancia, int registos, int bicicletasDisponiveis);
void gravarDados(tipoBicicleta dadosBic[], int totBic);

#endif // FUNCOESMENU_H_INCLUDED
