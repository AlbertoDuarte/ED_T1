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

lista* paraPosfixo(char* bufferexpressao) {
    char *buffern; /* buffer da expressao */
    int i, valido = 1, digitosbuffer = 0, qt_op = 0;
    char operador, prioridade, tmp;
    lista* expressao = criarLista(); /* custo 4 */
    pilhaC* operadores = criarPilhaC(); /* custo 3  */
    
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
            /* 2 ou mais operadores consecutivos diferente de parenteses invalida a expressao */
            if(qt_op >= 2) {
                valido = 0;
            }
            
            /* caso haja numero com mais de um digito, transforma para inteiro e coloca na lista de expressao infixa */
            if(digitosbuffer > 0) {
                buffern[digitosbuffer] = '\0';
                adicionarFinal(expressao, buffern);
                digitosbuffer = 0;
            }
            
            /* Se encontrar fechamento do parenteses, desempilhar ate achar a abertura */
            if(prioridade == 4) {
                operador = desempilharC(operadores);
                prioridade = verificarPrioridade(operador);
                
                while(prioridade != 3 && operador != VAZIO) {
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
    }
    /* desempilha o resto dos operadores */
    while(!pilhaVaziaC(operadores) && valido) {
        tmp = desempilharC(operadores);
        if(tmp == '(') {
            valido = 0;
        }
        else {
            adicionarFinal(expressao, charParaString(tmp));
        }
    }
    
    freePilhaC(operadores); // liberar pilha de operadores da memoria
    if(!valido) {
        printf("Expressao invalida!\n");
        freeLista(expressao);
        expressao = NULL;
    }
    return expressao;
}

int avaliarPosfixo(lista* expressao) {
    int valor, valor2;
    pilhaI* operandos = criarPilhaI();
    elemento* atual = expressao->inicio;
    
    while(atual != NULL) {
        /* caso o elemento atual seja um operador */
        if(verificarPrioridade((atual->dado)[0]) >= 1) {
            valor = desempilharI(operandos);
            valor2 = desempilharI(operandos);
            if((atual->dado)[0] == '+') { 
                empilharI(operandos, valor2+valor);
            }
            else if((atual->dado)[0] == '-') { 
                empilharI(operandos, valor2-valor);
            }
            else if((atual->dado)[0] == '*') { 
                empilharI(operandos, valor2*valor);
            }
            else if((atual->dado)[0] == '/') { 
                empilharI(operandos, valor2/valor);
            }
            
            else {
                empilharI(operandos, -999999);
            }
        }
        /* caso o elemento atual seja uma string representando um número */
        else {
            valor = atoi(atual->dado); // converte para int
            empilharI(operandos, valor);
        }
        atual = atual->proximo;
    }
    valor = desempilharI(operandos);
    freePilhaI(operandos);
    return valor;
}


int main() {
    /* recebe expressao infixa do usuario */
    int valor;
    char bufferexpressao[1000000];
    scanf("%[^\n]", bufferexpressao);
    
    lista* l = paraPosfixo(bufferexpressao);
    if(l!= NULL) {
        printf("Expressao posfixa = ");
        printLista(l);
        valor = avaliarPosfixo(l);
        printf("valor da expressao = %d\n", valor);
        freeLista(l);
    }

    return 0;
}