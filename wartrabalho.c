#include <stdio.h>
#include <string.h>

#define QTD 5

typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[QTD];

    printf("=== Cadastro de Territórios ===\n");
    for (int i = 0; i < QTD; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0; // remover \n

        printf("Cor do exército: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpar buffer
    }

    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < QTD; i++) {
        printf("Território: %s | Cor: %s | Tropas: %d\n",
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    return 0;
}
