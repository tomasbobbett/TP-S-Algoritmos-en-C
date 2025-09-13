#include "tp1.h"
#include <stdio.h>
#include <string.h>

#define READ_MODE "r"
#define WRITE_MODE "w"
#define CAPACIDAD_INICIAL_TP1 10

// Definición de la estructura oculta
struct tp1 {
    struct pokemon *pokemones_nombres;//Arrglo dinamico de pokemones ordenados por NOMBRE
    struct pokemon *pokemones;      // arreglo dinámico de pokemones ordenados por ID
    size_t cantidad, capacidad;     // cantidad de pokemones almacenados y capacidad del arreglo
};

// -----------------FUNCIONES AUXILIARES TO-DO(SACAR DEL TP0 A ARCHIVO SOLO DE FUNC AUXILIARES)-----------------
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
    if (!tp) return NULL;
    if (inicio > final) return NULL;
    if (inicio == final){
        if (tp->pokemones_nombres[inicio].nombre && strcmp(tp->pokemones_nombres[inicio].nombre, nombre) == 0){
            return &tp->pokemones_nombres[inicio];
        }
        return NULL;
    }
    int mid = (inicio + final) / 2;
    int cmp = strcmp(tp->pokemones_nombres[mid].nombre, nombre);
    if (cmp == 0) return &tp->pokemones_nombres[mid];
    if (cmp < 0) return busqueda_binaria_pokemon(tp, nombre, mid+1, final);
    return busqueda_binaria_pokemon(tp, nombre, inicio, mid-1);
}

static struct pokemon *busqueda_binaria_id(tp1_t *tp, int id,int inicio, int final){
    if (!tp) return NULL;
    if (inicio > final) return NULL;
    if (inicio == final){
        if (tp->pokemones[inicio].id == id) return &tp->pokemones[inicio];
        return NULL;
    }
    int mid = (inicio + final) / 2;
    if (tp->pokemones[mid].id == id) return &tp->pokemones[mid];
    if (tp->pokemones[mid].id < id) return busqueda_binaria_id(tp, id, mid+1, final);
    return busqueda_binaria_id(tp, id, inicio, mid-1);
}

static enum tipo_pokemon parsear_string_tipo(const char *tipo_str) {
    if (strcmp(tipo_str, "ELEC") == 0) return TIPO_ELEC;
    if (strcmp(tipo_str, "FUEG") == 0) return TIPO_FUEG;
    if (strcmp(tipo_str, "PLAN") == 0) return TIPO_PLAN;
    if (strcmp(tipo_str, "AGUA") == 0) return TIPO_AGUA;
    if (strcmp(tipo_str, "NORM") == 0) return TIPO_NORM;
    if (strcmp(tipo_str, "FANT") == 0) return TIPO_FANT;
    if (strcmp(tipo_str, "PSI") == 0)  return TIPO_PSI;
    if (strcmp(tipo_str, "LUCH") == 0) return TIPO_LUCH;
    return -1; // inválido
}

static bool existe_pokemon(struct tp1 *tp, int id){
    if (!tp) return false;
    for (size_t i = 0; i < tp->cantidad; i++){
        if (tp->pokemones[i].id == id) return true;
    }
    return false;
}

static bool tp1_redimensionar(tp1_t *tp) {
    if (!tp) return false;

    size_t nueva_capacidad = tp->capacidad ? tp->capacidad * 2 : CAPACIDAD_INICIAL_TP1;

    struct pokemon *nuevo_array = malloc(nueva_capacidad * sizeof(struct pokemon));
    struct pokemon *nuevo_array_nombres = malloc(nueva_capacidad * sizeof(struct pokemon));
    if (!nuevo_array || !nuevo_array_nombres) {
        free(nuevo_array);
        free(nuevo_array_nombres);
        return false;
    }

    /* copiar elementos actuales */
    for (size_t i = 0; i < tp->cantidad; i++) {
        nuevo_array[i] = tp->pokemones[i];
        nuevo_array_nombres[i] = tp->pokemones_nombres[i];
    }

    free(tp->pokemones);
    free(tp->pokemones_nombres);

    tp->pokemones = nuevo_array;
    tp->pokemones_nombres = nuevo_array_nombres;
    tp->capacidad = nueva_capacidad;
    return true;
}


static bool insertar_ordeando(struct tp1 *tp, struct pokemon p){
    if (!tp) return false;
    if (tp->capacidad == tp->cantidad){
        if (!tp1_redimensionar(tp)) return false;
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
    if (!tp) return false;
    if (tp->capacidad == tp->cantidad){
        if (!tp1_redimensionar(tp)) return false;
    }
    size_t i = tp->cantidad;
    while(i > 0 && strcmp(tp->pokemones_nombres[i-1].nombre, p.nombre) > 0){
        tp->pokemones_nombres[i] = tp->pokemones_nombres[i-1];
        i--;
    }
    tp->pokemones_nombres[i] = p;
    tp->cantidad++;
    return true;
}

/* ---------------------------------- LEER ARCHIVO------------------------------- */
tp1_t *tp1_leer_archivo(const char *nombre){
    FILE *file = fopen(nombre, READ_MODE);
    if (!file) return NULL;

    struct tp1 *tp = malloc(sizeof(struct tp1));
    if (!tp){ fclose(file); return NULL; }

    tp->cantidad = 0;
    tp->capacidad = CAPACIDAD_INICIAL_TP1;
    tp->pokemones = malloc(tp->capacidad * sizeof(struct pokemon));
    tp->pokemones_nombres = malloc(tp->capacidad * sizeof(struct pokemon));
    if (!tp->pokemones || !tp->pokemones_nombres) {
        free(tp->pokemones);
        free(tp->pokemones_nombres);
        free(tp);
        fclose(file);
        return NULL;
    }

    char linea[500];
    while (fgets(linea, sizeof(linea), file)) {
        int id, ataque, defensa, velocidad;
        char nombre_poke[120];
        char tipo_str[16];
        int leidos = sscanf(linea, "%d,%[^,],%[^,],%d,%d,%d", &id, nombre_poke, tipo_str, &ataque, &defensa, &velocidad);
        if (leidos != 6) continue;

        if (existe_pokemon(tp, id)) continue;

        struct pokemon p;
        p.id = id;
        p.nombre = strdup(nombre_poke);
        if (!p.nombre) { /* fallo de strdup: limpio y salgo */
            // liberar tp y lo que haya hasta ahora
            tp1_destruir(tp);
            fclose(file);
            return NULL;
        }
        p.tipo = parsear_string_tipo(tipo_str);
        p.ataque = ataque;
        p.defensa = defensa;
        p.velocidad = velocidad;

        /* insertar por id */
        if (!insertar_ordeando(tp, p)) {
            /* insertar_ordeando falló => p no fue copiadoo en nombres; liberar su nombre */
            free(p.nombre);
            tp1_destruir(tp);
            fclose(file);
            return NULL;
        }
        /* insertar por nombre (esta función incrementa tp->cantidad) */
        if (!insertar_nombre_ordenado(tp, p)) {
            /* aquí p ya fue colocado en pokemones (pero no incrementamos cantidad),
               y su puntero p.nombre está dentro de pokemones => no lo liberamos,
               simplemente destruimos todo y salimos. */
            tp1_destruir(tp);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return tp;
}

/* ---------------------------------- CANTIDAD ------------------------------- */

size_t tp1_cantidad(tp1_t *tp1){
    if (!tp1) return 0;
    return tp1->cantidad;
}
/* ---------------------------------- GUARDA ARCHIVO------------------------------- */

tp1_t *tp1_guardar_archivo(tp1_t *tp1, const char *nombre){
    if (!tp1 || !nombre) return NULL;
    FILE *file = fopen(nombre, WRITE_MODE);
    if(!file) return NULL;

    for (size_t i = 0; i < tp1->cantidad; i++){
        struct pokemon *p = &tp1->pokemones[i];
        fprintf(file, "%d,%s,%s,%d,%d,%d\n",p->id,p->nombre,tipo_a_string(p->tipo),p->ataque,p->defensa,p->velocidad);
    }
    fclose(file);
    return tp1;
}
/* ---------------------------------- UNION ------------------------------- */

tp1_t *tp1_union(tp1_t *un_tp, tp1_t *otro_tp){
    if (!un_tp && !otro_tp) return NULL;

    const char *tmp_file = "tmp_union.csv";

    if (!un_tp) {
        if (!tp1_guardar_archivo(otro_tp, tmp_file)) return NULL;
        tp1_t *res = tp1_leer_archivo(tmp_file);
        remove(tmp_file);
        return res;
    }

    if (!otro_tp) {
        if (!tp1_guardar_archivo(un_tp, tmp_file)) return NULL;
        tp1_t *res = tp1_leer_archivo(tmp_file);
        remove(tmp_file);
        return res;
    }

    tp1_t *res = malloc(sizeof(tp1_t));
    if (!res) return NULL;
    res->cantidad = 0;
    res->capacidad = un_tp->cantidad + otro_tp->cantidad;
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    res->pokemones_nombres = NULL; /* no construido aquí */
    if (!res->pokemones) { free(res); return NULL; }

    size_t i=0,j=0,k=0;
    while (i < un_tp->cantidad && j < otro_tp->cantidad) {
        if (un_tp->pokemones[i].id < otro_tp->pokemones[j].id) {
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++;
        } else if (un_tp->pokemones[i].id > otro_tp->pokemones[j].id) {
            res->pokemones[k] = otro_tp->pokemones[j];
            res->pokemones[k].nombre = strdup(otro_tp->pokemones[j].nombre);
            j++;
        } else {
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++; j++;
        }
        k++;
    }
    while (i < un_tp->cantidad) {
        res->pokemones[k] = un_tp->pokemones[i];
        res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
        i++; k++;
    }
    while (j < otro_tp->cantidad) {
        res->pokemones[k] = otro_tp->pokemones[j];
        res->pokemones[k].nombre = strdup(otro_tp->pokemones[j].nombre);
        j++; k++;
    }
    res->cantidad = k;
    return res;
}
/* ---------------------------------- INTERSECCION ------------------------------- */

tp1_t *tp1_interseccion(tp1_t *un_tp, tp1_t *otro_tp){
    if (!un_tp || !otro_tp) {
        tp1_t *res = malloc(sizeof(tp1_t));
        if (!res) return NULL;
        res->cantidad = 0;
        res->capacidad = 0;
        res->pokemones = NULL;
        res->pokemones_nombres = NULL;
        return res;
    }

    tp1_t *res = malloc(sizeof(tp1_t));
    if (!res) return NULL;
    res->cantidad = 0;
    res->capacidad = (un_tp->cantidad < otro_tp->cantidad) ? un_tp->cantidad : otro_tp->cantidad;
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    res->pokemones_nombres = NULL;
    if (!res->pokemones) { free(res); return NULL; }

    size_t i=0,j=0,k=0;
    while (i < un_tp->cantidad && j < otro_tp->cantidad) {
        if (un_tp->pokemones[i].id == otro_tp->pokemones[j].id) {
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++; j++; k++;
        } else if (un_tp->pokemones[i].id < otro_tp->pokemones[j].id) {
            i++;
        } else {
            j++;
        }
    }
    res->cantidad = k;
    return res;
}
/* ---------------------------------- DIFERENCIA ------------------------------- */

tp1_t *tp1_diferencia(tp1_t *un_tp, tp1_t *otro_tp){
    if (!un_tp) {
        tp1_t *res = malloc(sizeof(tp1_t));
        if (!res) return NULL;
        res->cantidad = 0;
        res->capacidad = 0;
        res->pokemones = NULL;
        res->pokemones_nombres = NULL;
        return res;
    }
    if (!otro_tp) {
        tp1_t *res = malloc(sizeof(tp1_t));
        if (!res) return NULL;
        res->cantidad = un_tp->cantidad;
        res->capacidad = un_tp->cantidad;
        res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
        res->pokemones_nombres = NULL;
        if (!res->pokemones) { free(res); return NULL; }
        for (size_t i = 0; i < un_tp->cantidad; i++) {
            res->pokemones[i] = un_tp->pokemones[i];
            res->pokemones[i].nombre = strdup(un_tp->pokemones[i].nombre);
        }
        return res;
    }

    tp1_t *res = malloc(sizeof(tp1_t));
    if (!res) return NULL;
    res->cantidad = 0;
    res->capacidad = un_tp->cantidad;
    res->pokemones = malloc(res->capacidad * sizeof(struct pokemon));
    res->pokemones_nombres = NULL;
    if (!res->pokemones) { free(res); return NULL; }

    size_t i = 0, j = 0, k = 0;
    while (i < un_tp->cantidad && j < otro_tp->cantidad) {
        if (un_tp->pokemones[i].id < otro_tp->pokemones[j].id) {
            res->pokemones[k] = un_tp->pokemones[i];
            res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
            i++; k++;
        } else if (un_tp->pokemones[i].id > otro_tp->pokemones[j].id) {
            j++;
        } else {
            i++; j++;
        }
    }
    while (i < un_tp->cantidad) {
        res->pokemones[k] = un_tp->pokemones[i];
        res->pokemones[k].nombre = strdup(un_tp->pokemones[i].nombre);
        i++; k++;
    }
    res->cantidad = k;
    return res;
}

/* ---------------------------------- BUSCAR POR NOMBRE ------------------------------- */
struct pokemon *tp1_buscar_nombre(tp1_t *tp, const char *nombre){
    if (!tp || tp->cantidad == 0 || !tp->pokemones_nombres) return NULL;
    return busqueda_binaria_pokemon(tp, nombre, 0, (int)tp->cantidad - 1);
}
/* ---------------------------------- BUSCAR POR ID ------------------------------- */
struct pokemon *tp1_buscar_id(tp1_t *tp, int id){
    if (!tp || tp->cantidad == 0 || !tp->pokemones) return NULL;
    return busqueda_binaria_id(tp, id, 0, (int)tp->cantidad - 1);
}

/* ---------------------------------- ITERAR ------------------------------- */
size_t tp1_con_cada_pokemon(tp1_t *un_tp, bool (*f)(struct pokemon *, void *), void *extra) {
    if (!un_tp || !f) return 0;

    size_t cont = 0;
    for (size_t i = 0; i < un_tp->cantidad; i++) {
        if (!f(&un_tp->pokemones[i], extra)) break;
        cont++;
    }
    return cont;
}

/* ---------------------------------- DESTRUIR ------------------------------- */
void tp1_destruir(tp1_t *tp1){
    if (!tp1) return;

    size_t n = tp1->cantidad;
    size_t cap = 0;
    if (tp1->pokemones) cap += n;
    if (tp1->pokemones_nombres) cap += n;

    char **unicos = NULL;
    size_t unicos_count = 0;
    if (cap > 0) {
        unicos = malloc(cap * sizeof(char*));
        if (unicos) {
            for (size_t i = 0; i < n; i++) {
                if (tp1->pokemones && tp1->pokemones[i].nombre) {
                    char *name = tp1->pokemones[i].nombre;
                    bool seen = false;
                    for (size_t j = 0; j < unicos_count; j++) if (unicos[j] == name) { seen = true; break; }
                    if (!seen) unicos[unicos_count++] = name;
                }
                if (tp1->pokemones_nombres && tp1->pokemones_nombres[i].nombre) {
                    char *name = tp1->pokemones_nombres[i].nombre;
                    bool seen = false;
                    for (size_t j = 0; j < unicos_count; j++) if (unicos[j] == name) { seen = true; break; }
                    if (!seen) unicos[unicos_count++] = name;
                }
            }
            for (size_t i = 0; i < unicos_count; i++) free(unicos[i]);
            free(unicos);
        } else {
            /* fallback menos completo: si no pudimos reservar el array auxiliar,
               liberamos solo nombres que estén en pokemones (esto evita double-free
               si nombres en pokemones son los canónicos en la mayoría de los casos) */
            if (tp1->pokemones) {
                for (size_t i = 0; i < n; i++) free(tp1->pokemones[i].nombre);
            } else if (tp1->pokemones_nombres) {
                for (size_t i = 0; i < n; i++) free(tp1->pokemones_nombres[i].nombre);
            }
        }
    }

    free(tp1->pokemones);
    free(tp1->pokemones_nombres);
    free(tp1);
}
