#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 10
#define TOTAL_TERRITORIOS 5

// Lista de missões disponíveis
char *missoes[5] = 
{
    "Eliminar todo o exercito Verde",
    "Eliminar todo o exercito Vermelho",
    "Eliminar todo o exercito Preto",
    "Eliminar todo o exercito Azul",
    "Eliminar todo o exercito Branco"
};

// Nome dos continentes (para exemplo dos territórios)
char *continentes[5] =
{
    "America",
    "Africa",
    "Europa",
    "Asia",
    "Oceania"
};

// Cores dos exércitos
char *cores[5] =
{
    "Verde",
    "Preto",
    "Azul",
    "Branco",
    "Vermelho"
};

// Estrutura de um território
typedef struct{
    char nome[30];
    char cor[10];
    int tropa;
} Territorio;


// ======== Protótipos das funções =========

void territoriosFixos(Territorio *territorios);
/* @brief Inicializa territórios fixos com nome, cor e tropas aleatórias
 * @param territorios ponteiro para array de Territorio
 */

void mostrarMapa(Territorio *territorios);
/* @brief Mostra todos os territórios no "mapa"
 * @param territorios ponteiro para array de Territorio
 */

void removerEnter(char *str);
/* @brief Remove o caractere '\n' de uma string
 * @param str ponteiro para string
 */

void limparBufferEntrada();
/* @brief Limpa o buffer de entrada (stdin) para evitar problemas com scanf/getchar
 */

void entregarMissao(char **missao, char **jogador);
/* @brief Entrega uma missão aleatória para o jogador (sem conflito com sua própria cor)
 * @param missao ponteiro para string missão
 * @param jogador ponteiro para string jogador
 */

void mostrarMenu(char *missao, char *jogador);
/* @brief Mostra o menu de opções do jogo
 * @param missao missão do jogador
 * @param jogador cor do jogador
 */

int rolarDados();
/* @brief Gera um número aleatório entre 1 e 6 (simulação de dado)
 * @return valor do dado (1–6)
 */

void atacar(Territorio *territorios);
/* @brief Realiza o ataque entre dois territórios
 * @param territorios ponteiro para array de Territorio
 */

int verificarMissao(Territorio *territorios, char* missao);
/* @brief Verifica se a missão foi concluída
 * @param territorios ponteiro para array de Territorio
 * @param missao string da missão
 * @return 1 se venceu, 0 se não
 */

void mostrarMissao(Territorio *territorios, char* minhaMissao);
/* @brief Mostra status da missão (cumprida ou não)
 * @param territorios ponteiro para array de Territorio
 * @param minhaMissao string missão do jogador
 */


// ================= MAIN ===================
int main()
{
    Territorio *territorios;
    territorios = malloc(MAX_TERRITORIOS * sizeof(Territorio)); // Aloca memória para os territórios
    
    if(!territorios){
        printf("\nError: Memory was not alocated!\n");
        return 1;
    }
    
    srand(time(NULL)); // inicializa o rand com o tempo atual
    
    territoriosFixos(territorios); // inicializa territórios
    char *minhaMissao;
    char *meuJogador;

    entregarMissao(&minhaMissao, &meuJogador); // atribui missão e jogador
    
    while ( 1 )
    {
        mostrarMapa(territorios);
        mostrarMenu(minhaMissao, meuJogador);
        int opcao;
        scanf("%d", &opcao);
        limparBufferEntrada();
        
        if(opcao > 2 || opcao < 0){
            printf("Opção inválida!\n");
            continue;
        }
        switch(opcao)
        {
            case 1:
                atacar(territorios);
                int won = verificarMissao(territorios, minhaMissao);
                if(won == 1){
                    printf("*******************************\n");
                    printf("     *    🎉 VENCEU 🎉    *\n");
                    printf("*******************************\n");
                }
                printf("\nPressione qualquer tecla para continuar.\n");
                getchar();
                continue;
            case 2:
                mostrarMissao(territorios, minhaMissao);
                printf("\nPressione qualquer tecla para continuar.\n");
                getchar();
                continue;
            case 0:
                printf("Saindo..\n");
                break;
        }
        if (opcao == 0) break;
    }
    
    free(territorios); // libera memória
    return 0;    
}


// ================= FUNÇÕES ==================


void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void removerEnter(char *str)
{
    if (!str) return;
    str[strcspn(str, "\n")] = '\0';
}

int rolarDados()
{
    return (rand()%6)+1;
}

int verifyInd(int indA, int indB)
{
    if (indA < 1 || indA > 5 || indB < 1 || indB > 5) {
        return 0;
    }else return 1;
}

void mostrarMissao(Territorio *territorios,char* minhaMissao){
    int won = verificarMissao(territorios, minhaMissao);
    if (won == 1){
        printf("\nParabéns, você cumpriu seu objetivo!\n\n");
    }else{
        printf("\nVocê ainda não concluiu sua missão! Continue a lutar.\n\n");
    }
}

int verificarMissao(Territorio *territorios, char *missao)
{
    int aindaNaoConcluida = 0;

    for(int i = 0; i < 5; i++){
        if(strstr(missao, territorios[i].cor)){ // se a cor da missão ainda existe no mapa
            aindaNaoConcluida = 1;
            break;
        }
    }

    if(!aindaNaoConcluida) return 1;
    return 0;
}

void atacar(Territorio *territorios)
{
    int indAtacante, indDefensor;
    int dadoAtk = rolarDados(), dadoDef=rolarDados();
    
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (1-5): ");
    scanf("%d", &indAtacante);
    limparBufferEntrada();
    printf("Escolha o territorio defensor (1-5): ");
    scanf("%d", &indDefensor);
    limparBufferEntrada();
    
    if(verifyInd(indAtacante, indDefensor))
    {
        printf("\n\n --- RESULTADO DA BATALHA ---\n");
        printf("ataque (%s): %d | defesa (%s): %d\n", 
            territorios[indAtacante-1].nome, dadoAtk, territorios[indDefensor-1].nome, dadoDef);
        if(dadoAtk > dadoDef){
            printf("VITORIA DO ATAQUE! a defesa perdeu 1 tropa.\n\n");
            territorios[indDefensor-1].tropa--;
            if(territorios[indDefensor-1].tropa == 0){
                printf("( %s ) conquistado por ( %s )\n\n", territorios[indDefensor-1].nome, territorios[indAtacante-1].nome);
                territorios[indDefensor-1].tropa++;
                strcpy(territorios[indDefensor-1].cor, territorios[indAtacante-1].cor);
                territorios[indAtacante-1].tropa--;
            }
        }else{
            printf("VITORIA DA DEFESA! o atacante perdeu 1 tropa.\n\n");
            territorios[indAtacante-1].tropa--;
        }
    }
}

void mostrarMapa(Territorio *territorios)
{
    printf("\n============== MAPA MUNDO ==============\n");
    for(int i = 0; i < TOTAL_TERRITORIOS; i++)
    {
        printf("%d. %-10s  (EXERCITO: %-8s   , TROPAS: %2d)\n", i+1, 
            territorios[i].nome, territorios[i].cor, territorios[i].tropa);
    }
    printf("\n========================================\n");
}

void territoriosFixos(Territorio *territorios)
{
    for(int i = 0; i < 5; i++){
        strcpy(territorios[i].nome, continentes[i]);
        strcpy(territorios[i].cor, cores[i]);
        territorios[i].tropa = (int) (rand()%5)+1; // tropas aleatórias entre 1 e 5
    }
}

void entregarMissao(char **missao, char **jogador)
{
    // Sorteia até que a missão não seja eliminar a própria cor do jogador
    do {
        *missao = missoes[rand() % 5];
        *jogador = cores[rand() % 5];
    } while (strstr(*missao, *jogador) != NULL);
}

void mostrarMenu(char *missao, char *jogador)
{
    printf("\n--- SUA MISSÃO (EXERCITO %s) ---\n",jogador);
    printf("%s\n",missao);
    printf("\n--- MENU DE AÇÕES ---\n");
    printf("1 - Atacar.\n2 - Verificar missão.\n0 - Sair.\nEscolha sua ação: ");
}

