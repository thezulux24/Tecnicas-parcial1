#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 14
#define MANO_JUGADOR 5
#define INICIAL_DECK 7
#include <string.h>

// Estructura para representar una carta
typedef struct Carta {
    char* nombre;
    int ataque;
    int defensa;
    int vida;
    int energia;
} Carta;

// Estructura para representar un nodo de la lista enlazada
typedef struct Nodo {
    Carta carta;
    struct Nodo* siguiente;
} Nodo;

// Estructura para representar una lista enlazada
typedef struct ListaEnlazada {
    Nodo* cabeza;
    int longitud;
} ListaEnlazada;

// Estructura para representar un personaje o un enemigo
typedef struct Personaje {
    char nombre[100];
    int vida_actual;
    int vida_total;
    int ataque;
} Personaje;

typedef struct Jugador {
    Personaje personaje;
    int energia;
    int defensa;
    int seleccion;
    int termino;
} Jugador;

typedef struct Enemigo {
    Personaje personaje;
} Enemigo;

// Estructura para representar una pila
typedef struct Pila {
    Carta* cartas;
    int tope;
    int capacidad;
} Pila;

// Prototipos de funciones
Nodo* crearNodo(Carta carta);
ListaEnlazada* crearListaEnlazada();
void agregarAlFinal(ListaEnlazada* lista, Carta carta);
Pila* inicializarPila(int capacidad);
void apilar(Pila* pila, Carta carta);
Carta desapilar(Pila* pila);
void barajarListaYApilar(ListaEnlazada* lista, Pila* pila_robo);
void seleccionarCartasDeck (Carta* cartas_disponibles, ListaEnlazada* deck_general, int num_cartas_inicial);
void imprimirListaCartas(ListaEnlazada* lista);
void robarCartas(Pila* pila_robo, ListaEnlazada* mano);
void imprimirPila(Pila* pila);
Carta* seleccionarTresCartasAleatorias(Carta* cartas_disponibles, ListaEnlazada* deck_general);
Carta obtenerCartaEnIndice(ListaEnlazada* lista, int indice);
void moverCartaAMiniDeck(ListaEnlazada* mini_deck, ListaEnlazada* pila_descarte);
void moverCartasAlFinalizarTurno(ListaEnlazada* mini_deck, ListaEnlazada* pila_descarte);
void turno(struct Enemigo enemigo, struct Jugador jugador, ListaEnlazada* mano, Pila* pila_robo, ListaEnlazada* pila_descarte);

int main() {
    int jugar = 1; //booleano para jugar

    // Definir todas las cartas disponibles en el juego
    Carta cartas_disponibles[NUM_CARTAS] = {
            {"Ataque",        5,  0,  0,  -1},
            {"Defensa",       0,  5,  0,  -1},
            {"Ultima Sangre", 12, 0,  -5, -1},
            {"Milagro",       0,  0,  0,  1},
            {"Resplandor",    15, 0,  0,  -2},
            {"Desvio",        0,  12, 0,  -2},
            {"Rebote",        5,  5,  0,  -1},
            {"Furia",         8,  3,  0,  -2},
            {"Escudo Divino", 0,  10, 0,  -2},
            {"Bendición",     0,  5,  10, -3},
            {"Contraataque",  6,  0,  0,  -2},
            {"Curación",      0,  0,  20, -3},
            {"Fuego Sagrado", 10, 0,  0,  -3},
            {"Meditación",    0,  0,  0,  3}

    };

    Jugador jugador;
    Enemigo enemigo;

    // Definir nombre del jugador
    printf("Ingresa el nombre del jugador: ");
    fgets(jugador.personaje.nombre, sizeof(jugador.personaje.nombre), stdin);

    strcpy(enemigo.personaje.nombre, "Kratos"); // ya que no se puede declarar con "="
    jugador.personaje.vida_actual = 50;
    jugador.personaje.vida_total = 50;
    enemigo.personaje.vida_actual = 50;
    enemigo.personaje.vida_total = 50;


    // Crear el deck general con las cartas iniciales
    ListaEnlazada *deck_general = crearListaEnlazada();
    seleccionarCartasDeck(cartas_disponibles, deck_general, INICIAL_DECK);

    
    // Prueba de impresion de cartas aleatorias para la Mano
    printf("Deck General:\n");
    imprimirListaCartas(deck_general);
    
    Pila *pila_robo = inicializarPila(NUM_CARTAS);
    // Barajar el deck general y colocarlo en la pila de robo

    barajarListaYApilar(deck_general, pila_robo);
    
    printf("\n");
    printf("Deck General Barajado:\n");
    imprimirListaCartas(deck_general);
    printf("\n");
    printf("Pila de robado:\n");
    imprimirPila(pila_robo);
    

    ListaEnlazada *pila_descarte = inicializarPila(NUM_CARTAS);
    ListaEnlazada *mano = crearListaEnlazada();
    robarCartas(pila_robo, mano);


    
       printf("Mano:\n");
       imprimirListaCartas(mano);
       printf("\n");
       printf("Pila de robado:\n");
       imprimirPila(pila_robo);
    

    printf("Recuerde que, AT=Ataque, DF=Defensa,LF= Efecto en vida  y EN=Costo de energia \n");
    
    while (jugador.personaje.vida_actual > 0 && enemigo.personaje.vida_actual > 0) {
    	//jugador.personaje.vida_actual, enemigo.personaje.vida_actual, mano, pila_robo, pila_descarte
    	robarCartas(pila_robo, mano);
    	turno(enemigo, jugador, ListaEnlazada* mano, Pila* pila_robo, ListaEnlazada* pila_descarte);
    	void moverCartasAlFinalizarTurno(ListaEnlazada* mini_deck, ListaEnlazada* pila_descarte);
		
		if (enemigo.personaje.ataque > jugador.defensa){
			jugador.personaje.vida_actual -= jugador.defensa + enemigo.personaje.ataque;
			printf("el enemigo ha generado %d dano\n", enemigo.personaje.ataque - jugador.defensa);
		}
		else{
			printf("¡Has bloqueado el ataque!\n");
		}
		

        if (jugador.personaje.vida_actual <= 0) {
            printf("HAS PERDIDO\n");
            jugar = 0;
        }
        else if (enemigo.personaje.vida_actual <= 0) {

            printf("HAS  GANADO, SELECIONA UNA DE LAS 3 CARTAS\n");
            Carta *cartas3 = seleccionarTresCartasAleatorias(cartas_disponibles, deck_general);
            // Imprimir las cartas seleccionadas
            printf("Cartas a seleccionar:\n");
            for (int i = 0; i < 3; i++) {
                printf("%s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n", cartas3[i].nombre,
                       cartas3[i].ataque, cartas3[i].defensa,
                       cartas3[i].vida, cartas3[i].energia);
            }
            jugar = 0;

        }
    }
    


       // Liberar memoria
       free(deck_general);
       free(pila_robo->cartas);
       free(pila_robo);
       free(pila_descarte);

       return 0;
   }
   // funcion de la pelea
   
	void turno(struct Enemigo enemigo, struct Jugador jugador, ListaEnlazada* mano, Pila* pila_robo, ListaEnlazada* pila_descarte){
		jugador.personaje.ataque=0;
		jugador.defensa=0;
		jugador.energia=3;
		jugador.termino = 1;
		enemigo.personaje.ataque = rand() % 8 + 5;
		while (jugador.termino!=0){
			printf("Hola %s, tu vida es &d/%d\n", jugador.personaje.nombre, jugador.personaje.vida_actual, jugador.personaje.vida_total);
			printf("Su enemigo se llama %s, su vida es de %d/%d", enemigo.personaje.nombre, enemigo.personaje.vida_actual, enemigo.personaje.vida_total);
			printf("----------------- \n");
		    printf("\n Las cartas disponibles son: \n");
		    printf("Mano:\n");
	    	imprimirListaCartas(mano);
	       	printf("\n");
	       	printf("Las cartas restantes en la Pila de robado son:\n");
	       	imprimirPila(pila_robo);
	       	printf("por favor seleccione su carta, o escriba 0 para terminar finalizar turno\n");
		    printf("\n ----------------- \n");
		    scanf("%d", jugador.seleccion);
		    if (jugador.seleccion==0){
		    	jugador.termino = 0;
				printf("\n ----------------- \n");
	            printf("turno finalizado\n");
		    }
			else if (jugador.seleccion!=0 && jugador.energia>0){
				jugador.personaje.ataque += Carta[jugador.seleccion-1]->ataque;
				jugador.defensa += Carta[jugador.seleccion-1]->defensa;
				jugador.energia -= Carta[jugador.seleccion-1]->energia;
				jugador.personaje.vida_actual += Carta[jugador.seleccion]->vida;
				
				moverCartaAMiniDeck(ListaEnlazada* mini_deck, ListaEnlazada* pila_descarte);
				
				if (enemigo.personaje.vida_actual > 0){
					printf("has generado %d dano a tu enemigo\n", jugador.personaje.ataque);
					enemigo.personaje.vida_actual -=jugador.personaje.ataque;
				}
			}
			else {
				printf("ERROR\n");
			}
		} 
	    
	}
	
   // Función para crear un nodo de la lista enlazada
   Nodo* crearNodo(Carta carta) {
       Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
       nuevoNodo->carta = carta;
       nuevoNodo->siguiente = NULL;
       return nuevoNodo;
   }

   // Función para crear una lista enlazada vacía
   ListaEnlazada* crearListaEnlazada() {
       ListaEnlazada* lista = (ListaEnlazada*)malloc(sizeof(ListaEnlazada));
       lista->cabeza = NULL;
       lista->longitud = 0;
       return lista;
   }

   // Función para agregar un nodo al final de la lista enlazada
   void agregarAlFinal(ListaEnlazada* lista, Carta carta) {
       Nodo* nuevoNodo = crearNodo(carta);
       if (lista->cabeza == NULL) {
           lista->cabeza = nuevoNodo;
       } else {
           Nodo* actual = lista->cabeza;
           while (actual->siguiente != NULL) {
               actual = actual->siguiente;
           }
           actual->siguiente = nuevoNodo;
       }
       lista->longitud++;
   }

   // Función para inicializar una pila
   Pila* inicializarPila(int capacidad) {
       Pila* pila = (Pila*)malloc(sizeof(Pila));
       pila->cartas = (Carta*)malloc(capacidad * sizeof(Carta));
       pila->tope = -1;
       pila->capacidad = capacidad;
       return pila;
   }

   // Función para apilar una carta en la pila
   void apilar(Pila* pila, Carta carta) {
       if (pila->tope < pila->capacidad - 1) {
           pila->tope++;
           pila->cartas[pila->tope] = carta;
       } else {
           printf("La pila está llena.\n");
       }
   }

   // Función para desapilar una carta de la pila
   Carta desapilar(Pila* pila) {
       if (pila->tope >= 0) {
           Carta carta = pila->cartas[pila->tope];
           pila->tope--;
           return carta;
       } else {
           printf("La pila está vacía.\n");
           Carta carta_vacia = {"", 0, 0, 0, 0};
           return carta_vacia;
       }
   }

   // Función para barajar un array de cartas
   void barajarListaYApilar(ListaEnlazada* lista, Pila* pila_robo) {
       srand(time(NULL));

       // Obtener la longitud de la lista
       int longitud = lista->longitud;

       // Convertir la lista enlazada a un array de punteros a nodo
       Nodo** nodos = (Nodo**)malloc(longitud * sizeof(Nodo*));
       Nodo* actual = lista->cabeza;
       int i = 0;
       while (actual != NULL) {
           nodos[i] = actual;
           actual = actual->siguiente;
           i++;
       }

       // Barajar los punteros en el array
       for (i = longitud - 1; i > 0; i--) {
           int j = rand() % (i + 1);
           Nodo* temp = nodos[i];
           nodos[i] = nodos[j];
           nodos[j] = temp;
       }

       // Reconstruir la lista enlazada con los nodos barajados
       lista->cabeza = nodos[0];
       for (i = 0; i < longitud - 1; i++) {
           nodos[i]->siguiente = nodos[i + 1];
       }
       nodos[longitud - 1]->siguiente = NULL;

       // Apilar los nodos barajados en la pila de robo
       for (i = 0; i < longitud; i++) {
           apilar(pila_robo, nodos[i]->carta);
       }

       // Liberar memoria del array de nodos
       free(nodos);
   }


   // Función para imprimir el contenido de una lista enlazada de cartas

   void imprimirListaCartas(ListaEnlazada* lista) {
       Nodo* actual = lista->cabeza;
       while (actual != NULL) {
           printf("%s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n", actual->carta.nombre, actual->carta.ataque, actual->carta.defensa, actual->carta.vida, actual->carta.energia);
           actual = actual->siguiente;
       }
   }




   void seleccionarCartasDeck(Carta* cartas_disponibles, ListaEnlazada* deck_general, int num_cartas_inicial) {
       srand(time(NULL));
       int cartas_seleccionadas[num_cartas_inicial]; // Array para registrar las cartas seleccionadas
       for (int i = 0; i < num_cartas_inicial; i++) {
           cartas_seleccionadas[i] = 0; // Inicializar todas las cartas como no seleccionadas
       }

       // Seleccionar aleatoriamente las cartas sin repetición
       int cartas_seleccionadas_count = 0;
       while (cartas_seleccionadas_count < num_cartas_inicial) {
           int indice_carta = rand() % NUM_CARTAS; // Seleccionar un índice aleatorio dentro del rango del array de cartas disponibles
           if (cartas_seleccionadas[indice_carta] == 0) { // Verificar si la carta ya fue seleccionada
               agregarAlFinal(deck_general, cartas_disponibles[indice_carta]); // Agregar la carta al deck general
               cartas_seleccionadas[indice_carta] = 1; // Marcar la carta como seleccionada
               cartas_seleccionadas_count++;
           }
       }
   }

   void robarCartas(Pila* pila_robo, ListaEnlazada* mano) {
       // Vaciar la mano actual (limpiar la lista enlazada)
       while (mano->cabeza != NULL) {
           Nodo* temp = mano->cabeza;
           mano->cabeza = mano->cabeza->siguiente;
           free(temp);
       }
       mano->longitud = 0;

       // Desapilar cartas de la pila de robo y agregarlas a la mano hasta que tenga 5 cartas
       while (mano->longitud < 5 && pila_robo->tope >= 0) {
           Carta carta = desapilar(pila_robo);
           agregarAlFinal(mano, carta);
       }
   }



   void imprimirPila(Pila* pila) {
       if (pila->tope == -1) {
           printf("La pila está vacía.\n");
       } else {
           for (int i = pila->tope; i >= 0; i--) {
               printf("%s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n",
                      pila->cartas[i].nombre, pila->cartas[i].ataque,
                      pila->cartas[i].defensa, pila->cartas[i].vida,
                      pila->cartas[i].energia);
           }
       }
   }

   Carta* seleccionarTresCartasAleatorias(Carta* cartas_disponibles, ListaEnlazada* deck_general) {
       // Inicializar un array estático para almacenar las tres cartas seleccionadas
       static Carta cartas_seleccionadas[3];

       // Obtener una lista de los nombres de las cartas en el deck general
       char* nombres_en_deck[deck_general->longitud];
       Nodo* actual = deck_general->cabeza;
       int i = 0;
       while (actual != NULL) {
           nombres_en_deck[i] = actual->carta.nombre;
           actual = actual->siguiente;
           i++;
       }

       // Semilla para la generación de números aleatorios
       srand(time(NULL));

       // Seleccionar tres cartas aleatorias que no estén en el deck general
       int cartas_seleccionadas_count = 0;
       for (int k = 0; k < NUM_CARTAS && cartas_seleccionadas_count < 3; k++) {
           // Verificar si el nombre de la carta está en el deck general
           int encontrado = 0;
           for (int j = 0; j < deck_general->longitud && encontrado == 0; j++) {
               if (strcmp(cartas_disponibles[k].nombre, nombres_en_deck[j]) == 0) {
                   encontrado = 1;
               }
           }
           // Si no se encuentra en el deck general, se agrega a las cartas seleccionadas
           if (!encontrado) {
               cartas_seleccionadas[cartas_seleccionadas_count] = cartas_disponibles[k];
               cartas_seleccionadas_count++;
           }
       }

       // Devolver el array de cartas seleccionadas
       return cartas_seleccionadas;
   }

   Carta obtenerCartaEnIndice(ListaEnlazada* lista, int indice) {
       Carta carta;
       int bool = 0;
       // Verificar si la lista está vacía o el índice es negativo
       if (lista == NULL || lista->cabeza == NULL || indice < 0) {
           // Manejar el caso de una lista vacía o un índice inválido
           bool = 1;
       }
       if (bool == 0) {
           Nodo *actual = lista->cabeza;
           int contador = 0;

           // Avanzar hasta el nodo en el índice dado
           while (actual != NULL && contador < indice) {
               actual = actual->siguiente;
               contador++;
           }

           if (actual != NULL) {
               carta = actual->carta;
           }
           else{
               printf("fuera de rango\n");
           }
       }
       return  carta;
       }

   // Función para mover una carta del mini deck a la pila de descarte
   void moverCartaAMiniDeck(ListaEnlazada* mini_deck, ListaEnlazada* pila_descarte) {
       // Verificar si el mini deck no está vacío
       if (mini_deck->longitud > 0) {
           // Obtener la primera carta del mini deck
           Carta carta = mini_deck->cabeza->carta;

           // Agregar la carta a la pila de descarte
           agregarAlFinal(pila_descarte, carta);

           // Eliminar la carta del mini deck
           Nodo* temp = mini_deck->cabeza;
           mini_deck->cabeza = mini_deck->cabeza->siguiente;
           free(temp);
           mini_deck->longitud--;

           printf("La carta se ha movido del mini deck a la pila de descarte.\n");
       }
   }

   // Función para mover todas las cartas del mini deck a la pila de descarte al finalizar el turno del jugador
   void moverCartasAlFinalizarTurno(ListaEnlazada* mini_deck, ListaEnlazada* pila_descarte) {
       // Verificar si el mini deck no está vacío
       while (mini_deck->longitud > 0) {
           // Obtener la primera carta del mini deck
           Carta carta = mini_deck->cabeza->carta;

           // Agregar la carta a la pila de descarte
           agregarAlFinal(pila_descarte, carta);

           // Eliminar la carta del mini deck
           Nodo* temp = mini_deck->cabeza;
           mini_deck->cabeza = mini_deck->cabeza->siguiente;
           free(temp);
           mini_deck->longitud--;
       }
   }
