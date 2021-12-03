#include <stdlib.h>
#include <stdio.h>

#include "funcoesAuxiliares.h"
#include "funcoesMenu.h"
#include "datas.h"
#include "bicicletas.h"
#include "registos.h"
#include "csv.h"

int main(void)
{
    // Vetores e contadores de elementos
    tipoBicicleta vetorBicicletas[MAX_BICICLETAS];
    int totalBicicletas;

    tipoRegReq vetorRegReq[MAX_REGISTOS];
    int totalRegReq;

    int op, bicicletasDisponiveis, carregarDados, gravarDados, controlo;
    float totalDistanciaPercorrida;

    // Se o utilizador quiser, carregar os dados já armazenados em ficheiros
    carregarDados = escolhaSimOuNao("\nPretende carregar os dados guardados em ficheiro?");
    if (carregarDados)
    {
        lerDadosFich(vetorBicicletas, &totalBicicletas, vetorRegReq, &totalRegReq);
    }
    else
    {
        totalBicicletas = totalRegReq = 0;
    }

    // O programa apenas ser terminado quando o utilizador selecionar a opção 0
    do
    {
        bicicletasDisponiveis = contarBicicletasDisponiveis(vetorBicicletas, totalBicicletas);
        totalDistanciaPercorrida = contarDistPercorrida(vetorBicicletas, totalBicicletas);
        op = menu(totalBicicletas, totalDistanciaPercorrida, totalRegReq, bicicletasDisponiveis);
        switch (op)
        {
        // 1. Nova Bicicleta
        case 1:
            controlo = criarBicicleta(vetorBicicletas, &totalBicicletas);
            // Se o estado da ultima bicicleta inserida for requisitada, pedir ao utilizador para efetuar um registo de requisicao
            if (controlo == 1 && vetorBicicletas[totalBicicletas - 1].estado == ESTADO_REQ)
            {
                printf("\nEfetue o registo de requisicao da bicicleta adicionada.\n");
                do
                {
                    controlo = criarReq(vetorRegReq, &totalRegReq, vetorBicicletas[totalBicicletas - 1]);
                } while (controlo != 1);
                printf("\nRegisto de requisicao efetuado com sucesso.\n");
            }
            break;
        // 2. Registo de Avaria/Disponibilidade
        case 2: registarAvariaDisponibilidade(vetorBicicletas, totalBicicletas);
            break;
        // 3. Registo de Requisição
        case 3: registarReq(vetorBicicletas, totalBicicletas, vetorRegReq, &totalRegReq); break;
        // 4. Registo de Devolucao
        case 4: registarDev(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq); break;
        // 5. Listagens
        case 5: listagens(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq); break;
        // 6. Informacoes
        case 6: informacoes(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq); break;
        // 7. Gravar
        case 7: gravarDadosFich(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq); break;
        // 8. Exportar para CSV
        case 8:
            gravarBicicletasCSV(vetorBicicletas, totalBicicletas);
            gravarRequisicoesCSV(vetorRegReq, totalRegReq);
            break;
        case 0:
            gravarDados = escolhaSimOuNao("\nPretende gravar os dados antes de sair? (Todos os dados nao gravados serao perdidos)");
            if (gravarDados)
            {
                gravarDadosFich(vetorBicicletas, totalBicicletas, vetorRegReq, totalRegReq);
            }
            break;
        }
    } while (op != 0);

	return 0;
}
