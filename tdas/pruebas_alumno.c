#include "pa2m.h"
#include "src/lista.h"
void prueba_lista_vacia()
{
	lista_t *lista =  lista_crear();
	pa2m_afirmar(lista_cantidad(lista) == 0, "Una lista recien creada devuelve 0 de cantidad");
	pa2m_afirmar(lista_vacia(lista), "Una lista recien creada devuelve que esta vacia");
	
	//tp1_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo("============== LISTA RECIEN CREADA ===============");
	prueba_lista_vacia();

	return pa2m_mostrar_reporte();
}
