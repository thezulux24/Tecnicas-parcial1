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
    int vidaJugador = 50;
    int vidaEnemigo = 50;
    int atack;
    int ataqueEnemigo;
    int defense;
    int energia;
    int termino = 0;
    int seleccion;
    while (vidaJugador > 0 || vidaEnemigo > 0){
        atack = 0, ataqueEnemigo = 0, defense = 0, energia = 3;
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
        contar = 0;

        for (int i=0; i<5; i++){
            opcion = deck[i];
        switch(opcion) {
            case 1:
                printf("Puedes elegir [1]Ataque\n AT= %d  EN= %d\n", cartas[0][0],cartas[0][3]);
                break;
            case 2:
                printf("Puedes elegir [2]Defensa\n DF= %d  EN= %d\n", cartas[1][1],cartas[1][3]);
                break;
            case 3:
                printf("Puedes elegir [3]Ultima sangre\n AT= %d  LF=%d  EN= %d\n", cartas[2][0],cartas[2][2],cartas[2][3]);
                break;
            case 4:
                printf("Puedes elegir [4]milagro\n ME=%d   EN=%d\n", cartas[3][4],cartas[3][3] );
                break;
            case 5:
                printf("Puedes elegir [5]resplandor\n AT= %d EN= %d\n", cartas[4][0],cartas[4][3]);
                break;
            case 6:
                printf("Puedes elegir [6]desvio\n DF= %d  EN= %d\n", cartas[5][1],cartas[5][3]);
                break;
            case 7:
                printf("Puedes elegir [7]rebote\n AT= %d DF= %d EN= %d\n", cartas[6][0], cartas[6][1],cartas[6][3]);
                break;        
            }
        }
        while (termino != 1){

            printf("por favor seleccione su carta, o escriba 0 para terminar finalizar turno\n");
            printf("su energia es: %d\n", energia);
            scanf("%d", &seleccion);
            if (seleccion == 0 ){
                termino = 1;
            }
            else{
                atack += cartas[seleccion-1][0];
                defense += cartas[seleccion-1][1];
                energia -= cartas[seleccion-1][3];
                vidaJugador += cartas[seleccion-1][2];
            }
            printf("ataque: %d defensa: %d\n", atack, defense);
        }
        termino = 0;
    }

    return 0;
}
