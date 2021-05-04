// Caroline Taus - 31983642
// Nathalia Papst - 31919928
// Rebecca Mello - 31911161

#include <stdio.h>              
#include <stdlib.h>            

// Função que printa os movimentos recursivamente
void hanoi(int n, char origem, char destino, char aux){
  if (n == 1) { // Caso seja o disco 1 (menor)
    printf("\n- Disco 1 é movido do pino %c para o pino %c\n",origem,destino);
  } 

  else { // Caso seja os discos maiores
    hanoi(n-1, origem, aux, destino); // Faz chamada recursiva de modo que o maior nunca vai para a mesma haste que o menor 
    printf("\n- Disco %d é movido do pino %c para o pino %c\n",n,origem,destino);
    hanoi(n-1, aux, destino, origem); //Recursivamente coloca os discos menores em cima dos maiores
  }
}


// Função de memoization que calcula a quantidade de passos
int cont_memo(int n, int * vet_memo) {
  int cont;
  if (vet_memo[n] != -1){  // Se o cálculo já foi feito
    return vet_memo[n];    // Retorna o valor guardado em vet_memo
  }
  if (n < 2) {     // Quando discos = 0 ou 1; qtd de passos = qtd discos
    return n; 
  }
  else if (n == 2) { // Quando discos = 2; passos = 3
    return 3; 
  }
    
  cont = cont_memo(n-1, vet_memo) + 1 + cont_memo(n-1, vet_memo); 
  vet_memo[n] = cont; // Adiciona no vetor
  return cont; // Retorna o contador
}


int main() {
  printf("\nQuantidade de discos: ");
  int numero;
  scanf("%d",&numero);
  int i;
  int vet_memo[numero + 1]; // Vetor que guarda os resultados da memoization

  if (numero == 0) { // Evitar que o programa rode e quebre se o usuário inserir 0
    printf("\nTotal de passos: 0\n");
  }
  else {
    printf("\nMovimentos: \n");
    hanoi(numero,'E', 'C', 'D'); // Hanoi recursivo
  }
  
  // Colocando -1 no vetor
  for (i = 0; i < numero+1; i++){
    vet_memo[i] = -1; 
  }
  
  printf("\n\nPassos: %d \n", cont_memo(numero, vet_memo));
  return 0;
}