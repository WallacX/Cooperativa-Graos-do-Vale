#include <stdio.h>
#include <math.h>

int decimal_para_binario (int);
int binario_para_decimal (int);

int main ()
{
    printf ("Insira a opção de conversão: 1- Decimal para Binario; 2- Binario para Decimal\n");
    int opcao;
    scanf ("%d", &opcao);

    int numero_decimal;
    int numero_binario;

    switch (opcao)
    {
        case 1:
        {
            printf ("Insira o numero decimal para conversão\n");
            scanf ("%d", &numero_decimal);
            
            printf ("O numero decimal convertido para binario eh %d", decimal_para_binario (numero_decimal));
            break;
        }
        case 2:
        {
            printf ("Insira o numero binario para conversão\n");
            scanf ("%d", &numero_binario);
    
            printf ("O numero binario convertido para decimal eh %d", binario_para_decimal (numero_binario));
            break;
        }
        default:
        {
            printf ("Opcao invalida!");
            break;
        }
    }

    return 0;
}
int decimal_para_binario (int numero_decimal)
{
    int numero_binario = 0;
    int resto_divisao;
    int posicao = 1;

    while (numero_decimal != 0) {
        resto_divisao = numero_decimal % 2;
        numero_decimal /= 2;
        numero_binario += resto_divisao * posicao;
        posicao = posicao * 10;
    }
    
    return numero_binario;

}
int binario_para_decimal (int numero_binario)
{
    int numero_decimal = 0;
    int expoente = 0;
    int digito;

    while (numero_binario != 0) 
    {
        digito = (numero_binario % 10);
        numero_decimal += (digito * pow(2, expoente));
        numero_binario = (numero_binario / 10);
        expoente++;
    }

    return numero_decimal;
   
}