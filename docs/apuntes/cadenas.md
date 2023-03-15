# Cadenas en C

Las cadenas en C, al igual que en otros lenguajes, son la forma en la que nos manejamos en muchos casos, para
interactuar con el usuario.
Imprimimos cadenas.
Leemos cadenas.
Y, de hecho, un literal de cadena suele ser el primero que se ve en el lenguaje, en el "Hola Mundo!".
Recordando dicho programa, el código fuente es el siguiente:

``` c title="Hola Mundo!" linenums="1"
#include <stdio.h>

int main(void)
{
    puts("Hola Mundo!");

    return 0;
}
```

En ese pequeño pedazo de código, en la línea 5, aparece el literal de cadena `#!c "Hola Mundo!"` pero ¿qué es una
cadena?"

Una cadena de texto, en C, es un arreglo de caracteres **que finaliza con caracter `'\0'`**.
Sin embargo, estos arreglos pueden ser definidos de diferentes maneras:

``` c linenums="1"
char v1[] = "Hola Mundo!";
char v2[] = {'H', 'o', 'l', 'a', ' ', 'M', 'u', 'n', 'd', 'o', '!', '\0'};
char v3[40] = "Hola Mundo!";
char v4[40] = {'H', 'o', 'l', 'a', ' ', 'M', 'u', 'n', 'd', 'o', '!', '\0'};
char *v5 = "Hola Mundo!";
const char v6[] = "Hola Mundo!";
const char v7[] = {'H', 'o', 'l', 'a', ' ', 'M', 'u', 'n', 'd', 'o', '!', '\0'};
const char v8[40] = "Hola Mundo!";
const char v9[40] = {'H', 'o', 'l', 'a', ' ', 'M', 'u', 'n', 'd', 'o', '!', '\0'};
const char *v10 = "Hola Mundo!";
```

Todas estas formas definen la cadena de texto "Hola Mundo!", con la diferencia de que cambia el tamaño del arreglo que
la contiene (y en los casos 5 y 10, cambia el tipo).

Los casos 6 a 10 son los mismos que los casos 1 a 5, pero constantes, por lo que analizaremos los casos 1 a 5.

## Explícito vs Implícito

La diferencia al definir las cadenas en `v1` y `v2` es estética, por decirlo de otro modo, `v1` y `v2` son arreglos de
igual tamaño (12 bytes), pero escritos de diferentes formas (`v2` es difícil de leer, y horrible).
Lo mismo ocurre comparando `v3` con `v4`: son 2 arreglos de 40 chars que en los primeros 12 almacenan la cadena
`#!c "Hola Mundo!"`.

Nótese que tanto `v1` como `v2` tienen el mismo tamaño, 12 bytes, que fue calculado por el compilador a partir de los
datos ingresados.

!!! attention "Importante"

    Pero si en`#!c "Hola Mundo!"` se cuentan 11 caracteres ¿por qué ocupa 12 bytes el arreglo? Por el `'\0'`.
    Al definir `v2` utilizando caracteres, el caracter `'\0'` se escribe explícitamente, pero al escribir el literal de
    cadena usando las comillas dobles (`"`), el `'\0'` se encuentra implícito, se definirse como cadena.

## Largo de una cadena

Sea como sea que se haya ingresado la cadena, estas poseen una priopiedad fácilmente calculable: un largo.
Se dice que una cadena es de largo N si tiene N caracteres **antes del primer `'\0'`**.
Es decir, la cadena `#!c "Hola Mundo!"` tiene largo 11, pero ocupa 12 bytes.
Para calcular el largo de una cadena, se puede utilizar el siguiente código:

``` c title="Cálculo del largo de una cadena" linenums="1"
char input[100] = "Hola Mundo!";
size_t length;

for (length = 0; input[length] != '\0'; ++length) ;

printf("input tiene largo %lu\n", length);
```

El ciclo anterio es un ciclo con un cuerpo vacío.
Es válido utilizar `{}` para indicar un cuerpo vacío en un ciclo, pero se suele indicar con `;` (punto y coma).

## Automático vs Manual

Si comparamos los casos `v1` y `v3` (o `v2` y `v4`) la diferencia que podemos ver es la cantidad de caracteres en el
arreglo.
En `v1`, como se menciona anteriormente, tenemos 12 chars que fueron calculados por el compilados de manera automática, mientras que en `v3` tenemos 40, dado que manualmente ingresamos dicho valor.
No hay otra diferencia y su uso depende del caso. 

## El primer puntero

En el caso `v5` (y `v10`) ya no tenemos un arreglo, sino un puntero.
`v5`, a diferencia de `v1`, `v2`, `v3` y `v4`, no admite que se modifique la cadena.
Esto no tiene que ver con que haya o no haya sido definida como `#!c const`, sino con el lugar en donde se aloja el
arreglo que almacena la cadena.
De `v1` a `v4`, se encuentra almacenado en _stack_ (o en caso de ser variables globales, se almacenan en una región de
memoria particular), mientras que `v5` almacena el arreglo en una región de sólo lectura.

## Ingreso de datos

El motivo más recurrente para el uso de cadenas es la interacción con el usuario.
Hasta el momento, si quisiéramos solicitar el ingreso de algún dato, escribiríamos algo como lo siguiente:

=== "Versión insegura"

    ``` c linenums="1"
    char input[20];
    
    scanf("%s", input);
    printf("%s\n", input);
    ```

=== "El deleite de un hacker"

    ``` c linenums="1"
    char input[20];
    
    scanf("%s", input);
    printf(input);
    ```

    Esta función es doblemente insegura: **NUNCA usar una cadena ingresada por el usuario como formato de printf**.

Sin embargo, esa forma de operar es insegura porque esperamos que el usuario no ingrese más de **19** caracteres
(necesitamos 1 para el `'\0'`, completando los 20).
Pero eso es muy fácil que suceda:

=== "Programa"

    ``` c linenums="1"
    #include <stdio.h>
    #include <stdlib.h>

    int main(void)
    {
        char input[20];

        scanf("%s", input);
        printf("Ingresaste: >>%s<<\n", input);

        return EXIT_SUCCESS;
    }
    ```

=== "Ejecución"

    ``` console
    $ python -c "print('B' * 27)" | ./scanf 
    Ingresaste: >>BBBBBBBBBBBBBBBBBBBBBBBBBBB<<
    *** stack smashing detected ***: terminated
    Aborted (core dumped)
    ```

Como podemos ver, el programa es inseguro porque es fácil hacer que escriba sobre memoria fuera de los límites del
arreglo (recordar el _out-of-bound error_ de [los arreglos](../arrays#acceso-out-of-bounds)).

### Ingreso seguro de datos

Debido, entre otras, a las vulnerabilidades expuestas, para leer cadenas, debemos utilizar la función `fgets`.
Dicha función se encuentra en la `stdio.h` y posee el siguiente prototipo:

```c title="Descripción y prototipo de `fgets`"
/* fgets() reads in at most one less than size characters from stream and stores
 * them into the buffer pointed to by s. Reading stops after an EOF or a newline.
 * If a newline is read, it is stored into the buffer. A terminating null byte
 * ('\0') is stored after the last character in the buffer. */
char *fgets(char *s, int size, FILE *stream);
```

Podemos ver que `fgets()` recibe un arreglo donde almacenar los caracteres que lea, el tamaño del arreglo, y el flujo de
entrada (`stdin` por el momento).
¿Cómo se utiliza `fgets()`? Veamos un ejemplo:

=== "Programa"

    ``` c
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        char input[20];
    
        fgets(input, 20, stdin);
        printf("Ingresaste: >>%s<<\n", input);
    
        return EXIT_SUCCESS;
    }
    ```

=== "Ejecución típica"

    ``` console
    $ python -c "print('usando fgets en C')" | ./fgets 
    Ingresaste: >>usando fgets en C
    <<
    ```

    Vemos que el `'\n'` es leído y almacenado en el arreglo (por eso `<<` aparece en la línea de abajo).

=== "Ejecución sin `'\n'`"

    ``` console
    $ python -c "print('usando fgets en C', end='')" | ./fgets 
    Ingresaste: >>usando fgets en C<<
    ```

=== "Ejecución maliciosa"

    ``` console
    $ python -c "print('B'*9999)" | ./fgets 
    Ingresaste: >>BBBBBBBBBBBBBBBBBBB<<
    ```

    Vemos que sólo se leeyeron 19 `B`s, sin el `'\n'` que ingresó `python`.

¿A dónde fueron a parar los demás caracteres de la ejecución maliciosa? Pues siguen en el buffer si nadie los leyó.

Usando `fgets()`, el valor de retorno de la función nos sirve para validar el ingreso de datos, como cadena.
Según su propia documentación

``` console
fgets() returns s on success, and NULL on error or when end of file occurs while
no characters have been read.
```

Es decir, si `fgets()` lee correctamente, retorna el mismo arreglo que se le pasó, en caso contrario retorna `#!c NULL`.
Entonces, si queremos validar que se haya ingresado **algo**, usaríamos:

``` c
if (NULL == fgets(input, MAX_SIZE, stdin)) {
    fprintf(stderr, "No se ingresó nada\n");
} else {
    printf("Ingresaste: >>%s<<\n", input);
}
```

O bien, si quisiéramos leer hasta agotar la entrada, como en el caso malicioso:

``` c
while (NULL != fgets(input, MAX_SIZE, stdin)) {
    printf("Ingresaste: >>%s<<\n", input);
}
```

!!! tip "¿Qué largo tiene el input?"

    Ahora que saben cómo usar `fgets()`, pueden probar de calcular el largo del mensaje que ingresa el usuario.

### Ingreso de otros tipos

Ahora que sabemos leer cadenas de manera segura, podemos pensar en convertir estos datos a otros tipos.
Dicho de otro modo, siempre leemos cadenas y luego procesamos esa cadena para sacar el dato que queremos.

La manera simple de hacerlo a esta altura, es usando la función `sscanf()` (notar que comienza con 2 s).
Dicha función se encuentra en `stdio.h` y tiene el siguiente prototipo:

``` c title="Prototipo de `sscanf()`"
int sscanf(const char *str, const char *format, ...);
```

Podemos ver que es similar a `scanf()`, sólo que tiene otra cadena antes del formato.
Entonces, la podemos utilizar del siguiente modo:

``` c title="Uso de `sscanf()`" linenums="1"
#include <stdio.h>
#include <stdlib.h>

#define MSG_ERR_INPUT "¡No se ingresó ningún valor!"

static const size_t MAX_SIZE = 100;

int main(void)
{
    char input[MAX_SIZE];
    double value;

    if (NULL == fgets(input, MAX_SIZE, stdin)) {
        fprintf(stderr, "%s\n", MSG_ERR_INPUT);
        return EXIT_FAILURE;
    }

    if (1 == sscanf(input, "%lf", &value)) {
        printf("Ingresaste %f\n", value);
    }

    return EXIT_SUCCESS;
}
```

Sin embargo, existen otras funciones que podemos utilizar para convertir los valores, y se llaman `strtoX()` donde `X`
puede ser `l` para convertir a `long int`, `d` para convertir a `double`, `ul` para convertir a `unsigned long` y, por
ahora, las utilizaremos del siguiente modo (equivalente a utilizar `sscanf()`):

``` c title="Uso de `strtoX()`" linenums="1"
#include <stdio.h>
#include <stdlib.h>

#define MSG_ERR_INPUT "¡No se ingresó ningún valor!"
#define MSG_ERR_TYPES "Esperaba [dlu]valor :("

static const size_t MAX_SIZE = 100;

int main(void)
{
    char input[MAX_SIZE];
    double dvalue;
    long lvalue;
    unsigned long ulvalue;

    if (NULL == fgets(input, MAX_SIZE, stdin)) {
        fprintf(stderr, "%s\n", MSG_ERR_INPUT);
        return EXIT_FAILURE;
    }

    switch (input[0]) {
    case 'd':
        dvalue = strtod(input + 1, NULL);
        printf("Ingresaste %f (double)\n", dvalue);
        break;
    case 'l':
        lvalue = strtol(input + 1, NULL, 10);
        printf("Ingresaste %li (long)\n", lvalue);
        break;
    case 'u':
        ulvalue = strtoul(input + 1, NULL, 10);
        printf("Ingresaste %lu (unsigned long)\n", ulvalue);
        break;
    default:
        fprintf(stderr, "%s\n", MSG_ERR_TYPES);
        return EXIT_FAILURE;
    }        

    return EXIT_SUCCESS;
}
```

!!! attention "No free lunch"

    Nótese que así como está escrito, no estamos validando correctamente si se ingresó el tipo de dato especificado, por
    ejemplo, ingresar `l2930.2939` imprimirá `Ingresaste 2930 (long)`.
    La diferencia con `scanf()` es que `.2939\n` no queda en el buffer de entrada.

## Biblioteca estándar para manejo de cadenas

Existe una biblioteca estándar para el uso de cadenas, `string.h`.
En ella pueden encontrar funciones de comparación de cadenas, para saber si dos cadenas son iguales (`strcmp()`), para
calcular su longitud (`strlen()`), etc.

Pueden ver un listado completo de las funciones en [cppreference](https://en.cppreference.com/w/cpp/header/cstring).
