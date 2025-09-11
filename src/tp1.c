#include "tp1.h"
#include <stdio.h>
#include <string.h>

#define READ_MODE "r"
#define WRITE_MODE "w"
#define CAPACIDAD_INICIAL_TP1 10

// Definición de la estructura oculta
struct tp1 {
    struct pokemon *pokemones;      // arreglo dinámico de punteros a pokemon (puntero a un arreglo de punteros)
    size_t cantidad, capacidad;     // cantidad de pokemones almacenados y capacidad del arreglo
};

// funciónes auxiliares para traducir el string de tipo a enum y de enum a tipo string
static const char* tipo_a_string(enum tipo_pokemon tipo) {
    switch (tipo) {
        case TIPO_ELEC: return "ELEC";
        case TIPO_FUEG: return "FUEG";
        case TIPO_PLAN: return "PLAN";
        case TIPO_AGUA: return "AGUA";
        case TIPO_NORM: return "NORM";
        case TIPO_FANT: return "FANT";
        case TIPO_PSI:  return "PSI";
        case TIPO_LUCH: return "LUCH";
        default: return "DESCONOCIDO";
    }
}
static enum tipo_pokemon parsear_string_tipo(const char *tipo_str) {
    if (strcmp(tipo_str, "ELEC") == 0){
        return TIPO_ELEC;
    }
    if (strcmp(tipo_str, "FUEG") == 0){
        return TIPO_FUEG;
    } 
    if (strcmp(tipo_str, "PLAN") == 0){
        return TIPO_PLAN;  
    } 
    if (strcmp(tipo_str, "AGUA") == 0){
        return TIPO_AGUA;
    }
    if (strcmp(tipo_str, "NORM") == 0) {
        return TIPO_NORM;
    }
    if (strcmp(tipo_str, "FANT") == 0){
        return TIPO_FANT;
    }
    if (strcmp(tipo_str, "PSI") == 0) {
        return TIPO_PSI;
    }
    if (strcmp(tipo_str, "LUCH") == 0){
        return TIPO_LUCH;
    }
    return -1; // inválido
}

static bool existe_pokemon(struct tp1 *tp, int id){ // funcion estatica para saber si el tp procesado ya habia sido procesado
    for (size_t i = 0; i < tp->cantidad; i++){//       La hacemos statica porque no tendira sentido usarla en el exterior de el scope general
        if (tp->pokemones[i].id == id){
            return true;
        }
    }
    return false;
}
static bool tp1_redimensionar(tp1_t *tp) {
    if (!tp) return false;

    size_t nueva_capacidad = tp->capacidad * 2;
    if (nueva_capacidad == 0) {
        nueva_capacidad = CAPACIDAD_INICIAL_TP1;
    }

    struct pokemon *nuevo_array = realloc(tp->pokemones, nueva_capacidad * sizeof(struct pokemon));
    if (!nuevo_array) return false;

    tp->pokemones = nuevo_array;
    tp->capacidad = nueva_capacidad;
    return true;
}
//Implementaciones de las funciones declaradas en tp1.h por la catedra---------------

tp1_t *tp1_leer_archivo(const char *nombre){
    FILE *file = fopen(nombre, READ_MODE);
    if (!file){
        return NULL;                //FALLO LA APERTURA DEL ARCHIVO CSV (404)
    }

    struct tp1 *tp = malloc(sizeof(struct tp1));// Reservamos memoria para el struct de tp1 
    if (!tp){
        fclose(file);
        return NULL;//Error al reservar memoria
    }   

    tp->cantidad = 0;
    tp->capacidad = CAPACIDAD_INICIAL_TP1;
    tp->pokemones = malloc(tp->capacidad * sizeof(struct pokemon));
    if(!tp->pokemones){
        free(tp);
        fclose(file);
        return NULL; //error al reservar memoria de pokemones
    }
    
    //Llenamos pokemones mientras leemos las lineas del archivo pasado por paramero
    char linea[500];
    while(fgets(linea,sizeof(linea),file)){

        int id, ataque, defensa, velocidad;
        char nombre_poke[120];                       //Inicializo el pokemon de la linea actual
        char tipo_str[16];      
        int lineaActual = sscanf(linea,"%d,%[^,],%[^,],%d,%d,%d", &id,nombre_poke,tipo_str, &ataque,&defensa,&velocidad);

        if (lineaActual != 6) {
            continue; // línea inválida, la salto porque encontro mas o menos de 6 caracteristicas del pokemon
        }

        //verificar si ya existe el pokemon en tp por la id
        if (existe_pokemon(tp,id)){
            continue;
        }
        //verificar si modifico la capacidad de tp REDIM usando la capacidad del struct tp1_t
        if (tp->capacidad == tp->cantidad){
            bool redim = tp1_redimensionar(tp);
            if (!redim){
                free(tp);
                fclose(file);
                return NULL;
            }
        }
        
        //Añadir pokemon leido a &tp->pokemones[tp->cantidad]; y luego aumentar cantidad para no reemplazar el anterior
        struct pokemon *p = &tp->pokemones[tp->cantidad];
        p->id = id;
        p->nombre = strdup(nombre_poke);
        p->tipo = parsear_string_tipo(tipo_str);
        p->ataque=ataque;
        p->defensa = defensa;
        p->velocidad = velocidad;

        tp->cantidad++;


    }
    fclose(file);
    return tp;
}

size_t tp1_cantidad(tp1_t *tp1){
    return tp1->cantidad;
}

tp1_t *tp1_guardar_archivo(tp1_t *tp1, const char *nombre){
    FILE *file = fopen(nombre, WRITE_MODE);
    if(!file){
        return NULL;
    }
    for (size_t i = 0; i < tp1->cantidad; i++){
        struct pokemon *p = &tp1->pokemones[i];
        fprintf(file, "%d,%s,%s,%d,%d,%d\n",p->id,p->nombre,tipo_a_string(p->tipo),p->ataque,p->defensa,p->velocidad);
    }
    fclose(file);
    return tp1;
}

tp1_t *tp1_union(tp1_t *un_tp, tp1_t otro_tp){
    tp1_t *res = malloc(sizeof(tp1_t));// Reservamos memoria para el struct de tp1 
    if (!res){
        return NULL;
    }
    res->cantidad = 0;
    res->capacidad = un_tp->cantidad + otro_tp.cantidad; 
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    if(!res->pokemones){
        free(res);
        return NULL;
    }
    
    for (size_t i = 0; i < un_tp->cantidad;i++){
        res->pokemones[res->cantidad] = un_tp->pokemones[i];
        res->cantidad++;
    }
    

    return res;
}   