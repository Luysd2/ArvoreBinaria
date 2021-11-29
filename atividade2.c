/*2. Faça uma arvore AVL em C, aonde as tenhamos no máximo 5 rotações com os seus elementos.*/
#include<stdio.h> 
#include<stdlib.h> 
int contadorDireito = 0;
int contadorEsquero = 0;  

struct No { 
    int x; //chave
    struct No *esquerda; 
    struct No *direita; 
    int autura; 
}; 
  
int max(int a, int b); 
  
// Uma função de utilidade para obter a altura da árvore
int autura(struct No *N) { 
    if (N == NULL) 
        return 0; 
    return N->autura; 
} 

int max(int a, int b) { 
    return (a > b)? a : b; 
} 
  
struct No* newNode(int key) { 
    struct No* no = (struct No*) 
    malloc(sizeof(struct No)); 
    no->x   = key; 
    no->esquerda   = NULL; 
    no->direita  = NULL; 
    no->autura = 1;  
    return(no); 
} 
// Uma função de utilidade para girar à direita a subárvore enraizada com y
// Veja o diagrama fornecido acima. 
struct No *girardireita(struct No *y) { 
    struct No *x = y->esquerda; 
    struct No *T2 = x->direita; 
  
    x->direita = y; 
    contadorDireito++;
    y->esquerda = T2; 
    contadorDireito++;
  
    y->autura = max(autura(y->esquerda), autura(y->direita))+1; 
    x->autura = max(autura(x->esquerda), autura(x->direita))+1; 
  
    // Retornar nova raiz
    return x; 
} 
  
// Uma função de utilidade para girar para a esquerda a subárvore enraizada com x
// Veja o diagrama fornecido acima
struct No *giraresquerda(struct No *x) { 
    struct No *y = x->direita; 
    struct No *T2 = y->esquerda; 
  
    // Executar rotação
    y->esquerda = x; 
    contadorEsquero++;
    x->direita = T2; 
    contadorEsquero++;
  
  
    x->autura = max(autura(x->esquerda), autura(x->direita))+1; 
    y->autura = max(autura(y->esquerda), autura(y->direita))+1; 
  
    // Retornar nova raiz
    return y; 
} 
  
// Obter fator de equilíbrio do nó N
int getBalance(struct No *N) { 
    if (N == NULL) 
        return 0; 
    return autura(N->esquerda) - autura(N->direita); 
} 
  
// Função recursiva para inserir uma chave na subárvore enraizada
// com nó e retorna a nova raiz da subárvore.
struct No* insert(struct No* no, int x) { 
    
    if (no == NULL) 
        return(newNode(x)); 
  
    if (x < no->x) 
        no->esquerda  = insert(no->esquerda, x); 
    else if (x > no->x) 
        no->direita = insert(no->direita, x); 
    else
        return no; 
  
    /*  Atualizar a altura deste nó ancestral */
    no->autura = 1 + max(autura(no->esquerda), 
                           autura(no->direita)); 
  
    /*  Obtenha o fator de equilíbrio deste ancestral
        nó para verificar se este nó se tornou
        desequilibrado */
    int balance = getBalance(no); 
  
    if (balance > 1 && x < no->esquerda->x) 
        return girardireita(no); 
   
    if (balance < -1 && x > no->direita->x) 
        return giraresquerda(no); 
  
    if (balance > 1 && x > no->esquerda->x) { 
        no->esquerda =  giraresquerda(no->esquerda); 
        return girardireita(no); 
    } 
 
    if (balance < -1 && x < no->direita->x) { 
        no->direita = girardireita(no->direita); 
        return giraresquerda(no); 
    } 
  
    return no; 
} 
  
//Uma função de utilidade para imprimir o percurso da pré-encomenda
// da árvore.
// A função também imprime a altura de cada nó 
void preOrder(struct No *raiz) { 
    if(raiz != NULL) { 
        printf("%d ", raiz->x); 
        preOrder(raiz->esquerda); 
        preOrder(raiz->direita); 
    } 
} 
  

int main() { 
  struct No *raiz = NULL; 
  

    int i;
    for (i = 1; i <= 6; i++){
        raiz = insert(raiz, i); 
    }

  printf("\n Árvore AVL \n\n");  
  preOrder(raiz); 
  printf("\n\n");
  int contadorTotal = contadorEsquero + contadorDireito;
  printf("Essa arvore teve um total de %d 'giros' \n\n", contadorTotal);

  return 0; 
} 