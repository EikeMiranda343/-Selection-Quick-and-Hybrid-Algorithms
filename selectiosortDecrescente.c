#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void gerarDecrescente(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i;
    }
}


void selectionSort(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j;
            }
        }
        int temp = vetor[indiceMenor];
        vetor[indiceMenor] = vetor[i];
        vetor[i] = temp;
    }
}

double calcularModa(double tempos[], int n) {
    int maxContagem = 0;
    double moda = tempos[0];

    for (int i = 0; i < n; i++) {
        int contagem = 0;
        for (int j = 0; j < n; j++) {
            if (tempos[j] == tempos[i]) {
                contagem++;
            }
        }
        if (contagem > maxContagem) {
            maxContagem = contagem;
            moda = tempos[i];
        }
    }
    return moda;
}

// Função para exportar os resultados para um arquivo CSV
void exportarResultadosParaCSV(const char *nomeArquivo, double tempos[], int n, double minimo, double maximo, double media, double moda, double desvio, double tempoTotal) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo CSV.\n");
        return;
    }

    // Escrevendo os tempos de execução
    fprintf(arquivo, "Repeticao,Tempo (s)\n");
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d,%.6f\n", i + 1, tempos[i]);
    }

    // Escrevendo as estatísticas globais
    fprintf(arquivo, "\nEstatistica,Valor (s)\n");
    fprintf(arquivo, "Tempo minimo,%.6f\n", minimo);
    fprintf(arquivo, "Tempo maximo,%.6f\n", maximo);
    fprintf(arquivo, "Tempo medio,%.6f\n", media);
    fprintf(arquivo, "Moda,%.6f\n", moda);
    fprintf(arquivo, "Desvio padrao,%.6f\n", desvio);
    fprintf(arquivo, "Tempo total de execucao,%.6f\n", tempoTotal);

    fclose(arquivo);
}

int main() {
    const int TAMANHO = 100000; 
    const int REPETICOES = 100; 
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    double tempos[REPETICOES];

    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    clock_t inicioTotal = clock(); 


    for (int i = 0; i < REPETICOES; i++) {
        gerarDecrescente(vetor, TAMANHO);
        clock_t inicio = clock();
        selectionSort(vetor, TAMANHO);
        clock_t fim = clock();
        tempos[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
    }

    double soma = 0, somaQuadrados = 0, minimo = tempos[0], maximo = tempos[0];
    for (int i = 0; i < REPETICOES; i++) {
        soma += tempos[i];
        somaQuadrados += tempos[i] * tempos[i];
        if (tempos[i] < minimo) minimo = tempos[i];
        if (tempos[i] > maximo) maximo = tempos[i];
    }
    double media = soma / REPETICOES;
    double variancia = (somaQuadrados / REPETICOES) - (media * media);
    double desvio = sqrt(variancia);
    double moda = calcularModa(tempos, REPETICOES);

    clock_t fimTotal = clock();
    double tempoTotal = (double)(fimTotal - inicioTotal) / CLOCKS_PER_SEC;

    printf("Selection Sort - Ordem Decrescente:\n");
    printf("Tempo mínimo: %.6f segundos\n", minimo);
    printf("Tempo máximo: %.6f segundos\n", maximo);
    printf("Tempo médio: %.6f segundos\n", media);
    printf("Moda: %.6f segundos\n", moda);
    printf("Desvio padrão: %.6f segundos\n", desvio);
    printf("Tempo total de execução: %.6f segundos\n", tempoTotal);

    // Exportando para CSV
    exportarResultadosParaCSV("selection_sort_decrescente.csv", tempos, REPETICOES, minimo, maximo, media, moda, desvio, tempoTotal);

    free(vetor);
    return 0;
}
