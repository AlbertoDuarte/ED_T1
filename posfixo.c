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

char* charParaString(char c) {
    char* buffer = (char*) malloc(sizeof(char)*2);
    buffer[0] = c;
    buffer[1] = '\0';
    return buffer;
}

lista* paraPosfixo() {
    char bufferexpressao[1000000], *buffern; /* buffer da expressao */
    int i, valido = 1, digitosbuffer = 0, qt_op = 0;
    char operador, prioridade, tmp;
    lista* expressao = criarLista();
    pilhaC* operadores = criarPilhaC();
    
    scanf("%[^\n]", bufferexpressao);
    
    /* verifica invalidez por falta de operandos no inicio */
    prioridade = verificarPrioridade(bufferexpressao[0]);
    if(prioridade == 1 || prioridade == 2) {
        valido = 0;
    }
    
    for(i = 0; bufferexpressao[i] != '\0' && valido; i++) {
        operador = bufferexpressao[i];
        prioridade = verificarPrioridade(operador);
        

        /* prioridade 0 -> operando
         * prioridade -1 -> espaco
           so pode haver 1 espaco consecutivo */
        if(prioridade == 0) {
            if(digitosbuffer == 0) {
                buffern = (char*) malloc(sizeof(char)*1000); /* buffer de numero */
            }
            buffern [digitosbuffer] = operador;
            digitosbuffer++;
            qt_op = 0;
        }
        
        else if(prioridade != -1) {
            if(prioridade == 1 || prioridade == 2) {
                qt_op++;
            }
            /* 2 ou mais operadores consecutivos != de parenteses invalida a expressao */
            if(qt_op >= 2) {
                valido = 0;
            }
            
            /* caso haja numero com mais de um digito, transforma para inteiro e coloca na lista de expressao infixa */
            if(digitosbuffer > 0) {
                buffern[digitosbuffer] = '\0';
                adicionarFinal(expressao, buffern);
                digitosbuffer = 0;
                printf("adicionando %s a lista expressao\n", buffern);
            }
            
            /* Se encontrar fechamento do parenteses, desempilhar ate achar a abertura */
            if(prioridade == 4) {
                operador = desempilharC(operadores);
                prioridade = verificarPrioridade(operador);
                
                while(prioridade != 3 && operador != VAZIO) {
                    printf("adicionando %c a expressao\n", operador);
                    adicionarFinal(expressao, charParaString(operador));
                    operador = desempilharC(operadores);
                    prioridade = verificarPrioridade(operador);
                }
                /* Caso o ultimo operador nao tenha sido parenteses a expressao e invalida */
                if(prioridade != 3) {
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
                    tmp = desempilharC(operadores);
                    printf("adicionando %c a expressao\n", tmp);
                    adicionarFinal(expressao, charParaString(tmp));
                }
                empilharC(operadores, operador);
            }
        }
    }
    /* verifica invalidez por falta de operandos no final */
    prioridade = verificarPrioridade(bufferexpressao[i-1]);
    if(prioridade == 1 || prioridade == 2) {
        valido = 0;
    }
    
    /* caso ainda haja numero com mais de um digito, transforma para inteiro e coloca na lista de expressao infixa */
    if(digitosbuffer > 0) {
        buffern[digitosbuffer] = '\0';
        adicionarFinal(expressao, buffern);
        printf("adicionando %s a lista expressao\n", buffern);
    }
    /* desempilha o resto dos operadores */
    while(!pilhaVaziaC(operadores) && valido) {
        tmp = desempilharC(operadores);
        if(tmp == '(') {
            valido = 0;
        }
        else {
            printf("adicionando operador %c a expressao\n", tmp);
            adicionarFinal(expressao, charParaString(tmp));
        }
    }
    
    freePilhaC(operadores); // liberar pilha de operadores da memoria
    
    if(!valido) {
        printf("Expressao invalida!!!\n");
        freeLista(expressao);
        expressao = NULL; /* TODO: dar free na expressao */
    }
    return expressao;
}


int main() {
    lista* l = paraPosfixo();
    if(l!= NULL) {
        freeLista(l);
        printLista(l);
    }

    return 0;
}