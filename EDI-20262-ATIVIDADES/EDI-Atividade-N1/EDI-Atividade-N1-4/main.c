#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int id;
    char nome[50];
    struct no *prox;
} No;
typedef No *NoPtr;

typedef struct {
    NoPtr ini;
    NoPtr fim;
} Cabecalho;
typedef Cabecalho *Fila;

Fila Criar() {
    Fila f = (Fila)malloc(sizeof(Cabecalho));
    if (f != NULL) {
        f->ini = NULL;
        f->fim = NULL;
    }
    return f;
}

// 1. Verificacao de Fila Vazia
int vazia(Fila f) {
    return (f == NULL || f->ini == NULL);
}

int inserir(Fila f, int id, const char *nome) {
    NoPtr novo = (NoPtr)malloc(sizeof(No));
    if (novo == NULL) return 0;
    
    novo->id = id;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->prox = NULL;
    
    if (vazia(f)) {
        f->ini = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    return 1;
}

void listarFila(Fila f) {
    if (vazia(f)) {
        printf("\n[AVISO] A fila esta vazia.\n");
        return;
    }
    NoPtr atual = f->ini;
    printf("\n=== FILA DE PACIENTES ===\n");
    while (atual != NULL) {
        printf("ID: %d - Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("=========================\n");
}

// 2. Atendimento do Paciente (Dequeue)
void atender(Fila f) {
    if (vazia(f)) {
        printf("\n[AVISO] Fila vazia! Nenhum paciente aguardando.\n");
        return;
    }
    NoPtr removido = f->ini;
    printf("\n>> ATENDIMENTO: Paciente ID %d - Nome: %s\n", removido->id, removido->nome);
    
    f->ini = removido->prox;
    // Se a fila ficar vazia apos a remocao, atualiza o 'fim'
    if (f->ini == NULL) {
        f->fim = NULL; 
    }
    free(removido);
}

// 3. Consulta do Proximo (Peek)
void proximo(Fila f) {
    if (vazia(f)) {
        printf("\n[AVISO] A fila esta vazia.\n");
        return;
    }
    printf("\n>> PROXIMO DA FILA: ID %d - Nome: %s\n", f->ini->id, f->ini->nome);
}

// 4. Tamanho da Fila
int tamanho(Fila f) {
    int cont = 0;
    NoPtr atual = f->ini;
    while (atual != NULL) {
        cont++;
        atual = atual->prox;
    }
    return cont;
}

// 5. Destruir e Desalocar a Fila
void destruir(Fila f) {
    if (f != NULL) {
        NoPtr atual = f->ini;
        while (atual != NULL) {
            NoPtr temp = atual->prox;
            free(atual); // Libera cada nó
            atual = temp;
        }
        free(f); // Libera o cabeçalho
        printf("\n>> Memoria da fila liberada com sucesso.\n");
    }
}

int main() {
    Fila filaAtendimento = Criar();
    int opcao, id;
    char nome[50];

    do {
        printf("\n--- SISTEMA HOSPITALAR (FATEC IPIRANGA) ---\n");
        printf("1. Chegada de Paciente (Inserir)\n");
        printf("2. Listar Fila\n");
        printf("3. Atender Paciente (Remover)\n");
        printf("4. Consultar Proximo\n");
        printf("5. Ver Tamanho da Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Informe o ID do paciente: ");
                scanf("%d", &id);
                getchar(); // Limpar buffer do teclado
                printf("Informe o Nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; 
                if (inserir(filaAtendimento, id, nome)) {
                    printf(">> Paciente inserido com sucesso!\n");
                } else {
                    printf(">> Erro ao inserir paciente.\n");
                }
                break;
            case 2:
                listarFila(filaAtendimento);
                break;
            case 3:
                atender(filaAtendimento);
                break;
            case 4:
                proximo(filaAtendimento);
                break;
            case 5:
                printf("\n>> Pacientes aguardando: %d\n", tamanho(filaAtendimento));
                break;
            case 0:
                printf("\nEncerrando o sistema e limpando a memoria...\n");
                destruir(filaAtendimento);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
