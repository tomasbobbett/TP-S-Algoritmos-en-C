#ifndef MAIN_AUX_H_
#define MAIN_AUX_H_
#include "tp1.h"
#include "lista.h"
#include <string.h>


#define BUSCAR "buscar"
#define ID "id"
#define NOMBRE "nombre"

//
void imprimir_pokemon(const struct pokemon *p);

//
void imprimir_uso(const char *prog);

/* Callback para insertar en lista con tp1_con_cada_pokemon */
bool insertar_en_lista(struct pokemon *p, void *lista);

/* Busca un pokemon por nombre recorriendo la lista */
struct pokemon *buscar_por_nombre(lista_t *lista, const char *nombre);

/* Busca un pokemon por id recorriendo la lista */
struct pokemon *buscar_por_id(lista_t *lista, int id);

#endif // MAIN_AUX_H