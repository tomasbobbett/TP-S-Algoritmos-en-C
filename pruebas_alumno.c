#include "pa2m.h"
#include "src/tp1.h"
#include <string.h>

// gcc -Wall -Wextra -std=c11 src/tp1.c pruebas_alumno.c -o test.exe

#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS "ejemplos/normal2.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_3_VALIDAS "ejemplos/lineas_inv.csv"
#define ARCHIVO_PRUEBA_1_REPETIDO "ejemplos/largo.csv"

// --------------------------------------PRUEBAS DE LECTURA DE
// ARCHIVOS------------------------------------
void tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo INEXISTENTE devuelve NULL");
	tp1_destruir(tp1);
}
void tp1_leer_archivo_devuelve_tp1()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(
		tp1 != NULL,
		"Abrir un archivo EXISTENTE nos devuelve el puntero al struct");
	tp1_destruir(tp1);
}
void tp1_leer_archivo_vacio_devuelve_tp1()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(
		tp1 != NULL,
		"Abrir un archivo VACIO nos devuelve igual el puntero al struct");
	tp1_destruir(tp1);
}
void tp1_leer_archivo_con_lineas_invalidas_devuelve_tp1()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo con lineas INVALIDAS nos "
				  "devuelve igual el puntero al struct");
	tp1_destruir(tp1);
}
// -------------------------------------------PRUEBAS DE
// CANTIDAD------------------------------------------------
void tp1_cantidad_lineas_validas()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(
		tp1_cantidad(tp1) == 5,
		"tp1_cantidad devuelve la cantidad correcta SIN lineas invalidas");
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_1_REPETIDO);
	pa2m_afirmar(
		tp1_cantidad(tp2) == 17,
		"tp1_cantidad devuelve la cantidad correcta con pokemones REPETIDOS");
	tp1_t *tp3 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1_cantidad(tp3) == 0,
		     "tp1_cantidad devuelve la 0 si NO hay lineas en el csv");
	tp1_destruir(tp1);
	tp1_destruir(tp2);
	tp1_destruir(tp3);
}
void tp1_cantidad_lineas_invalidas()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(
		tp1_cantidad(tp1) == 3,
		"tp1_cantidad devuelve la cantidad correcta CON lineas invalidas");
	tp1_destruir(tp1);
}

// -------------------------------------------PRUEBAS DE GUARDAR
// ARCHIVO------------------------------------------------
void tp1_guardar_archivo_valido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1_guardar_archivo(tp1, "salida.csv") != NULL,
		     "tp1_guardar_archivo puede crear un archivo nuevo");
	tp1_t *tp_guardado = tp1_leer_archivo("salida.csv");
	pa2m_afirmar(
		tp1_cantidad(tp1) == tp1_cantidad(tp_guardado),
		"tp1_guardar_archivo crea el archivo correctamente y coinciden "
		"en cantidad");
	pa2m_afirmar(
		!tp1_guardar_archivo(NULL, "salida.csv"),
		"tp1_guardar_archivo devuelve NULL si le pasamos un tp1 NULL");
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1_guardar_archivo(tp_vacio, "salida.csv") != NULL,
		     "tp1_guardar archivo genera el archivo aun cuando no hay "
		     "pokemones en el struct");
	tp1_destruir(tp1);
	tp1_destruir(tp_guardado);
	tp1_destruir(tp_vacio);
}
void tp1_guardar_archivo_invalido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	pa2m_afirmar(
		!tp1_guardar_archivo(tp1, "salida.csv"),
		"tp1_guardar archivo devuelve NULL si le pasamos un tp1 que fue "
		"leido incorrectamente");
	tp1_destruir(tp1);
}
// -------------------------------------------PRUEBAS DE
// UNION------------------------------------------------
void tp1_union_tp1_t_valido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS);
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);

	tp1_t *merge = tp1_union(tp1, tp2);
	tp1_t *merge_un_vacio = tp1_union(tp1, tp_vacio);
	tp1_t *merge_dos_vacios = tp1_union(tp_vacio, tp_vacio);

	pa2m_afirmar(
		tp1_cantidad(merge) == 10,
		"La funcion tp1_union junta la cantidad correcta de pokemones "
		"aun con REPETIDOS entre los dos");
	pa2m_afirmar(
		tp1_cantidad(tp1) == tp1_cantidad(merge_un_vacio),
		"La union de un struct con otro vacio devuelve el mismo primer struct");
	pa2m_afirmar(tp1_cantidad(merge_dos_vacios) == 0,
		     "La union de dos structs vacios devuelve otro vacio");

	tp1_destruir(tp1);
	tp1_destruir(tp2);
	tp1_destruir(tp_vacio);
	tp1_destruir(merge);
	tp1_destruir(merge_un_vacio);
	tp1_destruir(merge_dos_vacios);
}
void tp1_union_tp1_t_invalido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *merge = tp1_union(NULL, tp1);
	pa2m_afirmar(!merge, "La funcion tp1_union devuelve NULL si el "
			     "segundo es NULL");
	tp1_destruir(tp1);
	tp1_destruir(merge);
}
// -------------------------------------------PRUEBAS DE
// INTERSECCION------------------------------------------------
void tp1_interseccion_tp1_t_valido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS);
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);

	tp1_t *interseccion = tp1_interseccion(tp1, tp2);
	tp1_t *interseccion_con_vacio = tp1_interseccion(tp1, tp_vacio);
	tp1_t *interseccion_dos_vacios = tp1_interseccion(tp_vacio, tp_vacio);

	pa2m_afirmar(
		tp1_cantidad(interseccion) == 5,
		"Interseccion devuelve solo los pokemones presentes en ambos structs");
	pa2m_afirmar(
		tp1_cantidad(interseccion_con_vacio) == 0,
		"Interseccion con un struct vacio devuelve otro struct vacio");
	pa2m_afirmar(
		tp1_cantidad(interseccion_dos_vacios) == 0,
		"Interseccion de dos structs vacios devuelve otro struct vacio");

	tp1_destruir(tp1);
	tp1_destruir(tp2);
	tp1_destruir(tp_vacio);
	tp1_destruir(interseccion);
	tp1_destruir(interseccion_con_vacio);
	tp1_destruir(interseccion_dos_vacios);
}

void tp1_interseccion_tp1_t_invalido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);

	tp1_t *interseccion_null_1 = tp1_interseccion(NULL, tp1);
	tp1_t *interseccion_null_2 = tp1_interseccion(tp1, NULL);
	tp1_t *interseccion_null_ambos = tp1_interseccion(NULL, NULL);

	pa2m_afirmar(tp1_cantidad(interseccion_null_1) == 0,
		     "Interseccion con primer TP1 NULL devuelve struct vacio");
	pa2m_afirmar(tp1_cantidad(interseccion_null_2) == 0,
		     "Interseccion con segundo TP1 NULL devuelve struct vacio");
	pa2m_afirmar(tp1_cantidad(interseccion_null_ambos) == 0,
		     "Interseccion con ambos TP1 NULL devuelve struct vacio");

	tp1_destruir(tp1);
	tp1_destruir(interseccion_null_1);
	tp1_destruir(interseccion_null_2);
	tp1_destruir(interseccion_null_ambos);
}
// -------------------------------------------PRUEBAS DE
// DIFERENCIA------------------------------------------------
void tp1_diferencia_tp1_t_valido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS);
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);

	tp1_t *diferencia1 = tp1_diferencia(tp1, tp2);
	tp1_t *diferencia2 = tp1_diferencia(tp2, tp1);
	tp1_t *diferencia3 = tp1_diferencia(tp1, tp_vacio);
	tp1_t *diferencia4 = tp1_diferencia(tp_vacio, tp1);
	tp1_t *diferencia5 = tp1_diferencia(tp_vacio, tp_vacio);

	pa2m_afirmar(
		tp1_cantidad(diferencia1) == 0,
		"Diferencia (tp1 - tp2) devuelve 0 porque todos los de tp1 estan en tp2");
	pa2m_afirmar(
		tp1_cantidad(diferencia2) == 5,
		"Diferencia (tp2 - tp1) devuelve los que estan en tp2 pero no en tp1");
	pa2m_afirmar(tp1_cantidad(diferencia3) == tp1_cantidad(tp1),
		     "Diferencia con segundo vacio devuelve copia del primero");
	pa2m_afirmar(tp1_cantidad(diferencia4) == 0,
		     "Diferencia con primer vacio devuelve vacio");
	pa2m_afirmar(tp1_cantidad(diferencia5) == 0,
		     "Diferencia de dos vacios devuelve vacio");

	tp1_destruir(tp1);
	tp1_destruir(tp2);
	tp1_destruir(tp_vacio);
	tp1_destruir(diferencia1);
	tp1_destruir(diferencia2);
	tp1_destruir(diferencia3);
	tp1_destruir(diferencia4);
	tp1_destruir(diferencia5);
}

void tp1_diferencia_tp1_t_invalido()
{
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);

	tp1_t *dif1 = tp1_diferencia(NULL, tp1);
	tp1_t *dif2 = tp1_diferencia(tp1, NULL);
	tp1_t *dif3 = tp1_diferencia(NULL, NULL);

	pa2m_afirmar(!dif1, "Diferencia con primer TP1 NULL devuelve NULL");
	pa2m_afirmar(!dif2, "Diferencia con segundo TP1 NULL devuelve NULL");
	pa2m_afirmar(!dif3, "Diferencia con ambos TP1 NULL devuelve NULL");

	tp1_destruir(tp1);
	tp1_destruir(dif1);
	tp1_destruir(dif2);
	tp1_destruir(dif3);
}
// -------------------------------------------PRUEBAS DE BUSQUEDA POR
// NOMBRE------------------------------------------------
void tp1_buscar_nombre_existe_en_inicio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_nombre(tp, "Bulbasaur"); // primer nombre de ejemplo
	pa2m_afirmar(
		p != NULL && strcmp(p->nombre, "Bulbasaur") == 0,
		"Buscar nombre EXISTENTE al inicio devuelve puntero correcto");
	tp1_destruir(tp);
}

void tp1_buscar_nombre_existe_en_final()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_nombre(tp, "Pikachu"); // último nombre de ejemplo
	pa2m_afirmar(
		p != NULL && strcmp(p->nombre, "Pikachu") == 0,
		"Buscar nombre EXISTENTE al final devuelve puntero correcto");
	tp1_destruir(tp);
}

void tp1_buscar_nombre_existe_en_medio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_nombre(tp, "Charmander"); // nombre en medio
	pa2m_afirmar(
		p != NULL && strcmp(p->nombre, "Charmander") == 0,
		"Buscar nombre EXISTENTE en medio devuelve puntero correcto");
	tp1_destruir(tp);
}

void tp1_buscar_nombre_no_existe()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_nombre(tp, "Mewtwo"); // nombre que no está
	pa2m_afirmar(p == NULL, "Buscar nombre NO EXISTENTE devuelve NULL");
	tp1_destruir(tp);
}

void tp1_buscar_nombre_en_struct_vacio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	struct pokemon *p = tp1_buscar_nombre(tp, "Bulbasaur");
	pa2m_afirmar(p == NULL, "Buscar nombre en TP1 vacio devuelve NULL");
	tp1_destruir(tp);
}

void tp1_buscar_nombre_sensibilidad_mayusculas()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_nombre(tp, "bulbasaur"); // minúscula vs mayúscula
	pa2m_afirmar(p == NULL,
		     "Buscar nombre con diferencia de mayusculas devuelve "
		     "NULL (case sensitive)");
	tp1_destruir(tp);
}

void tp1_buscar_nombre_duplicados()
{
	tp1_t *tp = tp1_leer_archivo(
		ARCHIVO_PRUEBA_1_REPETIDO); // archivo con nombres repetidos
	struct pokemon *p = tp1_buscar_nombre(tp, "BULBASUR");
	pa2m_afirmar(
		p != NULL && p->id == 356,
		"Buscar nombre que se repite devuelve un puntero valido (el "
		"primero encontrado)");
	tp1_destruir(tp);
}
// -------------------------------------------PRUEBAS DE BUSQUEDA POR
// ID------------------------------------------------
void tp1_buscar_id_existe_al_inicio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_id(tp, 1); // ID del primer pokemon en el archivo
	pa2m_afirmar(p != NULL && p->id == 1,
		     "Buscar ID EXISTENTE al inicio devuelve puntero correcto");
	tp1_destruir(tp);
}

void tp1_buscar_id_existe_al_final()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p =
		tp1_buscar_id(tp, 5); // ID del último pokemon en el archivo
	pa2m_afirmar(p != NULL && p->id == 5,
		     "Buscar ID EXISTENTE al final devuelve puntero correcto");
	tp1_destruir(tp);
}

void tp1_buscar_id_existe_en_medio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_id(tp, 3); // ID en medio del arreglo
	pa2m_afirmar(p != NULL && p->id == 3,
		     "Buscar ID EXISTENTE en medio devuelve puntero correcto");
	tp1_destruir(tp);
}

void tp1_buscar_id_no_existe()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_id(tp, 999); // ID que no está
	pa2m_afirmar(p == NULL, "Buscar ID NO EXISTENTE devuelve NULL");
	tp1_destruir(tp);
}

void tp1_buscar_id_en_struct_vacio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	struct pokemon *p = tp1_buscar_id(tp, 1);
	pa2m_afirmar(p == NULL, "Buscar ID en TP1 vacio devuelve NULL");
	tp1_destruir(tp);
}

void tp1_buscar_id_duplicados()
{
	tp1_t *tp = tp1_leer_archivo(
		ARCHIVO_PRUEBA_1_REPETIDO); // archivo con IDs repetidos
	struct pokemon *p = tp1_buscar_id(tp, 356); // ID duplicado
	pa2m_afirmar(
		p != NULL && p->id == 356,
		"Buscar ID duplicado devuelve un puntero valido (el primero encontrado)");
	tp1_destruir(tp);
}

// -------------------------------------------PRUEBAS DE
// tp1_con_cada_pokemon------------------------------------------------

// Función auxiliar para pruebas: siempre devuelve true y cuenta pokemones
bool contar_pokemon(struct pokemon *p, void *extra)
{
	(void)p;
	size_t *cont = (size_t *)extra;
	(*cont)++;
	return true;
}

// Función auxiliar para pruebas: devuelve false si encuentra ID igual a un
// valor
bool detener_en_id(struct pokemon *p, void *extra)
{
	int *id_objetivo = (int *)extra;
	return p->id != *id_objetivo; // false si p->id == id_objetivo
}

void tp1_con_cada_pokemon_recorre_todos()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	size_t cont = 0;
	size_t procesados = tp1_con_cada_pokemon(tp, contar_pokemon, &cont);
	pa2m_afirmar(
		procesados == tp1_cantidad(tp),
		"tp1_con_cada_pokemon recorre todos los pokemones cuando f "
		"siempre devuelve true");
	pa2m_afirmar(
		cont == tp1_cantidad(tp),
		"Contador auxiliar coincide con cantidad de pokemones procesados");
	tp1_destruir(tp);
}

void tp1_con_cada_pokemon_se_detiene()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	int id_detener = 3;
	size_t procesados =
		tp1_con_cada_pokemon(tp, detener_en_id, &id_detener);
	pa2m_afirmar(
		procesados == 3,
		"tp1_con_cada_pokemon se detiene correctamente cuando f devuelve false");
	tp1_destruir(tp);
}

void tp1_con_cada_pokemon_struct_vacio()
{
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	size_t cont = 0;
	size_t procesados = tp1_con_cada_pokemon(tp, contar_pokemon, &cont);
	pa2m_afirmar(procesados == 0,
		     "tp1_con_cada_pokemon sobre struct vacio devuelve 0");
	tp1_destruir(tp);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de lectura de archivos");
	tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe();
	tp1_leer_archivo_devuelve_tp1();
	tp1_leer_archivo_vacio_devuelve_tp1();
	tp1_leer_archivo_con_lineas_invalidas_devuelve_tp1();

	pa2m_nuevo_grupo("Pruebas de tp1_cantidad");
	tp1_cantidad_lineas_validas();
	tp1_cantidad_lineas_invalidas();

	pa2m_nuevo_grupo("Pruebas de tp1_guardar_archivo");
	tp1_guardar_archivo_valido();
	tp1_guardar_archivo_invalido();

	pa2m_nuevo_grupo("Pruebas de tp1_union");
	tp1_union_tp1_t_valido();
	tp1_union_tp1_t_invalido();

	pa2m_nuevo_grupo("Pruebas de tp1_interseccion");
	tp1_interseccion_tp1_t_valido();
	tp1_interseccion_tp1_t_invalido();

	pa2m_nuevo_grupo("Pruebas de tp1_diferencia");
	tp1_diferencia_tp1_t_valido();
	tp1_diferencia_tp1_t_invalido();

	pa2m_nuevo_grupo("Pruebas de tp1_buscar_nombre");
	tp1_buscar_nombre_existe_en_inicio();
	tp1_buscar_nombre_existe_en_final();
	tp1_buscar_nombre_existe_en_medio();
	tp1_buscar_nombre_no_existe();
	tp1_buscar_nombre_en_struct_vacio();
	tp1_buscar_nombre_sensibilidad_mayusculas();
	tp1_buscar_nombre_duplicados();

	pa2m_nuevo_grupo("Pruebas de tp1_buscar_id");
	tp1_buscar_id_existe_al_inicio();
	tp1_buscar_id_existe_al_final();
	tp1_buscar_id_no_existe();
	tp1_buscar_id_en_struct_vacio();
	tp1_buscar_id_duplicados();

	pa2m_nuevo_grupo("Pruebas de tp1_iterador");
	tp1_con_cada_pokemon_recorre_todos();
	tp1_con_cada_pokemon_se_detiene();
	tp1_con_cada_pokemon_struct_vacio();
	return pa2m_mostrar_reporte();
}
