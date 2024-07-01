#include <stdio.h>


void Arquivos(FILE *database, FILE *basebin);
float pic(float *p, float *q, int n); //Calcula o PIC
float guc(float*p, float *q, float*u, int n);// Calcula o GCU



int main(){
    FILE *database, *basebin; //Cria um ponteiro do tipo file
    database = fopen("base.txt", "w"); //Cria uma base de dados vazia, na mesma pasta onde o arquivo .c está
    basebin = fopen("basebin.dat", "wb");
    fclose(database); //Fecha o arquivo para evitar possiveis erros
    fclose(basebin);

    Arquivos(database, basebin); //Chama a função passando a base de dados
    return 0;
}



//Trabalhei com os arquivos apenas nessa função, mas no futuro acredito que a leitura e a escrita serão em funções diferentes;
//A função está lendo apenas a 1º linha
void Arquivos(FILE *database, FILE *basebin){

    FILE *arquivoteste; // Cria ponteiro do tipo file

    //printf("Digite o nome do arquivo:");  Aqui vai ter a função pra verificar se o arquivo realmente existe e se existir ele passa como variavel na função

    arquivoteste = fopen("DadosGraos-Carga1.txt", "r"); // Ponteiro lê o arquivo que vamos trabalhar (Para teste usei apenas o 1º arquivo)

    int origem, carga, namostras, tipo, dia, mes; 
    float pesobruto;

        
    printf("Digite o dia: ");
    scanf("%d", &dia);
    printf("Digite o mes: ");
    scanf("%d", &mes);
    

    fscanf(arquivoteste, "%d %d %f %d %d", &origem, &carga, &pesobruto, &namostras, &tipo); //Função que lê os arquivos e salva nas váriavéis

    database = fopen("base.txt", "a"); 
    basebin = fopen("basebin.dat", "ab+");

    fprintf(database, "%d %d %.1f %d %d", origem, carga, pesobruto, namostras, tipo);//Escreve no arquivo


    //int faixa1[namostras], faixa2[namostras], faixa3[namostras], faixa4[namostras];
    //Iniciar o vetor zerado pra usar if !=0 na hora de imprimir 

    //int f1cont = 0, f2cont = 0, f3cont = 0, f4cont = 0;

    int nidentificacao, pesoimpurezas;
    float brutoamostra, grauumidade;
    for(int i = 1; i <= namostras; i++){
        if(fscanf(arquivoteste, "%d %f %d %f", &nidentificacao, &brutoamostra, &pesoimpurezas, &grauumidade) == 4){//Verifica se o fscanf conseguiu ler exatamente quatro valores
            fprintf(database, "\n%d %.2f %d %.1f", nidentificacao, brutoamostra, pesoimpurezas, grauumidade);
            /*if(grauumidade >= 0 && grauumidade <= 8,5){
                faixa1[i] = i;
                f1cont++;
            }
            else if(grauumidade >= 8,6 && grauumidade <= 15){
                faixa2[i] = i;
                f2cont++;
                }
                else if(grauumidade >= 15,1 && grauumidade <= 25){
                faixa3[i] = i;
                f3cont++;
                    }
                    else{
                        faixa4[i] = i;
                        f4cont++;
                        }*/

        } 
            

        
    }     
    
    fprintf(database, "\n%d %d %d %d %d %.3f %.2f %.2f\n",origem, carga, mes, dia, tipo, pesobruto, (float)pesoimpurezas, grauumidade);//Nessa função vai passar o valor do pic e do guc
    fwrite(&origem, sizeof(int), 1, basebin);
    fwrite(&carga, sizeof(int), 1, basebin);
    fwrite(&mes, sizeof(int), 1, basebin);
    fwrite(&dia, sizeof(int), 1, basebin);
    fwrite(&tipo, sizeof(int), 1, basebin);
    fwrite(&pesobruto, sizeof(float), 1, basebin);
    fwrite(&pesoimpurezas, sizeof(float), 1, basebin);
    fwrite(&grauumidade, sizeof(float), 1, basebin);


    fclose(arquivoteste); //Fecha o arquivo para evitar possíveis erros;
    
    fclose(basebin);
    fclose(database);
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




/*DÚVIDAS:
No banco de dados é necessario algum tipo de formatação?
Como buscar na pasta arquivos com mesmo nome?

*/
