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

    int op, bicicletasDisponiveis, registosDesloc;
    float totalDistanciaPercorrida;

    // Ler dados gravados
    totalBicicletas = lerFichBicicleta(vetorBicicletas);

    // Inicializar contadores e acumuladores
    totalDistanciaPercorrida = 0;
    registosDesloc = 0;
    bicicletasDisponiveis = 0;

    // O programa apenas ser terminado quando o utilizador selecionar a opção 0
    do
    {
        op = menu(totalBicicletas, totalDistanciaPercorrida, registosDesloc, bicicletasDisponiveis);
        switch (op)
        {
        // 1. Nova Bicicleta
        case 1: criarBicicleta(vetorBicicletas, &totalBicicletas);
        break;
        // 2. Registo de Avaria/Disponibilidade TODO
        case 2: registarAvariaDisponibilidade(vetorBicicletas, totalBicicletas);
         break;
        // 3. Registo de Requisição TODO
        case 3: break;
        // 4. Registo de Devolucao TODO
        case 4: break;
        // 5. Listagens TODO
        case 5: break;
        // 6. Informacoes TODO
        case 6: break;
        // 7. Gravar TODO
        case 7: gravarDados(vetorBicicletas, totalBicicletas); break;
        }
    } while (op != 0);
	return 0;
}
