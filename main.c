#include <stdio.h>

#include "src/tp1.h"

// argc es la cantidad de parámetros
// argv es un vector de strings con los parámetros
int main(int argc, char *argv[]){
	if (argc > 10){
		return 0;
	}
	//leer un archivo según el parámetro y hacer lo que corresponda según el enunciado
	tp1_t *tp = tp1_leer_archivo("ejemplos/normal.csv");
	tp1_t *tp2 = tp1_leer_archivo(argv[1]);
	
	tp1_t *tp_union1 = tp1_union(tp,tp2);
	printf("%lld",tp1_cantidad(tp_union1));

	tp1_guardar_archivo(tp_union1, "nuevooo");
	return 0;
}
