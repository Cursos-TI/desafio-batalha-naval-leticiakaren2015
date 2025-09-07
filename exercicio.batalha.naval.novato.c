#include <stdio.h>

#define TAM_TABULEIRO 10  //  tamanho tabuleiro 
#define TAM_NAVIO 3 //. tamanho do navio

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];  // matrix 10x10 representando o tamanho do tabuleiro

    // 1. Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro [i][j] = 0;
        }
    }


    // 2. Coordenadas iniciadas para os navios
    //   Navio na horizontal começa na lina 2, coluna 4
    int linhaH = 2, colunaH = 4;
    //   Navio vertical começa na linha 5, coluna 7
    int linhaV = 5, colunaV = 7;


    // 3. Posição navio na horizontal. (representado pelo número 3)
    for (int i = 0; i < TAM_NAVIO; i++){
        tabuleiro[linhaH][colunaH + i] = 3;
    }


    // 4. Posição navio na vertical. (também representado pelo 3)
    for(int i = 0; i < TAM_NAVIO; i++){
        tabuleiro[linhaV][colunaV] = 3;
    }


    // 5. Exibir o tabuleiro no console
    printf("=== Tabuleiro Batalha Naval ===\n\n");
    for(int i= 0; i < TAM_TABULEIRO; i++){
        for(int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d", tabuleiro[i][j]);  // imprimir o valor da posição
        }
        printf("\n");  // quebra de linha no final de cada linha da matrix
    }

    return 0;
}