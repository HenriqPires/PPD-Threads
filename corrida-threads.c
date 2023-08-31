#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <stdatomic.h>
#include <time.h>

// Função que gera um número aleatório entre 1 e 5
int gerarNumeroAleatorio() {
    return (rand() % 5) + 1;
}

// Função que simula a corrida da thread
int realizarCorrida(void* arg) {
    int idDaThread = *(int*)arg;
    int posicaoAtual = 0;
    int totalPassos = 0;

    printf("Thread %d - Iniciando\n", idDaThread);

    while (posicaoAtual < 50) {
        int passos = gerarNumeroAleatorio();
        totalPassos += passos;
        posicaoAtual += passos;

        printf("Vez da Thread %d\n", idDaThread);
        printf("Número sorteado: %d\n", passos);
        printf("Thread %d Andou %d casas\n", idDaThread, passos);
        printf("Posição atual da Thread %d: %d\n", idDaThread, posicaoAtual);

        thrd_sleep(&(struct timespec){1, 0}, NULL); //Aguardar 1 segundo
    }

    printf("Thread %d - Chegou à posição 50! Total de passos: %d\n", idDaThread, totalPassos);

    return totalPassos;
}

int main() {
    srand(time(NULL));

    const int numThreads = 2;
    thrd_t threads[numThreads];
    int threadArgs[numThreads];
    int resultados[numThreads];
    int threadsFinalizadas = 0;

    for (int i = 0; i < numThreads; i++) {
        threadArgs[i] = i + 1;
        thrd_create(&threads[i], (int (*)(void*))realizarCorrida, &threadArgs[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        thrd_join(threads[i], &resultados[i]);
        printf("Thread secundária %d finalizada.\n", i + 1);
    }

    int indiceVencedor = 0;
    for (int i = 1; i < numThreads; i++) {
        if (resultados[i] < resultados[indiceVencedor]) {
            indiceVencedor = i;
        }
    }

    printf("A thread %d venceu com %d passos!\n", indiceVencedor + 1, resultados[indiceVencedor]);

    return 0;
}
