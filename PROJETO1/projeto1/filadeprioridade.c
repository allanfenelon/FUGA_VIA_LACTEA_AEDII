#include <stdio.h>
#include <stdlib.h>
#include "filadeprioridade.h"
#include <time.h>
#define PROBABILITY 10

#define qtdMAX_Passageiro 50
#define qtdMAX_Recursos 100
#define TAMMAX_Nave 300
#define MAX_FILADEPRIORIDADE 300

//ESTRUTURA PASSAGEIRO
typedef struct Passageiro{
    char *nome[qtdMAX_Passageiro]; //VETOR DE NOME DOS PASSAGEIROS
    char *planeta[qtdMAX_Passageiro]; //VETOR DE NOME DE PLANETA DE ORIGEM DE PASSAEIROS
    int idade[qtdMAX_Passageiro]; //VETOR DE IDADE DOS PASSAGEIROS
    int id[qtdMAX_Passageiro]; //IDENTIFICADOR UNICO
    int tam; //QUANTIDADE DE PASSAGEIROS
}P;

P* iniciaPassageiro(){
    P* pas = (P*)malloc(sizeof(P));

    for(int i=0;i<qtdMAX_Passageiro;i++){
        pas->nome[i] = (char*)malloc(qtdMAX_Passageiro*sizeof(char));
        pas->planeta[i] = (char*)malloc(qtdMAX_Passageiro*sizeof(char));
    }
    pas->tam = 0;
    return pas;
}
//ALGORITMO DE INSERÇÃO DE PASSAGEIROS
int insere_passageiro(P *pas,int id, char *nome,char *planeta,int idade){
    if(pas==NULL || pas->tam==qtdMAX_Passageiro){
        return -1;
    }
    pas->nome[pas->tam] = strdup(nome);
    pas->id[pas->tam] = id;
    pas->idade[pas->tam] = idade;
    pas->planeta[pas->tam] = strdup(planeta);
    pas->tam++;
    return 1;

}
//ALGORITMO DE IMPRESSÃO DE PASSAGEIROS
void imprime_passageiro(P *pas){
    if(pas==NULL){
        printf("NAO EXISTE PASSAGEIROS\n");
    }
    if(pas->tam==0){
        printf("NAO HA PASSAGEIROS!\n");
    }
    printf("\nPASSAGEIROS: \n");
    for(int i=0;i<pas->tam;i++){
        printf("\nID: %d, NOME: %s, PLANETA DE ORIGEM: %s, IDADE: %d",pas->id[i],pas->nome[i],pas->planeta[i],pas->idade[i]);
    }
}
//ALGORITMO DE REMOÇÃO DE UM PASSAGEIRO
int remover_Passageiro(P *pas,int id){
    if(pas == NULL || pas->tam==0){
        return -1;
    }
    int i;
    for (i = 0; i < pas->tam; i++) {
        if (pas->id[i] == id) {
            break;
        }else{
            i=-1;
        }
    }
    if(i!=-1){
        for(int j = i;j<pas->tam;i++){
            pas->id[j] = pas->id[j+1];
            pas->idade[j] = pas->idade[j+1];
            pas->nome[j] = pas->nome[j+1];
            pas->planeta[j] = pas->planeta[j+1];
        }
        pas->tam--;
    }
    return 1;
}

//ESTRUTURA RECURSOS
typedef struct Recurso{
    char *nomeR[qtdMAX_Recursos]; //NOME DO RECURSO
    int qtd[qtdMAX_Recursos]; //QUANTIDADE DE ALGUM RECURSO X
    int tam;
}R;

R* iniciaRecurso(){
    R* rec = (R*)malloc(sizeof(R));
    for(int i=0;i<qtdMAX_Recursos;i++){
        rec->nomeR[i] = (char*)malloc(qtdMAX_Recursos*sizeof(char));
    }
    rec->tam=0;
    return rec;
}
//ALGORITMO DE INSERÇÃO DE RECURSOS
int insere_recurso(R *rec,char *recurso,int qtd){
    if(rec==NULL || rec->tam==qtdMAX_Recursos){
        return -1;
    }
    rec->nomeR[rec->tam] = strdup(recurso);
    rec->qtd[rec->tam] = qtd;
    rec->tam++;
    return 1;

}
//ALGORITMO DE IMPRESSÃO DE RECURSOS
void imprime_Recurso(R *rec){
    if(rec==NULL){
        printf("RECURSOS NAO ALOCADO!\n");
    }
    if(rec->tam==0){
        printf("NAO HA RECURSOS PARA IMPRIMIR\n");
    }
    printf("\nRECURSOS: \n");
    for(int i=0;i<rec->tam;i++){
        printf("\nRECURSO: %s, QUANTIDADE: %d\n",rec->nomeR[i],rec->qtd[i]);
    }
}

//ESTRUTURA NAVE
typedef struct Nave{
    int prio;
    char *nome;
    P *passageiros;
    R *recursos;
}N;
N* iniciaNave(){
    N* nave = (N*)malloc(sizeof(N));
    nave->passageiros = iniciaPassageiro();
    nave->recursos = iniciaRecurso();
    return nave;
}
//ALGORITMO DE INSERÇÃO DA NAVE
int insere_na_nave(N *n, char *nome, int prio,P *pass, R *rec){
    if(n==NULL){
        return -1;
    }
    n->passageiros = pass;
    n->recursos = rec;
    n->nome = strdup(nome);
    n->prio = prio;
    return 1;
}
//ALGORITMO DE IMPRIME CERTA NAVE
void imprime_nave(N *n){
    if(n==NULL){
        printf("NAVE NAO ALOCADA!\n");
    }
    printf("NOME: %s, PRIORIDADE: %d",n->nome,n->prio);
    imprime_passageiro(n->passageiros);
    imprime_Recurso(n->recursos);
}
char* get_NomeNave(N *n){
    if(n==NULL){
        return NULL;
    }
    return n->nome;
}

//ESTRUTURA FILA DE PRIORIDADE
typedef struct FiladePrio{
    N *naves[MAX_FILADEPRIORIDADE];
    int tam;
}H;

H* criaFila(){
    H* fila = (H*)malloc(sizeof(H));
    for(int i=0;i<MAX_FILADEPRIORIDADE;i++){
        fila->naves[i] = iniciaNave();
    }
    fila->tam = 0;
    return fila;
}
//ALGORITMO QUE VERIFICA SE A PRIORIDADE DEVE SER REALOCADA
int verificar_dadosN(N *nave){
    int random = rand() % 10; //Gera um número entra 1 e 10
    if (random == 1) { // Se o número gerado for igual a 1 então geraremos outro número
        nave->prio = rand() % 100;
        return 1;
    }

    return 0;
}
//ALGORITMO QUE CORRIGE SUBINDO
void subir(H *fila, int i) {
    int j = i / 2;
    if (j < 1) {
        return; // Chegou à raiz da heap, não há mais subida para fazer.
    }

    if((fila->naves[i]->prio)>(fila->naves[j]->prio)){

        N *tempNave = fila->naves[i];
        fila->naves[i] = fila->naves[j];
        fila->naves[j] = tempNave;
        subir(fila, j);
    }
}
//ALGORITMO DE INSERÇÃO
int inserir_Fila(H* fila, N *nave){
    if(fila==NULL || nave==NULL){ //VERIFICA SE FOI ALOCADO CORRETAMENTE
        return 0;
    }
    if(fila->tam == MAX_FILADEPRIORIDADE){ //VERIFICA SE ATINGIU O LIMITE MÁXIMO DA FILA
        return 0;
    }
    int tam = fila->tam;
    verificar_dadosN(nave);
    if(fila->tam==0){ //FAZEMOS ISSO PQ NOSSA FILA DE PRIO VAI COMERÇAR NO INDICE i=1
        fila->naves[tam] = NULL;
        fila->tam++;
        tam++;
    }
    fila->naves[tam] = nave; //O TAMANHO SERVE COMO INDICE PARA A INSERÇÃO
    fila->tam++;
    subir(fila,tam);

    return 1;
}

//ALGORITMO QUE CORRIGE DESCENDO
void descer(H *fila,int i){
    int j = 2*i;
    if(j<=(fila->tam)){
        if(j<fila->tam){
            if(fila->naves[j+1]->prio>fila->naves[j]->prio){
                j++;
            }
            if(fila->naves[i]->prio<fila->naves[j]->prio){
                N *tempNave = fila->naves[i];
                fila->naves[i] = fila->naves[j];
                fila->naves[j] = tempNave;
                descer(fila,j);
            }
        }
    }
}


//ALGORITMO DE REMOÇÃO (MAIOR PRIORIDADE)
N* remove_Fila(H* fila){
    if(fila==NULL || fila->tam == 0){
        return NULL;
    }
    N *aux = fila->naves[1];
    fila->naves[1] = fila->naves[fila->tam-1];
    fila->tam--;
    descer(fila, 1);

    return aux;
}
//ALGORITMO DE IMPRIMIR FILA DE PRIORIDADE
void imprime_fila(H *fila){
    if(fila==NULL){
        printf("FILA NÃO ALOCADA!\n");
    }
    if(fila->tam==0){
        printf("FILA VAZIA!\n");
    }
    for(int i=1;i<fila->tam;i++){
        printf("\nNAVE: %s, PRIORIDADE: %d\n", fila->naves[i]->nome, fila->naves[i]->prio);
    }

}
//ALGORITMO DE REALOCAÇÃO DE PRIORIDADE
void realocarPrio(H *fila,int pos,int aumentarOuSubir){
    int prio = fila->naves[pos]->prio;
    int newPrio = 0;
    if(aumentarOuSubir){
        newPrio = rand() % 100; //PROB DE TER A PRIORIDADE MAIOR (DOENCA A BORDO)
    }else{
        newPrio = rand() % 10; //PROB DE TER A PRIORIDADE MENOR (CLANDESTINO)
    }

    fila->naves[pos]->prio = newPrio;
    if(prio<newPrio){
        subir(fila,pos);
    }else if(prio>newPrio){
        descer(fila,pos);
    }
}
//ALGORITMO DE NOTIFICAÇÃO DE SURGIENTO DE DOENCA EM UMA NAVE
int doencaABordo(H *fila,int pos){
    if(pos>fila->tam){
        return -1;
    }
    if(pos==1){
        return -1;//POIS NAO PRECISA PQ ESTA COM PRIO MAXIMA JA
    }
    realocarPrio(fila,pos,1);
    return 1;
}
//ALGORITMO DE NOTIFICACAO DE PESSOA CLANDESTINA NA NAVE
int clandestino(H *fila, int pos, int id){
    if(fila == NULL || fila->tam==0){
        return -1;
    }
    remover_Passageiro(fila->naves[pos],id);
    realocarPrio(fila,pos,0);
    return 1;
}
char* get_primeiraNaveNome(H *fila){
     if(fila == NULL || fila->tam==0){
        return NULL;
    }
    return get_NomeNave(fila->naves[1]);
}

