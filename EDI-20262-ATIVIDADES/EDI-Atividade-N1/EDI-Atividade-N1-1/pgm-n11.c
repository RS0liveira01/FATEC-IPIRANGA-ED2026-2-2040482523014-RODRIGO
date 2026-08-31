#include <stdio.h>

#define TAMANHO_TURMA 5

/*---------------------------------------------------------
  Exibe o cabeçalho do sistema.
---------------------------------------------------------*/
void exibirCabecalho(void);

/*---------------------------------------------------------
  Recebe o vetor de notas e calcula a média.

  Em C, quando um vetor é passado para uma função,
  o que a função recebe é o endereço do primeiro
  elemento do vetor. Por isso alterações feitas
  nos elementos podem afetar o vetor original.
---------------------------------------------------------*/
float calcularMedia(float vetor[], int tamanho);

/*---------------------------------------------------------
  Demonstra passagem por valor.
---------------------------------------------------------*/
void simularAjuste(float notaOriginal, float bonus);

/*---------------------------------------------------------
  Demonstra passagem por referência através de ponteiro.
---------------------------------------------------------*/
void aplicarBonus(float *nota, float bonus);

int main(void)
{
    float notas[TAMANHO_TURMA];
    float bonus;
    float mediaInicial;
    float mediaFinal;
    int i;

    exibirCabecalho();

    for (i = 0; i < TAMANHO_TURMA; i++)
    {
        printf("Nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
    }

    printf("Informe o valor do bonus a aplicar: ");
    scanf("%f", &bonus);

    mediaInicial = calcularMedia(
        notas,
        TAMANHO_TURMA
    );

    printf("--- Media da turma antes do ajuste ---\n");
    printf("Media inicial: %.2f\n", mediaInicial);

    printf(
        "--- Simulacao do ajuste "
        "(passagem por valor) ---\n"
    );

    simularAjuste(
        notas[0],
        bonus
    );

    printf(
        "Nota do aluno 1 apos a simulacao "
        "(inalterada): %.2f\n",
        notas[0]
    );

    printf(
        "--- Aplicacao real do bonus "
        "(passagem por referencia) ---\n"
    );

    for (i = 0; i < TAMANHO_TURMA; i++)
    {
        aplicarBonus(
            &notas[i],
            bonus
        );
    }

    printf(
        "Bonus de %.2f aplicado a todas "
        "as notas da turma.\n",
        bonus
    );

    printf(
        "--- Notas finais da turma ---\n"
    );

    for (i = 0; i < TAMANHO_TURMA; i++)
    {
        printf(
            "Aluno %d: %.2f\n",
            i + 1,
            notas[i]
        );
    }

    mediaFinal = calcularMedia(
        notas,
        TAMANHO_TURMA
    );

    printf(
        "--- Media da turma apos o ajuste ---\n"
    );

    printf(
        "Media final: %.2f\n",
        mediaFinal
    );

    return 0;
}

/*---------------------------------------------------------
  Exibe o cabeçalho.
---------------------------------------------------------*/
void exibirCabecalho(void)
{
    printf("=================================\n");
    printf("SISTEMA DE NOTAS - TURMA ADS\n");
    printf("=================================\n");
}

/*---------------------------------------------------------
  Calcula a média das notas.
---------------------------------------------------------*/
float calcularMedia(float vetor[], int tamanho)
{
    float soma = 0.0f;
    int i;

    for (i = 0; i < tamanho; i++)
    {
        soma += vetor[i];
    }

    return soma / tamanho;
}

/*---------------------------------------------------------
  Passagem por valor.
---------------------------------------------------------*/
void simularAjuste(float notaOriginal, float bonus)
{
    float resultado;

    resultado = notaOriginal + bonus;

    printf(
        "Simulacao para o aluno 1: "
        "%.2f + %.2f = %.2f "
        "(nao aplicado ainda)\n",
        notaOriginal,
        bonus,
        resultado
    );
}

/*---------------------------------------------------------
  Passagem por referência.
---------------------------------------------------------*/
void aplicarBonus(float *nota, float bonus)
{
    *nota += bonus;
}