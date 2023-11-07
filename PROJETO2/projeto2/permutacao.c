
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filadeprioridade.h"
#include "telas.h"
#include "permutacao.h"
// ALGORITMO QUE RETORNA A POSICAO DA PROXIMA EXPANCAO DA PASSAGEM
int verifica_ProximaExpansao(H *fila) {
    int qtdNaves = get_TamFila(fila);
    int proximaExpansao = -1;

    // COMBINACOES PREDEFINIDAS
    char *combinacoes[6][4] = {
        {"agua", "remedios", "alimentos"},
        {"agua", "alimentos", "remedios"},
        {"remedios", "agua", "alimentos"},
        {"remedios", "alimentos", "agua"},
        {"alimentos", "remedios", "agua"},
        {"alimentos", "agua", "remedios"}
    };
    //VERIFICACAO
    for (int i = 1; i <= qtdNaves; i++) {
        for (int j = 0; j < 6; j++) {
            if (verifica_ExistenciaRec(fila, i, combinacoes[j])) {
                proximaExpansao = i;
            }
        }

        if(proximaExpansao != -1) {

            break;
        }
    }

    return proximaExpansao;
}

void retorna_NomeNaveExpancao(H *fila){
    int proximaExpansao = verifica_ProximaExpansao(fila);
    printf("\n+-------------------------------------------------------------------------------------------+");
    printf("\nQUANDO A NAVE: %s PASSAR A PASSAGEM IRA SE EXPANDIR!\n", get_NomeNave(get_navedaFila(fila,proximaExpansao)));
    printf("A POSICAO DE %s NO HEAP E: %d",get_NomeNave(get_navedaFila(fila,proximaExpansao)),proximaExpansao);
    printf("\n+-------------------------------------------------------------------------------------------+");
}

