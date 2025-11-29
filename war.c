#include <stdio.h>
#include <string.h>


struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};


int main() {
    struct Territorio territorios[5];
    int i;

    printf("==========================================\n");
    printf("     SISTEMA DE CADASTRO DE TERRITORIOS\n"); 
    printf("==========================================\n");

    for (i = 0; i < 5; i++) {
        printf("\n--- Cadastrando Territorio %d/5 ---\n", i + 1); 

        printf("Nome do Territorio: ");
        scanf(" %[^\n]", territorios[i].nome);

        printf("Cor do Exercito: "); 
        scanf(" %[^\n]", territorios[i].cor);

        printf("Quantidade de Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n\n");
    printf("==========================================\n");
    printf("       RELATORIO DE TERRITORIOS\n"); 
    printf("==========================================\n");
    
    printf("%-30s | %-10s | %s\n", "NOME", "COR", "TROPAS");
    printf("-------------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%-30s | %-10s | %d\n", 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }
    printf("-------------------------------------------------------\n");

    return 0;
}
