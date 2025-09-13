#include <string.h>
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
// -------------------------------------------PRUEBAS DE DIFERENCIA------------------------------------------------
void tp1_diferencia_tp1_t_valido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	tp1_t *tp2 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_10_LINEAS);
	tp1_t *tp_vacio = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);

	tp1_t *diferencia1 = tp1_diferencia(tp1, tp2);
	tp1_t *diferencia2 = tp1_diferencia(tp2, tp1);
	tp1_t *diferencia3 = tp1_diferencia(tp1, tp_vacio);
	tp1_t *diferencia4 = tp1_diferencia(tp_vacio, tp1);
	tp1_t *diferencia5 = tp1_diferencia(tp_vacio, tp_vacio);

	pa2m_afirmar(tp1_cantidad(diferencia1) == 0, "Diferencia (tp1 - tp2) devuelve 0 porque todos los de tp1 estan en tp2");
	pa2m_afirmar(tp1_cantidad(diferencia2) == 5, "Diferencia (tp2 - tp1) devuelve los que estan en tp2 pero no en tp1");
	pa2m_afirmar(tp1_cantidad(diferencia3) == tp1_cantidad(tp1), "Diferencia con segundo vacio devuelve copia del primero");
	pa2m_afirmar(tp1_cantidad(diferencia4) == 0, "Diferencia con primer vacio devuelve vacio");
	pa2m_afirmar(tp1_cantidad(diferencia5) == 0, "Diferencia de dos vacios devuelve vacio");
}

void tp1_diferencia_tp1_t_invalido(){
	tp1_t *tp1 = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);

	tp1_t *dif1 = tp1_diferencia(NULL, tp1);
	tp1_t *dif2 = tp1_diferencia(tp1, NULL);
	tp1_t *dif3 = tp1_diferencia(NULL, NULL);

	pa2m_afirmar(tp1_cantidad(dif1) == 0, "Diferencia con primer TP1 NULL devuelve vacio");
	pa2m_afirmar(tp1_cantidad(dif2) == tp1_cantidad(tp1), "Diferencia con segundo TP1 NULL devuelve copia del primero");
	pa2m_afirmar(tp1_cantidad(dif3) == 0, "Diferencia con ambos TP1 NULL devuelve vacio");
}
// -------------------------------------------PRUEBAS DE BUSQUEDA POR NOMBRE------------------------------------------------
void tp1_buscar_nombre_existe_en_inicio(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_nombre(tp, "Bulbasaur"); // primer nombre de ejemplo
	pa2m_afirmar(p != NULL && strcmp(p->nombre, "Bulbasaur") == 0, "Buscar nombre EXISTENTE al inicio devuelve puntero correcto");
}

void tp1_buscar_nombre_existe_en_final(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_nombre(tp, "Pikachu"); // último nombre de ejemplo
	pa2m_afirmar(p != NULL && strcmp(p->nombre, "Pikachu") == 0, "Buscar nombre EXISTENTE al final devuelve puntero correcto");
}

void tp1_buscar_nombre_existe_en_medio(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_nombre(tp, "Charmander"); // nombre en medio
	pa2m_afirmar(p != NULL && strcmp(p->nombre, "Charmander") == 0, "Buscar nombre EXISTENTE en medio devuelve puntero correcto");
}

void tp1_buscar_nombre_no_existe(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_nombre(tp, "Mewtwo"); // nombre que no está
	pa2m_afirmar(p == NULL, "Buscar nombre NO EXISTENTE devuelve NULL");
}

void tp1_buscar_nombre_en_struct_vacio(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_VACIO);
	struct pokemon *p = tp1_buscar_nombre(tp, "Bulbasaur");
	pa2m_afirmar(p == NULL, "Buscar nombre en TP1 vacio devuelve NULL");
}

void tp1_buscar_nombre_sensibilidad_mayusculas(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_EXISTENTE_5_LINEAS);
	struct pokemon *p = tp1_buscar_nombre(tp, "bulbasaur"); // minúscula vs mayúscula
	pa2m_afirmar(p == NULL, "Buscar nombre con diferencia de mayusculas devuelve NULL (case sensitive)");
}

void tp1_buscar_nombre_duplicados(){
	tp1_t *tp = tp1_leer_archivo(ARCHIVO_PRUEBA_1_REPETIDO); // archivo con nombres repetidos
	struct pokemon *p = tp1_buscar_nombre(tp, "BULBASUR");
	pa2m_afirmar(p != NULL && p->id == 356, "Buscar nombre que se repite devuelve un puntero valido (el primero encontrado)");
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
	return pa2m_mostrar_reporte();
}
