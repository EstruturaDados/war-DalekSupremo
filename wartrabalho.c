#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD 5

typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

// ---------- Funções Comuns ----------
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void simularAtaque(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nBatalha: %s (A) vs %s (D)\n", atacante->nome, defensor->nome);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoA, dadoD);

    if (dadoA >= dadoD) {
        defensor->tropas--;
        printf("%s perdeu 1 tropa!\n", defensor->nome);
        if (defensor->tropas <= 0) {
            defensor->tropas = 0;
            printf("%s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
        }
    } else {
        printf("%s defendeu com sucesso!\n", defensor->nome);
    }
}

// ---------- Nível Novato ----------
void nivelNovato() {
    Territorio mapa[QTD];
    printf("\n=== Cadastro de Territórios (Nível Novato) ===\n");

    for (int i = 0; i < QTD; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    exibirMapa(mapa, QTD);
}

// ---------- Nível Aventureiro ----------
void nivelAventureiro() {
    Territorio *mapa = calloc(QTD, sizeof(Territorio));
    printf("\n=== Cadastro de Territórios (Nível Aventureiro) ===\n");

    for (int i = 0; i < QTD; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do exército: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    int a, d;
    do {
        exibirMapa(mapa, QTD);
        printf("\nDigite atacante e defensor (0 0 para sair): ");
        scanf("%d %d", &a, &d);
        getchar();
        if (a == 0 || d == 0) break;

        if (a >= 1 && a <= QTD && d >= 1 && d <= QTD && a != d) {
            simularAtaque(&mapa[a - 1], &mapa[d - 1]);
        } else {
            printf("Escolha inválida!\n");
        }
    } while (1);

    free(mapa);
}

// ---------- Nível Mestre ----------
void inicializarTerritorios(Territorio *mapa) {
    char *nomes[QTD] = {"Brasil", "Argentina", "Chile", "Peru", "Colômbia"};
    char *cores[QTD] = {"Verde", "Azul", "Vermelho", "Amarelo", "Roxo"};
    for (int i = 0; i < QTD; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = rand() % 5 + 1;
    }
}

int verificarMissao(Territorio *mapa, int missao) {
    if (missao == 1) { // destruir exército verde
        for (int i = 0; i < QTD; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    } else if (missao == 2) { // conquistar 3 territórios
        char corJogador[20];
        strcpy(corJogador, mapa[0].cor);
        int count = 0;
        for (int i = 0; i < QTD; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                count++;
        }
        return count >= 3;
    }
    return 0;
}

void nivelMestre() {
    Territorio mapa[QTD];
    inicializarTerritorios(mapa);

    int missao = rand() % 2 + 1;
    printf("\n=== Nível Mestre ===\n");
    printf("Missão atribuída: ");
    if (missao == 1) printf("Destruir o exército Verde\n");
    else printf("Conquistar 3 territórios\n");

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirMapa(mapa, QTD);
            int a, d;
            printf("Digite atacante e defensor: ");
            scanf("%d %d", &a, &d);
            if (a >= 1 && a <= QTD && d >= 1 && d <= QTD && a != d) {
                simularAtaque(&mapa[a - 1], &mapa[d - 1]);
            }
        } else if (opcao == 2) {
            if (verificarMissao(mapa, missao)) {
                printf("\n🎉 MISSÃO CUMPRIDA! Você venceu!\n");
                break;
            } else {
                printf("\nMissão ainda não concluída.\n");
            }
        }
    } while (opcao != 0);
}

// ---------- Programa Principal ----------
int main() {
    srand(time(NULL));
    int escolha;

    do {
        printf("\n=== Desafio WAR Estruturado ===\n");
        printf("1 - Nível Novato (Cadastro)\n");
        printf("2 - Nível Aventureiro (Batalhas)\n");
        printf("3 - Nível Mestre (Missões)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar(); // limpar buffer

        if (escolha == 1) nivelNovato();
        else if (escolha == 2) nivelAventureiro();
        else if (escolha == 3) nivelMestre();

    } while (escolha != 0);

    printf("\nEncerrando o jogo... Até mais!\n");
    return 0;
}
