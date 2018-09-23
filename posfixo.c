#include <stdio.h>
#include "pilha.c"
#include "pilhaI.c"
#include "lista.c"

int verificarPrioridade(char c) {
    switch(c) {
        case VAZIO:
            return VAZIO;
        case '(':
            return 3;
        case ')':
            return 4;
        case '*':
            return 2;
        case '/':
            return 2;
        case '+':
            return 1;
        case '-':
            return 1;
        case ' ':
            return -1;
        default:
            return 0;
    }
}

lista* paraPosfixo() {
    char buffer[1000000];
    int i, operador, prioridade, valido = 1;
    lista* expressao = criarLista();
    pilhaC* operadores = criarPilha();
    
    scanf("%[^\n]", buffer);

    
    for(i = 0; buffer[i] != '\0' && valido; i++) {
        operador = buffer[i];
        prioridade = verificarPrioridade(operador);
        

        /* prioridade 0 -> operando
         * prioridade -1 -> espaco
           so pode haver 1 espaco consecutivo */
        if( (prioridade == -1 && expressao->fim->dado != ' ') || prioridade == 0) {
            adicionarFinal(expressao, operador);
        }
        
        else if(prioridade == -1) {
            printf("pnc\n");
        }
        
        /* Se encontrar fechamento do parenteses, desempilhar ate achar a abertura */
        else if(prioridade == 4) {
            adicionarFinal(expressao, ' ');
            operador = desempilharC(operadores);
            prioridade = verificarPrioridade(operador);
            
            while(prioridade != 3 && operador != VAZIO) {
                adicionarFinal(expressao, operador);
                operador = desempilharC(operadores);
                prioridade = verificarPrioridade(operador);
            }
            /* Caso o ultimo operador nao tenha sido parenteses a expressao e invalida */
            if(prioridade != 3) {
                printf("buceta");
                valido = 0;
            }
        }
        /* Se operador encontrado > operador do topo, empilhar */
        else if(!pilhaVaziaC(operadores) && prioridade > verificarPrioridade(lerTopoC(operadores)) ) {
            empilharC(operadores, operador);
        }
        
        /* Se operador encontrado <= operador do topo, desempilhar */
        else {
            while(!pilhaVaziaC(operadores) && prioridade <= verificarPrioridade(lerTopoC(operadores)) && verificarPrioridade(lerTopoC(operadores)) != 3 ) {
                adicionarFinal(expressao, desempilharC(operadores));
            }
            empilharC(operadores, operador);
        }
    }
    
    while(!pilhaVaziaC(operadores)) {
        adicionarFinal(expressao, ' ');
        adicionarFinal(expressao, desempilharC(operadores));
    }
    
    if(valido) {
        return expressao;
    }
    return;
}

lista *avaliarPosfixo(lista* expressao) {
    elemento = expressao->inicio;
    while(elemento != NULL) {
        
    }   
}

int main() {
    lista* l = paraPosfixo();
    if(l!= NULL) {
        printLista(l);
    }

    return 0;
}