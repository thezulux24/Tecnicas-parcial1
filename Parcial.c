#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ATRIBUTOS 5
#define CARTAS 7
/*
INTEGRANTES:
JHON DEIBY MEJIAS
BRAYAN DAVID ZULUAGA
RICARDO PEREZ
*/
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
    printf("ingresa tu nombre: ");
    getline(&nombre, &tamano, stdin);
    printf("Recuerde que, AT=Ataque, DF=Defensa, EN=Costo de energia, LF= Efecto en vida y ME=suma energia\n");
    while (vidaJugador > 0 && vidaEnemigo > 0){
        atack = 0, defense = 0, energia = 3, tamanoDinamico = 5;
        ataqueEnemigo = rand() % 8 + 5 ;
        deckUsable = (int*)realloc(deckUsable, tamanoDinamico * size);
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
	            switch(opcion) {
	            case 1:
	                printf("-> Seleccione [1] para elegir Ataque\n AT= %d  EN= %d\n", cartas[0][0],cartas[0][3]);
	                break;
	            case 2:
	                printf("->Seleccione [2] para elegir Defensa\n DF= %d  EN= %d\n", cartas[1][1],cartas[1][3]);
	                break;
	            case 3:
	                printf("-> Seleccione [3] para elegir Ultima sangre\n AT= %d  LF=%d  EN= %d\n", cartas[2][0],cartas[2][2],cartas[2][3]);
	                break;
	            case 4:
	                printf("-> Seleccione [4] para elegir Milagro\n ME=%d   EN=%d\n", cartas[3][4],cartas[3][3] );
	                break;
	            case 5:
	                printf("-> Seleccione [5] para elegir Resplandor\n AT= %d EN= %d\n", cartas[4][0],cartas[4][3]);
	                break;
	            case 6:
	                printf("-> Seleccione [6] para elegir Desvio\n DF= %d  EN= %d\n", cartas[5][1],cartas[5][3]);
	                break;
	            case 7:
	                printf("-> Seleccione [7] para elegir Rebote\n AT= %d DF= %d EN= %d\n", cartas[6][0], cartas[6][1],cartas[6][3]);
	                break;        
	            }
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
	                else if (energia - cartas[seleccion-1][3] >= 0){
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
	                    
	                        atack += cartas[seleccion-1][0];
	                        defense += cartas[seleccion-1][1];
	                        energia -= cartas[seleccion-1][3];
	                        vidaJugador += cartas[seleccion-1][2];
	                        energia += cartas[seleccion-1][4];
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
