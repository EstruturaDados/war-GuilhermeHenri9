#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[30];
    int tropas;
} Territorio;

typedef struct {
    int tipo; 
    char corAlvo[30];
    int qtdAlvo;
    char descricao[100];
} Missao;


void inicializarMapa(Territorio *mapa, int qtd);
Missao sortearMissao();
void exibirMenu();
void exibirMapa(const Territorio *mapa, int qtd); 
void exibirMissao(const Missao *m);               
void realizarAtaque(Territorio *mapa, int qtd);   
void verificarMissao(const Territorio *mapa, int qtd, const Missao *m);

int main() {
    srand(time(NULL));
    int qtd = 5;
    int opcao = -1;

    Territorio *mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (!mapa) return 1;

    inicializarMapa(mapa, qtd);
    Missao missaoAtual = sortearMissao();

    printf("\n=== BEM-VINDO AO WAR: NIVEL MESTRE ===\n");
    printf("Voce comanda o exercito: AZUL\n");

    while (opcao != 0) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirMapa(mapa, qtd);
                realizarAtaque(mapa, qtd);
                break;
            case 2:
                exibirMissao(&missaoAtual);
                verificarMissao(mapa, qtd, &missaoAtual);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }

    free(mapa);
    return 0;
}


void inicializarMapa(Territorio *mapa, int qtd) {
    strcpy(mapa[0].nome, "Brasil");   strcpy(mapa[0].cor, "Azul");     mapa[0].tropas = 5; 
    strcpy(mapa[1].nome, "Franca");   strcpy(mapa[1].cor, "Verde");    mapa[1].tropas = 3;
    strcpy(mapa[2].nome, "China");    strcpy(mapa[2].cor, "Vermelho"); mapa[2].tropas = 3;
    strcpy(mapa[3].nome, "Egipto");   strcpy(mapa[3].cor, "Amarelo");  mapa[3].tropas = 2;
    strcpy(mapa[4].nome, "EUA");      strcpy(mapa[4].cor, "Verde");    mapa[4].tropas = 4;
}

Missao sortearMissao() {
    Missao m;
    int r = rand() % 2; 

    if (r == 0) {
        m.tipo = 1;
        m.qtdAlvo = 3; 
        strcpy(m.descricao, "Conquistar 3 territorios para o exercito Azul.");
    } else {
        m.tipo = 2;
        strcpy(m.corAlvo, "Verde"); 
        strcpy(m.descricao, "Destruir completamente o exercito Verde.");
    }
    return m;
}

void exibirMenu() {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missao\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void exibirMapa(const Territorio *mapa, int qtd) {
    printf("\nMapa Global:\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %-15s | Exercito: %-10s | Tropas: %d\n", 
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMissao(const Missao *m) {
    printf("\n>>> SUA MISSAO: %s <<<\n", m->descricao);
}

void realizarAtaque(Territorio *mapa, int qtd) {
    int idAtk, idDef;

    printf("\nQuem ataca? (1-%d): ", qtd);
    scanf("%d", &idAtk);
    printf("Quem defende? (1-%d): ", qtd);
    scanf("%d", &idDef);

    idAtk--; idDef--;

    if (idAtk < 0 || idAtk >= qtd || idDef < 0 || idDef >= qtd || idAtk == idDef) {
        printf("Movimento invalido!\n");
        return;
    }

    Territorio *atk = &mapa[idAtk];
    Territorio *def = &mapa[idDef];

    if (strcmp(atk->cor, "Azul") != 0) {
        printf("Atencao: Voce so deveria comandar o exercito Azul!\n");
    }

    if (atk->tropas <= 1) {
        printf("Tropas insuficientes para ataque.\n");
        return;
    }

    int dadoAtk = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;
    
    printf("Dados: Atk [%d] vs Def [%d] -> ", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("Vitoria do Ataque!\n");
        def->tropas--;
        if (def->tropas <= 0) {
            printf("TERRITORIO CONQUISTADO! %s agora eh %s.\n", def->nome, atk->cor);
            def->tropas = 1;
            strcpy(def->cor, atk->cor);
            atk->tropas--;
        }
    } else {
        printf("Defesa segurou!\n");
        atk->tropas--;
    }
}

void verificarMissao(const Territorio *mapa, int qtd, const Missao *m) {
    printf("\nverificando progresso...\n");
    
    if (m->tipo == 1) {
        int contagem = 0;
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                contagem++;
            }
        }
        printf("Territorios Azuis: %d / %d\n", contagem, m->qtdAlvo);
        
        if (contagem >= m->qtdAlvo) {
            printf("*** PARABENS! MISSAO CUMPRIDA! VITORIA! ***\n");
        } else {
            printf("Ainda falta conquistar mais territorios.\n");
        }
    } 
    else if (m->tipo == 2) {
        int vivos = 0;
        for (int i = 0; i < qtd; i++) {
            if (strcmp(mapa[i].cor, m->corAlvo) == 0) {
                vivos++;
            }
        }
        
        if (vivos == 0) {
             printf("*** PARABENS! O EXERCITO %s FOI ANIQUILADO! ***\n", m->corAlvo);
        } else {
            printf("Ainda existem %d territorios inimigos (%s).\n", vivos, m->corAlvo);
        }
    }
}