#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 50

// Função que verifica se uma página da Wikipedia existe
void* verificarPaginaWikiExistente(void* url) {
    char* paginaUrl = (char*)url;
    char resultado[1024];
    strcpy(resultado, paginaUrl);

    // Simulação de verificação da existência da página
    
    if (rand() % 2 == 0) {
        strcat(resultado, " - Existe");
    } else {
        strcat(resultado, " - Não existe");
    }

    pthread_exit((void*)strdup(resultado));
}

int main() {
    pthread_t threads[NUM_THREADS];
    char* wikiPageUrls[NUM_THREADS];

    srand(time(NULL));

    printf("Executando com threads:\n");

    for (int i = 0; i < NUM_THREADS; i++) {
        wikiPageUrls[i] = (char*)malloc(256);
        snprintf(wikiPageUrls[i], 256, "https://en.wikipedia.org/wiki/%d", i + 1);
        int rc = pthread_create(&threads[i], NULL, verificarPaginaWikiExistente, (void*)wikiPageUrls[i]);
        if (rc) {
            printf("Erro ao criar a Thread %d; código de erro: %d\n", i + 1, rc);
            exit(-1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        void* result;
        pthread_join(threads[i], &result);
        printf("%s\n", (char*)result);
        free(result);
        free(wikiPageUrls[i]);
        printf("Thread principal aguardando Thread %d terminar\n", i + 1);
    }

    pthread_exit(NULL);
}
