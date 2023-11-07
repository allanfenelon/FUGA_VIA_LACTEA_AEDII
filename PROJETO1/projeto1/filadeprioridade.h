typedef struct Passageiro P;
P* iniciaPassageiro();
int insere_passageiro(P *pas,int id, char *nome,char *planeta,int idade);
void imprime_passageiro(P *pas);
int remover_Passageiro(P *pas,int id);

typedef struct Recurso R;
R* iniciaRecurso();
int insere_recurso(R *rec,char *recurso,int qtd);
void imprime_Recurso(R *rec);

typedef struct Nave N;
N* iniciaNave();
int insere_na_nave(N *n, char *nome, int prio,P *pass, R *rec);
void imprime_nave(N *n);

typedef struct FiladePrio H;
H* criaFila();
int verificar_dadosN(N *nave);
void subir(H *fila, int i);
int inserir_Fila(H* fila, N *nave);
void descer(H *fila, int i);
N* remove_Fila(H* fila);
void imprime_fila(H *fila);
void realocarPrio(H *fila,int pos,int aumentarOuSubir);
int doencaABordo(H *fila,int pos);
int clandestino(H *fila, int pos, int id);
