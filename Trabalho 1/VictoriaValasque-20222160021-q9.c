#include <stdio.h>
#include <string.h>

#define TAMANHO_TABULEIRO 10
#define TOTAL_NAVIOS 6

typedef struct {
    int tamanho;
    int afundado;
    int acertos;
} Navio;

typedef struct {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    char tabuleiroAdversario[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Navio navios[TOTAL_NAVIOS];
    int totalNavios;
    int naviosAfundados;
} Jogador;

void inicializarTabuleiro(Jogador *j) {
    int i, k;
    for (i = 0; i < TAMANHO_TABULEIRO; i++)
        for (k = 0; k < TAMANHO_TABULEIRO; k++) {
            j->tabuleiro[i][k] = ' ';
            j->tabuleiroAdversario[i][k] = ' ';
        }
    j->naviosAfundados = 0;
    j->totalNavios = TOTAL_NAVIOS;
    int tamanhos[TOTAL_NAVIOS] = {4, 3, 2, 1, 1, 1};
    for (i = 0; i < TOTAL_NAVIOS; i++) {
        j->navios[i].tamanho = tamanhos[i];
        j->navios[i].afundado = 0;
        j->navios[i].acertos = 0;
    }
}

void imprimirTabuleiro(Jogador *j, int proprio) {
    int i, k;
    printf("\n   ");
    for (k = 0; k < TAMANHO_TABULEIRO; k++)
        printf(" %2d ", k + 1);
    printf("\n");
    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c  ", 'A' + i);
        for (k = 0; k < TAMANHO_TABULEIRO; k++) {
            char c;
            if (proprio)
                c = j->tabuleiro[i][k];
            else
                c = j->tabuleiroAdversario[i][k];
            printf("[%c] ", c == ' ' ? ' ' : c);
        }
        printf("\n");
    }
}

int posicionarNavio(Jogador *j, int navio, int linha, int coluna, char direcao) {
    int tamanho = j->navios[navio].tamanho;
    int dl = 0, dc = 0;

    if (direcao == 'H' || direcao == 'h') dc = 1;
    else dl = 1;

    int l = linha, c = coluna;
    int i;
    for (i = 0; i < tamanho; i++) {
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;
        if (j->tabuleiro[l][c] != ' ')
            return 0;
        l += dl;
        c += dc;
    }

    l = linha; c = coluna;
    for (i = 0; i < tamanho; i++) {
        j->tabuleiro[l][c] = 'N';
        l += dl;
        c += dc;
    }
    return 1;
}

void fazerTiro(Jogador *atirador, Jogador *alvo, int linha, int coluna) {
    if (alvo->tabuleiro[linha][coluna] == 'N') {
        alvo->tabuleiro[linha][coluna] = '0';
        atirador->tabuleiroAdversario[linha][coluna] = '0';
        printf("Acertou um navio!\n");

        int i;
        for (i = 0; i < TOTAL_NAVIOS; i++) {
            if (!alvo->navios[i].afundado) {
                alvo->navios[i].acertos++;
                if (alvo->navios[i].acertos >= alvo->navios[i].tamanho) {
                    alvo->navios[i].afundado = 1;
                    alvo->naviosAfundados++;
                    printf("Navio afundado!\n");
                }
                break;
            }
        }
    } else if (alvo->tabuleiro[linha][coluna] == ' ') {
        alvo->tabuleiro[linha][coluna] = 'X';
        atirador->tabuleiroAdversario[linha][coluna] = 'X';
        printf("Agua! Tiro na agua.\n");
    } else {
        printf("Posicao ja atacada!\n");
    }
}

int lerLinha(char entrada[]) {
    if (entrada[0] < 'A' || entrada[0] > 'J')
        if (entrada[0] < 'a' || entrada[0] > 'j')
            return -1;
    if (entrada[0] >= 'a') return entrada[0] - 'a';
    return entrada[0] - 'A';
}

int lerColuna(char entrada[]) {
    int col = 0, i = 1;
    while (entrada[i] != '\0') {
        if (entrada[i] < '0' || entrada[i] > '9') return -1;
        col = col * 10 + (entrada[i] - '0');
        i++;
    }
    col--;
    if (col < 0 || col >= TAMANHO_TABULEIRO) return -1;
    return col;
}

void configurarNavios(Jogador *j, int numJogador) {
    int i;
    printf("\n=== Jogador %d, posicione seus navios ===\n", numJogador);
    for (i = 0; i < TOTAL_NAVIOS; i++) {
        char entrada[10], direcao[5];
        int linha, coluna;
        printf("\nNavio %d (tamanho %d):\n", i + 1, j->navios[i].tamanho);
        imprimirTabuleiro(j, 1);
        while (1) {
            printf("Informe a posicao inicial (ex: A1): ");
            scanf("%s", entrada);
            linha = lerLinha(entrada);
            coluna = lerColuna(entrada);
            if (linha == -1 || coluna == -1) {
                printf("Posicao invalida!\n");
                continue;
            }
            if (j->navios[i].tamanho > 1) {
                printf("Informe a direcao (H=horizontal, V=vertical): ");
                scanf("%s", direcao);
            } else {
                direcao[0] = 'H';
            }
            if (posicionarNavio(j, i, linha, coluna, direcao[0]))
                break;
            else
                printf("Posicao invalida ou ocupada! Tente novamente.\n");
        }
    }
    imprimirTabuleiro(j, 1);
}

void turnoJogador(Jogador *atirador, Jogador *alvo, int numJogador) {
    char entrada[10];
    int linha, coluna;
    printf("\n=== Vez do Jogador %d ===\n", numJogador);
    printf("Seu tabuleiro:\n");
    imprimirTabuleiro(atirador, 1);
    printf("Tabuleiro do adversario:\n");
    imprimirTabuleiro(atirador, 0);
    while (1) {
        printf("Informe a posicao para atirar (ex: B5): ");
        scanf("%s", entrada);
        linha = lerLinha(entrada);
        coluna = lerColuna(entrada);
        if (linha == -1 || coluna == -1) {
            printf("Posicao invalida!\n");
            continue;
        }
        if (atirador->tabuleiroAdversario[linha][coluna] != ' ') {
            printf("Voce ja atirou aqui!\n");
            continue;
        }
        break;
    }
    fazerTiro(atirador, alvo, linha, coluna);
}

int main() {
    Jogador jogador1, jogador2;

    inicializarTabuleiro(&jogador1);
    inicializarTabuleiro(&jogador2);

    configurarNavios(&jogador1, 1);
    configurarNavios(&jogador2, 2);

    int turno = 1;
    while (1) {
        if (turno == 1) {
            turnoJogador(&jogador1, &jogador2, 1);
            if (jogador2.naviosAfundados == TOTAL_NAVIOS) {
                printf("\nJogador 1 venceu! Todos os navios do adversario foram afundados!\n");
                break;
            }
        } else {
            turnoJogador(&jogador2, &jogador1, 2);
            if (jogador1.naviosAfundados == TOTAL_NAVIOS) {
                printf("\nJogador 2 venceu! Todos os navios do adversario foram afundados!\n");
                break;
            }
        }
        turno = (turno == 1) ? 2 : 1;
    }

    return 0;
}
