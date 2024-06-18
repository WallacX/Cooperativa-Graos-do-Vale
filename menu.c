#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void wait ( int seconds ) //Apenas para deixar o programa com tempo regressivo, podemos fazer como tela de load
{
  clock_t endwait;
  endwait = clock () + seconds * CLK_TCK;
  while (clock() < endwait) {}
}//Função de tempo, apenas para deslogar o cmd.

int main()
{
    char nomeArquivo[200], dataRecebimento[200];
    int voltarPUm, voltarPDois, voltarPTres, voltarPQuatro, voltarPCinco, voltarPSeis, qnumero;
    voltarPSeis = 0;
    voltarPTres = 0;

    while (voltarPUm != 6)
    {

        voltarPUm = 0;
        voltarPDois = 0;
        system("cls");        
        printf(" _______________________________\n");
        printf("|       Escolha uma opcao:      |\n");
        printf("|-------------------------------|\n");
        printf("|     1 - Entrada de Dados      |\n");
        printf("|     2 - Banco de Dados        |\n");
        printf("|     3 - Saidas de Dados       |\n");
        printf("|     4 - Mostrar integrantes   |\n");
        printf("|     5 - Informacoes           |\n");
        printf("|     6 - Sair do programa      |\n");
        printf("|_______________________________|\n");
        printf("Escolha um opcao:               \n");
        scanf("%d", &voltarPUm);

        switch (voltarPUm)
        {

        case 1:

            system("cls");        
            printf(" _______________________________\n");
            printf("|            ENTRADA            |\n");
            printf("|-------------------------------|\n");
            printf("|Nome do Arquivo: ");
            fflush(stdin);
            scanf("%[^\n]", nomeArquivo);
            printf("|Data de recebimento: ");
            scanf("%s", &dataRecebimento);
            printf("|_______________________________|\n");
            printf("|            TESTE 1            |\n");
            printf("|            TESTE 1            |\n");
            printf("|            TESTE 1            |\n");
            printf("|            TESTE 1            |\n");
            printf("|            TESTE 1            |\n");
            printf("|_______________________________|\n");
            printf("|      Digite 5 para voltar     |\n");
            printf("|_______________________________|\n");
            scanf("%d", &voltarPDois);

            if(voltarPDois = 5){
                break;
            }

        case 2:
            system("cls");        
            printf(" _______________________________\n");
            printf("|            TESTE 2            |\n");
            printf("|-------------------------------|\n");
            printf("|            TESTE 2            |\n");
            printf("|            TESTE 2            |\n");
            printf("|            TESTE 2            |\n");
            printf("|            TESTE 2            |\n");
            printf("|            TESTE 2            |\n");
            printf("|            TESTE 2            |\n");
            printf("|            TESTE 2            |\n");
            printf("|_______________________________|\n");
            printf("|      Digite 5 para voltar     |\n");
            printf("|_______________________________|\n");
            scanf("%d",&voltarPTres);
            
            if(voltarPTres = 5){
                break;
            }

        case 3:
            system("cls");
            printf(" _______________________________\n");
            printf("|            TESTE 3            |\n");
            printf("|-------------------------------|\n");
            printf("|            TESTE 3            |\n");
            printf("|            TESTE 3            |\n");
            printf("|            TESTE 3            |\n");
            printf("|            TESTE 3            |\n");
            printf("|            TESTE 3            |\n");
            printf("|_______________________________|\n");            
            printf("|      Digite 5 para voltar     |\n");
            printf("|_______________________________|\n");
            scanf("%d",&voltarPQuatro);

            if(voltarPQuatro = 5){
                break;
            }

        case 4:

            system("cls");
            printf(" _______________________________\n");
            printf("|          INTEGRANTES          |\n");
            printf("|-------------------------------|\n");
            printf("|          Joao Marcelo         |\n");
            printf("|            Lucas E            |\n");
            printf("|         Tulio Amaral          |\n");
            printf("|           Vittor Hugo         |\n");
            printf("|         Wallace Elpidio       |\n");
            printf("|_______________________________|\n");            
            printf("|      Digite 5 para voltar     |\n");
            printf("|_______________________________|\n");
            scanf("%d", &voltarPCinco);

            if(voltarPCinco = 5){
                break;
            }

        case 5:

            system("cls");
            printf(" ________________________________\n");
            printf("|            INFORMACOES         |\n");
            printf("|--------------------------------|\n");
            printf("| 1- O programa mostra resultados|\n");
            printf("|apenas ate a segunda casa decimal|\n");
            printf("|              ------            |\n");
            printf("|2 - O nome de arquivos devem ser|\n");
            printf("|escritos sem espaco.            |\n");
            printf("|              ------            |\n");
            printf("|        5 - Para voltar         |\n");
            scanf("%d", &voltarPSeis);
            if(voltarPSeis = 5){
                break;
            }


        case 6:

            system("cls");
            printf("Obrigado por utilizar nossos servicos.\n");
            wait(1);
            printf("Saindo.\n");
            for (int x = 3; x > 0; x--)
            {

                printf("%d\n", x);
                wait(1);

            }

            break;

        default:
            break;
        }

    }
    


    return 0;
}
