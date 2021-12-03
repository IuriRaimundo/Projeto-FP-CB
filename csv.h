#ifndef CSV_H_INCLUDED
#define CSV_H_INCLUDED

#include <stdio.h>
#include "bicicletas.h"
#include "registos.h"

// Cabe�alhos dos ficheiros CSV e nome dos ficheiros
#define CABECALHO_CSV_BIC "identifica��o; nome; estado; campus atual; capacidade da bateria; dist�ncia percorrida; tempo de utiliza��o; total de cargas; requisi��es; avarias; substituicoes; data de aquisi��o"
#define NOME_CSV_BIC "bicicletas.csv"
#define CABECALHO_CSV_REG_REQ "identifica��o da requisi��o; identifica��o da bicicleta; nome do requisitante; campo de origem; campo de destino; data da requisi��o"
#define NOME_CSV_REG_REQ "requisi��es.csv"

void gravarBicicletasCSV(tipoBicicleta dadosBic[], int elem);
void gravarRequisicoesCSV(tipoRegReq dadosReg[], int elem);

#endif // CSV_H_INCLUDED
