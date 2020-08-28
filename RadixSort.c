// RADIX SORT
//AUTORAS: 
// Caroline Taus - 31983642
// Nathalia Papst - 31919928
// Rebecca Mello - 31911161

#include <stdio.h>
#include <stdlib.h>


// ------ IMPRIME VETOR ------
void printVetor(int vet[], int tam) 
{  
  printf("  [  ");
	for (int i = 0; i < tam; i++) 
		printf("%d  ", vet[i]); 
	printf("]"); 
  
} 

// ------ MAIOR NÚMERO ------
int maior(int vet[], int tam){
  // achando o maior número do vetor
  int maior = 0, cont = 0;
  for(int i = 0; i < tam; i++){
    if (vet[i] > maior) {
      maior = vet[i];
    }
  }
  // verificando quantos algarismos o maior número tem
  while (maior > 0){
    maior /= 10;
    cont++;
  }

  return cont;
}


// ------ RADIX ------
void radix(int vet[], int tam){
  int maior_n; // guarda num de casas decimais do maior alg
  int alg_atual = 1;  // controla a casa decimal atual
  
  //pega o número de algarismos do maior valor do vetor
  maior_n = maior(vet, tam);

  // for deve rodar o número de vezes = número de casas decimais do maior algarismo
  int aux, t,tmp;
  for (int i = 0; i < maior_n; i++){

    // estrutura do insertion sort
    for (int k = 1; k < tam; k++){
      t = k;
      
      // comparando somente as casas decimais "atuais"
      while (t > 0 && ((vet[t - 1]/alg_atual) % 10) > ((vet[t]/alg_atual) % 10)) {
        tmp = vet[t];
        vet[t] = vet[t - 1];   
        vet[t-1] = tmp;   
        t--; 
      } 
    }

    // muda a casa decimal atual
    alg_atual = alg_atual * 10; 

    // printado cada passo
    printf("\nPasso %d:        ",(i+1));
    printVetor(vet, tam);
  }
}


int main() { 

  int tam, num;
  printf("\nInsira a quantidade de numeros: ");
  scanf("%d", &tam);
  int *vet = (int *) malloc(tam * sizeof(int)); //criação do vet com o tamanho escolhido pelo usuário

  for (int i = 0; i < tam; i++){
    printf("\nInsira o numero %d: ", i + 1);
    scanf("%d", &num);
    vet[i] = num;
  }  

  printf("\n\nVetor original: ");
  printVetor(vet, tam);
  printf("\n");
  radix(vet, tam);
  printf("\n\nVetor final:    ");
  printVetor(vet, tam);
  
  return 0; 
}

