/*1. Faça uma arvore binária em C completa, aonde todos os nós Pai estão cheios.*/
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
struct item{
    int codigo;
};
typedef struct item Item; // como se fosse um apelido para o item

struct no{ 
    Item item;
    struct no *esquerda;
    struct no *direita;  
};
typedef struct no No; // apelido para o no
No *inicializar(){
    return 0;
}
    Item itemCreate(int codigo){
        Item item;
        item.codigo = codigo;
        return item;
    }

No *inserir(No *raiz, Item x){
    if(raiz == NULL){
        No *aux = (No *)malloc(sizeof(No));
        aux-> item = x;
        aux-> esquerda = NULL;
        aux-> direita = NULL;
        //esquerda e direita esta iniciando nula pq é a primira posissão(raiz)
        return aux;
    }else{
        if(x.codigo > raiz->item.codigo){
            raiz -> direita = inserir(raiz->direita,x);
        }else if (x.codigo < raiz->item.codigo){
            raiz -> esquerda = inserir(raiz->esquerda,x);
        } 
    }
    return raiz;
}
//aqui q faz a inversão da arvore
/*
void inverso(No *inv){
    if (inv != NULL){
        No *aux;
        inverso(inv->esquerda);
        inverso(inv->direita);
        
        aux = inv->esquerda;
        inv->esquerda = inv->direita;
        inv->direita = aux;
    }else
        return;
}
//
*/
// esse faz a ordenação Pré-Ordem 
void redprint(No*raiz){ 
    if(raiz != NULL){
        printf("%d ", raiz->item.codigo);
        redprint(raiz->esquerda);
        redprint(raiz->direita);
    }
}
//aqui eu to liberando a memoria, quando eu executar novamente esse codigo
//o msm espeço usado anteriormente sera usado d novo
void liberar(No*raiz){
    if(raiz != NULL){
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

int main(){
    
    No *raiz = NULL;
    srand(time(NULL));
    int i;
    for (i = 0; i < 15; i++){
        int x = (rand() % 100);
        raiz = inserir(raiz, itemCreate(x));
    }
    
    printf("Arvore \n");
    redprint(raiz);
    printf("\n ");

    liberar(raiz);
    return 0;
}