#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/tp1.h"
void mostrar_uso() {
    fprintf(stderr,
        "Uso:\n"
        "  ./tp1 <archivo.csv> buscar nombre <nombre>\n"
        "  ./tp1 <archivo.csv> buscar id <id>\n"
        "  ./tp1 <archivo.csv> union <archivo2.csv> <resultado.csv>\n"
        "  ./tp1 <archivo.csv> interseccion <archivo2.csv> <resultado.csv>\n"
        "  ./tp1 <archivo.csv> diferencia <archivo2.csv> <resultado.csv>\n"
        "  ./tp1 <archivo.csv> mostrar nombre\n"
        "  ./tp1 <archivo.csv> mostrar id\n");
}
static bool imprimir_pokemon(struct pokemon *pk, void *extra) {
   printf("%d,%s,%u,%d,%d,%d\n",
       pk->id,
       pk->nombre,
       pk->tipo,
       pk->ataque,
       pk->defensa,
       pk->velocidad);
    return true; // para que siga iterando
}
// argc es la cantidad de parámetros
// argv es un vector de strings con los parámetros
int main(int argc, char *argv[]){
	if (argc < 3){
		mostrar_uso();
		return 0;
	}
	const char *archivo1 = argv[1];
	const char *operacion = argv[2];

	tp1_t *pokedex = tp1_leer_archivo(archivo1);
	if (!pokedex) {
        fprintf(stderr, "Error al leer el archivo %s\n", archivo1);
        return 1;
    }
	if (strcmp(operacion, "buscar") == 0){
		  if (argc < 5) {
            mostrar_uso();
            tp1_destruir(pokedex);
            return 1;
        }
		const char *modo = argv[3];
        if (strcmp(modo, "nombre") == 0) {
            const char *nombre = argv[4];
            struct pokemon  *pk = tp1_buscar_nombre(pokedex, nombre);
            if (pk) imprimir_pokemon(pk, NULL);
            else printf("Pokemon no encontrado\n");
        } else if (strcmp(modo, "id") == 0) {
            int id = atoi(argv[4]);
            struct pokemon *pk = tp1_buscar_id(pokedex, id);
            if (pk) imprimir_pokemon(pk,NULL);
            else printf("Pokemon no encontrado\n");
        } else {
            mostrar_uso();
        }
	}else if (strcmp(operacion, "union") == 0 ||
               strcmp(operacion, "interseccion") == 0 ||
               strcmp(operacion, "diferencia") == 0) {

        if (argc < 5) {
            mostrar_uso();
            tp1_destruir(pokedex);
            return 1;
        }

        const char *archivo2 = argv[3];
        const char *archivo_salida = argv[4];

        tp1_t *pokedex2 = tp1_leer_archivo(archivo2);
        if (!pokedex2) {
            fprintf(stderr, "Error al leer el archivo %s\n", archivo2);
            tp1_destruir(pokedex);
            return 1;
        }

        tp1_t *resultado = NULL;
        if (strcmp(operacion, "union") == 0)
            resultado = tp1_union(pokedex, pokedex2);
        else if (strcmp(operacion, "interseccion") == 0)
            resultado = tp1_interseccion(pokedex, pokedex2);
        else if (strcmp(operacion, "diferencia") == 0)
            resultado = tp1_diferencia(pokedex, pokedex2);

        if (!resultado) {
            fprintf(stderr, "Error al generar resultado\n");
        } else {
            if (!tp1_guardar_archivo(resultado, archivo_salida)) {
                fprintf(stderr, "Error al guardar en %s\n", archivo_salida);
            }
            tp1_destruir(resultado);
        }

        tp1_destruir(pokedex2);

    } else if (strcmp(operacion, "mostrar") == 0) {
        if (argc < 4) {
            mostrar_uso();
            tp1_destruir(pokedex);
            return 1;
        }

        const char *criterio = argv[3];
        if (strcmp(criterio, "nombre") == 0) {
    		tp1_con_cada_pokemon(pokedex, imprimir_pokemon, NULL);
		} else if (strcmp(criterio, "id") == 0) {
   			 tp1_con_cada_pokemon(pokedex, imprimir_pokemon, NULL);
		}

    } else {
        mostrar_uso();
    }

    tp1_destruir(pokedex);
    return 0;
}