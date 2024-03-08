#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

void insertarAlInicio(struct Nodo **cabeza, int dato);
void imprimirLista(struct Nodo *cabeza);
void ordenarLista(struct Nodo **cabeza);

#endif