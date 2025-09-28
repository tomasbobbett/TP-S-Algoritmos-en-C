#ifndef COLA_H_
#define COLA_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct cola cola_t;

/**
  Crea una cola vacia
  Pre: -------------
  Post: devuelve una cola vacia o NULL si no hay memoria
 */
cola_t *cola_crear();

/**
  Encola un elemento al final de la cola
  Pre: la cola fue creada
  Post: devuelve true si se encoloo, false si no habia memoria
 */
bool cola_encolar(cola_t *cola, void *elemento);

/**
  Desencola el primer elemento de la cola
  Pre: la cola fue creads
  Post: devuelve el primer elemento o NULL si la cola estaba vacia
 */
void *cola_desencolar(cola_t *cola);

/**
  Devuelve el primer elemento de la cola sin desencolar
  Pre: la cola fue creada
  Post: devuelve el prime r elemento o NULL si la cola esta vacia
 */
void *cola_ver_primero(cola_t *cola);

/**
  Devuelve la cantidad de elementos en la cola
  Pre: la cola fue creada
  Post: devuelve el número de elementos en la cola
 */
size_t cola_cantidad(cola_t *cola);

/**
  Destruye la cola y libera la memoria asociada
  Pre: la cola fue creada
  Post: la cola fue destruida
 */
void cola_destruir(cola_t *cola);

#endif // COLA_H_
