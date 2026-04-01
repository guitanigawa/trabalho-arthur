#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char nome[50];
    char sobrenome[50];
    char data_nascimento[20];
} PERSONAL_INFO;

typedef struct no {
    PERSONAL_INFO info;
    struct no *mae;
    struct no *pai;

    struct no *proxIrmao;
} NO;

typedef NO* PONT;

PONT criaNovoNo(PERSONAL_INFO info){
    PONT novo = (PONT)malloc(sizeof(NO));
    
    novo->info = info;
    novo->mae = NULL;
    novo->pai = NULL;

    novo->proxIrmao = NULL;

    return(novo);
}

PONT inicializa(PERSONAL_INFO info) {
    return(criaNovoNo(info));
}


PONT buscaChave(char nome[50], PONT eu){
    if (eu == NULL) return NULL;
    if (eu->info.nome == nome) return eu;
    
    PONT p = eu->mae;
    while(p) {
        PONT resp = buscaChave(nome, p);
        if (resp) return(resp);
        p = p->proxIrmao;
    }
    
    p = eu->pai;
    while(p) {
        PONT resp = buscaChave(nome, p);
        if (resp) return(resp);
        p = p->proxIrmao;
    }
    
    return(NULL);
}

bool insere(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai){
    PONT pai = buscaChave(chavePai,raiz);
    if (!pai) return(false);
    
    PONT filho = criaNovoNo(novaChave);
    PONT p = pai->primFilho;
    
    if (!p) pai->primFilho = filho;
    else {
        while (p->proxIrmao)
        p = p->proxIrmao;
        p->proxIrmao = filho;
    }
    
     return(true);
}

void exibirArvore(PONT raiz){
    if (raiz == NULL) return;
    
    printf("%d(",raiz->chave);
    PONT p = raiz->primFilho;
    while (p) {
        exibirArvore(p);
        p = p->proxIrmao;
    }
    
    printf(")");
}

int main(){
    PONT raiz = inicializa(54);

    insere(raiz, 67, 54);
    insere(raiz, 68, 54);
    insere(raiz, 53, 68);
    insere(raiz, 52, 67);
    insere(raiz, 2, 52);
    insere(raiz, 3, 52);


    exibirArvore(raiz);
}