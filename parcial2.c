#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 14
#define MANO_JUGADOR 5
#define INICIAL_DECK 7

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
    char* nombre;
    int vida_actual;
    int vida_total;
} Personaje;

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
void barajar(Carta* cartas, int n);
Carta seleccionarCartaAleatoria(Carta* cartas_disponibles);
void seleccionarCartasDeck (Carta* cartas_disponibles, ListaEnlazada* deck_general, int num_cartas_inicial);

int main() {
    // Definir todas las cartas disponibles en el juego
    Carta cartas_disponibles[NUM_CARTAS] = {
            {"Ataque", 5, 0, 0, -1},
            {"Defensa", 0, 5, 0, -1},
            {"Ultima Sangre", 12, 0, -5, -1},
            {"Milagro", 0, 0, 0, 1},
            {"Resplandor", 15, 0, 0, -2},
            {"Desvio", 0, 12, 0, -2},
            {"Rebote", 5, 5, 0, -1},
            {"Furia", 8, 3, 0, -2},
            {"Escudo Divino", 0, 10, 0, -2},
            {"Bendición", 0, 0, 15, -3},
            {"Contraataque", 6, 0, 0, -2},
            {"Curación", 0, 0, 20, -3},
            {"Fuego Sagrado", 10, 0, 0, -3},
            {"Meditación", 0, 0, 0, 3}

    };


    // Crear el deck general con las cartas iniciales
    ListaEnlazada* deck_general = crearListaEnlazada();
    seleccionarCartasDeck(cartas_disponibles, deck_general, INICIAL_DECK);

    // Prueba de impresion de cartas aleatorias para la Mano
    printf("Deck General:\n");
    Nodo* actual = deck_general->cabeza;
    while (actual != NULL) {
        printf("%s (AT: %d, DF: %d, Vida: %d, Energia: %d)\n", actual->carta.nombre, actual->carta.ataque, actual->carta.defensa, actual->carta.vida, actual->carta.energia);
        actual = actual->siguiente;
    }


    // Barajar el deck general y colocarlo en la pila de robo
    barajar(cartas_disponibles, NUM_CARTAS);
    Pila* pila_robo = inicializarPila(NUM_CARTAS);
    for (int i = 0; i < NUM_CARTAS; i++) {
        apilar(pila_robo, cartas_disponibles[i]);
    }

    // Inicializar la pila de descarte
    Pila* pila_descarte = inicializarPila(NUM_CARTAS);

    // Implementar el resto de la lógica del combate aquí

    // Liberar memoria
    free(deck_general);
    free(pila_robo->cartas);
    free(pila_robo);
    free(pila_descarte->cartas);
    free(pila_descarte);

    return 0;
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
void barajar(Carta* cartas, int n) {
    if (n > 1) {
        srand(time(NULL));
        for (int i = 0; i < n - 1; i++) {
            int j = i + rand() / (RAND_MAX / (n - i) + 1);
            Carta temp = cartas[j];
            cartas[j] = cartas[i];
            cartas[i] = temp;
        }
    }
}

// Función para seleccionar aleatoriamente una carta de entre tres opciones
Carta seleccionarCartaAleatoria(Carta* cartas_disponibles) {
    srand(time(NULL));
    int indice = rand() % 3;
    return cartas_disponibles[indice];
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