#include <stdio.h>


void Arquivos(FILE *database);


int main(){
    FILE *database; //Cria um ponteiro do tipo file
    database = fopen("base.txt", "w"); //Cria uma base de dados vazia, na mesma pasta onde o arquivo .c está
    fclose(database); //Fecha o arquivo para evitar possiveis erros

    Arquivos(database); //Chama a função passando a base de dados
    return 0;
}



//Trabalhei com os arquivos apenas nessa função, mas no futuro acredito que a leitura e a escrita serão em funções diferentes;
//A função está lendo apenas a 1º linha
void Arquivos(FILE *database){

    FILE *arquivoteste; // Cria ponteiro do tipo file

    arquivoteste = fopen("DadosGraos-Carga1.txt", "r"); // Ponteiro lê o arquivo que vamos trabalhar (Para teste usei apenas o 1º arquivo)

    int a, b, d, e; 
    float c;

    fscanf(arquivoteste, "%d %d %f %d %d", &a, &b, &c, &d, &e); //Função que lê os arquivos e salva nas váriavéis
    fclose(arquivoteste); //Fecha o arquivo para evitar possíveis erros;

    database = fopen("base.txt", "a"); 
    fprintf(database, "%d %d %.1f %d %d", a, b, c, d, e);//Escreve no arquivo
    fclose(database);
}





/*DÚVIDAS:
Pq no prototipo de Arquivos se tirar o *database para de compilar?
Vamos salvar as informações de cada linha em um vetor dentro de outro vetor (um pra cada linha, e outro pra cada item em cada linha)?
Temos que ler os números nas linhas como no código ou vamos ler cada linha como uma string?
*/
