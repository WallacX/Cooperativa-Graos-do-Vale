#include "funcoes.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

//Definição dos comandos para mudança de cor dos textos imprimidos
#define PDR "\033[0m"
#define PTR "\033[30m"
#define VRM "\033[31m"
#define VRD "\033[32m"
#define AMA "\033[33m"
#define AZL "\033[34m"
#define BRA "\033[37m"


int qtdcarregamentos = 0;

void Menu(){
    //Chama as funções reponsavéis por cada opção do programa
    int opcao;

    system("clear");
    printf(" --------------------------------\n");
    printf("|         GRAOS DO VALE          |\n");
    printf("|________________________________|\n");
    printf("|1 - Entrada de arquivo          |\n");
    printf("|                                |\n");
    printf("|2 - Carregamento                |\n");
    printf("|                                |\n");
    printf("|3 - Relatório Mensal            |\n");
    printf("|                                |\n");
    printf("|4 - Relatório Geral             |\n");
    printf("|                                |\n");
    printf("|5 - Sair do Programa            |\n");
    printf("|________________________________|\n");
    printf(" Digite a opçao correspondente: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao){

        case 1:
            Entrada(); 
            Menu();
            break;
        
        case 2:
            Carregamento(); 
            Menu();
            break;
        
        case 3:
            EstatisticasMensais(); 
            Menu();
            break;
        
        case 4:
            RelatorioGeral(qtdcarregamentos);
            Menu();
            break;

        case 5:
            system("clear");
            printf(AZL"Obrigado por utilizar!!!");
            printf("\nAte mais!!!");
            break;
        
        default:
            system("clear");
            printf(VRM"Opção Inválida!!!!!!\a\n"PDR);
            sleep(2);
            system("clear");
            Menu();
            break;

    }
    
}


void Entrada(){ //Cria um arquivo e pede os dados das cargas
    system("clear");
    int numeroCarga, numeroAmostras, tipoCarga, pesoBrutoAmostra, idOrigem;
    float pesoCarga, medidasAmostra, pesoImpurezaAmostra;

    FILE *carregamento, *database;

    
    char nomearquivo[51];


    do{
        const char *diretorio = ".";

        printf("Digite o nome do arquivo ("AMA".txt"PDR"): ");
        fgets(nomearquivo, 50, stdin);
        nomearquivo[strcspn(nomearquivo, "\n")] = '\0';
        
        carregamento = fopen(nomearquivo, "r");

        if(carregamento == NULL){
            carregamento = fopen(nomearquivo, "w+");
            printf(VRD"Arquivo Criado!\n"PDR);
    
           
            printf("Identificacao da origem da carga: ");
            scanf("%d", &idOrigem);
            fprintf(carregamento, "%d ", idOrigem);
            
            printf("Numero de protocolo da carga: ");
            scanf("%d", &numeroCarga);
            fprintf(carregamento, " %d", numeroCarga);
            
            printf("Peso Bruto da carga: ");
            scanf("%f", &pesoCarga);
            fprintf(carregamento, " %.1f", pesoCarga);
            
            printf("Numero de amostras: ");
            scanf("%d", &numeroAmostras);
            fprintf(carregamento, " %d", numeroAmostras);
            
            printf("Digite o tipo da amostra: ");
            scanf("%d", &tipoCarga);
            fprintf(carregamento, " %d", tipoCarga);
            fprintf(carregamento, "\n");
            
            for(int i = 0; i < numeroAmostras; i++)
            {
                system("clear");
                fprintf(carregamento, "%.1d ", i+1);
                printf("Medida da amostra %d: ", i+1);
                scanf("%f", &medidasAmostra);
                fprintf(carregamento, "%-2.2f", medidasAmostra);
                printf("Peso bruto da amostra(Kg): ");
                scanf("%d", &pesoBrutoAmostra);
                fprintf(carregamento, " %-2d ", pesoBrutoAmostra);
                printf("Peso das impurezas da amostra(g): ");
                scanf("%f", &pesoImpurezaAmostra);
                fprintf(carregamento ,"%-2.1f\n", pesoImpurezaAmostra);

            }
            
            fclose(carregamento);
            printf("Arquivo salvo com " VRD "sucesso!\n" PDR);
            sleep(1);
            

        }else{
            printf(VRM"Arquivo Existente!\n"PDR);
            sleep(2);
            system("clear");
            fclose(carregamento);
        }
    }while(carregamento == NULL);
}


void Carregamento(){
    system("clear");

    FILE *carregamento, *database;

    char nomearquivo[51];


    do{
        const char *diretorio = ".";
        ListaTxt(diretorio);

        printf("Digite o nome de um arquivo: ");
        fgets(nomearquivo, 50, stdin);
        nomearquivo[strcspn(nomearquivo, "\n")] = '\0';


        carregamento = fopen(nomearquivo, "r");

        if(carregamento == NULL){
            system("clear");
            printf(VRM"Arquivo nao encontrado!\n"PDR);
            sleep(3);
            system("clear");

        }


    }while(carregamento == NULL);



    int origem, carga, qtdamostras, tipo, dia, mes; 
    float pesobruto;
    do{
        printf("Digite o dia: ");
        scanf("%d", &dia);
        if (dia>31 || dia<1){
            printf(VRM"Dia invalido!\n"PDR);
            sleep(2);
        }   
        
    }while (dia>31 || dia<1);
    do{
        printf("Digite o mes: ");
        scanf("%d", &mes);
        if(mes>12 || mes<1){
            printf(VRM"Mes invalido!\nPDR"); 
            sleep(2);
        }
    }while(mes>12 || mes<1);

    fscanf(carregamento, "%d %d %f %d %d", &origem, &carga, &pesobruto, &qtdamostras, &tipo); //Função que lê a 1º linha do arquivo e salva nas váriavéis

    database = fopen("database.dat", "ab+"); //Abre o banco de dados 

    int faixa1[qtdamostras], faixa2[qtdamostras] , faixa3[qtdamostras], faixa4[qtdamostras]; //Criamos os vetores que irão armazenar os n da amostra de cada faixa
    ZeraVetor(faixa1, qtdamostras);// Zeramos os vetores
    ZeraVetor(faixa2, qtdamostras);
    ZeraVetor(faixa3, qtdamostras);
    ZeraVetor(faixa4, qtdamostras);

    int nidentificacao = 0, pesoimpurezas, vpimpurezas[qtdamostras], f1cont = 0, f2cont = 0, f3cont = 0, f4cont = 0; //Essas variaveis alem de contar a qtd de amostras em cada faixa vão ajudar a salvar a umidade no vetor pra calcular o guc
    float brutoamostra, grauumidade, vgumidade[qtdamostras], vpbruto[qtdamostras];

    //Como o arquivo o ultimo caractere do arquivo é um \n  precisei definir o nidentificacao como 0 pra entrar no while 
    //Caso tire essa comparação do n identificação o codigo vai ler a ultima linha 2 vezes;

    while(!feof(carregamento) && nidentificacao < qtdamostras )
    { // checa se (!nao!) estamos no fim da arquivo (e se o n de identificacao e menor q a qtd de amostras) e inicia lendo a partir da linha 2 (Já lemos a 1º linha antes)
        fscanf(carregamento, "%d %f %d %f", &nidentificacao, &brutoamostra, &pesoimpurezas, &grauumidade);

        //Passa o peso e a umidade pros respectivos vetores
        vpimpurezas[nidentificacao - 1] = pesoimpurezas;
        vgumidade[nidentificacao - 1 ] = grauumidade;
        vpbruto[nidentificacao - 1] = brutoamostra;


        //Salva a umidade no respectivo vetor
        if(grauumidade >= 0 && grauumidade <= 8.5){
            faixa1[f1cont] = nidentificacao;
            f1cont++;
        }
        else if(grauumidade >= 8.6 && grauumidade <= 15){
            faixa2[f2cont] = nidentificacao;
            f2cont++;
            }
            else if(grauumidade > 15 && grauumidade <= 25){
                faixa3[f3cont] = nidentificacao;
                f3cont++;                
            }
                else{
                    faixa4[f4cont] = nidentificacao;
                    f4cont++;
                    }


        }


    float toneladas, pic, guc, plimpo;

    toneladas = CalculaToneladas(vpbruto, qtdamostras);
    pic = CalculaPic(vpbruto, vpimpurezas, qtdamostras);
    guc = CalculaGuc(vpbruto, vpimpurezas, vgumidade, qtdamostras);
    plimpo = CalculaPesoLimpo(vpbruto, vpimpurezas, qtdamostras);
    

    fwrite(&origem, sizeof(int), 1, database);
    fwrite(&carga, sizeof(int), 1, database);
    fwrite(&mes, sizeof(int), 1, database);
    fwrite(&dia, sizeof(int), 1, database);
    fwrite(&tipo, sizeof(int), 1, database);
    fwrite(&toneladas, sizeof(float), 1, database);
    fwrite(&pic, sizeof(float), 1, database);
    fwrite(&guc, sizeof(float), 1, database);


    fclose(carregamento); //Fecha os arquivo para evitar possíveis erros/lentidão;
    fclose(database);

    qtdcarregamentos++;


    Cabecalho(1,-1);
    RelatorioCarga(origem, dia, mes, guc, plimpo, tipo, f1cont, faixa1, f2cont, faixa2, f3cont, faixa3, f4cont, faixa4, qtdamostras);
    Rodape();
}


void EstatisticasMensais(){
    int mes;
    
    do{
        system("clear");
        printf("Digite o mes do relatorio ou 0 para carregar todos os meses: ");
        scanf("%d", &mes);
        if(mes>12 || mes<0) printf(VRM"\nMes invalido!\n\n"PDR);    
        sleep(2);
    }while(mes>12 || mes<0);
    
    
    Cabecalho(2, mes);
    RelatorioMensal(mes, qtdcarregamentos);
 
            
    getchar();
    Rodape();
}


int TxtExtensao(const char *filename){
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) return 0;
    return strcmp(dot, ".txt") == 0;
}


void ListaTxt(const char *directory){
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror("opendir");
        return;
    }
    printf(" -------------------------------------\n");
    printf("|        "AZL"Arquivos no diretorio"PDR"        |\n");
    printf("|-------------------------------------|\n");
    while ((entry = readdir(dp))) {
        if (TxtExtensao(entry->d_name)) {
            printf("|  %-35s|\n", entry->d_name);
        }
    }
    printf(" -------------------------------------\n");
    closedir(dp);
}


void ZeraVetor(int vetor[], int tam){
    for(int i = 0; i< tam; i++){
        vetor[i] = 0;
    }
}


float CalculaPic(float vbruto[], int vpeso[],int qtdamostras){

    float somap = 0,somaq = 0, pic;

    for(int i = 0; i < qtdamostras; i++)
    {
        somap += vbruto[i];//kg
        somaq += (0.001)*vpeso[i];//kg
    }
    if(somap != 0) pic = (somaq) /((1.0) * somap); //kg/kg
    else pic = 0.00;

    return pic;
}


float CalculaGuc(float vbruto[], int vpeso[] , float vgrau[],int qtdamostras){

    float numerador = 0, quociente = 0 , guc;

    for(int i=0;i<qtdamostras;i++)
    {
        numerador +=  vgrau[i] * (vbruto[i] - (0.001)*vpeso[i]);//kg
        quociente += (vbruto[i] - (0.001)*vpeso[i]);//kg    
    }
    if(quociente != 0)
        { 
            guc = numerador / quociente;             
        }
        else guc = 0.00;

    
    return guc;

}


float CalculaToneladas(float vpeso[], int qtdamostras){
    float toneladas = 0;
    for(int i = 0; i < qtdamostras; i++){
        toneladas += vpeso[i];
    }
    return toneladas;
}


float CalculaPesoLimpo(float vbruto[], int vimpurezas[], int qtdamostras){
    float plimpo = 0;
    for(int i = 0; i < qtdamostras; i++){
        plimpo += vbruto[i]  - 0.001*vimpurezas[i];
    }

    return plimpo;
}
