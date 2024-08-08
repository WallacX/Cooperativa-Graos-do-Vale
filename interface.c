#include "interface.h"
#include <stdio.h>

//Definição dos comandos para mudança de cor dos textos imprimidos
#define PDR "\033[0m"
#define PTR "\033[30m"
#define VRM "\033[31m"
#define VRD "\033[32m"
#define AMA "\033[33m"
#define AZL "\033[34m"
#define BRA "\033[37m"

void Cabecalho(int opcao, int mes){

  system("clear");
  printf(" __________________________________________________________________________________\n");
  printf("|UFG-BSI-IP (COOPERATIVA AGRICOLA GRAO_DO_VALE V1.0)                               |\n");
  printf("|ANO: 2024 ");
  if(opcao == 1)
      printf("Relatorio da Carga%-54s|\n","");
  else if(opcao == 2 && mes == 0)
      printf("Relatorio Mensal - Todos os Meses%-39s|\n", "");
  else if(opcao == 2 && mes != 0)
      printf("Relatorio Mensal - Mes: %02d %-45s|\n", mes, "");
  else if(opcao == 3)
      printf("Relatorio Geral%-57s|\n","");
  printf("|----------------------------------------------------------------------------------|");

}


void RelatorioCarga(int origem, int dia, int mes, float guc, float plimpo, int tipo, int f1cont, int faixa1[], int f2cont, int faixa2[], int f3cont, int faixa3[], int f4cont, int faixa4[], int qtdamostras){

  printf("\n|         Origem: "VRD"%d"PDR" \t\t Num. de amostras: "VRD"%d"PDR"\033[0m\t\tData: "VRD"%02d"PDR"/"VRD"%02d"PDR"/"VRD"24"PDR" %-12s|\n", origem, qtdamostras, dia, mes, "");
  printf("|         Umidade: "VRD"%.1f%%"PDR" \t Peso limpo: "VRD"%02.2f"PDR"\t\t\tTransgenico: "VRD"%-14d\033[0m|\n", guc, plimpo, tipo);
    printf("|%-82s|", "");

    //Impressão do relatório de carga de cada faixa
    int aux = 0;
    printf("\n|Umidade: Faixa 1 \t\t Quant.:"VRD" %-50d"PDR"|\n", f1cont);
    printf("|Ident. das Amostras:"AMA);

    for(int i =0; i< qtdamostras; i++){
        if(faixa1[i] != 0){

            if(faixa1[i] <= 9)
                aux+=2;
            else
                aux+=3;
            
            printf(" %d", faixa1[i]);
            if(faixa1[i+1] != 0){
                printf(",");
                aux++;
            }

        }
    }

    for(int i = 0; i <= 61 - aux; i++){
        printf(" ");
    }

    printf(PDR"|");
    printf("\n|%-82s|", "");

    
    
    printf("\n|Umidade: Faixa 2 \t\t Quant.:"VRD" %-50d"PDR"|\n", f2cont);
    printf("|Ident. das Amostras:"AMA);
    aux = 0;
    for(int i =0; i< qtdamostras; i++){
        if(faixa2[i] != 0){
            
            if(faixa2[i] <= 9)
                aux+=2;
            else
                aux+=3;
              
            printf(" %d", faixa2[i]);
            if(faixa2[i+1] != 0){
                printf(",");
                aux++;
            }
                
        }
    }

    for(int i = 0; i <= 61 - aux; i++){
        printf(" ");
    }

    printf(PDR"|");
    printf("\n|%-82s|", "");


    
    printf("\n|Umidade: Faixa 3 \t\t Quant.:"VRD" %-50d"PDR"|\n", f3cont);
    printf("|Ident. das Amostras:"AMA);
    aux = 0;
    for(int i =0; i< qtdamostras; i++){
        if(faixa3[i] != 0){

            if(faixa3[i] <= 9)
                aux+=2;
            else
                aux+=3;

            printf(" %d", faixa3[i]);
            if(faixa3[i+1] != 0){
                printf(",");
                aux++;
            }

        }
    }

    for(int i = 0; i <= 61 - aux; i++){
        printf(" ");
    }
    printf(PDR"|");
    printf("\n|%-82s|", "");


    
    printf("\n|Umidade: Faixa 4 \t\t Quant.:"VRD" %-50d"PDR"|\n", f4cont);
    printf("|Ident. das Amostras:"AMA);
    aux = 0;
    for(int i =0; i< qtdamostras; i++){
        if(faixa4[i] != 0){

            if(faixa4[i] <= 9)
                aux+=2;
            else
                aux+=3;

            printf(" %d", faixa4[i]);
            if(faixa4[i+1] != 0){
                printf(",");
                aux++;
            }

        }
    }

    for(int i = 0; i <= 61 - aux; i++){
        printf(" ");
    }
    printf(PDR"|");
    printf("\n|%-82s|\n", "");

    
    getchar();
}


void RelatorioMensal(int m, int qtdcarregamentos){
    printf("\n|Origem| Carga |   GU Faixa 1   |   GU Faixa 2   |   GU Faixa 3   |   GU Faixa 4   |");
    printf("\n|------+-------+----------------+----------------+----------------+----------------|\n");
    FILE *database = fopen("database.dat", "rb");
    int origem, carga, mes, dia, tipo;
    float pesobruto, pic, guc;

    if(m != 0){
        //Leitura de cada linha do arquivo comparando se é igual ao mes que foi passado
        for(int i = 0; i < qtdcarregamentos; i++){
            fread(&origem, sizeof(int), 1, database);
            fread(&carga, sizeof(int), 1, database);
            fread(&mes, sizeof(int), 1, database);
            fread(&dia, sizeof(int), 1, database);
            fread(&tipo, sizeof(int), 1, database);
            fread(&pesobruto, sizeof(float), 1, database);
            fread(&pic, sizeof(float), 1, database);
            fread(&guc, sizeof(float), 1, database);

            if(mes == m){
                printf("|"VRD"  %03d "PDR"|  "VRD"%03d  "PDR"|", origem, carga);

                if(guc >= 0 && guc <= 8.5)
                    printf("     "AMA"%05.2f"PDR"      |                |                |                |\n", guc);
                else if(guc >= 8.6 && guc <= 15)
                    printf("                |     "AMA"%05.2f"PDR"      |                |                |\n", guc);
                    else if(guc > 15 && guc <= 25)
                        printf("                |                |     "AMA"%05.2f"PDR"      |                |\n", guc);
                        else
                            printf("                |                |                |     "AMA"%05.2f"PDR"      |\n", guc);
            }
        }
    }
        
    else{
        //Leitura de cada linha do arquivo, do inicio ao fim imprimindo cada mes
        int aux = 0;
        for(int i = 1; i <= 12; i++){
            rewind(database);
            int aux2 = 0;
            for(int j = 0; j < qtdcarregamentos; j++){
                fread(&origem, sizeof(int), 1, database);
                fread(&carga, sizeof(int), 1, database);
                fread(&mes, sizeof(int), 1, database);
                fread(&dia, sizeof(int), 1, database);
                fread(&tipo, sizeof(int), 1, database);
                fread(&pesobruto, sizeof(float), 1, database);
                fread(&pic, sizeof(float), 1, database);
                fread(&guc, sizeof(float), 1, database);
                if(mes == i){
                    aux++, aux2++;
                    printf("|"VRD"  %03d "PDR"|  "VRD"%03d  "PDR"|", origem, carga);

                    if(guc >= 0 && guc <= 8.5)
                        printf("     "AMA"%05.2f"PDR"      |                |                |                |\n", guc);
                    else if(guc >= 8.6 && guc <= 15)
                        printf("                |     "AMA"%05.2f"PDR"      |                |                |\n", guc);
                        else if(guc > 15 && guc <= 25)
                            printf("                |                |     "AMA"%05.2f"PDR"      |                |\n", guc);
                            else
                                printf("                |                |                |     "AMA"%05.2f"PDR"      |\n", guc);
                }
            }

        if(aux != qtdcarregamentos && aux2 != 0)
            printf("|      |       |                |                |                |                |\n");
        }
        

    }
    
    fclose(database);
}


void RelatorioGeral(int qtdcargas){

    Cabecalho(3,-1);
    FILE *database = fopen("database.dat", "rb");
    int origem, carga, mes, dia, tipo;
    float pesobruto, pic, guc;

    printf("\n|          |Faixa 1   (umid.)|Faixa 2   (umid.)|Faixa 3   (umid.)|Faixa 4   (umid.)|\n");
    printf("|Ori- Peso |Peso  Tipo  (%)  |Peso  Tipo  (%)  |Peso  Tipo  (%)  |Peso  Tipo  (%)  |\n");
    printf("|Gem  Total|Limpo Trans      |Limpo Trans      |Limpo Trans      |Limpo Trans      |\n");
    printf("|-+--------+-----------------+-----------------+-----------------+---------------+-|\n");
    for(int i = 0; i < qtdcargas; i++){
        fread(&origem, sizeof(int), 1, database); //
        fread(&carga, sizeof(int), 1, database);
        fread(&mes, sizeof(int), 1, database);
        fread(&dia, sizeof(int), 1, database);
        fread(&tipo, sizeof(int), 1, database);
        fread(&pesobruto, sizeof(float), 1, database);
        fread(&pic, sizeof(float), 1, database);
        fread(&guc, sizeof(float), 1, database);

        
        printf("|"VRD"%03d  %05.2f"PDR"|", origem, pesobruto);
        
        if(guc >= 0 && guc <= 8.5)
            printf(AMA"%05.2f   %d   %05.2f"PDR"|                 |                 |                 |\n", pesobruto - (pesobruto * pic), tipo, guc);
        else if(guc >= 8.6 && guc <= 15)
            printf("                 |"AMA"%05.2f   %d   %05.2f"PDR"|                 |                 |\n", pesobruto - (pesobruto * pic), tipo, guc);
            else if(guc > 15 && guc <= 25)
                printf("                 |                 |"AMA"%05.2f   %d   %05.2f"PDR"|                 |\n", pesobruto - (pesobruto * pic), tipo, guc);
                else
                    printf("                 |                 |                 |"AMA"%05.2f   %d   %05.2f"PDR"|\n", pesobruto - (pesobruto * pic), tipo, guc);

    }
    Rodape();
    fclose(database);
}


void Rodape(){
    char aux;
    printf("|----------------------------------------------------------------------------------|\n"); 
    printf("|Programa desenvolvido pelos alunos%-48s|\n", "");
    printf("|Wallace Elpidio%-67s|\n", "");
    printf("|Lucas Eduardo%-69s|\n", "");
    printf("|Vittor Hugo%-71s|\n", "");
    printf("|Tulio Amaral%-70s|\n", "");
    printf("|Joao Marcelo%-70s|\n", "");
    printf(" ----------------------------------------------------------------------------------\n");

    printf(" Aperte ENTER para voltar ao menu: ");
    scanf("%c", &aux);
    
}
