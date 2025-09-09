#include "pa2m.h"
#include "src/tp1.h"
//gcc -Wall -Wextra -std=c11 src/tp1.c pruebas_alumno.c -o test.exe
#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_3_VALIDAS "ejemplos/lineas_inv.csv"
// --------------------------------------PRUEBAS DE LECTURA DE ARCHIVOS------------------------------------
void tp1_leer_archivo_devuelve_null_cuando_el_archivo_no_existe(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	pa2m_afirmar(tp1 == NULL, "Abrir un archivo inexistente devuelve NULL");
}
void tp1_leer_archivo_devuelve_tp1(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo EXISTENTE nos devuelve el puntero al struct");
}
void tp1_leer_archivo_vacio_devuelve_tp1(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo vacio nos devuelve igual el puntero al struct");
}
void tp1_leer_archivo_con_lineas_invalidas_devuelve_tp1(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(tp1 != NULL, "Abrir un archivo vacio nos devuelve igual el puntero al struct");
}
// -------------------------------------------PRUEBAS DE CANTIDAD------------------------------------------------
void tp1_cantidad_con_5_lineas_validas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1_cantidad(tp1) == 5, "tp1_cantidad devuelve la cantidad correcta SIN lineas invalidas");
}
void tp1_cantidad_lineas_invalidas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(tp1_cantidad(tp1) == 3, "tp1_cantidad devuelve la cantidad correcta con lineas invalidas");
}

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
	return pa2m_mostrar_reporte();
}
