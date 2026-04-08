// Participantes: Fabrício Cardoso, Guilherme Tanigawa

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
    struct no *antIrmao;
} NO;

typedef NO* PONT;



PONT criaNovoNo(PERSONAL_INFO info){
    PONT novo = (PONT)malloc(sizeof(NO));
    
    novo->info = info;
    novo->mae = NULL;
    novo->pai = NULL;

    novo->proxIrmao = NULL;
    novo->antIrmao = NULL;

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

    PONT resp = buscaChave(infoProc, inic->proxIrmao);
    if (resp) return resp;
    
    resp = buscaChave(infoProc, inic->mae);
    if (resp) return resp;
    
    resp = buscaChave(infoProc, inic->pai);
    if (resp) return resp;
    
    return NULL;
    
    return(NULL);
}

bool insereIrmao(PONT inic, PERSONAL_INFO infoIrmao, PERSONAL_INFO infoPessoa){
    PONT pessoa = buscaChave(infoPessoa, inic);
    if (!pessoa) return(false);
    
    PONT irmao = criaNovoNo(infoIrmao);
    // Achei que fosse fazer mais sentido dessa forma (irmãos sempre tem os mesmos pais)
    irmao->pai = pessoa->pai;
    irmao->mae = pessoa->mae;



    PONT p = pessoa; 
    while(p->proxIrmao)
        p = p->proxIrmao;
    
    p->proxIrmao = irmao;
    irmao->antIrmao = p;
    return(true);
}

bool inserePai(PONT inic, PERSONAL_INFO infoPai, PERSONAL_INFO infoFilho){
    PONT filho = buscaChave(infoFilho, inic);
    if (!filho) return(false);
    
    if(filho->pai) return(false);
    PONT pai = criaNovoNo(infoPai);
    filho->pai = pai;
    
    PONT p = filho->proxIrmao;
    while(p){
        if((p->pai != filho->pai)) p->pai = filho->pai;

        p = p->proxIrmao;
    }

    p = filho->antIrmao;
    while(p){
        if((p->pai != filho->pai)) p->pai = filho->pai;

        p = p->antIrmao;
    }

    return(true);
}

bool insereMae(PONT inic, PERSONAL_INFO infoMae, PERSONAL_INFO infoFilho){
    PONT filho = buscaChave(infoFilho, inic);
    if (!filho) return(false);

    if(filho->mae) return(false);
    PONT mae = criaNovoNo(infoMae);
    filho->mae = mae;
    
    PONT p = filho->proxIrmao;
    while(p){
        if((p->mae != filho->mae)) p->mae = filho->mae;

        p = p->proxIrmao;
    }

    p = filho->antIrmao;
    while(p){
        if((p->mae != filho->mae)) p->mae = filho->mae;

        p = p->antIrmao;
    }

    return(true);
}

void imprimirTodosIrmaos(PONT pessoa) {
    if (!pessoa) return;
    
    PONT primeiro = pessoa;
    while(primeiro->antIrmao) {
        primeiro = primeiro->antIrmao;
    }
    
    PONT irmao = primeiro;
    int count = 0;
    while(irmao) {
        count++;
        irmao = irmao->proxIrmao;
    }
    
    if (count <= 1) {
        printf("Nenhum\n");
        return;
    }
    
    irmao = primeiro;
    while(irmao) {
        if (irmao != pessoa) {
            printf("%s %s", irmao->info.nome, irmao->info.sobrenome);
            if (irmao->proxIrmao) printf(", ");
        }
        irmao = irmao->proxIrmao;
    }
    printf("\n");
}

void exibirArvore(PONT inic) {
    if (inic == NULL) return;
    
    PONT p = inic;
    while(p) {
        printf("------------------------\n");
        printf("Nome: %s %s\n", p->info.nome, p->info.sobrenome);
        printf("Nascimento: %s\n", p->info.data_nascimento);
        
        printf("Irmaos: ");
        imprimirTodosIrmaos(p);
        
        if(p->mae) 
            printf("Mae: %s %s\n", p->mae->info.nome, p->mae->info.sobrenome);
        if(p->pai) 
            printf("Pai: %s %s\n", p->pai->info.nome, p->pai->info.sobrenome);
        
        printf("------------------------\n");
        p = p->proxIrmao;
    }
    
    exibirArvore(inic->mae);
    exibirArvore(inic->pai);
}
int main() {
    // Criando eu
    PERSONAL_INFO eu = {"Guilherme", "Silva", "26/06/2007"};
    PONT arvore = inicializa(eu);
    
    // Inserindo pais
    PERSONAL_INFO pai = {"Paulo", "Silva", "17/09/1980"};
    PERSONAL_INFO mae = {"Selma", "Tanigawa", "20/04/1982"};
    
    inserePai(arvore, pai, eu);
    insereMae(arvore, mae, eu);

    // Inserindo irmãos do pai
    PERSONAL_INFO irmaoPai1 = {"Giberto", "Silva", "17/09/1977"};
    PERSONAL_INFO irmaoPai2 = {"André", "Silva", "17/09/1975"};
    PERSONAL_INFO irmaoPai3 = {"Roberto", "Silva", "17/09/1970"};
    PERSONAL_INFO irmaoPai4 = {"Aparecido", "Silva", "17/09/1960"};

    insereIrmao(arvore, irmaoPai1, pai);
    insereIrmao(arvore, irmaoPai2, pai);
    insereIrmao(arvore, irmaoPai3, pai);
    insereIrmao(arvore, irmaoPai4, pai);

    // Inserindo irmãos da mãe
    PERSONAL_INFO irmaoMae1 = {"Eduardo", "Tanigawa", "20/04/1977"};
    PERSONAL_INFO irmaoMae2 = {"Cristina", "Tanigawa", "20/04/1976"};

    insereIrmao(arvore, irmaoMae1, mae);
    insereIrmao(arvore, irmaoMae2, mae);

    // Inserindo avós
    PERSONAL_INFO avoPai1 = {"Ilda", "Colombo", "17/09/1945"};
    PERSONAL_INFO avoPai2 = {"Sebastião", "Silva", "17/09/1943"};
    
    inserePai(arvore, avoPai2, pai);
    insereMae(arvore, avoPai1, pai);
    
    PERSONAL_INFO avoMae1 = {"Tamaki", "Tanigawa", "20/04/1960"};
    PERSONAL_INFO avoMae2 = {"Antonio", "Tanigawa", "20/04/1970"};

    inserePai(arvore, avoMae2, mae);
    insereMae(arvore, avoMae1, mae);    

    // Exibindo a árvore completa
    exibirArvore(arvore);
    
    return 0;
}