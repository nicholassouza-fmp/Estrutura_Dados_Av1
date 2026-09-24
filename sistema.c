#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_NOME             50
#define CAPACIDADE_INICIAL    5
#define MEDIA_APROVACAO     7.0f

char  (*nomes)[TAM_NOME] = NULL;
float *notas             = NULL;
int    totalAlunos       = 0;
int    capacidadeAtual   = 0;

void exibirMenu(void);
void cadastrarAluno(char (**nomesPtr)[TAM_NOME], float **notasPtr, int *total, int *capacidade);
void calcularMediaTurma(float notasArr[], int total);
void exibirExtremosNotas(char nomesArr[][TAM_NOME], float notasArr[], int total);
void exibirAlunos(char nomesArr[][TAM_NOME], float notasArr[], int total);
void listarAprovados(char nomesArr[][TAM_NOME], float notasArr[], int total);
float somaRecursiva(float notasArr[], int total);
int contarAprovadosRecursivo(float notasArr[], int total);
void exibirEstatisticasRecursivas(float notasArr[], int total);
void limparBufferEntrada(void);
void liberarMemoria(char (**nomesPtr)[TAM_NOME], float **notasPtr);
int lerInteiro(const char *mensagem, int *valor);
int lerFloat(const char *mensagem, float *valor);


int   validarNota(float nota);
int   buscarAlunoSequencial(char nomesArr[][TAM_NOME], int total, const char *nomeBusca);
void  buscarAlunoPorNome(char nomesArr[][TAM_NOME], float notasArr[], int total);
float calcularPercentualAprovacao(int aprovados, int total);
int   contarAcimaDaMedia(float notasArr[], int total, float media);
int   somaDigitosRecursivo(int n);
void  exibirInvertidoRecursivo(char nomesArr[][TAM_NOME], float notasArr[], int indice);
void  submenuExtras(char nomesArr[][TAM_NOME], float notasArr[], int total);

void exibirMenu(void) {
    printf("\n ========== SISTEMA DE GESTAO DE NOTAS ==========\n");
    printf("1 - Cadastro de alunos e notas\n");
    printf("2 - Lista de alunos e notas\n");
    printf("3 - Calcular a media geral da turma\n");
    printf("4 - Maior e menor nota registrada\n");
    printf("5 - Alunos aprovados\n");
    printf("6 - Estatisticas recursivas\n");
    printf("7 - Funcionalidades extras\n");
    printf("0 - Encerrar sistema\n");
}

void cadastrarAluno(char (**nomesPtr)[TAM_NOME], float **notasPtr, int *total, int *capacidade) {

    if (*total >= *capacidade) {
        int novaCapacidade = (*capacidade == 0) ? CAPACIDADE_INICIAL : (*capacidade * 2);

        char (*novoNomes)[TAM_NOME] = realloc(*nomesPtr, (size_t)novaCapacidade * sizeof(char[TAM_NOME]));
        float *novoNotas            = realloc(*notasPtr, (size_t)novaCapacidade * sizeof(float));

        if (novoNomes == NULL || novoNotas == NULL) {
            printf("\nErro: memoria insuficiente para expandir o cadastro!\n\n");
            return;
        }

        *nomesPtr   = novoNomes;
        *notasPtr   = novoNotas;
        *capacidade = novaCapacidade;
    }

    limparBufferEntrada();

    printf("\n === Cadastro de Alunos e Notas ===\n");
    do {
        int nomeValido = 1;
        int possuiLetra = 0;

        printf("Nome do aluno: ");

        if (fgets((*nomesPtr)[*total], TAM_NOME, stdin) == NULL) {
            printf("Entrada invalida. Digite o nome novamente.\n");
            continue;
        }

        (*nomesPtr)[*total][strcspn((*nomesPtr)[*total], "\n")] = '\0';

        for (int i = 0; (*nomesPtr)[*total][i] != '\0'; i++) {
            unsigned char caractere = (unsigned char)(*nomesPtr)[*total][i];

            if (isalpha(caractere)) {
                possuiLetra = 1;
            } else if (caractere != ' ') {
                nomeValido = 0;
                break;
            }
        }

        if (!nomeValido || !possuiLetra) {
            printf("Nome invalido. Digite somente letras e espacos.\n");
        } else {
            break;
        }
    } while (1);

    float notaDigitada;

    while (1) {
        if (!lerFloat("Nota (0.0 a 10.0): ", &notaDigitada)) {
            continue;
        }

        if (!validarNota(notaDigitada)) {
            printf("Nota fora do intervalo permitido.\n");
            continue;
        }

        break;
    }

    (*notasPtr)[*total] = notaDigitada;
    (*total)++;

    printf("Aluno cadastrado com sucesso! (%d cadastrados)\n\n", *total);
}

void calcularMediaTurma(float notasArr[], int total) {
    if (total == 0) {
        return; 
    }

    float soma = 0.0f;
    for (int i = 0; i < total; i++) {
        soma += notasArr[i];
    }
    float media = soma / total;

    printf("\nMEDIA DA TURMA: %.2f \n", media);
}

void exibirExtremosNotas(char nomesArr[][TAM_NOME], float notasArr[], int total) {
    if (total == 0) {
        return;
    }

    int indiceMaior = 0;
    int indiceMenor = 0;

    for (int i = 1; i < total; i++) {
        if (notasArr[i] > notasArr[indiceMaior]) {
            indiceMaior = i;
        }
        if (notasArr[i] < notasArr[indiceMenor]) {
            indiceMenor = i;
        }
    }

    printf("Maior nota: %.2f (Aluno: %s)\n", notasArr[indiceMaior], nomesArr[indiceMaior]);
    printf("Menor nota: %.2f (Aluno: %s)\n", notasArr[indiceMenor], nomesArr[indiceMenor]);
}

void exibirAlunos(char nomesArr[][TAM_NOME], float notasArr[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    printf("\n=== LISTAGEM GERAL DE ALUNOS ===\n");
    for (int i = 0; i < total; i++) {
        printf("%d. Aluno: %-20s | Nota: %.1f\n", i + 1, nomesArr[i], notasArr[i]);
    }
}


void listarAprovados(char nomesArr[][TAM_NOME], float notasArr[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    int aprovados = 0;
    printf("\n=== ALUNOS APROVADOS (Nota >= 7.0) ===\n");
    for (int i = 0; i < total; i++) {
        if (notasArr[i] >= 7.0f) {
            printf("- Aluno: %-20s | Nota: %.1f\n", nomesArr[i], notasArr[i]);
            aprovados++;
        }
    }

    printf("----------------------------------------\n");
    printf("Total de discentes aprovados: %d\n", aprovados);
}


float somaRecursiva(float notasArr[], int total) {
    if (total == 0) {
        return 0.0f; /* caso base */
    }
    return notasArr[total - 1] + somaRecursiva(notasArr, total - 1);
}

int contarAprovadosRecursivo(float notasArr[], int total) {
    if (total == 0) {
        return 0; /* caso base */
    }

    int aprovadoAtual;
    if (notasArr[total - 1] >= MEDIA_APROVACAO) {
        aprovadoAtual = 1;
    } else {
        aprovadoAtual = 0;
    }
    return aprovadoAtual + contarAprovadosRecursivo(notasArr, total - 1);
}

void exibirEstatisticasRecursivas(float notasArr[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    float soma      = somaRecursiva(notasArr, total);
    float media     = soma / total;
    int   aprovados = contarAprovadosRecursivo(notasArr, total);

    printf("\n=== ESTATISTICAS RECURSIVAS ===\n");
    printf("Soma total das notas : %.1f\n", soma);
    printf("Media da turma        : %.2f\n", media);
    printf("Total de aprovados    : %d\n", aprovados);
}


int validarNota(float nota) {
    return (nota >= 0.0f && nota <= 10.0f);
}

int buscarAlunoSequencial(char nomesArr[][TAM_NOME], int total, const char *nomeBusca) {
    for (int i = 0; i < total; i++) {
        if (strcmp(nomesArr[i], nomeBusca) == 0) {
            return i;
        }
    }
    return -1;
}

void buscarAlunoPorNome(char nomesArr[][TAM_NOME], float notasArr[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    limparBufferEntrada();
    printf("\nDigite o nome do aluno a buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = buscarAlunoSequencial(nomesArr, total, nomeBusca);
    if (pos >= 0) {
        printf("Aluno encontrado na posicao %d - Nota: %.2f\n", pos + 1, notasArr[pos]);
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

float calcularPercentualAprovacao(int aprovados, int total) {
    if (total == 0) {
        return 0.0f;
    }
    return ((float) aprovados / total) * 100.0f;
}

int contarAcimaDaMedia(float notasArr[], int total, float media) {
    int count = 0;
    for (int i = 0; i < total; i++) {
        if (notasArr[i] > media) {
            count++;
        }
    }
    return count;
}
void exibirEstatisticasComplementares(float notasArr[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    float soma = 0.0f;
    for (int i = 0; i < total; i++) {
        soma += notasArr[i];
    }
    float media = soma / total;

    int aprovados = contarAprovadosRecursivo(notasArr, total);
    float percentual = calcularPercentualAprovacao(aprovados, total);
    int acimaDaMedia = contarAcimaDaMedia(notasArr, total, media);

    printf("\n=== ESTATISTICAS COMPLEMENTARES ===\n");
    printf("Percentual de aprovacao : %.2f%%\n", percentual);
    printf("Alunos acima da media (%.2f): %d\n", media, acimaDaMedia);
}


int somaDigitosRecursivo(int n) {
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
        return 0;
    }
    return (n % 10) + somaDigitosRecursivo(n / 10);
}

void calcularSomaDigitos(void) {
    int numero;

    while (!lerInteiro("\nDigite um numero inteiro: ", &numero)) {
    }

    printf("Soma dos digitos: %d\n", somaDigitosRecursivo(numero));
}

void exibirInvertidoRecursivo(char nomesArr[][TAM_NOME], float notasArr[], int indice) {
    if (indice < 0) {
        return;
    }
    printf("- Aluno: %-20s | Nota: %.1f\n", nomesArr[indice], notasArr[indice]);
    exibirInvertidoRecursivo(nomesArr, notasArr, indice - 1);
}

void exibirListagemInvertida(char nomesArr[][TAM_NOME], float notasArr[], int total) {
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }
    printf("\n=== LISTAGEM INVERTIDA (RECURSIVA) ===\n");
    exibirInvertidoRecursivo(nomesArr, notasArr, total - 1);
}

void submenuExtras(char nomesArr[][TAM_NOME], float notasArr[], int total) {
    int opcaoExtra = -1;

    do {
        printf("\n----- Submenu de Extras -----\n");
        printf("1 - Buscar aluno por nome (busca sequencial)\n");
        printf("2 - Estatisticas complementares (%% aprovacao / acima da media)\n");
        printf("3 - Soma dos digitos de um numero (recursivo)\n");
        printf("4 - Exibir listagem invertida (recursivo)\n");
        printf("0 - Voltar ao menu principal\n");

        if (!lerInteiro("Escolha uma opcao: ", &opcaoExtra)) {
            continue;
        }

        switch (opcaoExtra) {
            case 1:
                buscarAlunoPorNome(nomesArr, notasArr, total);
                break;
            case 2:
                exibirEstatisticasComplementares(notasArr, total);
                break;
            case 3:
                calcularSomaDigitos();
                break;
            case 4:
                exibirListagemInvertida(nomesArr, notasArr, total);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Digite um valor entre 0 e 4.\n");
        }
    } while (opcaoExtra != 0);
}


void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\\n' && c != EOF) {
    }
}

int lerInteiro(const char *mensagem, int *valor) {
    char linha[100];
    char extra;

    printf("%s", mensagem);

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        printf("\nEntrada invalida. Digite novamente.\n");
        return 0;
    }

    if (sscanf(linha, " %d %c", valor, &extra) != 1) {
        printf("Valor invalido. Digite um numero inteiro.\n");
        return 0;
    }

    return 1;
}

int lerFloat(const char *mensagem, float *valor) {
    char linha[100];
    char extra;

    printf("%s", mensagem);

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        printf("\nEntrada invalida. Digite novamente.\n");
        return 0;
    }

    if (sscanf(linha, " %f %c", valor, &extra) != 1) {
        printf("Valor invalido. Digite um numero.\n");
        return 0;
    }

    return 1;
}


void liberarMemoria(char (**nomesPtr)[TAM_NOME], float **notasPtr) {
    free(*nomesPtr);
    free(*notasPtr);
    *nomesPtr = NULL;
    *notasPtr = NULL;
}

int main(void) {
    int opcao = -1;

    do {
        exibirMenu();

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarAluno(&nomes, &notas, &totalAlunos, &capacidadeAtual);
                break;
            case 2:
                exibirAlunos(nomes, notas, totalAlunos);
                break;
            case 3:
                calcularMediaTurma(notas, totalAlunos);
                break;
            case 4:
                exibirExtremosNotas(nomes, notas, totalAlunos);
                break;
            case 5:
                listarAprovados(nomes, notas, totalAlunos);
                break;
            case 6:
                exibirEstatisticasRecursivas(notas, totalAlunos);
                break;
            case 7:
                submenuExtras(nomes, notas, totalAlunos);
                break;
            case 0:
                printf("\nSistema Encerrado!\n");
                break;
            default:
                printf("Opcao invalida. Digite um valor entre 0 e 7.\n");
        }
    } while (opcao != 0);

    liberarMemoria(&nomes, &notas);
    return 0;
}
