# Arreglos en C

Los arreglos, a diferencia de las variables de tipos básicos (como `#!c int`, `#!c char` o `#!c double`) son variables
estructuradas.
Cada elemento del arreglo es almacenado en forma consecutiva en la memoria, permitiendo el acceso secuencia a cada
elemento del mismo.

Los arreglos pueden ser definidos de distintas dimensiones, por ejemplo, tenemos arreglos unidimensiones, pero también
bidimensionales o multidimensionales.

Además, los arreglos pueden ser dinámicos o estáticos.
Cuando se define un arreglo dinámico, se está hace uso de memoria dinámica, un tema que veremos más adelante.
En cambio, los arreglos estáticos se definen en tiempo de compilación y tienen un tamaño fijo.
Los arreglos que discutiremos en este documento son los de tipo **estático**.

## Arreglos unidimensionales

Un arreglo unidimensional---también llamado _array_ o vector---es una variable donde almacenamos en forma consecutiva un
tipo de variable dado (por ahora, variables de tipos básicos, pero podrían ser otras variables).

Un arreglo se puede definir de 2 maneras:

-   por cantidad, o
-   por enumeración.

Al definir el arreglo por cantidad, debemos indicar cuántos elementos tiene, como en el ejemplo siguiente:

``` c
int array[5];
```

en cambio, si quisiéramos definirlo por enumeración de sus elementos, podríamos hacerlo del siguiente modo:

``` c
int array[] = {94, 102, 19, -42, 75};
```

En dicho ejemplo, se define un arreglo que contiene 5 enteros.
La siguiente imagen ejemplifica cómo se almacenan estos enteros en memoria:

<figure markdown>
![Definición de array en memoria](img1.svg)
</figure>

En dicha imagen, se observa la definición del arreglo `array` y los 5 enteros, cada uno de ellos ocupando 4 bytes.
Sin embargo, en forma esquemática, generalmente dibujaremos el arreglo como una cantidad de elementos, y no de bytes, es
decir, dibujaríamos algo similar a la siguiente imagen:

<figure markdown>
![Esquema de un arreglo](img2.svg)
</figure>

### Acceso para lectura

Si queremos acceder a un elemento del arreglo, se utiliza el nombre de la variable (`array`) y los corchetes (`[]`)
indicando el índice al que queremos acceder.
Como en C se utiliza el 0-indexing, el primer elemento del arreglo se encuentra en el índice 0, y se accede mediante la
sentencia:

``` c
array[0]
```

Entonces, si quisiéramos acceder al 3er entero y almacenarlo en una variable llamada `aux` (también entera), haríamos lo
siguiente:

``` c
int aux;

aux = array[2];
```


### Modificación del arreglo

Si quisiéramos acceder a un elemento y modificarlo, al sintáxis es similar, sólo que el elemento que queremos modificar
debe ser un [LHS](https://en.wikipedia.org/wiki/Sides_of_an_equation), es decir, debe estar del lado izquierdo de la
ecuación, como en el siguiente ejemplo:

``` c
int aux = 3;

array[2] = aux;
array[2] = aux * 3;
array[2] = array[1] + array[0];
array[2] = 0;
```

#### Inicialización

La inicialización es la asignación de un valor a cada uno de los elementos del arreglo antes de ser utilizado en el
resto del programa.
Un ejemplo de inicialización que ya mencionamos es cuando se lo define por enumeración, pero también se lo puede
inicializar mediante un ciclo:

``` c
int array[5];

for (size_t i= 0; i < 5; ++i) {
    array[i] = i; /* o cualquier otra expresión */
}
```

Si un arreglo no es inicializado explícitamente, al igual que con cualquier otra variable, no se puede garantizar su
valor, lo que es particularmente problemático si su primer uso es como RHS.


??? example "Ejemplo: Inicialización con ceros"

    Si quisierámos inicializar un arreglo de 20 elementos con todos sus elementos en cero tenemos 3 alternativas:

    === "por enumeración"

        ``` c
        int array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0,0, 0, 0, 0, 0};
        ```

        Vemos que puede ser tedioso hacerlo así.

    === "por cantidad e iterar"

        ``` c
        int array[20];

        for (size_t i = 0; i < 20; ++i) {
            array[i] = 0;
        }
        ```

        Nos permite modificar el largo del arreglo, pero es demasiado para una simple inicialización en 0.

    === "aprovechando C"

        ``` c
        int array[20] = {0};
        ```

        Esa sentencia indica que se debe crear el arreglo y todos los **bytes** de la memoria de dicha variable debe ser
        inicializada a 0.
        Listo.

#### Arreglos constantes

Hay un caso particular, en que la variable puede ser definida como constante, donde no puede ser un LHS.
La forma de definir un arreglo constante es:

``` c
const int array[5];
```

Nótese el agregado del _keyword_ `const`.
La sentencia anterrior se lee del siguiente modo: `array` es un arreglo de 5 enteros constantes.

Si compilan el siguiente programa:

``` c
--8<-- "apuntes/arreglos/const_array.c"
```

verán el siguiente error:

``` console
$ gcc -std=c17 -Wall -pedantic -o const_array const_array.c
const_array.c: In function ‘main’:
const_array.c:8:14: error: assignment of read-only location ‘array[2]’
    8 |     array[2] = array[0] + array[1];
      |
```

### Arreglos y memoria

El modo de acceso visto antes tiene sentido ya que si el arreglo comienza en la posición de memoria `0xd9598b10`, su
primer elemento comienza en la posición de memoria `0xd9598b10`.
La siguiente tabla muestra las posiciones de memoria de todos los elementos y su forma de acceder:

<figure markdown>
| **Posición** | **Acceso** | **Dirección de memoria** |
| :----------: | :--------- | :----------------------- |
| `0`          | `array[0]` | `0xd9598b10`             |
| `1`          | `array[1]` | `0xd9598b14`             |
| `2`          | `array[2]` | `0xd9598b18`             |
| `3`          | `array[3]` | `0xd9598b1c`             |
| `4`          | `array[4]` | `0xd9598b20`             |
</figure>

!!! tip  "Observación"

    Notar que la posición de memoria del primer elemento es `0xd9598b10` y la del segundo es esa misma dirección **más
    4**, por los 4 bytes que ocupa el entero. La del tercero es la del segundo **más 4**. Y en general, si llamamos `p0`
    a la dirección de memoria del primer elemento, entonces la dirección de memoria del i-ésimo elemento es
    `p0 + i * sizeof(int)` (donde se utilizó el `sizeof(int)` por ser un arreglo de ints).

    Lo que aquí llamamos `p0`, en C es el nombre del arreglo, `array`, por lo que `array[3]` equivale a
    `array + 3 * sizeof(int)`.
    Vamos a ver, más adelante, que el compilador es "inteligente" respecto a estos accesos.


## Arreglos multidimensionales

Como se mencionó al principio, podemos definir arreglos que tengan más de una dimensión.
Un ejemplo típico es el caso del arreglo bidimensional, también llamado matriz.
Este arreglo bidimensional puede ser pensado como un arreglo (unidimensional) de dimensión `r` (cantidad de filas),
donde cada componente del arreglo es otro arreglo (unidimensional) de dimensión `c`  (cantidad de columnas).
Claramente, un arreglo de dos dimensiones como el que mencionamos recién tiene `r * c` componentes.

Del mismo modo que antes, un arreglo de 2 filas y 3 columnas se puede definir por cantidad

``` c
int mat[2][3];
```

o por enumeración

``` c
int matr[2][3] = { {11, 12, 13},
                   {21, 22, 23},};
```

y su inicialización puede ser como en la enumeración de recién, mediante ciclos anidados

``` c
for (size_t fila = 0; fila < 2; ++fila) {
    for (size_t columna = 0; columna < 3; ++columna) {
            matr[i][j] = i * j; /* o cualquier otra expresión */
    }
}
```

o asignado 0 a todos sus **bytes**, como en el ejemplo de inicialización con ceros del arreglo unidimensional.

La siguiente imagen ejemplifica cómo se almacenan esta matriz en memoria:

<figure markdown>
![Definición de matriz en memoria](img3.svg)
</figure>

En dicha imagen, se observa la definición de la matriz `matr` y los 6 enteros que la componen, cada uno de ellos
ocupando 4 bytes.
Podemos ver que, además, primero se encuentran los elementos de la primera fila y luego, a continuación, los elementos
de la segunda fila.
Sin embargo, en forma esquemática, generalmente dibujaremos el arreglo como una cantidad de elementos, y no de bytes, es
decir, dibujaríamos algo similar a la siguiente imagen:

<figure markdown>
![Esquema de una matriz](img4.svg)
</figure>

### Modificación

En una forma análoga al arreglo unidimensional, para acceder a un elemento se usa la expresión `matr[i][j]` donde `i` es
la fila a acceder (recordar que C es 0-_indexing_) y `j` es la columna a acceder.
Esta expresión puede ser un LHS al que se le asigna un valor.
En el siguiente código se inicializa una matriz con valores aleatorios:

``` c hl_lines="10"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int matr[2][3];

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            matr[i][j] = rand();
        }
    }

    return EXIT_SUCCESS;
}
```



### Acceso para lectura

El acceso para lectura sigue las mismas reglas que ya hemos visto, pero agregando un nuevo nivel de acceso mediante otro
par de corchetes y el índice correspondiente.
A modo de ejemplo, el siguiente código imprime por `#!c stdout` el contenido de la matriz:

``` c hl_lines="4 4 6 6"
    printf("int matr[2][3] = {");
    for (size_t i = 0; i < 2; ++i) {
        printf("{");
        printf("%i", matr[i][0]);
        for (size_t j = 1; j < 3; ++j) {
            printf(", %i", matr[i][j]);
        }
        puts("},");
    }
    puts("};");
```

Esta forma de acceder al elemento del arreglo se cumple independientemente de la dimensionalidad del arreglo.
Por ejemplo, definamos una matriz de 4 filas y 4 columnas como

``` c
float matrix[4][3];
```

Luego, podemos pensar que `#!c matrix[0]` nos da acceso a la fila 0, es decir, la primera fila.
Si bien (al menos con lo que hemos visto) no es válida la sentencia `#!c fila = matrix[0];`, podemos pensar que `fila`
es una variable que me permite acceder a una fila **completa**, es decir, es un arreglo pero ahora unidimensional.
Finalmente, para acceder al 3er elemento de la fila, haríamos `#!c fila[2]`.
Y si volvemos sobre nuestros pasos y reemplazamos `fila` por lo que le asignamos, la última expresión es `#!c
matrix[0][2]`.
De este modo podemos construir y acceder a arreglos n-dimensionales, por ejemplo

``` c
float tesseract[5][5][5][5];
/*              i  j  k  l */

cube = tesseract[0]; /* i = 0 */
plane = cube[2];     /* j = 2 */
line = plane[4];     /* k = 4 */
value = line[3];     /* l = 3 */

value =               line[3]; /* line es plane[4], entonces */
value =           plane[4][3]; /* plane es cube[2], entonces */
value =         cube[2][4][3]; /* cube es tesseract[0], entonces */
value = tesseract[0][2][4][3];
```

¿Cómo se tendrían que definir las variables `cube`, `plane`, `line` y `value` para poder ejecutar el código anterior? Lo
veremos más adelante.

### Arreglos multidimensionales y memoria

Volviendo sobre las direcciones de memoria de los datos almacenados, tenemos que recordar que si bien la variable puede
ser una matriz, un cubo, un teseracto, o elementos de mayor dimensión, siempre estamos almacenando variables del tipo
básico, por ejemplo `float`s.
Supongamos un arreglo `double cube[2][2][2]` que comienza en la posición de memoria `0x7ffc83aa4bf0`, entonces su primer
elemento comienza en la posición de memoria `0x7ffc83aa4bf0`.
La siguiente tabla muestra las posiciones de memoria de todos los elementos y su forma de acceder:

<figure markdown>
|   **Acceso**    | **Dirección de memoria** |   **Acceso**    | **Dirección de memoria** |
| :-------------- | :----------------------- | :-------------- | :----------------------- |
| `cube[0][0][0]` | `0x7ffc83aa4bf0`         | `cube[0][1][0]` | `0x7ffc83aa4c00`         |
| `cube[0][0][1]` | `0x7ffc83aa4bf8`         | `cube[0][1][1]` | `0x7ffc83aa4c08`         |
|                 |                          |                 |                          |
| `cube[1][0][0]` | `0x7ffc83aa4c10`         | `cube[1][1][0]` | `0x7ffc83aa4c20`         |
| `cube[1][0][1]` | `0x7ffc83aa4c18`         | `cube[1][1][1]` | `0x7ffc83aa4c28`         |
</figure>

!!! tip  "Observación"

    Notar que la posición de memoria del primer elemento es `0x7ffc83aa4bf0` y la del segundo es esa misma dirección
    **más 8**, por los 8 bytes que ocupa el `#!c double`.
    La del tercero es la del segundo **más 8**.
    Tomemos otro ejemplo, una matriz `double m[2][4]` con elementos en las direcciones

    |   **Acceso**    | **Dirección de memoria** |   **Acceso**    | **Dirección de memoria** |
    | :-------------- | :----------------------- | :-------------- | :----------------------- |
    | `m[0][0]`       | `0x7ffcf4e19580`         | `m[1][0]`       | `0x7ffcf4e195a0`         |
    | `m[0][1]`       | `0x7ffcf4e19588`         | `m[1][1]`       | `0x7ffcf4e195a8`         |
    | `m[0][2]`       | `0x7ffcf4e19590`         | `m[1][2]`       | `0x7ffcf4e195b0`         |
    | `m[0][3]`       | `0x7ffcf4e19598`         | `m[1][3]`       | `0x7ffcf4e195b8`         |

    Para empezar, se cumple lo mismo de antes, la dirección de uno es la del anterior **más 8**.

    Y en general, si llamamos `m` a la dirección de memoria del primer elemento, entonces la dirección de memoria del
    j-ésimo elemento, de la i-ésima fila `#!c m + i * (4 * sizeof(double) + j * sizeof(double)` (donde se utilizó el
    `#!c sizeof(double)` por ser un arreglo de `#!c double`s).
    Entonces, para el arreglo `#!c double m[2][4]`,

    |   **Acceso**    | **Dirección de memoria** |   **Acceso**    | **Dirección de memoria**          |
    | :-------------- | :----------------------- | :-------------- | :-------------------------------- |
    | `m[0][0]`       | `0x7ffcf4e19580`         | `m[i][j]`       | `0x7ffcf4e19580 + i * 32 + j * 8` |

Por otro lado, al ser arreglos estáticos, desde su definición podemos saber cuánto espacio ocupan.
El operador `#!c sizeof` nos puede dar el tamaño en bytes de un arreglo definido **estáticamente**, como se muestra en
el siguiente ejemplo:

``` c linenums="1"
--8<-- "apuntes/arreglos/sizeof.c"
```

que al ser compilado y ejecutado muestra:

``` console
$ gcc -std=c17 -Wall -pedantic sizeof_array.c -o sizeof_array
$ ./sizeof_array
  sizeof char array: 7 bytes
 sizeof short array: 14 bytes
   sizeof int array: 28 bytes
sizeof double array: 56 bytes
```


## Acceso out-of-bounds

El acceso _out-of-bounds_ es un error típico de acceso, sea para lectura o escritura, que se da al utilizar arreglos en
C.
Este lenguaje, a diferencia de otros, **no tiene _out-of-bounds checking_**, es decir, no comprueba que un acceso se
encuentre adentro de los límites definidos para un arreglo.
Por ejemplo, supongamos un arreglo definido como `#!c short array[4];`.
Supongamos, también, que comienza en la dirección 0.
Si comienza en la dirección 0x4 y tiene 4 elementos de tipo `#!c short`, entonces termina en la posición 0xc (no
inclusive), como se muestra en la siguiente figura

<figure markdown>
![](img5.svg)
</figure>

Para dicho arreglo, son válidos los accesos `array[i]` con $0 \leq i \lt 4$.
Acceder a elementos por fuera de nuestro arreglo puede tener distintas consecuencias:

1.  si la posición a la que accedemos le pertenece al programa en ejecución:

    1.  si el acceso era de lectura, se lee información inválida (es un error semántico).
    2.  si el acceso era de escritura, podemos estar sobreescribiendo memoria no utilizada u otra variable, lo que
        producirá un error en el futuro (tal vez no ocurra nada en esta ejecución, ni la siguiente, pero sí en
adelante).

2.  si la posición de memoria no le pertenece al programa en ejecución, el sistema operativo detectará un acceso
    indebido y emitirá la señal (en linux) [`SIGSEGV`](https://en.wikipedia.org/wiki/SIGSEGV) que significa «violación
    del segmento» (o _segmentation violation_).

Un error típico es el _off-by-one error_, es decir, nos pasamos del arreglo por 1 elemento.
Ese elemento suele pertenecer al programa en ejecución por lo que no suele generar el fallo, mientras que accesos a
elementos con `i` mucho mayores suelen hacerlo.
A continuación se muestran programas que ejemplifican este hecho:

=== "_off-by-one_"

    Como el siguiente programa tiene un acceso inválido por un elemento, es **posible** que no falle (aunque podría
    ocurrir que sí):

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/sigsegv_no.c"
    ```

=== "_off-by-many_"

    El siguiente programa está pensando para que falle, sin embargo, puede ser necesario aumentar el valor de la
    constante `WRONG_SIZE` para que lo haga.

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/sigsegv_si.c"
    ```

## Arreglos y funciones

A continuación se dan ejemplos de funciones que operan con arreglos:

=== "zeros"

    Una función que inicializa un vector con 0.

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/zeros.c"
    ```

=== "random"

    Una función que inicializa un vector con valores random en el intervalo $[a, b)$.

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/random.c"
    ```

=== "sum"

    Suma de todos los elementos del vector.

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/sum.c"
    ```

=== "sumar"

    Suma 2 vectores de igual longitud en un tercer vector (de igual o mayor longitud):

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/sumar.c"
    ```

=== "matriz ones"

    Carga unos en una matriz de `r` filas y `c` columnas.
    La matriz debe estar definida como:

    ``` c
    double matriz[200][200];
    ```

    En este caso, se debe cumplir que la cantidad de filas y columnas sea menor a 200, ya que la matriz tiene esos
    valores como máximo (pero podemos utilizar una submatriz).

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/matr_ones.c"
    ```

=== "traza"

    Calcula la traza de una matriz de `r` filas y `r` columnas (la traza está definida para matrices cuadradas).
    La matriz debe estar definida como:

    ``` c
    double matriz[200][200];
    ```

    En este caso, se debe cumplir que la cantidad de filas y columnas sea menor a 200, ya que la matriz tiene esos
    valores como máximo (pero podemos utilizar una submatriz).

    ``` c linenums="1"
    --8<-- "apuntes/arreglos/traza.c"
    ```


## Biblioteca estándar para manejo de arreglos

No hay ninguna biblioteca estándar para la manipulación de arreglos.

## Guías de ejercicios

La guía de ejercicios de arreglos se encuentra [aquí](../../guias/c/arreglos/).
