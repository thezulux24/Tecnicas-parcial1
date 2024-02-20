#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ATRIBUTOS 5
#define CARTAS 7
int main() {
    srand(time(NULL));
    int ataque[ATRIBUTOS] = {5,0,0,1,0};
    int defensa[ATRIBUTOS]= {0,5,0,1,0};
    int ultimaSangre[ATRIBUTOS]= {12,0,-5,1,0};
    int milagro[ATRIBUTOS]= {0,0,0,0,1};
    int resplandor[ATRIBUTOS]= {15,0,0,2,0};
    int desvio[ATRIBUTOS]= {0,12,0,2,0};
    int rebote[ATRIBUTOS]= {5,5,0,1,0};
    int *cartas[CARTAS] = {ataque,defensa,ultimaSangre,milagro,resplandor,desvio,rebote};
    int deck[5] = {0}; 
    int flag = 0;
    int numeroAleatorio;
    int contar = 0;
    int repetido ;
    int opcion;
    while (contar < 5) {
        numeroAleatorio = rand() % 8 ; 
        repetido = 0;
        for (int i = 0; i < 5 && !repetido; i++) {
            if (deck[i] == numeroAleatorio) {
                repetido = 1;
            }
        }
        if (!repetido) {
            deck[contar] = numeroAleatorio;
            contar++;
        }
    }

    for (int i=0; i<5; i++){
        opcion = deck[i];
    switch(opcion) {
        case 1:
            printf("Puedes elegir Ataque\n AT= %d  EN= %d\n", cartas[0][0],cartas[0][3]);
            break;
        case 2:
            printf("Puedes elegir Defensa\n DF= %d  EN= %d\n", cartas[1][1],cartas[1][3]);
            break;
        case 3:
            printf("Puedes elegir Ultima sangre\n AT= %d  LF=%d  EN= %d\n", cartas[2][0],cartas[2][2],cartas[2][3]);
            break;
        case 4:
            printf("Puedes elegir milagro\n ME=%d   EN=%d\n", cartas[3][4],cartas[3][3] );
            break;
        case 5:
            printf("Puedes elegir resplandor\n AT= %d EN= %d\n", cartas[4][0],cartas[4][3]);
            break;
        case 6:
            printf("Puedes elegir desvio\n DF= %d  EN= %d\n", cartas[5][1],cartas[5][3]);
            break;
        case 7:
            printf("Puedes elegir rebote\n AT= %d DF= %d EN= %d\n", cartas[6][0], cartas[6][1],cartas[6][3]);
            break;        
        }
    }
    

    return 0;
}