#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


//Pra essa semana: finalizar o menu e elaborar a impressão dos outros relátorios (Pelo menos o relatório geral)

void Arquivos(FILE *database, FILE *basebin);
float pic(float *p, float *q, int n); //Calcula o PIC
float guc(float*p, float *q, float*u, int n);// Calcula o GCU
void ZeraVetor(int vetor[], int tam);


//Pra facilitar os testes, sugiro que alterem o nome dos arquivos para carga1, carga2, etc.
//Os aqruivos precisam estar na pasta output gerada pelo proprio vscode na 1º execução
//Tabalhei com txt e bin lado a lado, pra facilitar nossa visualização do bando de dados

int main(){

    
    FILE *database, *basebin; //Cria um ponteiro do tipo file

    database = fopen("base.txt", "w"); //Cria uma base.txt de dados vazia, na mesma pasta onde o arquivo .c está
    basebin = fopen("basebin.dat", "wb"); //Cria uma base.dat (base em binario) de dados vazia, na mesma pasta onde o arquivo .c está

    fclose(database); //Fecha o arquivo para evitar possiveis erros
    fclose(basebin);

    Arquivos(database, basebin); //Chama a função passando a base de dados
    return 0;
}



//Trabalhei com os arquivos apenas nessa função, mas no futuro a leitura e a escrita serão em funções diferentes;


void Arquivos(FILE *database, FILE *basebin){

    FILE *carregamento; // Cria ponteiro do tipo file que vai apontar pro carregamento
    printf("Digite o nome do arquivo: ");

    //Pede o nome do arquivo
    char nomearquivo[51];
    fgets(nomearquivo, 50, stdin);
    nomearquivo[strcspn(nomearquivo, "\n")] = '\0'; // Substitue o \n por \0 no final da string

    carregamento = fopen(nomearquivo, "r"); //Tenta abrir o arquivo ( vai retornar 1 caso exista e 0 caso n exista)
    
    //Define as variaveis que vamos tirar da 1° linha e a data
    int origem, carga, qtdamostras, tipo, dia, mes; 
    float pesobruto;

    if(carregamento){ //Caso o arquivo exista pede o dia e o mes 
        printf("Digite o dia: ");
        scanf("%d", &dia);
        printf("Digite o mes: ");
        scanf("%d", &mes);
    
    }
    else
        printf("O arquivo nao existe!!!\n");


    fscanf(carregamento, "%d %d %f %d %d", &origem, &carga, &pesobruto, &qtdamostras, &tipo); //Função que lê a 1º do arquivo e salva nas váriavéis

    database = fopen("base.txt", "a"); 
    basebin = fopen("basebin.dat", "ab+"); //Abre o banco de dados 


    int faixa1[qtdamostras], faixa2[qtdamostras] , faixa3[qtdamostras], faixa4[qtdamostras]; //Criamos os vetores que irão armazenar os n da amostra de cada faixa
    ZeraVetor(faixa1, qtdamostras);// Zeramos os vetores
    ZeraVetor(faixa2, qtdamostras);
    ZeraVetor(faixa3, qtdamostras);
    ZeraVetor(faixa4, qtdamostras);
    //Iniciar o vetor zerado pra usar if !=0 na hora de imprimir 


    //Criamos as variaveis/vetores que vamos ultizar em cada linha
    int nidentificacao = 0, pesoimpurezas, vpic[qtdamostras], f1cont = 0, f2cont = 0, f3cont = 0, f4cont = 0; //Essas variaveis alem de contar a qtd de amostras em cada faixa vão ajudar a salvar a umidade no vetor pra calcular o guc
    float brutoamostra, grauumidade, vguc[qtdamostras];

    //Como o arquivo o ultimo caractere do arquivo é um \n  precisei definir o nidentificacao como 0 pra entrar no while 
    //Caso tire essa comparação do n identificação o codigo vai ler a ultima linha 2 vezes;

    while(!feof(carregamento) && nidentificacao < qtdamostras ){ // checa se (!nao!) estamos no fim da arquivo (e se o n de identificacao e menor q a qtd de amostras) e inicia lendo a partir da linha 2 (Já lemos a 1º linha antes)
        fscanf(carregamento, "%d %f %d %f", &nidentificacao, &brutoamostra, &pesoimpurezas, &grauumidade);
        fprintf(database, "\n%d %.2f %d %.1f", nidentificacao, brutoamostra, pesoimpurezas, grauumidade);

        //Passa o peso e a umidade pros respectivos vetores
        vpic[nidentificacao-1] = pesoimpurezas;
        vguc[nidentificacao-1] = grauumidade;
        
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
                f3cont++;                }
                else{
                    faixa4[f4cont] = nidentificacao;
                    f4cont++;
                    }

    
    }
        

    //No lugar de pesoimpuresas e graumidade vamos passar o pic e o guc
    //Usei essas variaveis só para testar 
    fprintf(database, "\n%d %d %d %d %d %.3f %.2f %.2f\n",origem, carga, mes, dia, tipo, pesobruto, (float)pesoimpurezas, grauumidade);
    fwrite(&origem, sizeof(int), 1, basebin);
    fwrite(&carga, sizeof(int), 1, basebin);
    fwrite(&mes, sizeof(int), 1, basebin);
    fwrite(&dia, sizeof(int), 1, basebin);
    fwrite(&tipo, sizeof(int), 1, basebin);
    fwrite(&pesobruto, sizeof(float), 1, basebin);
    fwrite(&pesoimpurezas, sizeof(float), 1, basebin);
    fwrite(&grauumidade, sizeof(float), 1, basebin);


    fclose(carregamento); //Fecha os arquivo para evitar possíveis erros/lentidão;
    fclose(basebin);
    fclose(database);


    //impressão
    printf("\nUFG-BSI-IP (COOPERATIVA AGRICOLA GRAO_DO_VALE)\n");
    printf("ANO: 2024\n");
    printf("---------------------------------------------------------------------\n");
    printf("Origem: %d \t\t Num. de amostras: %d\t\tData: %02d/%02d/24\n", origem, qtdamostras, dia, mes);
    printf("Umidade: %.1f%%\t\t Peso limpo: %02.2f\t\tTransgenico: %d\n",grauumidade, pesobruto - pesoimpurezas ,tipo);

    
    printf("\nUmidade: Faixa 1 \t\t Quant.: %d\n", f1cont);
    printf("Ident. das Amostras:");
    for(int i =0; i< qtdamostras; i++){
        if(faixa1[i] != 0)
            printf(" %d,", faixa1[i]);
    }

    printf("\n\nUmidade: Faixa 2 \t\t Quant.: %d\n", f2cont);
    printf("Ident. das Amostras:");
    for(int i =0; i< qtdamostras; i++){
        if(faixa2[i] != 0)
            printf(" %d,", faixa2[i]);
    }

    
    printf("\n\nUmidade: Faixa 3 \t\t Quant.: %d\n", f3cont);
    printf("Ident. das Amostras:");
    for(int i =0; i< qtdamostras; i++){
        if(faixa3[i] != 0)
            printf(" %d,", faixa3[i]);
    }

    printf("\n\nUmidade: Faixa 4 \t\t Quant.: %d\n", f4cont);
    printf("Ident. das Amostras:");
    for(int i =0; i< qtdamostras; i++){
        if(faixa4[i] != 0)
            printf(" %d,", faixa4[i]);
    }

    printf("\n\n----------------------------------------------------------------------------\n");
    printf("Programa desenvolvido pelos alunos:\n");
    printf("Lucas Eduardo\n");
    printf("Wallace Elpidio\n");
    printf("Joao Marcelo\n");
    printf("Tulio Amaral\n");
    printf("Vittor Hugo\n");


}


void ZeraVetor(int vetor[], int tam){
    for(int i = 0; i< tam; i++){
        vetor[i] = 0;
    }
}






float pic(float p[], float q[],int n){

    float somap = 0,somaq = 0, pic;

    for(int i=0;i<n;i++)
    {
        somap += p[i];   //somatório    
        somaq += q[i];   //somatório
    }

    pic = somap / somaq; //fórmula pic

    return pic;
}

float guc(float p[], float q[] , float u[],int n){

    float x = 0, y = 0 , guc; //x=somatio dividendo da fórmula, y= divisor fórmula

    for(int i=0;i<n;i++)
    {
        x +=  u[i] * (p[i] - q[i]);
        y += (p[i]-q[i]);    
    }

    guc = x / y; 

    return guc;

}
