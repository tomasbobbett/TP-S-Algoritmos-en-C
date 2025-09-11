#include <stdio.h>

#include "src/tp1.h"

#define MODO_LECTURA "r"
// argc es la cantidad de parámetros
// argv es un vector de strings con los parámetros
int main(int argc, char *argv[]){
	if (argc > 10){
		return 0;
	}
	//leer un archivo según el parámetro y hacer lo que corresponda según el enunciado
	tp1_t *tp = tp1_leer_archivo(argv[1]);
	printf("%lld",tp1_cantidad(tp));
	tp1_guardar_archivo(tp, "nuevooo");
	return 0;
}
