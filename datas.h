#ifndef DATAS_H_INCLUDED
#define DATAS_H_INCLUDED

// Ano minimo e ano máximo para a função validar data
#define ANO_MIN 1900
#define ANO_MAX 2200
// Formatos de data e hora
#define FORMATO_DATA "DD/MM/AAAA"
#define FORMATO_HORA "HH:MM"
// Strings
#define CARATERES_HORA 6
#define CARATERES_DATA 11

typedef struct {
	int dia, mes, ano;
} tipoData;

typedef struct {
    int hora;
    int minuto;
} tipoHora;

tipoData lerData(void);
int validarData(tipoData data);
tipoHora lerHora(void);
int validarHora(tipoHora hora);
int compararDatas(tipoData d1, tipoData d2);
void dataParaString(char str[], tipoData data, char separador);
void horaParaString(char str[], tipoHora hora);

#endif // DATAS_H_INCLUDED
