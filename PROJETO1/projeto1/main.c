#include <stdio.h>
#include <stdlib.h>
#include "filadeprioridade.h"
#include "telas.h"
#define MAX_CHAR 3000
#define TAM_MAX 3000
int main(){

    FILE *arquivo;
    char linha[TAM_MAX];
    int numNaves = 8; // (NUMERO DE NAVES NO ARQUIVO)+1
    char *nomeN;
    int prioN;
    H* fila;
    fila= criaFila();

    N *naves[numNaves];
    //ABRIR O ARQUIVO DE LEITURA
    arquivo = fopen("leitura.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    P *pas[numNaves];
    R *rec[numNaves];


    for (int i = 0; i < numNaves; i++) {
        naves[i] = iniciaNave();
        pas[i] = iniciaPassageiro();
        rec[i] = iniciaRecurso();
        // LE O CABECALHO (NOME NAVE,PRIO)
        fgets(linha, sizeof(linha), arquivo);
        if (strcmp(linha, "\n") == 0) break;

        //LE OS DADOS
        fgets(linha, sizeof(linha), arquivo);
        if (strcmp(linha, "\n") == 0) break;
        char *nomeNave = strtok(linha, ",");
        char *prioNave = strtok(NULL, "\n");
        nomeN = strdup(nomeNave);
        prioN = atoi(prioNave);



        //LE O CABECALHO (ID,NOME,IDADE,PLANETA DE ORIGEM)
        fgets(linha, sizeof(linha), arquivo);
        for(int j = 0; j<TAM_MAX;j++){
            //LE OS DADOS
            fgets(linha, sizeof(linha), arquivo);
            if (strcmp(linha, "\n") == 0) break;
            char *token_id = strtok(linha, ",");
            char *token_nome = strtok(NULL, ",");
            char *token_idade = strtok(NULL, ",");
            char *token_planeta = strtok(NULL, "\n");
            insere_passageiro(pas[i],atoi(token_id), token_nome,token_planeta,atoi(token_idade));
        }

        //LE O CABECALHO (RECURSO,QUANTIDADE)
        fgets(linha, sizeof(linha), arquivo);
        for(int j = 0; j<TAM_MAX;j++){
            //LE OS DADOS
            fgets(linha, sizeof(linha), arquivo);
            if (strcmp(linha, "\n") == 0) break;
            char *token_nomeRec = strtok(linha, ",");
            char *token_qtd = strtok(NULL, "\n");
            insere_recurso(rec[i], token_nomeRec,atoi(token_qtd));
        }
        //printf("Nome nave: %s, prio %d",nomeNave,atoi(prioNave));
        insere_na_nave(naves[i], nomeN,prioN,pas[i],rec[i]);
        inserir_Fila(fila,naves[i]);
    }
    fclose(arquivo);
    principal(fila);


    return 0;
}
