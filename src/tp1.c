#include "tp1.h"
#include <stdio.h>
#include <string.h>

#define READ_MODE "r"

#define CAPACIDAD_INICIAL_TP1 10

// Definición de la estructura oculta
struct tp1 {
    struct pokemon *pokemones;      // arreglo dinámico de punteros a pokemon (puntero a un arreglo de punteros)
    size_t cantidad, capacidad;     // cantidad de pokemones almacenados y capacidad del arreglo
};

//Implementaciones de las funciones declaradas en tp1.h por la catedra---------------

tp1_t *tp1_leer_archivo(const char *nombre) {
    FILE *file = fopen(nombre, READ_MODE);
    if (!file){
        return NULL;                //FALLO LA APERTURA DEL ARCHIVO CSV (404)
    }

    struct tp1 *tp = malloc(sizeof(struct(tp1)));
    if (!tp){
        fclose();
        return NULL;//Error al reservar memoria
    }   
    tp->cantidad = 0;
    tp->capacidad = CAPACIDAD_INICIAL_TP1;
    tp->pokemones = malloc(tp->capacidad, sizeof(struct(pokemon)));
    if(!tp->pokemones){
        free(tp);
        fclose(f);
        return NULL; //error al reservar memoria de pokemones
    }
    char linea[256];
    while(fgets(linea,sizeof(linea),file)){

        int id, ataque, defensa, velocidad;
        char nombre_poke[64];                       //Inicializo el pokemon de la linea actual
        char tipo_str[16];      
        int lineaActual = sscanf(linea,"%d,%63[^,],%15[^,],%d,%d,%d", &id,nombre_poke,tipo_str, &ataque,&defensa,&velocidad);

        if (leidos != 6) {
            continue; // línea inválida, la salto porque encontro mas o menos de 6 caracteristicas del pokemon
        }

        //verificar si ya existe el pokemon en tp

        //verificar si modifico la capacidad de tp REDIM

        //Añadir pokemon leido a &tp->pokemones[tp->cantidad]; y luego aumentar cantidad para no reemplazar el anterior
        fclose(f)
        return tp
    }
}

