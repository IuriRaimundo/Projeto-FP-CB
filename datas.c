#include <ctype.h>
#include <string.h>

#include "datas.h"
#include "funcoesAuxiliares.h"

// Esta função lê a partir do teclado uma data e devolve uma estrutura tipoData
tipoData lerData(void)
{
    tipoData data;
    char entrada[12];
    char aux[5];
    int valoresData[3] = {0}, i, contAux, contValoresData;
    do
    {
        lerString(entrada, 12);
        // Percorrer vetor entrada para adicionar os valores dia, mes e ano ao vetor valoresData
        for (i = 0, contAux = 0, contValoresData = 0; i < 12; i++)
        {
            // Se entrada[i] for digito, adicionar ao vetor aux e incrementar contador de carateres no vetor aux
            // Caso entrada[i] seja o último carater antes do \0, converter aux para inteiro e guardar no vetor valoresData
            // Se não for digito, converter aux para inteiro e guardar no vetor valoresData e reiniciar contador dos carateres aux
            if (entrada[i] != '\0' && isdigit(entrada[i]))
            {
                // Se contAux for 4 ou superior vai ultrapassar o tamanho do vetor aux
                if (contAux < 4)
                {
                    aux[contAux] = entrada[i];
                    contAux++;
                }
                else
                {
                    i = 11;
                }
            }
            // Se contValoresData for 3 ou superior vai ultrapassar o tamanho do vetor valoresData
            else if (contValoresData < 3)
            {
                aux[contAux] = '\0';
                valoresData[contValoresData] = atoi(aux);
                contAux = 0;
                contValoresData++;
            }
            else
            {
                i = 11;
            }
        }
        data.dia = valoresData[0];
        data.mes = valoresData[1];
        data.ano = valoresData[2];
        if (!validarData(data))
        {
            printf("\n\tData invalida, tente novamente: ");
        }
    } while (!validarData(data));
    return data;
}

// Esta função recebe uma estrutura tipoData e verifica a sua validade, retorna 1 se válido e 0 se inválido.
int validarData(tipoData data)
{
    int dataValida, d, m, a;
    dataValida = 1;
    d = data.dia;
    m = data.mes;
    a = data.ano;
    // Validar ano
    if (a > ANO_MIN && a < ANO_MAX)
    {
        // Validar Mês
        if (m > 0 && m < 13)
        {
            // Validar dias
            // Verificar dias para meses com 31 dias
            if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && (d < 1 || d > 31))
            {
                dataValida = 0;
            }
            else
            {
                // Verificar dias de fevereiro
                if (m == 2)
                {
                    // Se o dia for 29 e o ano não for bisexto, a data é invalida
                    if (d == 29 && !(a % 400 == 0 || (a % 4 == 0 && a % 100 != 0)))
                    {
                        dataValida = 0;
                    }
                    else
                    {
                        if (d < 1 || d > 28)
                        {
                            dataValida = 0;
                        }
                    }
                }
                else
                {
                    if (d < 1 || d > 30)
                    {
                        dataValida = 0;
                    }
                }
            }
        }
        else
        {
            dataValida = 0;
        }
    }
    else
    {
        dataValida = 0;
    }

    return dataValida;
}

// Lê e devolve uma estrutura tipoHora
tipoHora lerHora(void)
{
    tipoHora hora;
    // Vetores para guardar a entrada do utilizador e guardar digitos para serem convertidos posteriormente
    char entrada[6]; char aux[3] = {'\0'};
    // Vetor para guardar valores convertidos
    int valoresHora[2] = {-1, -1}; // Incializado com -1 porque 0:0 seria é uma hora válida
    // Contadores
    int i, n, contAux, contValoresHora;
    do
    {

        // Ler 5 carateres do utilizador para ler uma hora do formato HH:MM
        lerString(entrada, 6);
        n = strlen(entrada);
        contAux = 0;
        contValoresHora = 0;

        // Percorrer vetor de carateres entrada
        for (i = 0; i <= n; i++)
        {
            // Se o carater for digito e não for \0 deve ir para o vetor aux
            if (isdigit(entrada[i]) && entrada[i] != '\0')
            {
                // Se o contAux não seja menor que 2, a introdução não foi correta e o vetor aux chegou ao limite
                if (contAux < 2)
                {
                    aux[contAux] = entrada[i];
                    contAux++;
                }
            }
            else if (entrada[i] == '\0' || entrada[i] == ':')
            {
                aux[contAux] = '\0'; // Terminar a string
                valoresHora[contValoresHora] = atoi(aux); // Converter o vetor Aux para numero inteiro e guardar no valoresData
                contValoresHora++;
                contAux = 0; // Para substituir os valores do auxiliar nas seguintes iterações
            }
        }

        // Guardar os valores na estrutura
        hora.hora = valoresHora[0];
        hora.minuto = valoresHora[1];

        if (!validarHora(hora))
        {
            printf("\n\tHora invalida, insere novamente (HH:MM): ");
        }
    } while (!validarHora(hora));

    return hora;
}

// Recebe uma estrutura do tipoHora e verifica se é válida
// Devolve 1 se válida, 0 se não.
int validarHora(tipoHora hora)
{
    int valido = 1;
    if (hora.hora > 23 || hora.hora < 0 || hora.minuto < 0 || hora.minuto > 59)
    {
        valido = 0;
    }
    return valido;
}
