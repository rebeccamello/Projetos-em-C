// Autoras: Caroline Taus - 31983642
// Rebecca Mello - 31911161
// Nathalia Papst - 31919928

#include <stdio.h>
#define tam 20

// DECLARANDO FUNCOES
void printmatriz(char m[tam][tam]);
int pop(char m[tam][tam]);
int viz(char m[tam][tam],int i,int j);
void tencell(char m[tam][tam]);
void glider(char m[tam][tam]);
void exploder(char m[tam][tam]);
void smallexp(char m[tam][tam]);
void tumbler(char m[tam][tam]);
void clear(char m[tam][tam]);
void cat(char m[tam][tam]);
void XKCD(char m[tam][tam]);
void lightweight(char m[tam][tam]); 

//MAIN
int main(void) {
  char matriz[tam][tam];  //criação da matriz
  int opc = 1;
  int vetmorre[2000];     //criacao de um vetor para guardar o local dos que vao "morrer"
  int vetnasc[2000];      //criacao de um vetor para guardar o local dos que vao "nascer"
   
  //Inicialização da matriz
  for(int i = 0; i <= tam; i++){
    for(int j = 0; j <= tam; j++){
      matriz[i][j] = ' ';
    }
  }
  printmatriz(matriz);

  while(opc != 0){

    printf(" _________________________________");
    printf("\n                                   ");
    printf("\n|               MENU              |");
    printf("\n|  0 - Encerrar programa          |");
    printf("\n|  1 - Colocar uma celula         |");
    printf("\n|  2 - Remover uma celula         |");
    printf("\n|  3 - Rodar                      |");
    printf("\n|  4 - Escolher um modelo         |");
    printf("\n|  5 - Remover todas as células   |");
    
    printf("\n __________________________________");
    printf("\n\nQual opcao deseja? ");
    scanf("%d", &opc);

    //  valida a opcao
    while (opc > 5 || opc < 0){
      printf("Opcao invalida! Digite novamente: ");
      scanf("%d", &opc);
    }

    //  ----------   opcoes do menu ----------

    //  OPC ENCERRAR
    if (opc == 0){
      printf("\nPrograma encerrado!\n\nBye bye! ^______^\n");
      break;
    }

    //  OPC INSERIR
    else if (opc == 1){
      int l, c;
      printf("\nQual linha deseja inserir? ");
      scanf("%d", &l);
      printf("\nQual coluna deseja inserir? ");
      scanf("%d", &c);

      matriz[l][c] = 'x';        //coloca a celula de acordo com as informacoes digitadas
    }

    //  OPC REMOVER
    else if(opc == 2){
      int l, c;
      printf("\nDe qual linha deseja remover? ");
      scanf("%d", &l);
      printf("\nDe qual coluna deseja remover? ");
      scanf("%d", &c);

      matriz[l][c] = ' ';
    }

    //  OPC RODAR
    else if (opc == 3){
      int quant, quant2, cont = 0, cont2 = 0, linha, coluna;
      for (int i = 0; i < tam; i++){
        for (int j = 0; j < tam ; j++){

          //caso encontre uma celula
          if (matriz[i][j] == 'x'){
            quant = viz(matriz, i, j);  //ve quantos vizinhos tem          

            if (quant != 2 && quant != 3){   //casos para celula morrer
              linha = i;                     //guarda a linha
              coluna = j;                    //guarda a coluna
              vetmorre[cont] = linha;        //insere no vetor
              vetmorre[cont + 1] = coluna;
              cont = cont + 2;               //vai de dois em dois ja que a cada um que morre, sao dois numeros inseridos no vetor (sua linha e coluna)
            }
            printf("\n");
          }

          //caso esteja um espaco vazio
          else{
            quant2 = viz(matriz,i,j);        //ve quantos vizinhos tem 
            if (quant2 == 3){                
              linha = i;                     //guarda a linha
              coluna = j;                    //guarda a coluna
              vetnasc[cont2] = linha;        //insere no vetor
              vetnasc[cont2 + 1] = coluna;
              cont2 = cont2 + 2;
            } 
          }
        }
      }
      for (int i = 0; i < cont; i = i + 2){       //passa pelo vetor inteiro, matando as celulas de acordo com sua linha e coluna. Indices pares sao as linhas e os impares sao as colunas
        matriz[vetmorre[i]][vetmorre[i+1]] = ' '; 

      }
      for (int i = 0; i < cont2; i = i + 2){
        matriz[vetnasc[i]][vetnasc[i+1]] = 'x'; //nasce
      }
    }

    //MODELOS
    else if (opc == 4){ 
      int mod;
      printf("\n==========================");
      printf("\n    Modelos possíveis:");
      printf("\n\n    1 - Exploder");
      printf("\n    2 - 10 cell row");
      printf("\n    3 - Glider"); 
      printf("\n    4 - Small Exploder");
      printf("\n    5 - Tumbler");
      printf("\n    6 - Lightweight Spaceship ");
      printf("\n    7 - XKCD (Rip John Conway)");
      printf("\n    8 - Cat");
      printf("\n\n==========================");
      printf("\n\nQual modelo gostaria de testar? ");
      scanf("%d", &mod);

      if (mod == 1){
        clear(matriz);
        exploder(matriz);
      }

      else if (mod == 2){
        clear(matriz);
        tencell(matriz);
      }

      else if (mod == 3){
        clear(matriz);
        glider(matriz);
      }

      else if(mod == 4){
        clear(matriz);
        smallexp(matriz);
      }

      else if(mod == 5){
        clear(matriz);
        tumbler(matriz);
      }

      else if(mod == 6){
        clear(matriz);
        lightweight(matriz);
      }

      else if(mod == 7){
        clear(matriz);
        XKCD(matriz);
      }

      else if(mod == 8){
        clear(matriz);
        cat(matriz);
      }
    }
    
    else if(opc == 5){
      clear(matriz); 
    }

    printmatriz(matriz);
  }
    return 0;
}


// FUNÇÃO PRA PRINTAR MATRIZ   
void printmatriz(char m[tam][tam]){
  int i,j;
  printf("\n\t\t\t\t\t\t\t\t\t\tMatriz:\n\n");
  printf("      0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19\n");
  for(int i = 0; i < tam; i++){
    if(i <10){printf("%d   |",i);}
    else {printf("%d  |",i);}

    for(int j = 0; j < tam; j++){
      printf(" %c ", m[i][j]);
      printf("|");
    }
    printf("\n");
  }
  printf("\n");
}

// VERIFICAR VIZINHOS
int viz(char m[tam][tam],int i,int j){
  int cont = 0;
  
      if (m[i][j - 1] == 'x'){ // viz esq
        cont++;}
      if (m[i][j + 1] == 'x'){ // viz dir
        cont++;}
      if (m[i - 1][j] == 'x'){ // viz cima
        cont++;}
      if (m[i + 1][j] == 'x'){ // viz baixo
        cont++;}
      if (m[i-1][j-1] == 'x'){ // viz esq cima
        cont++;}
      if (m[i-1][j+1] == 'x'){ // viz dir cima
        cont++;}
      if (m[i+1][j-1] == 'x'){ // viz esq baixo
        cont++;}
      if (m[i+1][j+1] == 'x'){ // viz dir baixo
        cont++;}
  return cont;
}


// FUNÇÃO PARA LIMPAR A MATRIZ
void clear(char m[tam][tam]){
  for (int i = 0; i < tam; i++){
    for (int j = 0; j < tam; j++){
      if (m[i][j] == 'x'){
        m[i][j] = ' ';
      }
    }
  }
}



// FUNÇÕES DOS MODELOS

// 10 CELL ROW
void tencell(char m[tam][tam]){
  m[9][5] = 'x';   
  m[9][6] = 'x';    
  m[9][7] = 'x';
  m[9][8] = 'x';
  m[9][9] = 'x';
  m[9][10] = 'x';
  m[9][11] = 'x';
  m[9][12] = 'x';
  m[9][13] = 'x';
  m[9][14] = 'x';
}

// GLIDER
void glider(char m[tam][tam]){
  m[8][9] = 'x';
  m[9][10] = 'x';
  m[10][8] = 'x';
  m[10][9] = 'x';
  m[10][10] = 'x';
}

//EXPLODER 
void exploder(char m[tam][tam]){
  m[6][6] = 'x';
  m[6][8] = 'x';
  m[6][10] = 'x';
  m[7][6] = 'x';
  m[7][10] = 'x';
  m[8][6] = 'x';
  m[8][10] = 'x';
  m[9][6] = 'x';
  m[9][10] = 'x';
  m[10][6] = 'x';
  m[10][8] = 'x';
  m[10][10] = 'x';
}

// SMALL EXPLODER  
void smallexp(char m[tam][tam]){
  m[7][9] = 'x';
  m[8][8] = 'x';
  m[8][9] = 'x';
  m[8][10] = 'x';
  m[9][8] = 'x';
  m[9][10] = 'x';
  m[10][9] = 'x';
}

// TUMBLER 
void tumbler(char m[tam][tam]){
  m[7][7] = 'x';
  m[7][8] = 'x';
  m[7][10] = 'x';
  m[7][11] = 'x';
  m[8][7] = 'x';
  m[8][8] = 'x';
  m[8][10] = 'x';
  m[8][11] = 'x';
  m[9][8] = 'x';
  m[9][10] = 'x';
  m[10][6] = 'x';
  m[10][8] = 'x';
  m[10][10] = 'x';
  m[10][12] = 'x';
  m[11][6] = 'x';
  m[11][8] = 'x';
  m[11][10] = 'x';
  m[11][12] = 'x';
  m[12][6] = 'x';
  m[12][7] = 'x';
  m[12][11] = 'x';
  m[12][12] = 'x';

}
// GATINHO
void cat(char m[tam][tam]){
  m[3][7] = 'x';
  m[3][11] = 'x';
  m[5][6] = 'x';
  m[5][8] = 'x';
  m[5][9] = 'x';
  m[5][10] = 'x';
  m[5][12] = 'x';
  m[6][6] = 'x';
  m[6][12] = 'x';
  m[7][8] = 'x';
  m[7][10] = 'x';
  m[9][5] = 'x';
  m[9][6] = 'x';
  m[9][7] = 'x';
  m[9][9] = 'x';
  m[9][11] = 'x';
  m[9][12] = 'x';
  m[9][13]  = 'x';
  m[10][5] = 'x';
  m[10][6] = 'x';
  m[10][7] = 'x';
  m[10][11] = 'x';
  m[10][12] = 'x';
  m[10][13]  = 'x';

}

void XKCD(char m[tam][tam]){
  m[4][8] = 'x';
  m[4][9] = 'x';
  m[4][10] = 'x';
  m[5][8] = 'x';
  m[5][10] = 'x';
  m[6][8] = 'x';
  m[6][10] = 'x';
  m[7][9] = 'x';
  m[8][6] = 'x';
  m[8][8] = 'x';
  m[8][9] = 'x';
  m[8][10] = 'x';
  m[9][7] = 'x';
  m[9][9] = 'x';
  m[9][11] = 'x';
  m[10][9] = 'x';
  m[10][12] = 'x';
  m[11][8] = 'x';
  m[11][10] = 'x';
  m[12][8] = 'x';
  m[12][10] = 'x';
}

void lightweight(char m[tam][tam]){
  m[8][8] = 'x';
  m[8][9] = 'x';
  m[8][10] = 'x';
  m[8][11] = 'x';
  m[9][7] = 'x';
  m[9][11] = 'x';
  m[10][11] = 'x';
  m[11][7] = 'x';
  m[11][10] = 'x';
}

