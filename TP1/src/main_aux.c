#include "main_aux.h"
#include "tp1.h"
#include <stdio.h>
void mostrar_uso()
{
	printf("Uso:\n"
	       "  ./tp1 <archivo.csv> buscar nombre <nombre>\n"
	       "  ./tp1 <archivo.csv> buscar id <id>\n"
	       "  ./tp1 <archivo.csv> union <archivo2.csv> <resultado.csv>\n"
	       "  ./tp1 <archivo.csv> interseccion <archivo2.csv> <resultado.csv>\n"
	       "  ./tp1 <archivo.csv> diferencia <archivo2.csv> <resultado.csv>\n"
	       "  ./tp1 <archivo.csv> mostrar nombre\n"
	       "  ./tp1 <archivo.csv> mostrar id\n");
}
const char *tipo_a_string(enum tipo_pokemon tipo)
{
	switch (tipo) {
	case TIPO_ELEC:
		return "ELEC";
	case TIPO_FUEG:
		return "FUEG";
	case TIPO_PLAN:
		return "PLAN";
	case TIPO_AGUA:
		return "AGUA";
	case TIPO_NORM:
		return "NORM";
	case TIPO_FANT:
		return "FANT";
	case TIPO_PSI:
		return "PSI";
	case TIPO_LUCH:
		return "LUCH";
	default:
		return "DESCONOCIDO";
	}
}

bool imprimir_pokemon(struct pokemon *pk, void *extra)
{
	(void)extra;
	printf("%d,%s,%s,%d,%d,%d\n", pk->id, pk->nombre,
	       tipo_a_string(pk->tipo), pk->ataque, pk->defensa, pk->velocidad);
	return true; // para que siga iterando
}