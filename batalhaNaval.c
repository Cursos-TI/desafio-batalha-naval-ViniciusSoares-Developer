#include <stdio.h>
#include <stdbool.h>

int main() {
    // Variavel para guardar o navio
    int navio[3] = {3, 3, 3};

    /**
     * Variavel para guardar o tabuleiro totalmente zerado
     * 
     * 0 -> Agua
     * 3 -> Navio
     */
    int tabuleiro[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    int naviosColocados = 0; // Quantidade de navios já posicionados
    int totalNavio = 2; // Total de navios há se posicionar

    // Roda enquanto todos os navios não foram posicionados
    while (naviosColocados < totalNavio) {
        int coordenadaY, coordenadaX; // Variaveis para informar qual a primeira posição do barco
        printf("Cordenadas iniciais do %d° navio (de 1 a 10): ", naviosColocados + 1);
        // Scans para lê a entrada do usuário
        scanf("%d", &coordenadaY);
        scanf("%d", &coordenadaX);

        // Retirar 1 utilizando pre decremento pos a entrada do usuário vem de 1 a 10
        --coordenadaY;
        --coordenadaX;
        
        /**
         * Verificar se as coordenadas digitas está dentro dos limites do tabuleiro do jogo
         * Caso não esteja dentro dos limites o jogo retorna a perguntar as coordenadas
         * para coletar um novo posicionamento inicial para o navio
         */
        bool coordenadaYForaDoLimite = coordenadaY < 0 || coordenadaY > 9;
        bool coordenadaXForaDoLimite = coordenadaX < 0 || coordenadaX > 9;
        if (coordenadaYForaDoLimite || coordenadaXForaDoLimite) {
            printf("Valor digitado para %s fora do limite do mapa.\n", coordenadaYForaDoLimite ? "Y" : "X");
            continue; 
        }
        
        // Loop aninhado para colocar os valores dentro do tabuleiro
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                /*
                 * Para dinamismo todo barco par é horizontal e impar é vertical.
                 * 
                 * se as posições de Y e X batem com o da entrada ele seta os valores
                 * caso já tenha navio posicionado ele retorna ao inicio e não posiciona o navio
                 */
                if (y == coordenadaY && x == coordenadaX) {
                    if ((naviosColocados + 1) % 2 != 0 && coordenadaX <= 7) {
                        if (tabuleiro[y][x] != 0 || tabuleiro[y][x + 1] != 0 || tabuleiro[y][x + 2] != 0) {
                            printf("Não é possivel colocar o navio onde outro está!\n");
                            break;
                        }
                        tabuleiro[y][x] = navio[0];
                        tabuleiro[y][x + 1] = navio[1];
                        tabuleiro[y][x + 2] = navio[2];
                        ++naviosColocados;
                    } else if (coordenadaY <= 7) {
                        if (tabuleiro[y][x] != 0 || tabuleiro[y + 1][x] != 0 || tabuleiro[y + 2][x] != 0) {
                            printf("Não é possivel colocar o navio onde outro está!\n");
                            break;
                        }
                        tabuleiro[y][x] = navio[0];
                        tabuleiro[y + 1][x] = navio[1];
                        tabuleiro[y + 2][x] = navio[2];
                        ++naviosColocados;
                    } else {
                        printf("Navio parte fora do limite!\n");
                        break;
                    }
                }
            }
        }
        
    }

    // Exibi o tabuleiro
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            printf("%d ", tabuleiro[y][x]);
        }
        printf("\n");
    }

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}
