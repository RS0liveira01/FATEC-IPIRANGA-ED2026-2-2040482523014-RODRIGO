/* --------------------------------------------------------*
 * Disciplina : Estrutura de Dados                         *
 * Prof. Verissimo                                         *
 *---------------------------------------------------------*
 * Objetivo do Programa : Controlar os atendimentos de     *
 * um lava-rapido utilizando alocacao dinamica e recursao. *
 * Data - 30/08/2026                                       *
 * Autor : Rodrigo Santos                                  *
 *---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_PREMIUM 100.0

typedef struct
{
    char placa[8];
    float valor;
} Veiculo;

void exibirCabecalho(void);
void preencherFrota(Veiculo *frota, int quantidade);
void exibirFrotaRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade
);
float calcularValorTotalRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade
);
int buscarVeiculoRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade,
    char placa[8]
);
int contarPremiumRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade
);

int main(void)
{
    int quantidade;
    int posicao;
    int premium;
    float valorTotal;

    char placaBusca[8];

    Veiculo *frota;

    exibirCabecalho();

    printf("Quantos veiculos serao atendidos hoje? ");
    scanf("%d", &quantidade);

    frota = (Veiculo *)malloc(
        quantidade * sizeof(Veiculo)
    );

    /* Verificacao obrigatoria do malloc */
    if (frota == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    preencherFrota(
        frota,
        quantidade
    );

    printf(
        "--- Veiculos atendidos hoje ---\n"
    );

    exibirFrotaRecursivo(
        frota,
        0,
        quantidade
    );

    printf(
        "--- Busca recursiva por placa ---\n"
    );

    printf("Placa a ser pesquisada: ");
    scanf("%7s", placaBusca);

    posicao = buscarVeiculoRecursivo(
        frota,
        0,
        quantidade,
        placaBusca
    );

    if (posicao == -1)
    {
        printf(
            "Veiculo nao encontrado na frota.\n"
        );
    }
    else
    {
        printf(
            "Veiculo encontrado na posicao %d! "
            "Placa: %s | Valor: R$ %.2f\n",
            posicao + 1,
            frota[posicao].placa,
            frota[posicao].valor
        );
    }

    valorTotal =
        calcularValorTotalRecursivo(
            frota,
            0,
            quantidade
        );

    premium =
        contarPremiumRecursivo(
            frota,
            0,
            quantidade
        );

    printf(
        "--- Resumo do dia ---\n"
    );

    printf(
        "Total de veiculos atendidos: %d\n",
        quantidade
    );

    printf(
        "Servicos premium (>= R$ %.2f): %d\n",
        VALOR_PREMIUM,
        premium
    );

    printf(
        "Valor total arrecadado: R$ %.2f\n",
        valorTotal
    );

    free(frota);

    frota = NULL;

    printf(
        "Memoria da frota liberada com sucesso. "
        "Sistema encerrado.\n"
    );

    return 0;
}

void exibirCabecalho(void)
{
    printf(
        "=================================\n"
    );

    printf(
        "LAVA-RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n"
    );

    printf(
        "=================================\n"
    );
}

void preencherFrota(
    Veiculo *frota,
    int quantidade
)
{
    int i;

    for (i = 0; i < quantidade; i++)
    {
        printf(
            "Placa do veiculo %d: ",
            i + 1
        );

        scanf(
            "%7s",
            (frota + i)->placa
        );

        printf(
            "Valor do servico (R$): "
        );

        scanf(
            "%f",
            &((frota + i)->valor)
        );
    }
}

void exibirFrotaRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade
)
{
    if (indice == quantidade)
    {
        return;
    }

    printf(
        "%d) Placa: %s | Valor: R$ %.2f\n",
        indice + 1,
        (frota + indice)->placa,
        (frota + indice)->valor
    );

    exibirFrotaRecursivo(
        frota,
        indice + 1,
        quantidade
    );
}

float calcularValorTotalRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade
)
{
    /*
       Caso base:
       quando indice == quantidade,
       todos os elementos foram processados.
    */
    if (indice == quantidade)
    {
        return 0.0f;
    }

    /*
       Passo recursivo:
       soma o valor atual ao resultado
       da chamada para o proximo indice.
    */
    return
        (frota + indice)->valor +
        calcularValorTotalRecursivo(
            frota,
            indice + 1,
            quantidade
        );
}

int buscarVeiculoRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade,
    char placa[8]
)
{
    if (indice == quantidade)
    {
        return -1;
    }

    if (
        strcmp(
            (frota + indice)->placa,
            placa
        ) == 0
       )
    {
        return indice;
    }

    return buscarVeiculoRecursivo(
        frota,
        indice + 1,
        quantidade,
        placa
    );
}

int contarPremiumRecursivo(
    Veiculo *frota,
    int indice,
    int quantidade
)
{
    if (indice == quantidade)
    {
        return 0;
    }

    if (
        (frota + indice)->valor >=
        VALOR_PREMIUM
       )
    {
        return 1 +
               contarPremiumRecursivo(
                   frota,
                   indice + 1,
                   quantidade
               );
    }

    return contarPremiumRecursivo(
        frota,
        indice + 1,
        quantidade
    );
}