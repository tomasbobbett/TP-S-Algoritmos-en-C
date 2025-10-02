#include "src/lista.h"
#include <stdio.h>

bool mostrar_elemento(void *_elemento, void *extra)
{
	int *elemento = _elemento;
	printf("Elemento: %i\n", *elemento);
	return true;
}

int main(int argc, char *argv[])
{
	int datos[] = { 6, 1, 8, 2, 4 };
	int cantidad = sizeof(datos) / sizeof(*datos);
	lista_t *lista = lista_crear();

	for (int i = 0; i < cantidad; i++) {
		lista_agregar(lista, datos + i);
	}

	printf("Muestro la lista por pantalla O(n²)\n");
	for (int i = 0; i < cantidad; i++) {
		int *elemento = lista_buscar_elemento(lista, i);
		printf("Elemento: %i\n", *elemento);
	}

	printf("\nMuestro la lista por pantalla O(n)\n");
	lista_con_cada_elemento(lista, mostrar_elemento, NULL);

	printf("Muestro la lista por pantalla O(n)\n");
	for (lista_iterador_t *i = lista_iterador_crear(lista);
	     lista_iterador_hay_mas_elementos(i); lista_iterador_siguiente(i)) {
		int *elemento = lista_iterador_obtener_actual(i);
		printf("Elemento: %i\n", *elemento);
	}

	return 0;
}
