#include "lista.h"
#include <stdio.h>

typedef struct nodo {
    void *dato;
    struct nodo *siguiente;
} nodo_t;

struct lista {
    nodo_t *cabeza;
    nodo_t *cola;
    size_t cantidad;
};

struct lista_iterador {
    nodo_t *actual;
};

nodo_t *crear_nodo(void *dato, nodo_t *siguiente){
    nodo_t *nodo_res = malloc(sizeof(nodo_t));
    if (!nodo_res){
        free(nodo_res);
        return NULL;
    }
    nodo_res->dato = dato;
    nodo_res->siguiente = siguiente;
    return nodo_res;
}   
//-------------------------IMPLEMENTACION DE PRIMITIVAS----------------------------
//crear lista
lista_t *lista_crear(){
    lista_t *res = malloc(sizeof(lista_t));
    if (!res){
        free(res);
        return NULL;
    }
    res->cabeza = NULL;
    res->cola = NULL;
    res->cantidad = 0;

    return res;
}

// lista_vacia, lista_cantidad: O(1)
bool lista_vacia(lista_t *lista){
    return (lista->cantidad == 0);
}

size_t lista_cantidad(lista_t *lista){
    return lista->cantidad;
}


// lista_agregar (al final): O(1) (si guardamos cola)
bool lista_agregar(lista_t *lista, void *dato){
    nodo_t *nodo = crear_nodo(dato,NULL); 
    if (!nodo){
        return false;
    }
    if (lista->cantidad == 0){
        lista->cola = nodo;
        lista->cabeza = nodo;
        lista->cantidad++;
        return true;
    }
    lista->cola->siguiente = nodo; 
    lista->cola = nodo;
    lista->cantidad++;
    return true;
}
// lista_insertar: O(n) (recorrer hasta la posición)
bool lista_insertar(lista_t *lista, void *elemento, size_t posicion){
    if (posicion >= lista->cantidad) return false; // posición inválida

    if (posicion == 0) { // insertar al principio
        nodo_t *nuevo_nodo = crear_nodo(elemento, lista->cabeza);
        lista->cabeza = nuevo_nodo;
        if (lista->cantidad == 0){
            lista->cola = nuevo_nodo;//la lista esta vacia
        } 
        lista->cantidad++;
        return true;
    }

    // insertar en el medio (posición entre 1 y cantidad-1)
    size_t i = 0;
    nodo_t *act = lista->cabeza;
    while (i < posicion - 1) {
        act = act->siguiente;
        i++;
    }
    nodo_t *nuevo_nodo = crear_nodo(elemento, act->siguiente);
    act->siguiente = nuevo_nodo;
    lista->cantidad++;
    return true;
}
// lista_eliminar_elemento: O(n)
void *lista_eliminar_elemento(lista_t *lista, size_t posicion){
    if (lista->cantidad == 0 || posicion >= lista->cantidad ){
        return NULL;
    }
    if (posicion == 0){
        nodo_t *borrado = lista->cabeza;
        void *dato = borrado->dato;
        lista->cabeza = borrado->siguiente;
        free(borrado);
        lista->cantidad--;
        if (lista->cantidad == 0) {
            lista->cola = NULL;
        }
        return dato;
    }
    size_t posicion_actual = 0;
    nodo_t *act = lista->cabeza;
    while (posicion_actual != posicion - 1)
    {
        act = act->siguiente;
        posicion_actual++;
    }
    nodo_t *borrado = act->siguiente;
    void *dato = borrado->dato;   // Guardamos el dato antes del free
    act->siguiente = borrado->siguiente;
    free(borrado);
    if (posicion == lista->cantidad - 1){
        lista->cola = act;
    }
    lista->cantidad--;
    return dato;
}

// lista_buscar_posicion: O(n)
int lista_buscar_posicion(lista_t *lista, void *elemento,int (*comparador)(const void *, const void *)){
        

}
// lista_buscar_elemento: O(n)
void *lista_buscar_elemento(lista_t *lista, size_t posicion){
    if (lista->cantidad == 0 || posicion >= lista->cantidad ){
        return NULL;
    }
    if (posicion == 0){
        return lista->cabeza->dato;
    }else if (posicion == lista->cantidad-1){
        return lista->cola->dato;
    }
    size_t posicion_actual = 0;
    nodo_t *nodo_actual = lista->cabeza;
    while (posicion_actual != posicion){
        nodo_actual = nodo_actual->siguiente;
        posicion_actual++;
    }
    return nodo_actual->dato;
}

// lista_con_cada_elemento: **O(n)hasta quefdevuelvafalse`

// Iterador: avanzar y obtener actual son O(1)