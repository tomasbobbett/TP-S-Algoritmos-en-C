#include "pa2m.h"
#include "src/tp1.h"
//gcc -Wall -Wextra -std=c11 src/tp1.c pruebas_alumno.c -o test.exe
#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS "ejemplos/normal2.csv"
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
void tp1_cantidad_lineas_validas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1_cantidad(tp1) == 5, "tp1_cantidad devuelve la cantidad correcta SIN lineas invalidas");
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_1_REPETIDO);
	pa2m_afirmar(tp1_cantidad(tp2) == 15, "tp1_cantidad devuelve la cantidad correcta con pokemones REPETIDOS");
	tp1_t *tp3 = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1_cantidad(tp3) == 0, "tp1_cantidad devuelve la 0 si NO hay lineas en el csv");
}
void tp1_cantidad_lineas_invalidas(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_3_VALIDAS);
	pa2m_afirmar(tp1_cantidad(tp1) == 3, "tp1_cantidad devuelve la cantidad correcta CON lineas invalidas");
}

// -------------------------------------------PRUEBAS DE GUARDAR ARCHIVO------------------------------------------------
void tp1_guardar_archivo_valido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	pa2m_afirmar(tp1_guardar_archivo(tp1, "salida.csv")!=NULL, "tp1_guardar_archivo puede crear un archivo nuevo");
	tp1_t *tp_guardado = tp1_leer_archivo("salida.csv");
	pa2m_afirmar( tp1_cantidad(tp1) == tp1_cantidad(tp_guardado) , "tp1_guardar_archivo crea el archivo correctamente y coinciden en cantidad");
	pa2m_afirmar(!tp1_guardar_archivo(NULL, "salida.csv"),"tp1_guardar_archivo devuelve NULL si le pasamos un tp1 NULL");
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	pa2m_afirmar(tp1_guardar_archivo(tp_vacio,"salida.csv")!= NULL, "tp1_guardar archivo genera el archivo aun cuando no hay pokemones en el struct");
}
void tp1_guardar_archivo_invalido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_INEXISTENTE);
	pa2m_afirmar(!tp1_guardar_archivo(tp1, "salida.csv"), "tp1_guardar archivo devuelve NULL si le pasamos un tp1 que fue leido incorrectamente");
}
// -------------------------------------------PRUEBAS DE UNION------------------------------------------------
void tp1_union_tp1_t_valido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS);
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);

	tp1_t *merge = tp1_union(tp1,tp2);
	tp1_t *merge_un_vacio = tp1_union(tp1,tp_vacio);
	tp1_t *merge_dos_vacios = tp1_union(tp_vacio,tp_vacio);

	pa2m_afirmar(tp1_cantidad(merge) == 10, "La funcion tp1_union junta la cantidad correcta de pokemones aun con REPETIDOS entre los dos");
	pa2m_afirmar(tp1_cantidad(tp1) == tp1_cantidad(merge_un_vacio), "La union de un struct con otro vacio devuelve el mismo primer struct");
	pa2m_afirmar(tp1_cantidad(merge_dos_vacios) ==0, "La union de dos structs vacios devuelve otro vacio");
	
}
void tp1_union_tp1_t_invalido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *merge = tp1_union(NULL, tp1);
	pa2m_afirmar( tp1_cantidad(merge) == tp1_cantidad(tp1), "La funcion tp1_union devuelve una copia del primer tp si el segundo es NULL");

}
// -------------------------------------------PRUEBAS DE INTERSECCION------------------------------------------------
void tp1_interseccion_tp1_t_valido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS);
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);

	tp1_t *interseccion = tp1_interseccion(tp1,tp2);
	tp1_t *interseccion_con_vacio = tp1_interseccion(tp1,tp_vacio);
	tp1_t *interseccion_dos_vacios = tp1_interseccion(tp_vacio,tp_vacio);

	pa2m_afirmar(tp1_cantidad(interseccion) == 5, "Interseccion devuelve solo los pokemones presentes en ambos structs");
	pa2m_afirmar(tp1_cantidad(interseccion_con_vacio) == 0, "Interseccion con un struct vacio devuelve otro struct vacio");
	pa2m_afirmar(tp1_cantidad(interseccion_dos_vacios) == 0, "Interseccion de dos structs vacios devuelve otro struct vacio");
}

void tp1_interseccion_tp1_t_invalido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);

	tp1_t *interseccion_null_1 = tp1_interseccion(NULL, tp1);
	tp1_t *interseccion_null_2 = tp1_interseccion(tp1, NULL);
	tp1_t *interseccion_null_ambos = tp1_interseccion(NULL, NULL);

	pa2m_afirmar(tp1_cantidad(interseccion_null_1) == 0, "Interseccion con primer TP1 NULL devuelve struct vacio");
	pa2m_afirmar(tp1_cantidad(interseccion_null_2) == 0, "Interseccion con segundo TP1 NULL devuelve struct vacio");
	pa2m_afirmar(tp1_cantidad(interseccion_null_ambos) == 0, "Interseccion con ambos TP1 NULL devuelve struct vacio");
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


	return pa2m_mostrar_reporte();

	
}
