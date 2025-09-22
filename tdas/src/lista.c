#include "lista.h"


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
    if (lista->cola == NULL){
        lista->cola = crear_nodo(dato,NULL);
        lista->cantidad++;
    }
    
}
// lista_insertar: O(n) (recorrer hasta la posición)

// lista_eliminar_elemento: O(n)

// lista_buscar_posicion: O(n)

// lista_buscar_elemento: O(n)

// lista_con_cada_elemento: **O(n)hasta quefdevuelvafalse`

// Iterador: avanzar y obtener actual son O(1)