#include "lista.h"
#include <stdio.h>

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

nodo_t *crear_nodo(void *dato, nodo_t *siguiente)
{
	nodo_t *nodo_res = malloc(sizeof(nodo_t));
	if (!nodo_res) {
		free(nodo_res);
		return NULL;
	}
	nodo_res->dato = dato;
	nodo_res->siguiente = siguiente;
	return nodo_res;
}
//-------------------------IMPLEMENTACION DE PRIMITIVAS----------------------------

//crear lista o(1)
lista_t *lista_crear()
{
	lista_t *res = malloc(sizeof(lista_t));
	if (!res) {
		free(res);
		return NULL;
	}
	res->cabeza = NULL;
	res->cola = NULL;
	res->cantidad = 0;

	return res;
}

// lista_vacia: O (1)
bool lista_vacia(lista_t *lista)
{
	if (!lista) {
		return true;
	}
	return (lista->cantidad == 0);
}

//lista_cantidad: O(1)
size_t lista_cantidad(lista_t *lista)
{
	if (!lista) {
		return 0;
	}
	return lista->cantidad;
}

// lista_agregar (al final): O(1)
bool lista_agregar(lista_t *lista, void *dato)
{
	if (lista == NULL) {
		return false;
	}
	nodo_t *nodo = crear_nodo(dato, NULL);
	if (!nodo) {
		return false;
	}
	if (lista->cantidad == 0) {
		lista->cola = nodo;
		lista->cabeza = nodo;
		lista->cantidad++;
		return true;
	}
	lista->cola->siguiente = nodo;
	lista->cola = nodo;
	lista->cantidad++;
	return true;
}

// lista_insertar: O(n) (recorrer hasta la posicion) O(1) si es en la primera posicion.
bool lista_insertar(lista_t *lista, void *elemento, size_t posicion)
{
	if (!lista) {
		return NULL;
	}
	if (posicion >= lista->cantidad || lista->cantidad == 0)
		return false;

	if (posicion == 0) {
		nodo_t *nuevo_nodo = crear_nodo(elemento, lista->cabeza);
		lista->cabeza = nuevo_nodo;
		lista->cantidad++;
		return true;
	}

	size_t i = 0;
	nodo_t *act = lista->cabeza;
	while (i < posicion - 1) {
		act = act->siguiente;
		i++;
	}
	nodo_t *nuevo_nodo = crear_nodo(elemento, act->siguiente);
	act->siguiente = nuevo_nodo;
	lista->cantidad++;
	return true;
}

// lista_eliminar_elemento: O(n) - o(1) si es el primer elemento
void *lista_eliminar_elemento(lista_t *lista, size_t posicion)
{
	if (!lista) {
		return NULL;
	}
	if (lista->cantidad == 0 || posicion >= lista->cantidad) {
		return NULL;
	}
	if (posicion == 0) {
		nodo_t *borrado = lista->cabeza;
		void *dato = borrado->dato;
		lista->cabeza = borrado->siguiente;
		free(borrado);
		lista->cantidad--;
		if (lista->cantidad == 0) {
			lista->cola = NULL;
		}
		return dato;
	}
	size_t posicion_actual = 0;
	nodo_t *act = lista->cabeza;
	while (posicion_actual != posicion - 1) {
		act = act->siguiente;
		posicion_actual++;
	}
	nodo_t *borrado = act->siguiente;
	void *dato = borrado->dato;
	act->siguiente = borrado->siguiente;
	free(borrado);
	if (posicion == lista->cantidad - 1) {
		lista->cola = act;
	}
	lista->cantidad--;
	return dato;
}

// lista_buscar_posicion: O(n)
int lista_buscar_posicion(lista_t *lista, void *elemento,
			  int (*comparador)(const void *, const void *))
{
	if (!lista || comparador == NULL) {
		return -1;
	}
	if (lista->cantidad == 0) {
		return -1;
	}

	nodo_t *act = lista->cabeza;
	int posicion = 0;

	while (act != NULL) {
		if (comparador(act->dato, elemento) == 0) {
			return posicion;
		}
		act = act->siguiente;
		posicion++;
	}

	return -1;
}

// lista_buscar_elemento: O(n)
void *lista_buscar_elemento(lista_t *lista, size_t posicion)
{
	if (!lista) {
		return NULL;
	}
	if (lista->cantidad == 0 || posicion >= lista->cantidad) {
		return NULL;
	}
	if (posicion == 0) {
		return lista->cabeza->dato;
	} else if (posicion == lista->cantidad - 1) {
		return lista->cola->dato;
	}
	size_t posicion_actual = 0;
	nodo_t *nodo_actual = lista->cabeza;
	while (posicion_actual != posicion) {
		nodo_actual = nodo_actual->siguiente;
		posicion_actual++;
	}
	return nodo_actual->dato;
}

// lista_con_cada_elemento: **O(n)hasta que devuelva false`
size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *),
			       void *extra)
{
	if (!lista || !f || !extra) {
		return 0;
	}
	if (lista->cantidad == 0) {
		return 0;
	}
	size_t cantidad_modificados = 0;
	nodo_t *nodo_actual = lista->cabeza;
	while (nodo_actual != NULL) {
		cantidad_modificados++;
		if (!f(nodo_actual->dato, extra)) {
			break;
		}
		nodo_actual = nodo_actual->siguiente;
	}
	return cantidad_modificados;
}

void lista_destruir(lista_t *lista)
{
	if (!lista) {
		return;
	}
	nodo_t *actual = lista->cabeza;
	while (actual) {
		nodo_t *sig = actual->siguiente;
		free(actual);
		actual = sig;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (!lista || !destructor) {
		return;
	}
	nodo_t *actual = lista->cabeza;
	while (actual) {
		nodo_t *sig = actual->siguiente;
		if (destructor) {
			destructor(actual->dato);
		}
		free(actual);
		actual = sig;
	}
	free(lista);
}

//-------------------------------------------------ITERADOR---------------------------------------------------
// Iterador: avanzar y obtener actual son O(1)

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista) {
		return NULL;
	}
	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	iterador->actual = lista->cabeza;
	return iterador;
}

bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)
{
	if (!it) {
		return false;
	}
	return it->actual != NULL;
}

void lista_iterador_siguiente(lista_iterador_t *it)
{
	if (!it) {
		return;
	}
	if (it->actual) {
		it->actual = it->actual->siguiente;
	}
}

void *lista_iterador_obtener_actual(lista_iterador_t *it)
{
	if (!it) {
		return NULL;
	}
	if (!it->actual) {
		return NULL;
	}
	return it->actual->dato;
}

void lista_iterador_destruir(lista_iterador_t *it)
{
	if (!it) {
		return;
	}
	free(it);
}
