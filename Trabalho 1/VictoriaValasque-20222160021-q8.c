#include <stdio.h>

typedef struct {
    char tabuleiro[3][3];
    int jogadorAtual;
    int fimDeJogo;
} Jogo;

void inicializarJogo(Jogo *j) {
    int i, k;
    for (i = 0; i < 3; i++)
        for (k = 0; k < 3; k++)
            j->tabuleiro[i][k] = ' ';
    j->jogadorAtual = 1;
    j->fimDeJogo = 0;
}

void imprimirTabuleiro(Jogo *j) {
    int i, k;
    printf("\n    1   2   3\n");
    printf("  +---+---+---+\n");
    for (i = 0; i < 3; i++) {
        printf("%c |", 'A' + i);
        for (k = 0; k < 3; k++)
            printf(" %c |", j->tabuleiro[i][k]);
        printf("\n  +---+---+---+\n");
    }
}

int verificarVencedor(Jogo *j) {
    int i;
    char m = (j->jogadorAtual == 1) ? 'X' : '0';
    for (i = 0; i < 3; i++) {
        if (j->tabuleiro[i][0] == m && j->tabuleiro[i][1] == m && j->tabuleiro[i][2] == m)
            return 1;
        if (j->tabuleiro[0][i] == m && j->tabuleiro[1][i] == m && j->tabuleiro[2][i] == m)
            return 1;
    }
    if (j->tabuleiro[0][0] == m && j->tabuleiro[1][1] == m && j->tabuleiro[2][2] == m)
        return 1;
    if (j->tabuleiro[0][2] == m && j->tabuleiro[1][1] == m && j->tabuleiro[2][0] == m)
        return 1;
    return 0;
}

int tabuleiroCheio(Jogo *j) {
    int i, k;
    for (i = 0; i < 3; i++)
        for (k = 0; k < 3; k++)
            if (j->tabuleiro[i][k] == ' ') return 0;
    return 1;
}

void realizarJogada(Jogo *j) {
    char entrada[10];
    int linha, coluna;
    char marca = (j->jogadorAtual == 1) ? 'X' : '0';

    while (1) {
        imprimirTabuleiro(j);
        printf("Jogador %d, informe sua jogada: ", j->jogadorAtual);
        scanf("%s", entrada);

        if ((entrada[0] >= 'A' && entrada[0] <= 'C') && (entrada[1] >= '1' && entrada[1] <= '3')) {
            linha = entrada[0] - 'A';
            coluna = entrada[1] - '1';
        } else if ((entrada[0] >= 'a' && entrada[0] <= 'c') && (entrada[1] >= '1' && entrada[1] <= '3')) {
            linha = entrada[0] - 'a';
            coluna = entrada[1] - '1';
        } else {
            printf("Celula invalida! Use o formato ex: A1, B2, C3\n");
            continue;
        }

        if (j->tabuleiro[linha][coluna] != ' ') {
            printf("Celula ja ocupada! Tente novamente.\n");
            continue;
        }

        j->tabuleiro[linha][coluna] = marca;
        break;
    }
}

int main() {
    Jogo j;
    inicializarJogo(&j);

    while (!j.fimDeJogo) {
        realizarJogada(&j);

        if (verificarVencedor(&j)) {
            imprimirTabuleiro(&j);
            printf("Jogador %d venceu!\n", j.jogadorAtual);
            j.fimDeJogo = 1;
        } else if (tabuleiroCheio(&j)) {
            imprimirTabuleiro(&j);
            printf("Empate! Nao houve ganhador.\n");
            j.fimDeJogo = 1;
        } else {
            j.jogadorAtual = (j.jogadorAtual == 1) ? 2 : 1;
        }
    }

    return 0;
}
