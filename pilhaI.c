#include <stdio.h>
#include <stdlib.h>

//TODO: Fazer exercicio dos slides de letras e numeros A1B2C3D4E = A4B3C2D1E
//TODO: implementar fila com pilhas

#define VAZIO -1

typedef struct elementoP {
    struct elementoP* proximo;
    int dado;
}elementoP;

typedef struct pilhaI {
    elementoP* topo;
}pilhaI;

pilhaI* criarPilha() {
    pilhaI* p = (pilhaI*)malloc(sizeof(pilhaI ));
    p->topo = NULL;
    return p;
}

void empilharI(pilhaI * p, int n) {
    elementoP* novo = (elementoP*)malloc(sizeof(elementoP));
    
    novo->dado = n;
    novo->proximo = p->topo;
    p->topo = novo;
}    

int lerTopoI(pilhaI * p) {
    if(p->topo == NULL) {
        return VAZIO;
    } else {
        return p->topo->dado;
    }
}

int desempilharI(pilhaI * p) {
    int tmp_dado;
    elementoP* tmp;
    
    if(p->topo == NULL) {
        printf("Pilha n possui valores\n");
        return VAZIO;
    }
    
    tmp = p->topo;
    p->topo = p->topo->proximo;
    tmp_dado = tmp->dado;
    free(tmp);
    
    return tmp_dado;
}

int pilhaVaziaI(pilhaI * p) {
    if(p->topo == NULL) {
        return 1;
    }
    return 0;
}