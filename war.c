#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*==========================================================
    STRUCT DE TERRITÓRIOS
==========================================================*/
typedef struct {
    char nome[30];
    int tropas;
} Territorio;

/*==========================================================
    FUNÇÃO: SIMULA UM ATAQUE ENTRE TERRITÓRIOS
==========================================================*/
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas < 2) {
        printf("\n[ERRO] %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }

    printf("\n>>> %s está atacando %s...\n", atacante->nome, defensor->nome);

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("Dado do Atacante (%s): %d\n", atacante->nome, dadoAtk);
    printf("Dado do Defensor  (%s): %d\n", defensor->nome, dadoDef);

    if (dadoAtk > dadoDef) {
        defensor->tropas--;
        printf("\nResultado: %s venceu o duelo!\n", atacante->nome);

        if (defensor->tropas <= 0) {
            printf("🎉 %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);

            defensor->tropas = 1;        // território conquistado recebe 1 tropa
            atacante->tropas--;          // atacante envia 1 tropa para ocupar
        }

    } else if (dadoDef > dadoAtk) {
        atacante->tropas--;
        printf("\nResultado: %s defendeu com sucesso!\n", defensor->nome);

    } else {
        printf("\nEmpate! Nada acontece.\n");
    }
}

/*==========================================================
    FUNÇÃO PRINCIPAL
==========================================================*/
int main() {
    srand(time(NULL));

    int qtd;
    printf("Quantos territórios deseja criar? (1 a 5): ");
    scanf("%d", &qtd);

    if (qtd < 1 || qtd > 5) {
        printf("Quantidade inválida!\n");
        return 0;
    }

    /*======================================================
        ALOCAÇÃO DINÂMICA COM CALLOC
    ======================================================*/
    Territorio *mapa = calloc(qtd, sizeof(Territorio));

    printf("\n=== CADASTRO DOS TERRITÓRIOS ===\n");

    for (int i = 0; i < qtd; i++) {
        printf("\nNome do território %d: ", i + 1);
        scanf("%s", mapa[i].nome);

        printf("Tropas iniciais em %s: ", mapa[i].nome);
        scanf("%d", &mapa[i].tropas);
    }

    /*======================================================
        LOOP INTERATIVO DE ATAQUES
    ======================================================*/
    int opcao = 1;

    while (opcao != 0) {
        printf("\n\n=== MAPA ATUAL ===\n");
        for (int i = 0; i < qtd; i++) {
            printf("%d - %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].tropas);
        }

        printf("\nEscolha o território ATACANTE (1-%d) ou 0 para sair: ", qtd);
        int a;
        scanf("%d", &a);

        if (a == 0)
            break;

        printf("Escolha o território DEFENSOR (1-%d): ", qtd);
        int d;
        scanf("%d", &d);

        if (a < 1 || a > qtd || d < 1 || d > qtd) {
            printf("\n[ERRO] Entrada inválida!\n");
            continue;
        }

        if (a == d) {
            printf("\n[ERRO] Um território não pode atacar ele mesmo!\n");
            continue;
        }

        atacar(&mapa[a - 1], &mapa[d - 1]);
    }

    /*======================================================
        LIBERAÇÃO DE MEMÓRIA
    ======================================================*/
    free(mapa);

    printf("\n=== FIM DO PROGRAMA ===\n");
    return 0;
}
