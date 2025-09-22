# TDA Lista/Pila/Cola

Se pide implementar una lista simplemente enlazada, una pila y una cola según las interfaces definidas en clase.

Los TDAs entregados deberan compilar y pasar las pruebas dispuestas por la cátedra sin errores, adicionalmente estas pruebas deberán ser ejecutadas **sin pérdida de memoria**.


En el archivo main.c se debe implementar un programa que por línea de comandos reciba el nombre de un archivo y utilizando las primitivas del TP1 cargue un archivo de pokemones en una lista. Se deben implementar las funcionalidades de búsqueda de pokemon por nombre y por id utilizando las primitivas de lista. No se permite modificar los archivos de cabecera.


Se facilita al alumno un archivo simple de _ejemplo_ (**ejemplo.c**). **Este archivo no es mas que un programa mínimo hecho en clase como ejemplo de utilización de los iteradores y existe solamente a modo de ejemplo**. No fue compilado en clase por lo que puede contener errores. No es parte de la entrega.

Recordar que es obligatorio entregar un informe que explique cómo se implementaron los TDAs, cómo funcionan, la complejidad de las operaciones y cualquier aclaración que sea necesaria para el corrector.

Recordar también que es obligatorio entregar **pruebas_alumno.c** con las pruebas realizadas para verificar 
el correcto funcionamiento de los TDA.

## Restricciones

  Para que el trabajo se considere aprobado, la implementación debe cumplir los siguientes requisitos:

  - Las lista debe ser simplemente enlazada
  - Las operaciones **apilar**, **desapilar** y **tope** deben ser **O(1)**
  - Las operaciones **encolar**, **desencolar** y **frente** deben ser **O(1)**
  - Las implementaciones de pila y cola deben reutilizar la implementación de lista

## Parte teórica

Explicar teóricamente los siguientes puntos (no necesariamente en orden, pero por favor usando diagramas):

   - Explicar qué es una lista, lista enlazada y lista doblemente enlazada.
     - Explicar las características de cada una.
     - Explicar las diferencias internas de implementación.
     - Explicar ventajas y desventajas de cada una, si existen.
   - Explicar qué es una lista circular y de qué maneras se puede implementar.
   - Explicar la diferencia de funcionamiento entre cola y pila.
   - Explicar la diferencia entre un iterador interno y uno externo.
