#include <stdlib.h>
#include <stdio.h>

#include "funcoesAuxiliares.h"
#include "funcoesMenu.h"
#include "datas.h"
#include "bicicletas.h"
#include "registos.h"

int main(void)
{
    // Vetores e contadores de elementos
    tipoBicicleta vetorBicicletas[MAX_BICICLETAS];
    int totalBicicletas;

    tipoRegReq vetorRegReq[MAX_REGISTOS];
    int totalRegReq;

    int op, bicicletasDisponiveis, registosDesloc;
    float totalDistanciaPercorrida;

    // Ler dados gravados
    lerDadosFich(vetorBicicletas, &totalBicicletas, vetorRegReq, &totalRegReq);

    // Inicializar contadores e acumuladores
    totalDistanciaPercorrida = 0;
    registosDesloc = 0;
    bicicletasDisponiveis = 0;
    totalRegReq = 0;

    // O programa apenas ser terminado quando o utilizador selecionar a opção 0
    do
    {
        op = menu(totalBicicletas, totalDistanciaPercorrida, registosDesloc, bicicletasDisponiveis);
        switch (op)
        {
        // 1. Nova Bicicleta
        case 1: criarBicicleta(vetorBicicletas, &totalBicicletas);
        break;
        // 2. Registo de Avaria/Disponibilidade
        case 2: registarAvariaDisponibilidade(vetorBicicletas, totalBicicletas);
         break;
        // 3. Registo de Requisição
        case 3: registarReq(vetorBicicletas, totalBicicletas, vetorRegReq, &totalRegReq); break;
        // 4. Registo de Devolucao
        case 4: registarDev(vetorBicicletas, totalBicicletas); break;
        // 5. Listagens
        case 5: listagens(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq); break;
        // 6. Informacoes TODO
        case 6: break;
        // 7. Gravar TODO
        case 7: gravarDadosFich(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq); break;
        }
    } while (op != 0);
	return 0;
}
