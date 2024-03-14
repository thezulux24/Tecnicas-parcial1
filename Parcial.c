#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CARTAS 7

typedef struct Carta {
    char* nombre;
    int ataque;
    int defensa;
    int vida;
    int energia;
} Carta;

int main() {
    srand(time(NULL));

    Carta ataque = {"Ataque", 5, 0, 0, -1};
    Carta defensa = {"Defensa", 0, 5, 0, -1};
    Carta ultimaSangre = {"Ultima Sangre", 12, 0, -5, -1};
    Carta milagro = {"Milagro", 0, 0, 0, 1};
    Carta resplandor = {"Resplandor", 15, 0, 0, -2};
    Carta desvio = {"Desvio", 0, 12, 0, -2};
    Carta rebote = {"Rebote", 5, 5, 0, -1};

    Carta *cartas[CARTAS] = {&ataque, &defensa, &ultimaSangre, &milagro, &resplandor, &desvio, &rebote};

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
    int *deckUsable  = (int*)malloc(5 * sizeof(int));
    int tamanoDinamico = 5;
    int flag2 = 0;
    char *nombre= NULL; ;
    size_t tamano = 0;
    printf("ingresa tu nombre: ");
    getline(&nombre, &tamano, stdin);
    printf("Recuerde que, AT=Ataque, DF=Defensa, EN=Costo de energia, LF= Efecto en vida y ME=suma energia\n");
    while (vidaJugador > 0 && vidaEnemigo > 0){
        atack = 0, defense = 0, energia = 3;
        ataqueEnemigo = rand() % 8 + 5 ;
        while (contar < 5) {
            numeroAleatorio = rand() % 7 + 1  ; 
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

        
        while (termino != 1 ){
			
		if (vidaEnemigo>0){
			
	            printf("Hola, %s tú vida es: %d/%d\n", nombre, vidaJugador, vidaJugador2);
	            printf("su energia es: %d\n", energia);
	            printf("Su enemigo se llama Kratos, su vida es: %d/%d\n", vidaEnemigo, vidaEnemigo2);
	            printf("su enemigo le hara: %d dano\n", ataqueEnemigo);
	            printf("----------------- \n");
	            printf("\n Las cartas disponibles son: \n");
	            for (int i=0; i<tamanoDinamico; i++){
	                opcion = deckUsable[i];
	                printf("-> Seleccione [%d] para elegir %s\n AT= %d DF= %d LF= %d EN= %d\n", opcion, cartas[opcion-1]->nombre, cartas[opcion-1]->ataque, cartas[opcion-1]->defensa, cartas[opcion-1]->vida, cartas[opcion-1]->energia);
	            }
	            printf("\n");
	            printf("por favor seleccione su carta, o escriba 0 para terminar finalizar turno\n");
	            printf("\n ----------------- \n");
	            
	            
	                scanf("%d", &seleccion);
	                if (seleccion == 0 ){
	                    termino = 1;
	                    printf("\n ----------------- \n");
	                    printf("turno finalizado\n");
	                }
	                else if (energia - cartas[seleccion-1]->energia >= 0){
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
	                    
	                        atack += cartas[seleccion-1]->ataque;
	                        defense += cartas[seleccion-1]->defensa;
	                        energia -= cartas[seleccion-1]->energia;
	                        vidaJugador += cartas[seleccion-1]->vida;
	                        printf("ataque: %d defensa: %d\n", atack, defense);
	                    if (vidaEnemigo>0){
	                        printf("has generado %d dano a tu enemigo\n", atack);
	                        vidaEnemigo -= atack;
	                    }
	                        atack = 0;
	                    
	
	                }
	                else if (flag2 == 0){
	                    printf("¡LA CARTA YA NO ESTA EN EL DECK!\n");
	                    
	                }
	                flag2 = 0;
	                
	            }
	            
	            else {
	            printf("¡NO TIENES ENERGIA SUFICIENTE!\n");
	            }
        	}
        	else{
        		termino = 1;
			}
		}
        

        // termina el ciclo
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
        else if (vidaJugador<0){
            printf("Has Perdido \n");
        }
        printf("\n ----------------- \n");
        termino = 0;
    
	}
    

    return 0;
}
