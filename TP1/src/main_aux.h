#ifndef MAIN_H_
#define MAIN_H_
#include "tp1.h"

const char *tipo_a_string(enum tipo_pokemon tipo);

bool imprimir_pokemon(struct pokemon *pk, void *extra);

void mostrar_uso();

#endif