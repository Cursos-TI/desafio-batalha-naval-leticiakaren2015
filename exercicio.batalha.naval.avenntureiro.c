#include  <stdio.h>


#define TAM_TABULEIRO 10    // tamanho fixo do tabuleiro 
#define TAM_NAVIO 3         // tamanhos fixos dos navio
#define NAVIO 3             // valor usados para representar navios no tabuleiro

// Função para verificar se um navio pode ser colocado em determinada posição
int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direção, int diagonal) {
    // direção: 0 = horizontal, 1 = vertical
    // diagonal: 0 = não, = ↘︎, 2 = ↙︎

    for ( int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        
        if (diagonal == 0) {
            //horizontal ou vertical
            if ( direção == 0) c +=i;   // horizontal
            else l += i;                // vertical
        
        } else if (diagonal == 1) {
            // ↘︎ diagonal
            l += i;
            c += i;
        } else if (diagonal == 2) {
            // ↙︎ diagonal
            l += i;
            c -= i;
        }

        // Vertical limites do tabuleiro
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) return 0;
        // Verificar sobreposição
        if (tabuleiro [l][c] == NAVIO) return 0;  
    }
    return 1;
}

//  Função para posicionar o navio no tabuleiro
void posicionarNavio (int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direção, int diagonal) {
    for ( int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if ( diagonal == 0) {
            if (direção == 0) c += i;
            else l += i;
        } else if (diagonal == 1) {
            l += i;
            c += i;
        } else if (diagonal == 2) {
            l += i;
            c -= i;
        }

        tabuleiro [l][c] = NAVIO; // marca navio
    }
}

int main () {

    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    
    //1. Inicializar tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Definir coordenadas dos 4 navios
    // Navio horizontal (linha 2, coluna 4)
    if(podePosicionar(tabuleiro, 2, 4, 0, 0)) {
        posicionarNavio(tabuleiro, 2, 4, 0, 0);
    }

    // Navio vertical (linha 5, coluna 7)
    if(podePosicionar(tabuleiro, 5, 7, 1, 0)) {
        posicionarNavio(tabuleiro, 5, 7, 1, 0);
    }

    // Navio na diagonal ↘︎ (linha 0, coluna 0)
    if(podePosicionar(tabuleiro, 0, 0, 0, 1)) {
        posicionarNavio(tabuleiro, 0, 0, 0, 1);
    }

    // Navio diagonal ↙︎ (linha 0, coluna 9)
    if(podePosicionar(tabuleiro, 0, 9, 0, 2)) {
        posicionarNavio(tabuleiro, 0, 9, 0, 2);
    }

    // Exibir tabuleiro
    printf("=== Tabuleiro Batalha Naval (Aventureiro)===\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d" , tabuleiro[i][j]);
        }
        printf("\n");
    }
    return 0;
}
