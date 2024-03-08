#include "lista_enlazada.h"
#include <stdio.h>
#include <stdlib.h>

void insertarAlInicio(struct Nodo **cabeza, int dato) {
    // Crear un nuevo nodo
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = *cabeza;

    // Actualizar la cabeza de la lista para que apunte al nuevo nodo
    *cabeza = nuevoNodo;
}

// Función para imprimir los elementos de la lista
void imprimirLista(struct Nodo *cabeza) {
    printf("Lista enlazada: ");
    while (cabeza != NULL) {
        printf("%d -> ", cabeza->dato);
        cabeza = cabeza->siguiente;
    }
    printf("NULL\n");
}

// Función para ordenar la lista enlazada utilizando el algoritmo de inserción
void ordenarListaAsc(struct Nodo **cabeza) {
    struct Nodo *actual = *cabeza;
    struct Nodo *indice;

    // Caso base: si la lista está vacía o tiene solo un elemento, ya está ordenada
    if (actual == NULL || actual->siguiente == NULL)
        return;

    // Recorrer la lista
    while (actual != NULL) {
        indice = actual->siguiente;

        // Recorrer la lista desde el inicio hasta el nodo actual
        while (indice != NULL) {
            // Si se encuentra un elemento menor, intercambiar los datos
            if (actual->dato > indice->dato) {
                int temp = actual->dato;
                actual->dato = indice->dato;
                indice->dato = temp;
            }
            indice = indice->siguiente;
        }
        actual = actual->siguiente;
    }
}

void ordenarListaDesc(struct Nodo **cabeza) {
    struct Nodo *actual = *cabeza;
    struct Nodo *indice;
    struct Nodo *max;

    // Caso base: si la lista está vacía o tiene solo un elemento, ya está ordenada
    if (actual == NULL || actual->siguiente == NULL)
        return;

    // Recorrer la lista
    while (actual != NULL) {
        indice = actual->siguiente;
        max = actual;

        // Buscar el nodo con el dato máximo
        while (indice != NULL) {
            if (indice->dato > max->dato)
                max = indice;
            indice = indice->siguiente;
        }

        // Intercambiar el dato del nodo actual con el dato del nodo con el máximo
        int temp = actual->dato;
        actual->dato = max->dato;
        max->dato = temp;

        actual = actual->siguiente;
    }
}