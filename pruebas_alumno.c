#include "pa2m.h"
#include "src/tp1.h"
//gcc -Wall -Wextra -std=c11 src/tp1.c pruebas_alumno.c -o test.exe
#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_3_VALIDAS "ejemplos/lineas_inv.csv"
#define ARCHIVO_PRUEBA_1_REPETIDO "ejemplos/largo.csv"
// --------------------------------------PRUEBAS DE LECTURA DE ARCHIVOS------------------------------------
void tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo INEXISTENTE devuelve NULL");
}
void tp1_leer_archivo_devuelve_tp1(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo EXISTENTE nos devuelve el puntero al struct");
}
void tp1_leer_archivo_vacio_devuelve_tp1(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo VACIO nos devuelve igual el puntero al struct");
}
void tp1_leer_archivo_con_lineas_invalidas_devuelve_tp1(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo con lineas INVALIDAS nos devuelve igual el puntero al struct");
}
// -------------------------------------------PRUEBAS DE CANTIDAD------------------------------------------------
void tp1_cantidad_con_5_lineas_validas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1_cantidad(tp1) == 5, "tp1_cantidad devuelve la cantidad correcta SIN lineas invalidas");
}
void tp1_cantidad_lineas_invalidas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(tp1_cantidad(tp1) == 3, "tp1_cantidad devuelve la cantidad correcta CON lineas invalidas");
}
void tp1_cantidad_lineas_sin_lineas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1_cantidad(tp1) == 0, "tp1_cantidad devuelve la 0 si NO hay lineas en el csv");
}
void tp1_cantidad_pokemon_repetido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_1_REPETIDO);
	pa2m_afirmar(tp1_cantidad(tp1) == 15, "tp1_cantidad devuelve la cantidad correcta con pokemones REPETIDOS");
}
// -------------------------------------------PRUEBAS DE UNION------------------------------------------------
void tp1_cantidad_pokemon_repetido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);

	
}

// -------------------------------------------PRUEBAS DE X------------------------------------------------

int main()
{
	pa2m_nuevo_grupo("Pruebas de lectura de archivos");
	tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe();
	tp1_leer_archivo_devuelve_tp1();
	tp1_leer_archivo_vacio_devuelve_tp1();
	tp1_leer_archivo_con_lineas_invalidas_devuelve_tp1();
	pa2m_nuevo_grupo("Pruebas de tp1_cantidad");
	tp1_cantidad_con_5_lineas_validas();
	tp1_cantidad_lineas_invalidas();
	tp1_cantidad_lineas_sin_lineas();
	tp1_cantidad_pokemon_repetido();
	pa2m_nuevo_grupo("Pruebas de tp1_union");


	return pa2m_mostrar_reporte();
}
