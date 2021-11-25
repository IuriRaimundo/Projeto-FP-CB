#ifndef DATAS_H_INCLUDED
#define DATAS_H_INCLUDED

// Ano minimo e ano máximo para a função validar data
#define ANO_MIN 1900
#define ANO_MAX 2200

typedef struct {
	int dia, mes, ano;
} tipoData;

typedef struct {
    int hora;
    int minuto;
} tipoHora;

tipoData lerData(void);
int validarData(tipoData data);

#endif // DATAS_H_INCLUDED
