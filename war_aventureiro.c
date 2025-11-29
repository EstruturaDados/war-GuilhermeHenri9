#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>  


typedef struct {
    char nome[30];
    char cor[30];
    int tropas;
} Territorio;


void simularBatalha(Territorio *atacante, Territorio *defensor);
void exibirMapa(Territorio *mapa, int qtd);

int main() {

    srand(time(NULL));

    int i;
    int qtd_territorios = 5;

    Territorio *mapa = (Territorio*) calloc(qtd_territorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        return 1;
    }

    printf("=== SETUP DO JOGO: CADASTRO ===\n");

    for(i = 0; i < qtd_territorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        
        printf("Cor do Exercito: ");
        scanf(" %[^\n]", mapa[i].cor);
        
        printf("Tropas iniciais: ");
        scanf("%d", &mapa[i].tropas);
    }

    int idAtacante, idDefensor;
    int continuar = 1;

    while(continuar) {
        exibirMapa(mapa, qtd_territorios);

        printf("\n=== FASE DE ATAQUE ===\n");
        printf("Digite o numero do territorio ATACANTE (1-5) ou 0 para sair: ");
        scanf("%d", &idAtacante);

        if (idAtacante == 0) break;

        printf("Digite o numero do territorio DEFENSOR (1-5): ");
        scanf("%d", &idDefensor);

        if (idAtacante < 1 || idAtacante > 5 || idDefensor < 1 || idDefensor > 5) {
            printf("\n[!] Erro: Territorio invalido. Tente novamente.\n");
            continue;
        }

        if (idAtacante == idDefensor) {
            printf("\n[!] Erro: Voce nao pode atacar a si mesmo!\n");
            continue;
        }

        simularBatalha(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
        
        printf("\nPressione 1 para continuar ou 0 para sair: ");
        scanf("%d", &continuar);
    }


    free(mapa);
    printf("\nJogo encerrado. Memoria liberada.\n");

    return 0;
}


void simularBatalha(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n[!] O atacante nao tem tropas suficientes para atacar!\n");
        return;
    }

    printf("\n>>> BATALHA INICIADA: %s vs %s <<<\n", atacante->nome, defensor->nome);

    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("Dados rolados -> Ataque: [%d] | Defesa: [%d]\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        printf("Resultado: VITORIA DO ATACANTE!\n");
        defensor->tropas--; 
        
        if (defensor->tropas <= 0) {
            printf("\n*** O TERRITORIO %s FOI CONQUISTADO! ***\n", defensor->nome);
            defensor->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
            atacante->tropas--;
            printf("Agora %s pertence ao exercito %s.\n", defensor->nome, atacante->cor);
        }
    } else {
        printf("Resultado: VITORIA DA DEFESA!\n");
        atacante->tropas--;
    }
}

void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n--- SITUACAO ATUAL DO MAPA ---\n");
    for(int i = 0; i < qtd; i++) {
        printf("[%d] %-20s (Cor: %-10s) - Tropas: %d\n", 
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("------------------------------\n");
}