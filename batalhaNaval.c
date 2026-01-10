#include <stdio.h>
#include <stdbool.h>

void exibirTabuleiro(int tabuleiro[10][10]) {
    // Exibi o tabuleiro
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            printf("%d ", tabuleiro[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Variavel para guardar o navio
    int navio[3] = {3, 3, 3};

    /**
     * Variavel para guardar o tabuleiro totalmente zerado
     * 
     * 0 -> Agua
     * 3 -> Navio
     */
    int tabuleiro[10][10] = {0};

    int naviosColocados = 0; // Quantidade de navios já posicionados
    int totalNavio = 4; // Total de navios há se posicionar

    int coordenadasIniciais[4][2] = {
        {0, 0},
        {9, 7},
        {3, 4},
        {3, 6},
    };

    // Roda enquanto todos os navios não foram posicionados
    while (naviosColocados < totalNavio) {
        int coordenadaY = coordenadasIniciais[naviosColocados][0], coordenadaX = coordenadasIniciais[naviosColocados][1]; // Variaveis para informar qual a primeira posição do barco

        int limitTabuleiroDesteNavio = 10 - 3;
        // Loop aninhado para colocar os valores dentro do tabuleiro
        for (int y = 0; y < sizeof(tabuleiro); y++) {
            for (int x = 0; x < sizeof(tabuleiro[y]); x++) {
                /* 
                 * se as posições de Y e X batem com o da entrada ele seta os valores
                 * caso já tenha navio posicionado ele retorna ao inicio e não posiciona o navio
                 */
                if (y == coordenadaY && x == coordenadaX) {
                    for (int n = 0; n < 3; n++) {
                        int yToSetNavio = y, xToSetNavio = x;
                        switch (naviosColocados)
                        {
                        case 0:
                            yToSetNavio += n;
                            break;
                        case 1:
                            xToSetNavio += n;
                            break;
                        default:
                            yToSetNavio += n;
                            xToSetNavio += n;
                            break;
                        }

                        // Verifica se o navio não está sobrepondo outro ou se esta dentro do tabuleiro
                        if ((tabuleiro[yToSetNavio][xToSetNavio] != 0) || !(yToSetNavio >= 0 && yToSetNavio <= 9 && xToSetNavio >= 0 && xToSetNavio <= 9)) {
                            printf("O navio %d colocado esta em um local invalido!\n\n", naviosColocados + 1);
                            // Limpa os valores inseridos anteriormente
                            do {
                                n--;

                                switch (naviosColocados)
                                {
                                case 0:
                                    yToSetNavio -= n;
                                    break;
                                case 1:
                                    yToSetNavio -= n;
                                    break;
                                default:
                                    yToSetNavio -= n;
                                    xToSetNavio -= n;
                                    break;
                                }

                                tabuleiro[yToSetNavio][xToSetNavio] = 0;
                            } while (n > 0);
                            break;
                        }
                        
                        tabuleiro[yToSetNavio][xToSetNavio] = navio[n];
                    }
                    ++naviosColocados;
                }
            }
        }
        
    }

    /**
     * Criação da habilidade cone
     * 
     * Cria de forma dinamica o cone utilizando a logica
     * se a posição de x estiver entre 2 - y e 2 + y (sendo y a linha em que está)
     * utiliza  a logica tambem de 2 - y >= 0 para saber se já foi completado o cone dentro da matriz
     */
    int cone[5][5] = {0}; // <- Inicializa a matriz
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (x >= 2 - y && x <= 2 + y && 2 - y >= 0) {
                cone[y][x] = 1;
            } else {
                cone[y][x] = 0;
            }
        }
    }

    /**
     * Criação da habilidade cruz
     * 
     * Cria de forma dinamica a cruz utilizando a logica
     * Se o x ou y esta no centro ele inseri o valor de 1
     */
    int cruz[5][5] = {0};
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (y == 2 || x == 2) {
                cruz[y][x] = 1;
            }
        }
    }

    /**
     * Criação da habilidade octaendro
     * 
     * Cria de forma dinamica octaendro utilizando a logica
     * Se o y for da metade para cima da matriz ele cria um cone
     * quando for após a metade ele cria uma matriz invertida, retirando o y maximo - o y atual
     */
    int octaendro[5][5] = {0};
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (
                (y <= 2 && x >= 2 - y && x <= 2 + y) || ( y > 2 && x >= 2 - (4 - y) && x <= 2 + (4 - y))
            ) {
                octaendro[y][x] = 1;
            } else {
                octaendro[y][x] = 0;
            }
        }
    }

    /**
     * Posicionar a habilidade de cone no tabuleiro.
     * 
     * valida se a posição do cone será valida calculando com base no topo dele.
     * 
     * Posiciona o cone no tabuleiro movendo a posição dele x - 2 para centralizar a ponta.
     * 
     * Coloca o valor de 5 no tabuleiro onde é local de dano (1) da habilidade.
     */
    int posCone[2] = {0, 2};
    if (posCone[0] <= 7 && posCone[1] <= 7 && posCone[1] >= 2) {
        //Se for Valido ele inseri o cone dentro do tabuleiro
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (cone[y][x] == 1) {
                    tabuleiro[y + posCone[0]][x + posCone[1] - 2] = 5;
                }
            }
        }
    } else {
        printf("Posicionamento invalido da habilidade cone\n\n");
    }

    /** 
     * Posicionar a habilidade de cruz no tabuleiro.
     * 
     * Valida se a habilidade ficará dentro do tabuleiro.
     * 
     * Reposiciona utilizando o centro da cruz dentro do tabuleiro sendo
     * movido no x - 2 e y - 2 para que o centro seja onde foi designado a habilidade.
     * 
     * Verifica se é local de dano (1) da habilidade e coloca o 5 no tabuleiro.
     */
    int posCruz[2] = {2, 7};
    if (posCruz[0] <= 7 && posCruz[0] >= 2 && posCruz[1] <= 7 && posCruz[1] >= 2) {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (cruz[y][x] == 1) {
                    tabuleiro[y + posCruz[0] - 2][x + posCruz[1] - 2] = 5;
                }
            }
        }
    } else {
        printf("Posicionamento invalido da habilidade cruz\n\n");
    }

    /** 
     * Posicionar a habilidade de octaendro no tabuleiro.
     * 
     * Valida se a habilidade ficará dentro do tabuleiro.
     * 
     * Reposiciona utilizando o centro do octaendro dentro do tabuleiro sendo
     * movido no x - 2 e y - 2 para que o centro seja onde foi designado a habilidade.
     * 
     * Verifica se é local de dano (1) da habilidade e coloca o 5 no tabuleiro.
     */
    int posOctaendro[2] = {7, 3};
    int yCentro = 2;
    if (posOctaendro[0] <= 7 && posOctaendro[0] >= 2 && posOctaendro[1] <= 7 && posOctaendro[1] >= 2) {
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (octaendro[y][x] == 1) {
                    tabuleiro[y + posOctaendro[0] - 2][x + posOctaendro[1] - 2] = 5;
                }
            }
        }
    } else {
        printf("Posicionamento invalido da habilidade cruz\n\n");
    }

    // exibi o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}
