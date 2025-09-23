#include "pa2m.h"
#include "src/lista.h"



void prueba_lista_vacia()
{
	int num = 1;
	lista_t *lista =  lista_crear();
	pa2m_afirmar(lista_cantidad(lista) == 0, "Una lista recien creada devuelve 0 de cantidad");
	pa2m_afirmar(lista_vacia(lista), "Una lista recien creada devuelve que esta vacia");
	pa2m_afirmar(lista_insertar(lista,&num,0) == false && lista_insertar(lista,&num,1) == false, "Una lista recien creada devuelve false si se intenta insertar elemento en alguna posicion");
	pa2m_afirmar(lista_eliminar_elemento(lista,0) == false, "Eliminar en una lista vacia devuelve false");
	lista_agregar(lista, &num);
	pa2m_afirmar(lista_cantidad(lista) == 1, "Agregar un elemento a la lista vacia suma la cantidad correcta");
	
	//tp1_destruir(lista);
}

void prueba_lista_borrar()
{
	int num = 1;
	int num2 = 2;
	lista_t *lista =  lista_crear();
	lista_agregar(lista,&num);
	pa2m_afirmar(lista_eliminar_elemento(lista,0) == &num, "Eliminar un elemento de la lista devuelve el valor eliminado correctamente");
	lista_agregar(lista,&num);
	lista_agregar(lista,&num2);
	pa2m_afirmar(lista_eliminar_elemento(lista,1) == &num2, "Eliminar un elemento de la lista devuelve el valor eliminado correctamente");

}

int main()
{
	pa2m_nuevo_grupo("============== LISTA RECIEN CREADA ===============");
	prueba_lista_vacia();
	pa2m_nuevo_grupo("============== LISTA ELIMINAR ===============");
	prueba_lista_borrar();
	
	return pa2m_mostrar_reporte();
}
