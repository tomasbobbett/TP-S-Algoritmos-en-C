#include "cola.h"
#include "lista.h"

struct cola{
    lista_t *lista_elementos;
};

cola_t *cola_crear(){
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola){
        return NULL;
    }
    cola->lista_elementos = lista_crear();
    return cola;
}

bool cola_encolar(cola_t *cola, void *elemento){
    if (lista_agregar(cola->lista_elementos,elemento)){
        return true;
    }
    return false;
}

void *cola_desencolar(cola_t *cola){
    if (lista_cantidad(cola->lista_elementos) == 0){
        return NULL;
    }
    return lista_eliminar_elemento(cola->lista_elementos, 0);
}

void *cola_ver_primero(cola_t *cola){
    if (lista_cantidad(cola->lista_elementos) == 0){
        return NULL;
    }
    return lista_buscar_elemento(cola->lista_elementos, 0);
}

size_t cola_cantidad(cola_t *cola){
    return lista_cantidad(cola->lista_elementos);
}

void cola_destruir(cola_t *cola){
    lista_destruir(cola->lista_elementos);
    free(cola);
}