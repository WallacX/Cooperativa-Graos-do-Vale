#include <stdio.h>
//#define n 15

float pic(float *brutoamostra, float *pesoimpurezas, int qtdamostras);
float guc(float*brutoamostra, float *pesoimpurezas, float*grauumidade, int qtdamostras);

int main(){

    int qtdamostras;
    printf("\nDigite o valor de n° de amostras: ");
    scanf("%d",&qtdamostras);

    float brutoamostra[qtdamostras],pesoimpurezas[qtdamostras],grauumidade[qtdamostras];
    
    for(int i=0; i<qtdamostras;i++)
    {
    printf("\nbrutoamostra[%d], pesoimpurezas[%d], grauumidade[%d]", i, i, i);
    scanf("%f %f %f", &brutoamostra[i], &pesoimpurezas[i], &grauumidade[i]);
    }

    printf("\nPic: %.2f",pic(brutoamostra,pesoimpurezas,qtdamostras));
    printf("\nGuc: %.2f",guc(brutoamostra,pesoimpurezas,grauumidade,qtdamostras));

    return 0;

}

float pic(float brutoamostra[], float pesoimpurezas[],int qtdamostras){

    float somap = 0,somaq = 0, pic;

    for(int i=0;i<qtdamostras;i++)
    {
        somap += brutoamostra[i];       
        somaq += pesoimpurezas[i];
    }

    pic = somap / somaq;

    return pic;
}

float guc(float brutoamostra[], float pesoimpurezas[] , float grauumidade[],int qtdamostras){

    float x = 0, y = 0 , guc;

    for(int i=0;i<qtdamostras;i++)
    {
        x +=  grauumidade[i] * (brutoamostra[i] - pesoimpurezas[i]);
        y += (brutoamostra[i]-pesoimpurezas[i]);    
    }

    guc = x / y;

    return guc;

}

