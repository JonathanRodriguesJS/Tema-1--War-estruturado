# Jogo de Territórios

## Descrição
Este é um jogo de estratégia inspirado em War, onde cada jogador controla exércitos em diferentes territórios. O objetivo principal é cumprir missões específicas, atacar outros territórios e conquistar o mapa.

O jogo foi implementado em **C**, utilizando alocação dinâmica de memória para os territórios, funções de ataque, verificação de missão e menu interativo.

---

## Funcionalidades

- Inicialização de territórios com cores e tropas aleatórias
- Distribuição de missões para os jogadores
- Menu interativo com opções:
  - Atacar territórios
  - Verificar missão
  - Sair do jogo
- Sistema de combate baseado em rolagem de dados
- Verificação automática de conclusão da missão

---

## Estrutura do Código

### Arquivos
- `main.c` - arquivo principal com todas as funções

### Funções principais

- `territoriosFixos(Territorio *territorios)`  
  Inicializa os territórios com nome, cor e número de tropas aleatório.

- `mostrarMapa(Territorio *territorios)`  
  Exibe todos os territórios no mapa com o nome, cor e tropas.

- `entregarMissao(char **missao, char **jogador)`  
  Atribui uma missão aleatória para o jogador, garantindo que não seja eliminar seu próprio exército.

- `mostrarMenu(char *missao, char *jogador)`  
  Mostra o menu de ações disponíveis para o jogador.

- `rolarDados()`  
  Gera um valor aleatório de 1 a 6 simulando a rolagem de um dado.

- `atacar(Territorio *territorios)`  
  Permite atacar outro território, calculando o resultado do combate.

- `verificarMissao(Territorio *territorios, char *missao)`  
  Verifica se a missão do jogador foi concluída.

- `mostrarMissao(Territorio *territorios, char* minhaMissao)`  
  Exibe o status da missão (cumprida ou não).

---

## Como Compilar e Rodar

1. Abra o terminal na pasta do projeto.
2. Compile com `gcc main.c -o jogo`.
3. Execute com `./jogo` (Linux/Mac) ou `jogo.exe` (Windows).

---

## Dependências

- Compilador C (GCC recomendado)
- Biblioteca padrão de C (`stdio.h`, `stdlib.h`, `string.h`, `time.h`)

---

## Observações

- Cada território começa com 1 a 5 tropas aleatórias.
- A missão é concluída quando todos os territórios do exército alvo são eliminados.
- O menu é interativo e continua até o jogador decidir sair.

---

## Autor

**Jonathan** - Código criado como projeto pessoal de jogo de estratégia em C.
