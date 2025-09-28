#ifndef PILA_H_
#define PILA_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct pila pila_t;

/**
  Crea una pila vacia
  Pre: ----
  Post: devuelve una pila vacia o NULL si no hay memoria
 */
pila_t *pila_crear();

/**
  Apila un elemento en el tope de la pila
  Pre: la pila fue creada
  Post: devuelve true si se apilo, false si no habia memora
 */
bool pila_apilar(pila_t *pila, void *elemento);

/**
  Desapila el elemento del tope de la pila
  Pre: la pila fue creada
  Post: devuelve el elemento desapilado o NULL si la pila estaba vacia
 */
void *pila_desapilar(pila_t *pila);

/**
  Devuelve el elemento en el tope de la pila sin desapilar
  Pre: la pila fue creada
  Post: devuelve el elemento en el tope o NULL si la pila esta vacia
 */
void *pila_ver_primero(pila_t *pila);

/**
  Devuelve la cantidad de elementos en la pila
  Pre: la pila fue creada
  Post: devuelve el nmero de elementos en la pila
 */
size_t pila_cantidad(pila_t *pila);

/**
  Destruye la pila y libera la memoria asocisda
  Pre: la pila fue creada
  Post: la pila fue destruidz
 */
void pila_destruir(pila_t *pila);

#endif // PILA_H_
