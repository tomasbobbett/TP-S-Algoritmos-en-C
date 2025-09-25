#include "pila.h"
#include "lista.h"


typedef struct pila{
    lista_t *lista_elementos;
};

pila_t *pila_crear(){
    pila_t *pila = malloc(sizeof(pila_t));
    if (!pila){
        return NULL;
    }
    pila->lista_elementos = lista_crear();
    return pila;
}

bool pila_apilar(pila_t *pila, void *elemento){
    if ( lista_cantidad(pila->lista_elementos) == 0){
        lista_agregar(pila->lista_elementos,elemento);
    }
    if (lista_insertar(pila->lista_elementos, 0, elemento)){
        return true;
    }
    return false;
}

void *pila_desapilar(pila_t *pila){
    if (lista_cantidad(pila->lista_elementos) == 0){
        return NULL;
    }
    return lista_eliminar_elemento(pila->lista_elementos,0);
}

void *pila_ver_primero(pila_t *pila){
    if (lista_cantidad(pila->lista_elementos) == 0){
        return NULL;
    }
    return lista_buscar_elemento(pila->lista_elementos, 0);
}

size_t pila_cantidad(pila_t *pila){
    return lista_cantidad(pila->lista_elementos);
}

void pila_destruir(pila_t *pila){
    free(pila->lista_elementos);
    free(pila);
}