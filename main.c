#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "interface.h"


int main(){
    
    FILE *database; //Cria um ponteiro do tipo file

    database = fopen("database.dat", "wb"); //Cria uma base.dat (base em binario) de dados vazia, na mesma pasta onde o arquivo .c está

    fclose(database); //Fecha o arquivo para evitar possiveis erros

    Menu();

    return 0;
}
