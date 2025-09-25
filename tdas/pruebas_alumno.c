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

int comparador_int(const void *a, const void *b) {
    if (*(int*)a == *(int*)b){
		return 0;
	}else if (*(int*)a > *(int*)b){
		return 1;
	}
    return -1;
}

void prueba_lista_buscar() {
    int a = 10, b = 20, c = 30;
    lista_t *lista = lista_crear();

    lista_agregar(lista, &a);
    lista_agregar(lista, &b);
    lista_agregar(lista, &c);

    pa2m_afirmar(*(int*)lista_buscar_elemento(lista, 0) == 10,
        "Buscar elemento en la primera posicion devuelve el correcto");
    pa2m_afirmar(*(int*)lista_buscar_elemento(lista, 1) == 20,
        "Buscar elemento en la posicion del medio devuelve el correcto");
    pa2m_afirmar(*(int*)lista_buscar_elemento(lista, 2) == 30,
        "Buscar elemento en la ultima posicion devuelve el correcto");
    pa2m_afirmar(lista_buscar_elemento(lista, 3) == NULL,
        "Buscar elemento en posicion inexistente devuelve NULL");

    pa2m_afirmar(lista_buscar_posicion(lista, &a, &comparador_int) == 0,
        "Buscar posicion del primer elemento devuelve 0");
    pa2m_afirmar(lista_buscar_posicion(lista, &b, comparador_int) == 1,
        "Buscar posicion de un elemento intermedio devuelve correcta");
    pa2m_afirmar(lista_buscar_posicion(lista, &c, comparador_int) == 2,
        "Buscar posicion del ultimo elemento devuelve correcta");

    int x = 99;
    pa2m_afirmar(lista_buscar_posicion(lista, &x, comparador_int) == -1,
        "Buscar un elemento inexistente devuelve -1");

    lista_destruir(lista);
}

bool sumar_elementos(void *dato, void *extra)
{
	int *suma = (int *)extra;
	*suma += *(int *)dato;
	return true; // nunca corta
}

bool cortar_en_valor(void *dato, void *extra)
{
	int buscado = *(int *)extra;
	return (*(int *)dato != buscado); // corta cuando encuentra el valor
}

void prueba_lista_con_cada_elemento()
{
	int a = 1, b = 2, c = 3, d = 4;
	lista_t *lista = lista_crear();
	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);
	lista_agregar(lista, &d);

	// Recorrer toda la lista sumando
	int suma = 0;
	size_t aplicados = lista_con_cada_elemento(lista, sumar_elementos, &suma);
	pa2m_afirmar(aplicados == 4, "Se aplico la funcion a todos los elementos");
	pa2m_afirmar(suma == 10, "La suma acumulada de los elementos es correcta (10)");

	// Recorrer cortando en el valor 3
	int buscado = 3;
	aplicados = lista_con_cada_elemento(lista, cortar_en_valor, &buscado);
	pa2m_afirmar(aplicados == 3,
		"El recorrido corta al encontrar el valor buscado (3), aplicando la funcion 3 veces");

	// Caso lista vacia
	lista_t *vacia = lista_crear();
	aplicados = lista_con_cada_elemento(vacia, sumar_elementos, &suma);
	pa2m_afirmar(aplicados == 0, "En una lista vacia no se aplica la funcion");

	lista_destruir(lista);
	lista_destruir(vacia);
}

void prueba_lista_iterador()
{
	int a = 1, b = 2, c = 3;

	// Caso lista vacia
	lista_t *vacia = lista_crear();
	lista_iterador_t *it_vacio = lista_iterador_crear(vacia);
	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it_vacio),
		"Un iterador creado sobre lista vacia no tiene elementos");
	pa2m_afirmar(lista_iterador_obtener_actual(it_vacio) == NULL,
		"Un iterador creado sobre lista vacia devuelve NULL al obtener actual");
	lista_iterador_destruir(it_vacio);
	lista_destruir(vacia);

	// Caso lista con un solo elemento
	lista_t *una = lista_crear();
	lista_agregar(una, &a);
	lista_iterador_t *it_una = lista_iterador_crear(una);
	pa2m_afirmar(lista_iterador_hay_mas_elementos(it_una),
		"Iterador detecta un unico elemento presente");
	pa2m_afirmar(*(int*)lista_iterador_obtener_actual(it_una) == 1,
		"Iterador devuelve correctamente el unico elemento");
	lista_iterador_siguiente(it_una);
	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it_una),
		"Iterador no tiene mas elementos luego de avanzar al final");
	lista_iterador_destruir(it_una);
	lista_destruir(una);

	// Caso lista con varios elementos
	lista_t *lista = lista_crear();
	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	lista_iterador_t *it = lista_iterador_crear(lista);
	int esperados[] = {1, 2, 3};
	int i = 0;
	while (lista_iterador_hay_mas_elementos(it)) {
		pa2m_afirmar(*(int*)lista_iterador_obtener_actual(it) == esperados[i],
			"Iterador recorre en orden el elemento esperado");
		lista_iterador_siguiente(it);
		i++;
	}
	pa2m_afirmar(i == 3, "Iterador recorrio todos los elementos");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}


int main()
{
	pa2m_nuevo_grupo("============== LISTA RECIEN CREADA ===============");
	prueba_lista_vacia();
	pa2m_nuevo_grupo("============== LISTA ELIMINAR ===============");
	prueba_lista_borrar();
	pa2m_nuevo_grupo("============== LISTA AGREGAR-INSERTAR ===============");
	prueba_lista_agregar_insertar();
	pa2m_nuevo_grupo("============== LISTA BUSCAR ELEMENTO-POSICION ===============");
	prueba_lista_buscar();
	pa2m_nuevo_grupo("============== LISTA RECORRER CON CADA ELEMENTO ===============");
	prueba_lista_con_cada_elemento();
	pa2m_nuevo_grupo("============== LISTA ITERADOR EXTERNO ===============");
	prueba_lista_iterador();

	return pa2m_mostrar_reporte();
}
