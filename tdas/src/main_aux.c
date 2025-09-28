#include "main_aux.h"
#include <stdio.h>
#include <stdlib.h>

void imprimir_pokemon(const struct pokemon *p)
{
	if (!p)
		return;
	printf("ID: %d, ", p->id);
	printf("Nombre: %s, ", p->nombre ? p->nombre : "(null)");
	printf("Tipo: %d, ", (int)p->tipo);
	printf("Ataque: %d, Defensa: %d, Velocidad: %d\n", p->ataque,
	       p->defensa, p->velocidad);
}

void imprimir_uso(const char *prog)
{
	fprintf(stderr, "Uso:\n");
	fprintf(stderr, "  %s <archivo.csv> buscar nombre <nombre>\n", prog);
	fprintf(stderr, "  %s <archivo.csv> buscar id <id>\n", prog);
}

bool insertar_en_lista(struct pokemon *p, void *lista)
{
	return lista_agregar((lista_t *)lista, p);
}

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
