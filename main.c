#include <stdio.h>

#include "src/tp1.h"

#define MODO_LECTURA "r"
// argc es la cantidad de parámetros
// argv es un vector de strings con los parámetros
int main(int argc, char *argv[])
{
	//leer un archivo según el parámetro y hacer lo que corresponda según el enunciado
	FILE *archivo = fopen(argv[1], MODO_LECTURA);
	if (archivo == NULL) {
		perror("Error al abrir el archivo");
		return 1;
	}
	
	
	// Procesar el archivo

	
	fclose(archivo);
	return 0;
}
