#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#include <stdio.h>
#include "bicicletas.h"
#include "registos.h"

#define CABECALHO_CSV_BIC "identificação; nome; estado; campus atual; capacidade da bateria; distância percorrida; tempo de utilização; total de cargas; requisições; avarias; data de aquisição"
#define NOME_CSV_BIC "bicicletas.csv"
#define CABECALHO_CSV_REG_REQ "identificação da bicicleta; nome do requisitante; campo de origem; campo de destino; data da requisição"
#define NOME_CSV_REG_REQ "requisições.csv"

void gravarBicicletasCSV(tipoBicicleta dadosBic[], int elem);

#endif // CSV_H_INCLUDED
