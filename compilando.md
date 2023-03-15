# Compilando con el GCC[^1]

[^1]: basado en el documento escrito por Sebastián Santisi y Patricio Moreno ([aquí](../compilacion-con-gcc.pdf)).

## Introducción

Este es un instructivo, a modo informativo, para poder compilar con el `gcc`.
En este documento se muestra lo básico sobre el proceso de compilación.
Para más información, se recomienda leer la documentación del gcc, ya sea en la
[web](https://man.archlinux.org/man/gcc.1.en) o utilizando el comando `man gcc` en una terminal de linux o mac.

## Compilando

El programa que nos sirve para compilar se llama `gcc`.
Supongamos que queremos compilar el código fuente `prueba.c` y que el mismo se encuentra en el directorio
`/home/user/src/prueba.c`.
Lo compilaremos de la siguiente manera (es importante recordar que `gcc` es una aplicación desarrollada para ser
ejecutada en una terminal y, como todas las herramientas de los sistemas unix, distingue entre mayúsculas y minúsculas
en los argumentos):

``` shell
user@localhost ~/src$ gcc -o prueba prueba.c -Wall -pedantic -std=c17 -lm
```

Esto compila el código fuente `prueba.c` creando el ejecutable `prueba` (el cual puede ser ejecutado en la terminal
mediante el comando `./prueba`).
Ahora bien ¿qué significa cada parámetro?

| **Parámetro** | **Comprensión** | **Descripción** |
| ------------: | :-------------: | :-------------- |
| `-o` | _output_ | Indica que **el siguiente** argumento será el nombre con el cual queremos que se compile nuestro programa. |
| `-Wall` | _warning all_ | Indica que queremos que el compilador nos muestre todas las advertencias que considere necesarias respecto al código fuente. |
| `-std=c17` | _standard_ | Indica que queremos que compile según el estándar ISO C17. |
| `-pedantic` | _pedante_ | Indica que queremos que el compilador sea más estricto en cuanto al seguimiento del estándar y el uso de _features_ o extensiones del compilador. Por ejemplo, el estándar C89 no admite comentarios con `//`, pero los compiladores normalmente sí, es un _feature_ o extensión del compilador. Este parámetro sirve para advertirnos si estamos haciendo uso de estas extensiones. |
| `-lm` | _math_ | Indica que queremos enlazar contra la biblioteca matemática, sino no se realiza dicho enlazado y funciones como `pow` no se encontrarán. |

Estos argumentos que se han presentado alcanzan para comenzar a utilizar el compilador.
Otros argumentos que acepta el compilador son

-   `-x c`: Obliga al compilador a compilar nuestro código fuente como si fuera C. GCC compila muchos otros lenguajes y
    se vale de la extensión para saber qué tipo de compilación hacer. `.C` es la extensión que reconoce como C.
-   `-O0`: nivel de optimizaciones 0. No realiza optimizaciones.
-   `-O1`: aplica optimizaciones al código generado para reducir el espacio y mejorar la velocidad de ejecución del
    programa.
-   `-Og`: similar a `O1` pero intenta mantener el código generado similar a lo que se escribió como código C.
-   `-O2`: similar a `O1` pero con un nivel de optimización más agresivo.
-   `-O3`: similar a `O2` pero aún más agresivo, incluso provocando que el código generado (el binario) no respete el
    estándar.
-   `-Os`: optimiza la compilación para que el ejecutable ocupe menos espacio.
-   `-Ofast': optimiza la compilación para que el binario disminuya su tiempo de ejecución.
-   `-E`: solamente preprocesa el código, parando en antes de realizar la compilación.
-   `-S`: solamente genera el código assembly.
-   `-c`: detiene la compilación luego de generar el código objeto, no enlaza.
-   `-g`: compila el programa agregando información para facilitar el debugging del binario.
-   `--help`: da una pequeña ayuda mostrando algunos de los argumentos que admite el programa.
