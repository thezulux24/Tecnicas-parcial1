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
    int vidaJugador2 = 50;
    int vidaEnemigo = 50;
    int vidaEnemigo2 = 50;
    int atack;
    int ataqueEnemigo;
    int defense;
    int energia;
    int termino = 0;
    int seleccion;
    int size = sizeof(int);
    int *deckUsable  = (int*)malloc(0);
    int tamanoDinamico;
    int flag2 = 0;
    char *nombre= NULL; ;
    size_t tamano = 0;
    printf("ingresa tu nombre");
    getline(&nombre, &tamano, stdin);
    while (vidaJugador > 0 && vidaEnemigo > 0){
        atack = 0, defense = 0, energia = 3, tamanoDinamico = 5;
        ataqueEnemigo = rand() % 8 + 5 ;
        deckUsable = (int*)realloc(deckUsable, tamanoDinamico * size);
        while (contar < 5) {
            numeroAleatorio = rand() % 8  ; 
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
        for (int i = 0; i < tamanoDinamico; i++){
            deckUsable[i]= deck[i];
        }

        for (int i=0; i<tamanoDinamico; i++){
            opcion = deckUsable[i];
        switch(opcion) {
            case 1:
                printf("-> Puedes elegir [1]Ataque\n AT= %d  EN= %d\n", cartas[0][0],cartas[0][3]);
                break;
            case 2:
                printf("-> Puedes elegir [2]Defensa\n DF= %d  EN= %d\n", cartas[1][1],cartas[1][3]);
                break;
            case 3:
                printf("-> Puedes elegir [3]Ultima sangre\n AT= %d  LF=%d  EN= %d\n", cartas[2][0],cartas[2][2],cartas[2][3]);
                break;
            case 4:
                printf("-> Puedes elegir [4]milagro\n ME=%d   EN=%d\n", cartas[3][4],cartas[3][3] );
                break;
            case 5:
                printf("-> Puedes elegir [5]resplandor\n AT= %d EN= %d\n", cartas[4][0],cartas[4][3]);
                break;
            case 6:
                printf("-> Puedes elegir [6]desvio\n DF= %d  EN= %d\n", cartas[5][1],cartas[5][3]);
                break;
            case 7:
                printf("-> Puedes elegir [7]rebote\n AT= %d DF= %d EN= %d\n", cartas[6][0], cartas[6][1],cartas[6][3]);
                break;        
            }
        }
        while (termino != 1 ){
            printf("\n");
            printf("por favor seleccione su carta, o escriba 0 para terminar finalizar turno\n");
            printf("\n ----------------- \n");
            printf("");
            printf("Hola, %s , tú vida es: %d/%d\n", nombre, vidaJugador, vidaJugador2);
            printf("su energia es: %d\n", energia);
            printf("Su enemigo se llama Kratos, su vida es: %d/%d\n", vidaEnemigo, vidaEnemigo2);
            printf("su enemigo le hara: %d dano\n", ataqueEnemigo);
            printf("----------------- \n");
            
            scanf("%d", &seleccion);
            if (seleccion == 0 ){
                termino = 1;
                printf("\n ----------------- \n");
                printf("turno finalizado\n");
            }
            else{
                for (int i = 0; i < tamanoDinamico ; i++){
                    if (deckUsable[i] == seleccion ){
                        flag2 = 1;            
                    }
                    if (flag2 == 1 && i != tamanoDinamico -1){
                        deckUsable[i] = deckUsable[i+1];
                    }

                    
                }
                if (flag2 == 1){
                    tamanoDinamico -= 1;
                    deckUsable = (int*)realloc(deckUsable, tamanoDinamico*size);
                    if (energia - cartas[seleccion-1][3] >= 0){
                        atack += cartas[seleccion-1][0];
                        defense += cartas[seleccion-1][1];
                        energia -= cartas[seleccion-1][3];
                        vidaJugador += cartas[seleccion-1][2];
                        energia += cartas[seleccion-1][4];
                        printf("ataque: %d defensa: %d\n", atack, defense);
                        printf("has generado %d dano a tu enemigo\n", atack);
                        vidaEnemigo -= atack;
                        atack = 0;
                    }
                    else {
                        printf("¡NO TIENES ENERGIA SUFICIENTE!\n");
                    }
                }
                else if (flag2 == 0){
                    printf("¡LA CARTA YA NO ESTA EN EL DECK!\n");
                    
                }
                flag2 = 0;
                
            }
        }
        if (ataqueEnemigo > defense){
            vidaJugador -= defense + ataqueEnemigo;
            printf("el enemigo ha generado %d dano\n", ataqueEnemigo-defense);
        }
        else{
            printf("has bloqueado el ataque\n");
        }


        if (vidaEnemigo < 0){
            printf("HAS GANADO\n");
        }
        printf("\n ----------------- \n");
        termino = 0;
    }

    return 0;
}
