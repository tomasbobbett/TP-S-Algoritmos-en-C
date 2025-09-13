#include "tp1.h"
#include <stdio.h>
#include <string.h>

#define READ_MODE "r"
#define WRITE_MODE "w"
#define CAPACIDAD_INICIAL_TP1 10

// Definición de la estructura oculta
struct tp1 {
    struct pokemon *pokemones_nombres;
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
static struct pokemon *busqueda_binaria_pokemon(tp1_t *tp, const char *nombre,int inicio, int final){
    if (inicio >= final){
        if (strcmp(tp->pokemones_nombres[inicio].nombre, nombre) == 0){
            return &tp->pokemones_nombres[inicio];
        }
        return NULL;
    }
    int mid = ((inicio + final) / 2);
    if (strcmp(tp->pokemones_nombres[mid].nombre, nombre) == 0){
        return &tp->pokemones_nombres[mid];
    }else if (strcmp(tp->pokemones_nombres[mid].nombre, nombre) < 0){
        return busqueda_binaria_pokemon(tp,nombre,mid+1,final);
    }
    return busqueda_binaria_pokemon(tp,nombre,inicio,mid);
}

static struct pokemon *busqueda_binaria_id(tp1_t *tp, int id,int inicio, int final){
    if (inicio >= final){
        if (tp->pokemones[inicio].id == id){
            return &tp->pokemones[inicio];
        }
        return NULL;
    }
    int mid = ((inicio + final) / 2);
    if (tp->pokemones[mid].id == id){
        return &tp->pokemones[mid];
    }else if ((tp->pokemones[mid].id< id)){
        return busqueda_binaria_pokemon(tp,id,mid+1,final);
    }
    return busqueda_binaria_pokemon(tp,id,inicio,mid);

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
 // funcion estatica para saber si el pokemon procesado ya habia sido procesado
static bool existe_pokemon(struct tp1 *tp, int id){
    for (size_t i = 0; i < tp->cantidad; i++){//       La hacemos statica porque no tendira sentido usarla en el exterior de el scope general
        if (tp->pokemones[i].id == id){
            return true;
        }
    }
    return false;
}
// Funcion para redimensinoar el tamaño de memoria almacenado para tp->pokemones
static bool tp1_redimensionar(tp1_t *tp) {
    if (!tp) return false;

    size_t nueva_capacidad = tp->capacidad * 2;
    if (nueva_capacidad == 0) {
        nueva_capacidad = CAPACIDAD_INICIAL_TP1;
    }

    struct pokemon *nuevo_array = realloc(tp->pokemones, nueva_capacidad * sizeof(struct pokemon));
    struct pokemon *nuevo_array_nombre = realloc(tp->pokemones_nombres, nueva_capacidad * sizeof(struct pokemon));
    if (!nuevo_array) return false;
    if (!nuevo_array_nombre) return false;

    tp->pokemones = nuevo_array;
    tp->pokemones_nombres = nuevo_array_nombre;
    tp->capacidad = nueva_capacidad;
    return true;
}
//Implementaciones de las funciones declaradas en tp1.h por la catedra---------------
static bool insertar_ordeando(struct tp1 *tp, struct pokemon p){
    if (tp->capacidad == tp->cantidad){
        bool redim = tp1_redimensionar(tp);
        if (!redim){                                //Antes de agregr el pokemon chequeamos si hay que redimensionar
            return false;
        }
    }
    size_t i = tp->cantidad;
    while(i > 0 && tp->pokemones[i-1].id > p.id){
        tp->pokemones[i] = tp->pokemones[i-1];
        i--;
    }
    tp->pokemones[i] = p;
    return true;
}
static bool insertar_nombre_ordenado(struct tp1 *tp, struct pokemon p){
    size_t i = tp->cantidad;
    while(i > 0 && strcmp(tp->pokemones_nombres[i-1].nombre, p.nombre)>0){
        tp->pokemones_nombres[i] = tp->pokemones_nombres[i-1];
        i--;
    }
    tp->pokemones_nombres[i] = p;
    tp->cantidad++;
    return true;
}

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
    tp->pokemones_nombres = malloc(tp->capacidad * sizeof(struct pokemon));
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
        //Añadir pokemon leido a &tp->pokemones[tp->cantidad]; y luego aumentar cantidad para no reemplazar el anterior
        struct pokemon p;
        p.id = id;
        p.nombre = strdup(nombre_poke);
        p.tipo = parsear_string_tipo(tipo_str);
        p.ataque=ataque;
        p.defensa = defensa;
        p.velocidad = velocidad;
        if (!insertar_ordeando(tp,p)){
            fclose(file);
            // EXPLOTAR MEMORIA
            return  NULL;
        }
        if(!insertar_nombre_ordenado(tp,p)){
            fclose(file);
            return NULL;
        }
        
    }
    fclose(file);
    return tp;
}

size_t tp1_cantidad(tp1_t *tp1){
    return tp1->cantidad;
}

tp1_t *tp1_guardar_archivo(tp1_t *tp1, const char *nombre){
    FILE *file = fopen(nombre, WRITE_MODE);
    if(!file || !tp1){
        return NULL;
    }
    for (size_t i = 0; i < tp1->cantidad; i++){
        struct pokemon *p = &tp1->pokemones[i];
        fprintf(file, "%d,%s,%s,%d,%d,%d\n",p->id,p->nombre,tipo_a_string(p->tipo),p->ataque,p->defensa,p->velocidad);
    }
    fclose(file);
    return tp1;
}

tp1_t *tp1_union(tp1_t *un_tp, tp1_t *otro_tp){
    if (un_tp == NULL && otro_tp == NULL){
        return NULL;
    }
     const char *tmp_file = "tmp_union.csv";

    // Si un_tp es NULL → usamos solo otro_tp
    if (!un_tp) {
        if (!tp1_guardar_archivo(otro_tp, tmp_file)) return NULL;
        tp1_t *res = tp1_leer_archivo(tmp_file);
        remove(tmp_file); // borramos el temporal
        return res;
    }

    // Si otro_tp es NULL → usamos solo un_tp
    if (!otro_tp) {
        if (!tp1_guardar_archivo(un_tp, tmp_file)) return NULL;
        tp1_t *res = tp1_leer_archivo(tmp_file);
        remove(tmp_file); // borramos el temporal
        return res;
    }

    tp1_t *res = malloc(sizeof(tp1_t));// Reservamos memoria para el struct de tp1 
    if (!res){
        return NULL;
    }
    res->cantidad = 0;
    res->capacidad = un_tp->cantidad + otro_tp->cantidad; 
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while(i<un_tp->cantidad && j < otro_tp->cantidad){
        if (un_tp->pokemones[i].id < otro_tp->pokemones[j].id){
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++;
        }
        else if (un_tp->pokemones[i].id > otro_tp->pokemones[j].id){
            res->pokemones[k] = otro_tp->pokemones[j];
            res->pokemones[k].nombre = strdup(otro_tp->pokemones[j].nombre);
            j++;
        }else{
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++;
            j++;
        }
        k++;
    }
    while(i < un_tp->cantidad){
         res->pokemones[k] = un_tp->pokemones[i];
        res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
        i++;
        k++;
    }
    while(j < otro_tp->cantidad){
        res->pokemones[k] = otro_tp->pokemones[j];
        res->pokemones[k].nombre = strdup(otro_tp->pokemones[j].nombre);
        j++;
        k++;
    }
    res->cantidad = k;
    return res;
}   


tp1_t *tp1_interseccion(tp1_t *un_tp, tp1_t *otro_tp){
    if (!un_tp || !otro_tp) {
        // Intersección con NULL → vacía
        tp1_t *res = malloc(sizeof(tp1_t));
        if (!res) return NULL;
        res->cantidad = 0;
        res->capacidad = 0;
        res->pokemones = NULL;
        return res;
    }

    tp1_t *res = malloc(sizeof(tp1_t));// Reservamos memoria para el struct resultante de la inters
    if (!res){
        return NULL;
    }
    res->cantidad = 0;
    if (un_tp->cantidad < otro_tp->cantidad){
        res->capacidad = un_tp->cantidad;
    }else{
        res->capacidad = otro_tp->cantidad;
    }
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while(i<un_tp->cantidad && j < otro_tp->cantidad){
        if (un_tp->pokemones[i].id == otro_tp->pokemones[j].id){
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++;
            j++;
            k++;
        }else if (un_tp->pokemones[i].id < otro_tp->pokemones[j].id){
            i++;
        }else{
            j++;
        }
    }
    res->cantidad = k;
    return res;
}


tp1_t *tp1_diferencia(tp1_t *un_tp, tp1_t *otro_tp){
    if (un_tp == NULL) {
        tp1_t *res = malloc(sizeof(tp1_t));
        if (!res){
            return NULL;  
        } 
        res->cantidad = 0;
        res->capacidad = 0;
        res->pokemones = NULL;
        return res;
    }
    if (otro_tp == NULL) {
        // Copiar un_tp
        tp1_t *res = malloc(sizeof(tp1_t));
        if (!res){
            return NULL;
        } 
        res->cantidad = un_tp->cantidad;
        res->capacidad = un_tp->cantidad;
        res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
        if (!res->pokemones) {
            free(res); return NULL;
        }
        for (size_t i = 0; i < un_tp->cantidad; i++) {
            res->pokemones[i] = un_tp->pokemones[i];
            res->pokemones[i].nombre = strdup(un_tp->pokemones[i].nombre);
        }
        return res;
    }

    tp1_t *res =  malloc(sizeof(tp1_t));
    if (!res){
        return NULL;
    }
    res->cantidad = 0;
    res->capacidad = un_tp->cantidad;
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    size_t i = 0,j = 0, k= 0;
    while(i<un_tp->cantidad && j < otro_tp->cantidad){
        if (un_tp->pokemones[i].id < otro_tp->pokemones[j].id){
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++;
             k++;
        }else if (un_tp->pokemones[i].id > otro_tp->pokemones[j].id){
            j++;
        }else{
            i++;
            j++;
        }
    }
    while (i < un_tp->cantidad) {
        res->pokemones[k] = un_tp->pokemones[i];
        res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
        i++;
        k++;
    }
    res->cantidad = k;
    return res;
}


struct pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre){
    if (tp->cantidad == 0){
        return NULL;
    }
    struct pokemon *res = busqueda_binaria_pokemon(tp,nombre,0,tp->cantidad-1);
    return res;
}

struct pokemon *tp1_buscar_id(tp1_t *tp, int id){
    if (tp->cantidad == 0){
        return NULL;
    }
    struct pokemon *res = busqueda_binaria_id(tp,id,0,tp->cantidad-1);
    return res;
}