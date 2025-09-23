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
    if (posicion > lista->cantidad || lista->cantidad==0){
        return false;
    }
    if (posicion == 0){
        nodo_t *cabeza_vieja = lista->cabeza; 
        nodo_t *nuevo_nodo = crear_nodo(elemento, cabeza_vieja);
        lista->cabeza = nuevo_nodo;
        lista->cantidad++;
        return true;
    }else if (posicion == lista->cantidad - 1){
        lista_agregar(lista, elemento);
    }
    size_t posicion_actual = 0;
    nodo_t *act = lista->cabeza;
    while (posicion_actual != posicion-1){
        act = act->siguiente;
        posicion_actual++;
    }    // 4, 5, 6, 4, 5
    nodo_t *nuevo_nodo = crear_nodo(elemento, act->siguiente);
    act->siguiente = nuevo_nodo;
    lista->cantidad++;
    return true;
}
// lista_eliminar_elemento: O(n)
void *lista_eliminar_elemento(lista_t *lista, size_t posicion){
    if (lista->cantidad == 0 || posicion > lista->cantidad ){
        return false;
    }
    if (posicion == 0){
        nodo_t *borrado = lista->cabeza;
        lista->cabeza = borrado->siguiente;
        lista->cantidad--;
        return borrado->dato;
    }else if (posicion == lista->cantidad - 1){
        nodo_t *borrado = lista->cola;

        //IMPLEMETAR BORRAR ULTIMO NO SE COMO MIERDA HACER////////////////////////////////////////
        
        return borrado->dato;
    }
    return lista->cabeza;
}

// lista_buscar_posicion: O(n)

// lista_buscar_elemento: O(n)

// lista_con_cada_elemento: **O(n)hasta quefdevuelvafalse`

// Iterador: avanzar y obtener actual son O(1)