#include <stdio.h>

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

/*---------------------------------------------------------
  Vetor global compartilhado por todas as funções.
---------------------------------------------------------*/
int estoque[TAMANHO_ESTOQUE];

/* Protótipos */
void exibirCabecalho(void);
void preencherEstoque(void);
void exibirEstoque(int momento);
float calcularMediaEstoque(void);
void simularReposicao(int quantidadeAtual, int reposicao);
void aplicarReposicaoGeral(int reposicao);
void identificarEstoqueCritico(int minimo);

int main(void)
{
    int reposicao;
    float media;

    exibirCabecalho();

    preencherEstoque();

    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &reposicao);

    exibirEstoque(0);

    printf("-- Simulacao de reposicao (passagem por valor) --\n");

    simularReposicao(estoque[0], reposicao);

    printf(
        "Quantidade do produto 1 apos a simulacao "
        "(inalterada): %d\n",
        estoque[0]
    );

    printf(
        "-- Aplicacao real da reposicao "
        "(ponteiro interno ao vetor global) --\n"
    );

    aplicarReposicaoGeral(reposicao);

    printf(
        "Reposicao de %d unidades aplicada a todos "
        "os produtos do estoque.\n",
        reposicao
    );

    exibirEstoque(1);

    media = calcularMediaEstoque();

    printf("-- Media geral do estoque --\n");
    printf("Media final: %.2f unidades\n", media);

    printf(
        "-- Analise de estoque critico "
        "(minimo = %d unidades) --\n",
        ESTOQUE_MINIMO
    );

    identificarEstoqueCritico(ESTOQUE_MINIMO);

    return 0;
}

/*---------------------------------------------------------
  Exibe o cabecalho do sistema.
---------------------------------------------------------*/
void exibirCabecalho(void)
{
    printf("=================================\n");
    printf("SISTEMA DE ESTOQUE - LOJA CONSTRUMAIS\n");
    printf("=================================\n");
}

/*---------------------------------------------------------
  Le as quantidades dos produtos utilizando ponteiros.
---------------------------------------------------------*/
void preencherEstoque(void)
{
    int *p = estoque;
    int i;

    for (i = 0; i < TAMANHO_ESTOQUE; i++)
    {
        printf("Quantidade do produto %d: ", i + 1);
        scanf("%d", (p + i));
    }
}

/*---------------------------------------------------------
  Exibe o estoque atual ou final conforme o parametro.
---------------------------------------------------------*/
void exibirEstoque(int momento)
{
    int *p = estoque;
    int i;

    if (momento == 0)
    {
        printf("-- Estoque atual (antes da reposicao) --\n");
    }
    else
    {
        printf("-- Estoque final (apos reposicao) --\n");
    }

    for (i = 0; i < TAMANHO_ESTOQUE; i++)
    {
        printf(
            "Produto %d: %d unidades\n",
            i + 1,
            *(p + i)
        );
    }
}

/*---------------------------------------------------------
  Calcula a media das quantidades em estoque.
---------------------------------------------------------*/
float calcularMediaEstoque(void)
{
    int *p = estoque;
    int i;
    int soma = 0;

    for (i = 0; i < TAMANHO_ESTOQUE; i++)
    {
        /*
        p + i  -> endereco do elemento i.

        *(p + i) -> valor armazenado no endereco
        apontado por p + i.
        */
        soma += *(p + i);
    }

    return (float)soma / TAMANHO_ESTOQUE;
}

/*---------------------------------------------------------
  Demonstra passagem por valor.
---------------------------------------------------------*/
void simularReposicao(int quantidadeAtual, int reposicao)
{
    int resultado;

    resultado = quantidadeAtual + reposicao;

    printf(
        "Simulacao para o produto 1: %d + %d = %d "
        "(nao aplicado ainda)\n",
        quantidadeAtual,
        reposicao,
        resultado
    );
}

/*---------------------------------------------------------
  Aplica a reposicao ao vetor global.
---------------------------------------------------------*/
void aplicarReposicaoGeral(int reposicao)
{
    int *p = estoque;
    int i;

    for (i = 0; i < TAMANHO_ESTOQUE; i++)
    {
        *(p + i) += reposicao;
    }
}

/*---------------------------------------------------------
  Identifica produtos abaixo do estoque minimo.
---------------------------------------------------------*/
void identificarEstoqueCritico(int minimo)
{
    int *p = estoque;
    int i;
    int encontrouCritico = 0;

    for (i = 0; i < TAMANHO_ESTOQUE; i++)
    {
        if (*(p + i) < minimo)
        {
            printf(
                "Produto %d esta em nivel critico: "
                "%d unidades (abaixo do minimo)\n",
                i + 1,
                *(p + i)
            );

            encontrouCritico = 1;
        }
    }

    if (!encontrouCritico)
    {
        printf(
            "Estoque regularizado. "
            "Nenhum produto esta abaixo do minimo.\n"
        );
    }
}