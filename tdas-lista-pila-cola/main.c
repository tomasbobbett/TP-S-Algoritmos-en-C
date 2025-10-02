#include "src/tp1.h"
#include "src/lista.h"
#include "src/main_aux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
