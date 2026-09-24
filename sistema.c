#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void exibirMenu(void) {
    printf("\n ========== SISTEMA DE GESTAO DE NOTAS ==========\n");
    printf("1 - Cadastro de alunos e notas\n");
    printf("2 - Lista de alunos e notas\n");
    printf("3 - Calcular a media geral da turma\n");
    printf("4 - Maior e menor nota registrada\n");
    printf("5 - Alunos aprovados\n");
    printf("6 - Estatisticas recursivas\n");
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
    printf("Nome do aluno: ");
    fgets((*nomesPtr)[*total], TAM_NOME, stdin);
    (*nomesPtr)[*total][strcspn((*nomesPtr)[*total], "\n")] = '\0';

    float notaDigitada;
    int notaValida = 0;

    do {
        printf("Nota (0.0 a 10.0): ");
        if (scanf("%f", &notaDigitada) != 1) {
            printf("Valor invalido. Digite um numero.\n");
            limparBufferEntrada();
            continue;
        }
        if (notaDigitada < 0.0f || notaDigitada > 10.0f) {
            printf("Nota fora do intervalo permitido.\n");
        } else {
            notaValida = 1;
        }
    } while (!notaValida);

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

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void liberarMemoria(char (**nomesPtr)[TAM_NOME], float **notasPtr) {
    free(*nomesPtr);
    free(*notasPtr);
    *nomesPtr = NULL;
    *notasPtr = NULL;
}

int main(void) {
    int opcao = -1;

    while (opcao != 0) {
        exibirMenu();
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida. Digite um numero.\n");
            limparBufferEntrada();
            opcao = -1;
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
            case 0:
                printf("\nSistema Encerrado!\n");
                break;
            default:
                break;
        }
    }

    liberarMemoria(&nomes, &notas);
    return 0;
}