#include <stdio.h>

#define TAM_TABULEIRO 10    // tamanho fixo do tabuleiro 
#define TAM_NAVIO 3         // tamanhos fixos dos navios
#define NAVIO 3             // valor usado para representar navios no tabuleiro
#define HABILIDADE 5        // valor usado para representar área de habilidade

// Função para verificar se um navio pode ser colocado em determinada posição
int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direção, int diagonal) {
    // direção: 0 = horizontal, 1 = vertical
    // diagonal: 0 = não, 1 = ↘︎, 2 = ↙︎

    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (diagonal == 0) {
            // horizontal ou vertical
            if (direção == 0) c += i;   // horizontal
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

        // Verificar limites do tabuleiro
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO) return 0;
        // Verificar sobreposição
        if (tabuleiro[l][c] == NAVIO) return 0;  
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int direção, int diagonal) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (diagonal == 0) {
            if (direção == 0) c += i;
            else l += i;
        } else if (diagonal == 1) {
            l += i;
            c += i;
        } else if (diagonal == 2) {
            l += i;
            c -= i;
        }

        tabuleiro[l][c] = NAVIO; // marca navio
    }
}

// ========== Funções de habilidade ==========

// Constrói a matriz da habilidade em cone (ponta em cima, expandindo para baixo)
void construirCone(int n, int cone[n][n]) {
    int centro = n / 2;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            cone[r][c] = 0;

    for (int r = 0; r <= centro; r++) {
        for (int c = 0; c < n; c++) {
            if ((c >= centro - r) && (c <= centro + r))
                cone[r][c] = 1;
        }
    }
}

// Constrói a matriz da habilidade em cruz (linha e colunas centrais)
void construirCruz(int n, int cruz[n][n]) {
    int centro = n / 2;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            cruz[r][c] = 0;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == centro || c == centro)
                cruz[r][c] = 1;
        }
    }
}

// Constrói a matriz da habilidade em octaedro
void construirOctaedro(int n, int oct[n][n]) {
    int centro = n / 2;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            oct[r][c] = 0;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int deltaLinha = (r - centro >= 0) ? (r - centro) : -(r - centro);
            int deltaColuna = (c - centro >= 0) ? (c - centro) : -(c - centro);
            if (deltaLinha + deltaColuna <= centro)
                oct[r][c] = 1;
        }
    }
}

// Aplicar uma habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                        int habilidade[][7], int tamanho,
                        int origemLinha, int origemColuna, int pontaOrigem) {
    int centro = tamanho / 2;

    for (int r = 0; r < tamanho; r++) {
        for (int c = 0; c < tamanho; c++) {
            if (habilidade[r][c] != 1) continue; // ignorar células não afetadas

            int br, bc; // coordenadas no tabuleiro

            if (pontaOrigem) {
                // Alinha a ponta da matriz na origem
                br = origemLinha + r;
                bc = origemColuna + (c - centro);
            } else {
                // Centraliza a matriz na origem
                br = origemLinha + (r - centro);
                bc = origemColuna + (c - centro);
            }

            // Verifica limites
            if (br < 0 || br >= TAM_TABULEIRO || bc < 0 || bc >= TAM_TABULEIRO) continue;

            // Marca a área da habilidade no tabuleiro
            tabuleiro[br][bc] = HABILIDADE;
        }
    }
}

// ========== Função Principal ==========
int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializar o tabuleiro com água (0)
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tabuleiro[i][j] = 0;

    // Posicionar 4 navios
    if (podePosicionar(tabuleiro, 2, 4, 0, 0)) posicionarNavio(tabuleiro, 2, 4, 0, 0);  // horizontal
    if (podePosicionar(tabuleiro, 5, 7, 1, 0)) posicionarNavio(tabuleiro, 5, 7, 1, 0);  // vertical
    if (podePosicionar(tabuleiro, 0, 0, 0, 1)) posicionarNavio(tabuleiro, 0, 0, 0, 1);  // diagonal ↘︎
    if (podePosicionar(tabuleiro, 2, 4, 0, 2)) posicionarNavio(tabuleiro, 2, 4, 0, 2);  // diagonal ↙︎

    // Constrói as matrizes de habilidade (7x7)
    const int tamanho = 7;
    int cone[tamanho][tamanho];
    int cruz[tamanho][tamanho];
    int octaedro[tamanho][tamanho];

    construirCone(tamanho, cone);
    construirCruz(tamanho, cruz);
    construirOctaedro(tamanho, octaedro);

    // Define as origens das habilidades
    int origemConeLinha = 1, origemConeColuna = 5;       // ponta do cone
    int origemCruzLinha = 6, origemCruzColuna = 2;       // centro da cruz
    int origemOctaedroLinha = 4, origemOctaedroColuna = 6; // centro do octaedro

    // Aplicar habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, tamanho, origemConeLinha, origemConeColuna, 1);
    aplicarHabilidade(tabuleiro, cruz, tamanho, origemCruzLinha, origemCruzColuna, 0);
    aplicarHabilidade(tabuleiro, octaedro, tamanho, origemOctaedroLinha, origemOctaedroColuna, 0);

    // Exibir o tabuleiro
    printf("=== Tabuleiro Batalha Naval (Mestre) ===\n\n");
    

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
