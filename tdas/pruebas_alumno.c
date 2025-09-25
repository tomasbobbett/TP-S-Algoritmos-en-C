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
	int ultimo = 100;
	int medio = 50;
	lista_t *lista =  lista_crear();
	lista_agregar(lista,&num);
	lista_agregar(lista,&num2);
	pa2m_afirmar(lista_eliminar_elemento(lista,0) == &num && lista_eliminar_elemento(lista,0) == &num2,
	"Eliminar el PRIMER elemento de la lista devuelve el valor eliminado correctamente");
	lista_agregar(lista,&num);
	lista_agregar(lista,&medio);
	lista_agregar(lista,&num);
	lista_agregar(lista,&ultimo);
	pa2m_afirmar(lista_eliminar_elemento(lista,lista_cantidad(lista)-1) == &ultimo,
	"Eliminar el ULTIMO elemento de la lista devuelve el valor eliminado correctamente");
	pa2m_afirmar(lista_eliminar_elemento(lista,(lista_cantidad(lista)-1)/2) == &medio,
	"Eliminar el elemento del MEDIO de la lista devuelve el valor eliminado correctamente");
	pa2m_afirmar(!lista_eliminar_elemento(lista,50),
	"Intentar eliminar en una posicion inexistente devuelve NULL");
	pa2m_afirmar(lista_eliminar_elemento(lista,1) == &num,
	"Eliminar el ulitmo en una lista de DOS elementos devuelve el valor eliminado correctamente");
	pa2m_afirmar(lista_eliminar_elemento(lista,0) == &num,
	"Eliminar el ulitmo en una lista de UN elemento devuelve el valor eliminado correctamente");
	pa2m_afirmar(lista_cantidad(lista) == 0,
	"La cantidad de elementos es 0 luego de eliminar todos los elementos de la lista");
	pa2m_afirmar(lista_eliminar_elemento(lista,0) == NULL,
	"Intentar eliminar algun elemento luego de eliminar todos devuelve NULL");
}

void prueba_lista_agregar_insertar() {
    int a = 1, b = 2, c = 3, d = 4;
    lista_t *lista = lista_crear();
    pa2m_afirmar(lista_agregar(lista, &a), "Agregar elemento al final devuelve true");
    pa2m_afirmar(lista_agregar(lista, &b), "Agregar segundo elemento al final devuelve true");
    pa2m_afirmar(lista_insertar(lista, &c, 1), "Insertar elemento en posicion intermedia devuelve true");
    pa2m_afirmar(lista_insertar(lista, &d, 0), "Insertar elemento en posicion 0 devuelve true");
    pa2m_afirmar(lista_cantidad(lista) == 4, "Cantidad de elementos es correcta luego de agregar/insertar");
    pa2m_afirmar(lista_buscar_elemento(lista, 0) == &d, "Primer elemento es el correcto tras insercion");
    pa2m_afirmar(lista_buscar_elemento(lista, 1) == &a, "Elemento en posicion 1 es correcto");
    pa2m_afirmar(lista_buscar_elemento(lista, 2) == &c, "Elemento en posicion 2 es correcto");
    pa2m_afirmar(lista_buscar_elemento(lista, 3) == &b, "Ultimo elemento es correcto");
}
int main()
{
	pa2m_nuevo_grupo("============== LISTA RECIEN CREADA ===============");
	prueba_lista_vacia();
	pa2m_nuevo_grupo("============== LISTA ELIMINAR ===============");
	prueba_lista_borrar();
	pa2m_nuevo_grupo("============== LISTA AGREGAR-INSERTAR ===============");
	prueba_lista_agregar_insertar();
	return pa2m_mostrar_reporte();
}
