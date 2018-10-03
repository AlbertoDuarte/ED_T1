#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
    char* dado;
    struct elemento* proximo;
}elemento;

typedef struct lista {
    elemento* inicio;
    elemento* fim;
}lista;

void printLista(lista* l) {
    elemento* tmp = l->inicio;
    while(tmp != NULL) {
        printf("%s", tmp->dado);
        tmp = tmp->proximo;
    }
    printf("\n");
}

lista* criarLista() {
    lista* l = (lista*)malloc(sizeof(lista));
    l->inicio = NULL;
    l->fim = NULL;
    
    return l;
}

int adicionarInicio(lista* l, char* n) {
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    novo->dado = n;
    novo->proximo = l->inicio;
    l->inicio = novo;
    if(l->fim == NULL) {
        l->fim = novo;
    }
    
    return 0;
}

int adicionarFinal(lista* l, char* n) {
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    novo->dado = n;
    novo->proximo = NULL;
    
    if(l->inicio == NULL) {
        l->inicio = novo;
    }
    
    else {
        l->fim->proximo = novo;
    }
    
    l->fim = novo;
    return 0;
}

int adicionar(lista* l, char* n, int pos) {
    int i;
    
    if(pos < 0) {
        return 1;
    }
    
    if(pos == 0) {
        adicionarInicio(l, n);
        return 0;
    }
    
    elemento* atual = l->inicio;
    if(atual == NULL) {
        printf("Posicao nao existe!\n");
        return 2;
    }
    
    for(i = 1; i < pos; i++) {
        if(atual->proximo == NULL) {
            printf("Posicao nao existe!\n");
            return 2;
        }
        atual = atual->proximo;
    }
    
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    novo->dado = n;
    
    novo->proximo = atual->proximo;
    atual->proximo = novo;
    if(novo->proximo == NULL) {
        l->fim = novo;
    }
    
    
    return 0;
}

int trocarValor(lista* l, char* n, int pos) {
    int i;
    
    if(pos < 0) {
        return 1;
    }
    
    elemento* atual = l->inicio;
    if(atual == NULL) {
        printf("Posicao nao existe!\n");
        return 2;
    }
    
    for(i = 0; i < pos; i++) {
        if(atual->proximo == NULL) {
            printf("Posicao nao existe!\n");
            return 2;
        }
        atual = atual->proximo;
    }
    
    atual->dado = n;
    
    
    return 0;
}    


int removerInicio(lista* l) {
    elemento* primeiro = l->inicio;
    l->inicio = l->inicio->proximo;
    free(primeiro);
    
    if(l->inicio == NULL) {
        l->fim = NULL;
    }
    
    return 0;
}

int removerFim(lista *l) {
    elemento* atual = l->inicio;
    elemento* anterior = NULL;
    
    while(atual->proximo != NULL) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    l->fim = anterior;
    l->fim->proximo = NULL;
    free(atual);
    
    return 0;
}

void freeLista(lista* l) {
    if(l->inicio != NULL) {
        elemento* atual = l->inicio;
        elemento* proximo = atual->proximo;
        while(proximo!=NULL) {
            free(atual->dado);
            free(atual);
            atual = proximo;
            proximo = atual->proximo;
        }
        free(atual->dado);
        free(atual);
        }
    free(l);
}