
#include <stdio.h>
#include <stdlib.h>
#include "filadeprioridade.h"

void limpar_tela(){
    system("cls");
}
void tela_inicial(){
    printf("\nADMINISTRACAO DE PASSAGEM\n");
    printf("(1) - IMPRIMIR FILA\n");
    printf("(2) - PASSAR NAVE NA PASSAGEM\n");
    printf("(3) - NOTIFICAR DOENCA A BORDO\n");
    printf("(4) - NOTIFICAR CLANDESTINO\n");
    printf("(5) - INSERIR NAVE INDIVIDUALMENTE\n");
    printf("(6) - SAIR\n");
}

void tela_setNaveIndividualmente(H *fila) {
    char nomeNave[100];
    int prioridade;
    int auxQtd = 5; //FIXAMOS A QUANTIDADE DE 5 PASSAGEIROS E 5 RECURSOS PARA O TESTE DESTA INSERCAO
    char nome[100];
    char planeta[100];
    int id, idade, qtdRec;
    N *nave;
    nave = iniciaNave();
    P *pass;
    pass = iniciaPassageiro();
    R *rec;
    rec = iniciaRecurso();

    printf("DIGITE O NOME DA NAVE E A PRIORIDADE DELA: \n");

    if (fgets(nomeNave, sizeof(nomeNave), stdin) == NULL) {
        printf("Erro ao ler o nome da nave.\n");
        return;
    }
    nomeNave[strcspn(nomeNave, "\n")] = '\0';  // Remove o caractere de nova linha.

    scanf("%d", &prioridade);

    if (auxQtd > 1) {
        for (int i = 0; i < auxQtd; i++) {
            printf("DIGITE O NOME DO PASSAGEIRO, IDADE, PLANETA DE ORIGEM E O SEU IDENTIFICADOR UNICO: \n");
            if (scanf("%s %d %s %d", nome, &idade, planeta, &id) != 4) {
                printf("Erro ao ler os dados do passageiro.\n");
                break; // Encerrar a entrada se ocorrer um erro
            }
            insere_passageiro(pass, id, nome, planeta, idade);
        }
    }

    if (auxQtd > 1) {
        for (int i = 0; i < auxQtd; i++) {
            printf("DIGITE O NOME DO RECURSO E A QUANTIDADE: \n");
            if (scanf("%s %d", nome, &qtdRec) != 2) {
                printf("Erro ao ler os dados do recurso.\n");
                break; // Encerrar a entrada se ocorrer um erro
            }
            insere_recurso(rec, nome, qtdRec);
        }
    }
    insere_na_nave(nave, nomeNave, prioridade, pass, rec);
    inserir_Fila(fila, nave);
}

void principal(H *fila){
    int ativo = 1;
    int leituraOP;
    int leituraCase,leituraCase2;
    int auxWhile;
    while(ativo){
        tela_inicial();
        printf("DIGITE UMA OPCAO: ");
        scanf("%d",&leituraOP);
        switch(leituraOP){
            case 1:
                limpar_tela();
                imprime_fila(fila);
                break;
            case 2:
                limpar_tela();
                char *auxNome;
                if(get_primeiraNaveNome(fila)!=NULL){
                    printf("%s PASSOU PELA PASSAGEM!", get_primeiraNaveNome(fila));
                }else{
                    printf("FILA VAZIA!");
                }
                remove_Fila(fila);
                break;
            case 3:
                limpar_tela();
                imprime_fila(fila);
                auxWhile = 1;
                while(auxWhile){
                    printf("EM QUAL POSICAO A NAVE COM DOENCA ESTA? \n");
                    scanf("%d",&leituraCase);
                    if(doencaABordo(fila,leituraCase)!=-1){
                       printf("DOENCA NOTIFICADA!");
                       auxWhile = 0;
                    }
                    limpar_tela();
                    printf("OPERACAO INVALIDA!");
                }
                break;
            case 4:
                limpar_tela();
                imprime_fila(fila);
                auxWhile = 1;
                while(auxWhile){
                    printf("EM QUAL POSICAO A NAVE COM CLANDESTINO ESTA? \n");
                    scanf("%d",&leituraCase);
                    printf("DIGITE O ID DO CLANDESTINO PARA REMOCAO DA NAVE:\n");
                    scanf("%d",&leituraCase2);
                    if(clandestino(fila,leituraCase,leituraCase2)!=-1){
                        printf("REMOCAO DE CLANDESTINO FEITA E A RELOCACAO DE PRIORIDADE! \n");
                    }
                    limpar_tela();
                    printf("OPERACAO INVALIDA!");
                }
                break;
            case 5:
                tela_setNaveIndividualmente(fila);
                break;
            case 6:
                printf("SAINDO...\n");
                ativo = 0;
                break;
            default:
                printf("OPCAO INVALIDA!");
                break;
        }
    }
}
