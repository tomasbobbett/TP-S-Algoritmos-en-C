#include "src/tp1.h"
#include "src/lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUSCAR "buscar"
#define ID "id"
#define NOMBRE "nombre"

static void imprimir_pokemon(const struct pokemon *p)
{
	if (!p)
		return;
	printf("ID: %d, ", p->id);
	printf("Nombre: %s, ", p->nombre ? p->nombre : "(null)");
	printf("Tipo: %d, ", (int)p->tipo);
	printf("Ataque: %d, Defensa: %d, Velocidad: %d\n", p->ataque,
	       p->defensa, p->velocidad);
}

static void imprimir_uso(const char *prog)
{
	fprintf(stderr, "Uso:\n");
	fprintf(stderr, "  %s <archivo.csv> buscar nombre <nombre>\n", prog);
	fprintf(stderr, "  %s <archivo.csv> buscar id <id>\n", prog);
}

/* Callback para insertar en lista con tp1_con_cada_pokemon */
bool insertar_en_lista(struct pokemon *p, void *lista)
{
	return lista_agregar((lista_t *)lista, p);
}

/* Busca un pokemon por nombre recorriendo la lista */
struct pokemon *buscar_por_nombre(lista_t *lista, const char *nombre)
{
	size_t cant = lista_cantidad(lista);
	for (size_t i = 0; i < cant; i++) {
		struct pokemon *p = lista_buscar_elemento(lista, i);
		if (p && p->nombre && strcmp(p->nombre, nombre) == 0) {
			return p;
		}
	}
	return NULL;
}

/* Busca un pokemon por id recorriendo la lista */
struct pokemon *buscar_por_id(lista_t *lista, int id)
{
	size_t cant = lista_cantidad(lista);
	for (size_t i = 0; i < cant; i++) {
		struct pokemon *p = lista_buscar_elemento(lista, i);
		if (p && p->id == id) {
			return p;
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 5 || strcmp(argv[2], BUSCAR) != 0) {
		imprimir_uso(argv[0]);
		return -1;
	}

	const char *nombre_archivo = argv[1];
	const char *modo = argv[3];
	const char *valor = argv[4];

	tp1_t *pokemones = tp1_leer_archivo(nombre_archivo);
	if (!pokemones) {
		fprintf(stderr, "Error al leer archivo '%s'\n", nombre_archivo);
		return -1;
	}

	/* Creo la lista y cargo los pokemones */
	lista_t *lista = lista_crear();
	if (!lista) {
		tp1_destruir(pokemones);
		return -1;
	}
	tp1_con_cada_pokemon(pokemones, insertar_en_lista, lista);

	struct pokemon *res = NULL;
	if (strcmp(modo, NOMBRE) == 0) {
		res = buscar_por_nombre(lista, valor);
		if (res)
			imprimir_pokemon(res);
		else
			printf("No se encontró pokemon con nombre '%s'\n",
			       valor);
	} else if (strcmp(modo, ID) == 0) {
		int id = atoi(valor);
		res = buscar_por_id(lista, id);
		if (res)
			imprimir_pokemon(res);
		else
			printf("No se encontró pokemon con id %d\n", id);
	} else {
		imprimir_uso(argv[0]);
	}

	lista_destruir(
		lista); // la lista no libera pokemones, sólo los punteros
	tp1_destruir(pokemones);
	return 0;
}
