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


PONT buscaChave(PERSONAL_INFO infoProc, PONT inic){
    if (inic == NULL) return NULL;
    if (strcmp(inic->info.nome, infoProc.nome) == 0 
        && strcmp(inic->info.sobrenome, infoProc.sobrenome) == 0
        && strcmp(inic->info.data_nascimento, infoProc.data_nascimento) == 0
    ) return inic;
    
    PONT p = inic->mae;
    while(p) {
        PONT resp = buscaChave(infoProc, p);
        if (resp) return(resp);
        p = p->proxIrmao;
    }
    
    p = inic->pai;
    while(p) {
        PONT resp = buscaChave(infoProc, p);
        if (resp) return(resp);
        p = p->proxIrmao;
    }
    
    return(NULL);
}

bool insereIrmao(PONT inic, PERSONAL_INFO infoIrmao, PERSONAL_INFO infoPessoa){
    PONT pessoa = buscaChave(infoPessoa, inic);
    if (!pessoa) return(false);
    
    PONT irmao = criaNovoNo(infoIrmao);
    irmao->pai = pessoa->pai;
    irmao->mae = pessoa->mae;

    PONT p = pessoa;    
    while (p->proxIrmao)
        p = p->proxIrmao;
    p->proxIrmao = irmao;
    
    return(true);
}

bool inserePai(PONT inic, PERSONAL_INFO infoPai, PERSONAL_INFO infoFilho){
    PONT filho = buscaChave(infoFilho, inic);
    if (!filho) return(false);
    
    PONT pai = criaNovoNo(infoPai);
    PONT p = filho->proxIrmao;
    
    
    if (!p) pessoa->proxIrmao = irmao;
    else {
        while (p->proxIrmao)
            p = p->proxIrmao;
        p->proxIrmao = irmao;
    }
    
     return(true);
}

// void exibirArvore(PONT raiz){
//     if (raiz == NULL) return;
    
//     printf("%d(",raiz->chave);
//     PONT p = raiz->primFilho;
//     while (p) {
//         exibirArvore(p);
//         p = p->proxIrmao;
//     }
    
//     printf(")");
// }

// int main(){
//     PONT raiz = inicializa(54);

//     insere(raiz, 67, 54);
//     insere(raiz, 68, 54);
//     insere(raiz, 53, 68);
//     insere(raiz, 52, 67);
//     insere(raiz, 2, 52);
//     insere(raiz, 3, 52);


//     exibirArvore(raiz);
// }