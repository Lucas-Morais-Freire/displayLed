#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(unsigned char** m) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printbyte(unsigned char c){
  unsigned char i;
  unsigned char and;
  for(i = 128; i > 0; i = i >> 1){
    and = i & c;
    if(and){
      printf("1");
    }
    else{
      printf("0");
    }
  }
}

int main() {

    unsigned char** m; //crio o ponteiro para a matriz
    m = (unsigned char**)malloc(8*sizeof(unsigned char*)); //aloco memoria para o bloco auxiliar
    m[0] = (unsigned char*)malloc(8*8*sizeof(unsigned char)); //aloco memoria para os valores
    for (int i = 1; i < 8; i++) { //guardo os endereços no bloco auxiliar.
        m[i] = m[i - 1] + 8;
    }

    srand(time(NULL)); // crio uma seed aleatoria para preencher a matriz com zeros e uns

    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            m[i][j] = rand() % 2; //preencho a matriz com os valores aleatorios
        }
    }

    printMatrix(m); // imprimo a matriz

    unsigned long long int state = 0; // declaro a variavel state, que guardara a matriz em uma sequencia de bits
    unsigned char* p; //crio um ponteiro de 1 byte de tamanho
    p = &state; //atribuo o endereço de state para ele.

    for (i = 7; i >= 0; i--) {// agora, escrevo os valores da matriz nos bits de "state"
        unsigned long long int temp = 0; //inicializo uma variavel temporaria para guardar os valores de cada linha da matriz como sendo um inteiro de 8 bytes

        for (j = 7; j >= 0; j--) {
            temp += ((unsigned long long)(m[i][j])) << 7 - j; //leio cada elemento da linha atual da matriz da direita para a direita, e vou somando à "res", deslocando os bits pela quantidade necessaria para ir escrevendo-os na posicao correspondente ao que se tinha na matriz.
        }

        state += temp << 8*(7 - i); //escrevo os bits de temp em state, deslocando-os pela quantidade necessaria para alinhar a sequencia.
    }

    free(m[0]); //libero a mamemoria dos valores
    free(m); //libero a memoria do bloco auxiliar

    printf("|");
    for (i = 7; i >= 0; i--) { //imprimo cada byte da variavel state por meio de seu ponteiro.
        printbyte(p[i]);
        printf("|");
    }

    return 0;
}