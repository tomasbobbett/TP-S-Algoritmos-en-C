# TDA LISTA/PILA/COLA

## Repositorio de Tomás Bobbett - 110560 - Tomas_Bobbett@hotmail.com

- Para compilar: Estando en el directorio principal

```bash
gcc -Wall -Werror -Wconversion -std=c99 src/..c sarasa.c -o sarasa
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
línea con valgrind
```
---
##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluir **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
<h3>1. Explicar qué es una lista, lista enlazada y lista doblemente enlazada:</h3>
Una lista a secas es un conjunto ordenado de objetos donde cada posición tiene un elemento, pero una lista enlazada 
es un tipo de dato abstracto (TDA) que es representado por medio de nodos conectados en una sola direccion (simplemente enlazada). 

-------------------IMAGEN DE LISTA ENLAZADA GENERAL------------------------------

Cada uno de estos nodos tiene un puntero al siguiente nodo en la lista (si este es el ultimo su siguiente seria NULL)
y tambien contiene el puntero al dato en si q almacen el nodo.

-------------------IMAGEN DE NODO SOLO----------------------------------

La diferencia entre la lista SIMPLEMENTE enlazada y la DOBLEMENTE enlazada esta en, como indica el nombre, la cantidad de direcciones en que se puede mover de un nodo a otro. 

-------------------IMAGEN LISTA SIMPLE Y DOBLE-------------------------

Sus caracteristicas son que la lista simple tiene una sola direccion, por lo que solo se puede recorrer para un solo lado. En 
cambio, en la doble se puede ir en dos direcciones (adelante y atras).
Esto es una ventaja hablando de complejidad, pero tambien es una desventaja al ser mas complicado de implementar. Esto ocurre ya que
el nodo de la doblemente enlazada tiene un puntero de mas para el nodo anterior, mientras que los nodos de la simplemente 
enlazada solo tiene uno para su siguiente.

-------------------IMAGEN DIFERENCIA DE NODOS--------------------------


La ventaja en la complejidad esta en la primitiva de eliminar al final, siendo O(n) en la lista simplemente enlazada, pero O(1) en la
doble. ¿Por que? a la hora de eliminar al final de la lista simplemente enlazada, necesitamos tener dos nodos, primero el ultimo y
luego su anterior para actualizar la cola de la lista, pero... ¿como hacemos para voler para atras? ¡No se puede! Habria que volver a 
recorrer tooda la lista para conseguir este nodo, por eso su complejidad O(n). En cambio, la ventaja de la lista doblemente enlazada al 
tener un puntero al nodo anterior, permite el acceso a este en O(1). Por lo que la complejidad para eliminar es O(1).

<h3>2.Explicar qué es una lista circular y de qué maneras se puede implementar.</h3>
Una lista circular es una lista en la que el último nodo apunta nuevamente al primero, formando un ciclo cerrado.

-----------------IMAGEN DE LISTA CIRCULAR GENERAL----------------------

Puede implementarse como lista simple (la cola apunta a la cabeza) o como lista doble (la cola apunta a la cabeza y la cabeza al final).

-----------------IMAGEN DE LISTA CIRCULAR DOBLEMENTE ENLAZADA-----------

Se usa cuando se necesita un recorrido infinito, como en sistemas de turnos o buffers circulares.

<h3>3.Explicar la diferencia de funcionamiento entre cola y pila.</h3>
Una cola es una estructura FIFO (first in, first out), donde el primer elemento en entrar es el primero en salir, como una fila de personas.

-----------------IMAGEN DE DIAGRAMA DE FUNCIONAMIENTO DE LA COLA--------------------------------

Una pila es una estructura LIFO (last in, first out), donde el último en entrar es el primero en salir, como una pila de platos.

-----------------IMAGEN DE DIAGRAMA DE FUNCIONAMIENTO DE LA PILA--------------------------------

La diferencia está en el orden de extracción y en las operaciones principales: en la cola se encola y desencola, en la pila se apila y desapila.

<h3>4.Explicar la diferencia entre un iterador interno y uno externo.</h3>
Un iterador interno es una función que recorre la estructura por dentro, aplicando otra función a cada elemento sin que el usuario tenga control del paso a paso.
Un iterador externo en cambio le da al usuario el control para avanzar manualmente sobre los elementos con operaciones como avanzar() o hay_siguiente().
El interno es más simple de usar, pero el externo brinda mayor flexibilidad porque se puede detener el recorrido en cualquier punto.
