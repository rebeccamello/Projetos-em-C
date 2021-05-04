// Equipe: Caroline Taus - 31983642
//       : Nathalia Papst - 31919928
//       : Rebecca Mello - 31911161 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- estrutura nó ---
struct no {
  int freq;
  char c;
  struct no *esq;
  struct no *dir;
  struct no* prox;
};
typedef struct no No;

// --- estrutura lista ---
struct lista {
  struct no* prim;
};
typedef struct lista Lista;


// --- calcula frequência de cada caractere ---
void frequencia(char letras[], int freq[]){
  int c = 0;
  while (letras[c] != 0){ // enquanto houver caractere no vetor 
    if (letras[c] >= 'a' && letras[c] <= 'z') // se for uma letra minuscula
      freq[letras[c] - 'a']++;

    else if(letras[c] >= 'A' && letras[c] <= 'Z') // se for uma letra minuscula
      freq[letras[c] - 'A' + 27]++;

    else if(letras[c] == ' ') // se for um espaço
      freq[26]++;
  c++;
  }
}

// --- inicializa a lista ---
Lista inicializa (No *no){
  Lista l;
  l.prim = no;
  return l;
}


// --- imprime lista ---
void imprime(Lista l){
  No* p; 
  p = l.prim; // cursor apontando pro prim elemento

  while (p != NULL){
    p = p -> prox;
  }
}

// --- cria nó da lista ---
No* cria_no (int f, char c, No* e, No* d, No* p){
  No* no = (No*) malloc(sizeof(No));
  no -> freq = f;     // frequência
  no -> c = c;        // caractere
  no -> esq = e;      // esquerda
  no -> dir = d;      // direita
  no -> prox = p;     // próximo
  return no;
}

// --- insere elementos na lista em ordem de frequência ---
void insere_ordenado (Lista* l, int f, char c, No* e, No* d) {
  No* novo = cria_no(f, c, e, d, NULL); // cria o nó
  No* ant = NULL;                       // cursor que aponta pro elemento anterior
  No* p = l -> prim;                    // cursor que aponta pro primeiro elemento

  // enquanto a frequência for menor vai percorrendo a lista
  while (p != NULL && p->freq < f) {
    ant = p;
    p = p -> prox;
  }
  
  // acha o lugar que deve ser inserido
  if (ant == NULL) { // se for no início da lista
    novo -> prox = l -> prim;
    l -> prim = novo;
  }
  else {            // se for no meio da lista
    novo->prox = ant->prox;
    ant->prox = novo;
  }
}


// --- Retira primeiro elemento ---
Lista* retira (Lista* l) {
  No* p = l -> prim; // ponteiro que pega o primeiro da lista
  l -> prim = p->prox;
  return l;
}


// --- Cria a árvore pro caso de ter apenas um / o mesmo charac ---
void cria_arv1elem(Lista *l) {
  No* cursor = l -> prim;
  int soma = cursor -> freq;
  insere_ordenado (l, soma, '*', cursor, NULL); // insere elem pai
  
  // retira o outro elemento da lista
  No* p = l -> prim -> prox; // ponteiro que pega o segundo da lista
  l -> prim -> prox = NULL;
}


// --- funcao de somar freq de elementos e criar no ---
void cria_arv(Lista *l){
  // pega os dois primeiros nós da lista (menores frequências)
  No* cursor1 = l -> prim;
  No* cursor2 = l -> prim -> prox;
  // faz a soma das frequências
  int soma = cursor1 -> freq + cursor2 -> freq;
  //cria nó intermediário com soma e insere ele na lista
  insere_ordenado (l, soma, '*', cursor1, cursor2);
  // retira folhas da lista  
  retira(l);
  retira(l);
}



// --- Função que codifica cada caractere ---
void codifica(No *no, char vet[53][50], char *c, char caracs[53]){
  
  if (no != NULL){ // Se o nó não é NULL
    if (no -> c != '*') { // Se o nó é uma folha

      for (int letra = 0; letra < 53; letra++){
        if (no -> c == caracs[letra]){ // Se a caractere do nó for igual ao caractere do vetor de caracteres na posição letra
          strcpy(vet[letra], c); // Copia o c para o vetor de binários na posição letra
          break;
        }
      }
    }
    char aux_esq[50];
    strcpy(aux_esq, c); // Copia o c para aux_esq
    codifica(no -> esq, vet, strcat(aux_esq, "0"),caracs); // concatena 0 quando vai pra esq
    codifica(no -> dir, vet, strcat(c, "1"), caracs);   // concatena 1 quando vai pra dir
  }
}

// --- Função de decodificação ---
void decodifica(Lista *l, char *codAlg, int contAlg) {
  No* no = l -> prim;
  int i = 0;	
  while (i <= contAlg) { // percorre todo o vetor do código
     
 	  if (no -> esq == NULL && no -> dir == NULL) { //se for folha
      printf("%c", no -> c); // printa char
      no = l ->prim; // volta pra raiz
    }
      
    if (codAlg[i] == '0'){ // se 0 vai pra esq na árvore
      no = no -> esq; 
      i++;
    }

    else  {  // se 1 vai pra dir na árvore
      no = no -> dir;
      i++;
    }
  }
}

// --- Função que printa o código inteiro ---
void cria_cod_full(char caracs[53], char frase[100], char vet[53][50], char *cod[200]){

  int aux = 0; // variavel de indice do vetor cod
  for(int i = 0; i < 100; i++) {  // passa por todo vetor frase
    for(int j = 0; j < 53; j++) { // passa por todo vetor de caracs
      if(frase[i] == caracs[j]) { // caso o elemento de frase seja igual a um caractere de caracs, copia seu codigo para vetor cod
        cod[aux] = vet[j]; 
        aux++;
      }
    }
  }
  
  printf("\n\n\nCodificação: \n");
  for(int k = 0; k < 53; k++) {
    if (strcmp(cod[k],"-1") != 0) { // caso o caracter for diferente de -1, printa
      printf("%s", cod[k]);
    }
  }
} 

// ---- MAIN ----
int main(void) {
  Lista L = inicializa(NULL);
  char b[50]; // vetor que guarda binário da direita, 
  char vet[53][50];  // vet guarda todos codigos binario
  char *cod[200];  // juntar código binário em ordem
  
  
  int qtdnos = 0; //contador de nós da lista
  char *gets(char *str);
  char caracs[53] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', 'A','B','C','D','E','F','G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y','Z'};

  printf("\nInsira a frase a ser codificada (apenas letras sem acento e espaço):\n\n");
  char frase[100];
  int freq[53];

  // zera os dois vetores
  for (int i = 0; i < 100; i++){
    frase[i] = 0;
  }

  for (int i = 0; i < 53; i++){
    freq[i] = 0;
  }

  // input da frase
  gets(frase);
  int i = 0;
  
  
  // chama funcao de ver frequencia de cada caractere
  frequencia(frase, freq); 

  // insere as folhas na lista 
  for (int k = 0; k < 53; k++){
    if (freq[k] != 0){
      qtdnos++;
      insere_ordenado(&L, freq[k], caracs[k], NULL, NULL);
    }
  }

  if (qtdnos == 1) { // se só tiver um elemento
    cria_arv1elem(&L);
  }
  
  // while roda até que tenha apena um elemento na lista (que será a raiz da árvore)
  while (qtdnos != 1){
    cria_arv(&L); // cria árvore de huffman
    qtdnos--;
  }


  // for que coloca todos os valores do vetor como -1
  for (int i = 0 ; i < 53 ; i++){
    strcpy(vet[i],"-1"); 
  }

  for (int i = 0 ; i < 200 ; i++){
    cod[i] = "-1";
  }

  codifica(L.prim, vet, b, caracs);


  // print de cada folha (caractere) com seu respectivo código binário
  printf("\n --------------------------------------");
  printf("\n\nCódigos:");
  for (int k = 0; k < 53; k++ ){
    if (strcmp(vet[k],"-1") != 0){
      printf("\n%c : %s", caracs[k], vet[k]);
    }
  }  
  
  // código binário inteiro
  cria_cod_full(caracs, frase, vet, cod);

  
  // criação de um vetor com apenas 1 algarismo binário por indice
  int contAlgs = 0;
  for (int i = 0; i < 200; i++) { // percorre cod 
    if (strcmp(cod[i],"-1") != 0){ // ignora -1 em cod
    int len = strlen(cod[i]); 
      for (int j = 0; j < len; j++){
        contAlgs++;
        }
      }
  }

  char codAlg[contAlgs];
  
  int ind_alg = 0;
  for (int i = 0; i < 200; i++) { // percorre cod 
    if (strcmp(cod[i],"-1") != 0){ // ignora -1 em cod
    int len = strlen(cod[i]); 
    
      for (int j = 0; j < len; j++){
        
          codAlg[ind_alg] = cod[i][j];
          ind_alg++;        
          }
      }
  }

  printf("\n\n\nDecodificação: \n");
  decodifica(&L, codAlg,contAlgs);
  
  return 0;
}
