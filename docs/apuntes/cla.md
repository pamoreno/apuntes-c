# Argumentos en línea de comandos

Cuando ejecutamos un programa, generalmente podemos modificar su comportamiento en tiempo de ejecución mediante
argumentos que se le pasan en la línea de comandos (CLA).
Por ejemplo, al ejecutar el `gcc` podemos indicarle que queremos ver una ayuda en vez de compilar un código fuente.
Para ello, en lugar de ejecutar el programa como hacemos siempre (`gcc -Wall -std=c17 ...`) ejecutamos el comando
pasándole un _flag_, o bandera, de ayuda: `--help`

``` console title="Invocación al gcc con --help"
$ gcc --help
Usage: gcc [options] file...
Options:
  -pass-exit-codes         Exit with highest error code from a phase.
  --help                   Display this information.
  --target-help            Display target specific command line options (including assembler and linker options).
  --help={common|optimizers|params|target|warnings|[^]{joined|separate|undocumented}}[,...].
                           Display specific types of command line options.
...
  -E                       Preprocess only; do not compile, assemble or link.
  -S                       Compile only; do not assemble or link.
  -c                       Compile and assemble, but do not link.
  -o <file>                Place the output into <file>.
  -pie                     Create a dynamically linked position independent
                           executable.
  -shared                  Create a shared library.
  -x <language>            Specify the language of the following input files.
                           Permissible languages include: c c++ assembler none
                           'none' means revert to the default behavior of
                           guessing the language based on the file's extension.

Options starting with -g, -f, -m, -O, -W, or --param are automatically
 passed on to the various sub-processes invoked by gcc.  In order to pass
 other options on to these processes the -W<letter> options must be used.

For bug reporting instructions, please see:
<https://bugs.archlinux.org/>.
```

mientras que si quisiéramos ver únicamente la versión del compilador, lo invocaríamos con `--version`:

``` console title="Invocación al gcc con --version"
$ gcc --version
gcc (GCC) 12.2.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```

Por otro lado, hemos estado invocando al `gcc` utilizando los parámetros `-Wall`, `-std=c17`, `-g`, `-Og`, etc.
Todos estos parámetros modifican el comportamiento del programa, sin necesidad de recompilarlo, y además no requieren de
intervención posterior del usuario.

## Tipos de argumentos

En el `gcc`, todos los argumentos que mostramos se pueden intercambiar, pueden estar en cualquier orden, sin embargo,
hay programas que requieren que los argumentos, o algunos de ellos, aparezcan en posiciones específicas.
Estos argumentos se denominan _posicionales_, porque su interpretación depende de la posición en la que aparecen.
Por ejemplo, podríamos tener un programa para dividir 2 números que se ejecuta del siguiente modo:

``` console
$ ./dividir 9203.23 912.17
```

Para saber si la operación es $9203.23 / 912.17$ o $912.17 / 9203.23$ necesitamos leer la documentación del programa.
Sin embargo, otro programa que realiza la misma operación podría ser invocado del siguiente modo:

``` console
$ ./dividir --numerador 9203.23 --denominador 912.17
```

donde, a priori, resulta claro que la operación es $9203.23 / 912.17$.
Estos argumentos son **no** posicionales, ya que los programas que aceptan la invocación anterior suelen aceptar también
la siguiente invocación:

``` console
$ ./dividir --denominador 912.17 --numerador 9203.23
```

donde hemos intercambiado el orden de los argumentos, pero la operación se entiende que es la misma.

Cómo se hace para que el programa interprete estos argumentos depende del desarrollador.
Lo que todos los sistemas operativos nos brindan es una forma de acceder a esos argumentos.

En resumen, hay 2 tipos de argumentos:

-   posicionales
-   no posicionales

Normalmente se prefieren los argumentos no posicionales para dar flexibilidad al usuario y que éste no deba recordar en
qué orden van, sino cuáles deben ir.

Además, los argumentos pueden tener un identificador, como es el caso de `--numerador`, que indica que el siguiente
argumento es el numerador, o pueden ser identificados por su posición y nada más.
Son extraños los programas que admiten identificadores como `--numerador` y `--denominador`, pero no permiten invertir
su orden, ya que al estar fijas sus posiciones, uno debe recordarlas y podría poner directamente el valor, sin el
identificador.

## Argumentos en línea de comandos

En C, estos argumentos se pasan a la función `main`, como cualquier otro argumento a una función.
Para ello, debemos cambiar el prototipo de la función, del siguiente modo:

``` c title="Función main que recibe argumentos"
int main (int argc, char *argv[])
```

Podemos ver que ahora `main` recibe 2 argumentos: un entero y un arreglo de cadenas.
El sistema operativo carga en `argc` la cantidad de argumentos recibidos, y en `argv` carga los argumentos (utilizando
el espacio para separar cada argumento).
De este modo, si invocamos al `gcc` del siguiente modo

``` console
$ gcc -std=c17 -Wall -pedantic -o mi_programa app.c -lm
```

`argv` y `argc` se cargan como si las variables hubiesen sido definidas de la siguiente forma

``` c
char *argv[] = {"gcc", "-std=c17", "-Wall", "-pedantic", "-o", "mi_programa", "app.c", "-lm", NULL};
int argc = 8;
```

Acá podemos ver algunas propiedades:

1.  El primer argumento que se cargó en el arreglo es el nombre del programa (`gcc`).
    Más adelante veremos que no es el nombre del programa, sino la forma en la que fui invocado.
2.  Todos los argumentos fueron copiados tal y como se los escribió: el carácter `'-'` no es un modificador especial
    para el programa en sí, sino que es el desarrollador quien le da un comportamiento especial.
3.  Los argumentos son cargados en el orden en el que fueron ingresados.
4.  El último elemento de arreglo `argv` es `#!c NULL`.
5.  **Siempre** se cumple que `argv[argc]` es `#!c NULL`.

Para verificar esto, veamos el siguiente ejemplo.

!!! example "Ejemplo: un programa que imprime sus argumentos"

    El siguiente programa recibirá una cantidad indefinida de argumentos en línea de comandos e imprimirá todos ellos
    por `#!c stdout`.

    ``` c linenums="1"
    --8<-- "apuntes/cla/primero.c"
    ```

    Y al ejecutarlo podemos ver lo siguiente:

    ``` console
    $ gcc -Wall -pedantic -std=c17 -o cla primero.c
    $ ./cla
    argv[0] -> "./cla"
    $ ./cla primero segundo tercero 5 123.23 true false -23.12 fhg
    argv[0] -> "./cla"
    argv[1] -> "primero"
    argv[2] -> "segundo"
    argv[3] -> "tercero"
    argv[4] -> "5"
    argv[5] -> "123.23"
    argv[6] -> "true"
    argv[7] -> "false"
    argv[8] -> "-23.12"
    argv[9] -> "fhg"
    $ ./cla "uno y sólo uno"
    argv[0] -> "./cla"
    argv[1] -> "uno y sólo uno"
    $  ../ejemplos/../ejemplos/../ejemplos/cla "mirá argv[0]"
    argv[0] -> "../ejemplos/../ejemplos/../ejemplos/cla"
    argv[1] -> "mirá argv[0]"
    ```

## Procesamiento de los argumentos

Si bien, al programa se busca eficiencia y rendimiento, suele haber una parte de los programas donde esas
características pasan a un segundo plano.
Esta sección es la del procesamiento de los argumentos.
Esto se debe a que es una tarea que debe realizarse una única vez, por lo que no suele ser necesario que este
procesamiento sea el más eficiente (claro está que si el procesamiento realiza tareas complejas, estas deberán ser
optimizadas).

Para avanzar en el procesamiento de los argumentos, implementaremos el programa que divide 2 números, de diferentes
maneras.
Sin embargo, podemos partir del siguiente código:

=== "Código principal"

    ``` c linenums="1" title="Divisor: código base"
    --8<-- "apuntes/cla/divisor.c"
    ```

=== "Auxiliares"

    === "`arg_parser.h`"

        ``` c linenums="1"
        --8<-- "apuntes/cla/arg_parser.h"
        ```

    === "`status.h`"

        ``` c linenums="1"
        --8<-- "apuntes/cla/status.h"
        ```

    === "`status.c`"

        ``` c linenums="1"
        --8<-- "apuntes/cla/status.c"
        ```

### Argumentos posicionales

Comenzamos con el modo más simple de procesamiento de los argumentos.
Aquí indicaremos que el primer argumento del programa es el numerador y el siguiente el denominador.
Para ello, tenemos que implementar la función `parse_arguments` que no está entre los archivos anteriores.

Como `argv[0]` siempre es el programa, nuestros argumentos estarán en `argv[1]` y `argv[2]`.
Para ello, tenemos que asegurarnos que la cantidad de argumentos es la necesaria, y esto lo hacemos mirando el valor de
`argc`.

``` c linenums="1" title="Procesamiento posicional"
--8<-- "apuntes/cla/arg_posicional.c"
```

La función implementada chequea que los argumentos recibidos sean válidos y luego intenta convertir los argumentos
recibidos.
Si las conversiones funcionan correctamente, se almacenan en los argumentos recibidos, modificando las variables de
`main` recibidas por puntero.

El programa podemos compilarlo y ejecutarlo del siguiente modo:

``` console title="Compilación y ejecución"
$ gcc -Wall -pedantic -std=c17 -O3 -o divisor divisor.c arg_posicional.c status.c
$ ./divisor
Failed to parse arguments (ST_ERR_INSUFFICIENT_ARGUMENTS)
$ ./divisor 0
Failed to parse arguments (ST_ERR_INSUFFICIENT_ARGUMENTS)
$ ./divisor 0 1
0
$ ./divisor 99l. 5
Failed to parse arguments (ST_ERR_INVALID_NUMERATOR)
$ ./divisor 99. 5s
Failed to parse arguments (ST_ERR_INVALID_DENOMINATOR)
$ ./divisor 100 2
50
$ ./divisor 100.1 2
50.05
$ ./divisor 100.1 33
3.03333
$ ./divisor 100 33 5 6 5
Failed to parse arguments (ST_ERR_TOO_MANY_ARGUMENTS)
```

### Argumentos no posicionales

Si quisiéramos permitir al usuario ingresar los argumentos en cualquier orden, por ejemplo, indicando los valores
mediante los argumentos `--numerador` y `--denominador`, debemos modificar la función `parse_arguments`.

Para ello, podríamos implementar la función del siguiente modo:

``` c linenums="1" title="Procesamiento no posicional"
--8<-- "apuntes/cla/arg_no_posicional_1.c"
```

En este caso, el primer `for` itera por los argumentos que ingresa el usuario mientras que el segundo `for` itera por
los argumentos válidos, buscando si el ingresado por el usuario es válido y cuál es.
El programa podemos compilarlo y ejecutarlo del siguiente modo:

``` console title="Compilación y ejecución"
$ gcc -Wall -pedantic -std=c17 -O3 -o divisor divisor.c arg_no_posicional_1.c status.c
$ ./divisor 100 33
Failed to parse arguments (ST_ERR_INSUFFICIENT_ARGUMENTS)
$ ./divisor --numerador 100 --denominador 8
12.5
$ ./divisor --denominador 8 --numerador 100
12.5
$ ./divisor --denominador 8 --numerador
Failed to parse arguments (ST_ERR_INSUFFICIENT_ARGUMENTS)
$ ./divisor --denominador 8 --numerador 100 extra
Failed to parse arguments (ST_ERR_TOO_MANY_ARGUMENTS)
$ ./divisor --denominador 8 --numerador 100xxxxxx
Failed to parse arguments (ST_ERR_INVALID_NUMERATOR)
$ ./divisor --numerador 100 --denominador 8xxx
Failed to parse arguments (ST_ERR_INVALID_DENOMINATOR)
$ ./divisor --numerator 100 --denominador 8
Failed to parse arguments (ST_ERR_UNKNOWN_ARGUMENT)
$ ./divisor --numerador 100 --denominator 8
Failed to parse arguments (ST_ERR_UNKNOWN_ARGUMENT)
```

### Argumentos no posicionales (bis)

El ejemplo anterior ya nos sirve para implementar argumentos no posicionales pero ¿qué ocurre si veo que `--numerador`
es demasiado largo y quisiera aceptar `-n`?
La primera opción es modificar el arreglo donde dice `--numerador` por `-n` y _voilà_.
Sin embargo, si es una aplicación "grande", podríamos actualizarla y hacer que dejen de funcionar sistemas que antes
funcionaban (no es retrocompatible).
Para ello, necesitamos aceptar ambos argumentos.

El siguiente código aplica mínimos cambios al anterior para lograr dicho cometido.
Sin embargo, no implica que se la mejor forma de hacerlo (de hecho, hay muchas maneras diferentes de implementarlo).
Una forma típica es utilizando estructuras, tema aún no cubierto :slight_smile:.

``` c linenums="1" title="Procesamiento no posicional"
--8<-- "apuntes/cla/arg_no_posicional_2.c"
```

La resolución propuesta agrega los argumentos necesarios como un par de argumentos adicionales, que no guardan relación
con los anteriores más que porque procesan los mismos datos.
El programa podemos compilarlo y ejecutarlo del siguiente modo:

``` console title="Compilación y ejecución"
$ gcc -Wall -pedantic -std=c17 -O3 -o divisor divisor.c arg_no_posicional_2.c status.c
$ ./divisor 100 33 5 6 5
Failed to parse arguments (ST_ERR_TOO_MANY_ARGUMENTS)
$ ./divisor 100 33
Failed to parse arguments (ST_ERR_INSUFFICIENT_ARGUMENTS)
$ ./divisor --numerador 100 --denominador 8
12.5
$ ./divisor --numerador 100 -d 8
12.5
$ ./divisor -n 100 --denominador 8
12.5
$ ./divisor -n 100 -d 8
12.5
$ ./divisor --denominador 8 --numerador
Failed to parse arguments (ST_ERR_INSUFFICIENT_ARGUMENTS)
$ ./divisor --denominador 8 --numerador 100 extra
Failed to parse arguments (ST_ERR_TOO_MANY_ARGUMENTS)
$ ./divisor --denominador 8 --numerador 100xxxxxx
Failed to parse arguments (ST_ERR_INVALID_NUMERATOR)
$ ./divisor --numerador 100 -d 8xxx
Failed to parse arguments (ST_ERR_INVALID_DENOMINATOR)
$ ./divisor --numerador 100 -D 8
Failed to parse arguments (ST_ERR_UNKNOWN_ARGUMENT)
```

Podemos ver las diferencias entre ambos archivos no posicionales como lo muestra git, en formato diff.

``` diff
diff --git a/arg_no_posicional_1.c b/arg_no_posicional_2.c
index fd33ccf..b17bd94 100644
--- a/arg_no_posicional_1.c
+++ b/arg_no_posicional_2.c
@@ -6,14 +6,18 @@
 #include <string.h>

 typedef enum {
-    ARG_NUMERATOR,
-    ARG_DENOMINATOR,
+    ARG_NUMERATOR_SHORT,
+    ARG_NUMERATOR_LONG,
+    ARG_DENOMINATOR_SHORT,
+    ARG_DENOMINATOR_LONG,
 } arg_t;


 static const char *valid_args[] = {
-    [ARG_NUMERATOR] = "--numerador",
-    [ARG_DENOMINATOR] = "--denominador",
+    [ARG_NUMERATOR_SHORT] = "-n",
+    [ARG_NUMERATOR_LONG] = "--numerador",
+    [ARG_DENOMINATOR_SHORT] = "-d",
+    [ARG_DENOMINATOR_LONG] = "--denominador",
 };


@@ -46,7 +50,8 @@ status_t parse_arguments(int argc, char *argv[], double *num, double *den)
             }
         }
         switch (arg) {
-            case ARG_NUMERATOR:
+            case ARG_NUMERATOR_SHORT:
+            case ARG_NUMERATOR_LONG:
                 i++;
                 _num = strtod(argv[i], &pend);
                 if ('\0' != *pend) {
@@ -54,7 +59,8 @@ status_t parse_arguments(int argc, char *argv[], double *num, double *den)
                 }
                 num_processed = true;
                 break;
-            case ARG_DENOMINATOR:
+            case ARG_DENOMINATOR_SHORT:
+            case ARG_DENOMINATOR_LONG:
                 i++;
                 _den = strtod(argv[i], &pend);
                 if ('\0' != *pend) {
```

## Nota final

Claramente, al procesar argumentos hacemos lo mismo que al procesar cadenas de texto.
A estas cadenas les podemos dar el formato que queramos, es decir, podemos requerir de quien invoca que ingrese el
argumento de la forma que nosotros pedimos.
Las formas clásicas son las vistas en estos ejemplo, en opción corta y opción larga, y agregando a cualquiera de ellas
la posibilidad de separar el argumento de su opción por el carácter `=` en lugar de espacios.
En los ejemplos anteriores, esto implica que el numerador, por ejemplo, podría ser ingresado como `-n=1023`,
`--numerador=182`, `--numerador 2993` o `-n 1.21` (y lo mismo para el denominador).
Además, podríamos considerar que el programa reciba un argumento `--digits N`, que utilizamos para imprimir el resultado
de la división N dígitos decimales.
También podríamos aceptar argumentos por omisión, es decir, donde se le asigna un número en la inicialización y si no es
modificado no es un error, sino que se utiliza aquel por omisión.

Otros argumentos podrían utilizar más de un argumento siguiente, por ejemplo, si quisiéramos implementar un programa que
dada una serie de números nos da su valor medio, y si lo solicitamos, otros momentos, como la varianza.
Distintas formas de invocar dicho programa podrían ser:

``` console
$ ./statistics -n 92.1 2.3 6.4 9.2 492.1 5.09 6.12 --max --min --mean --std
$ ./statistics --max --min -n 92.1 2.3 6.4 9.2 492.1 5.09 6.12 --mean --std
$ ./statistics --max --min --mean --std 92.1 2.3 6.4 9.2 492.1 5.09 6.12
```

En este último ejemplo, `--max`, `--min`, `--mean` y `--std` no toman ningún otro argumento, son banderas que indican si
se solicita un dato o no (y por omisión, no se lo pide), y `-n` toma todos los demás argumentos hasta el siguiente
argumento válido, o hasta el final.

## Biblioteca estándar para manejo de argumentos

No hay ninguna biblioteca estándar para la manipulación de argumentos.

## Guías de ejercicios

La guía de ejercicios de argumentos en línea de comandos se encuentra [aquí](../../guias/c/cla/).
