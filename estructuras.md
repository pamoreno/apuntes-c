# Estructuras

Típicamente, en todo programa no minúsculo, se trabaja con datos que están relacionados entre sí.
Por ejemplo, con puntos en $\mathbb{R}^n$, con figuras geométricas, con usuarios, con sensores, etc.
Hasta ahora, la solución para manipular datos en $\mathbb{R}^2$ sería tener 2 variables que nos sirvan para identificar
$x$ e $y$ (sean 2 `#!c float` o 2 arreglos), para manipular usuarios tendríamos que tener todos los datos importantes
(un identificador, un nombre, un nombre de usuario, y otros que dependerán de la aplicación).
Por ejemplo, pensemos una aplicación que opera con vectores (que inician en el origen): utilizaremos 3 `#!c float` para
almacenar las coordenadas del vector, e implementaremos funciones que suman, restan, multiplican vectores por
constantes, etc.

``` c linenums="1"
/* consideramos un vector desde (0, 0, ), por lo que sólo necesitamos 3 puntos para representarlo */

/* @brief suma 2 vectores y nos devuelve las componentes de la suma en un tercer vector
 * @param outx componente x de un vector de salida
 * @param outy componente y de un vector de salida
 * @param outz componente z de un vector de salida
 * @param in1x componente x de un vector de entrada
 * @param in1y componente y de un vector de entrada
 * @param in1z componente z de un vector de entrada
 * @param in2x componente x de un vector de entrada
 * @param in2y componente y de un vector de entrada
 * @param in2z componente z de un vector de entrada
*/
status_t vector_suma(double *outx, double *outy, *double outz,
                     double in1x, double in1y, double in1z,
                     double in2x, double in2y, double in2z)
{
    if ((NULL == outx) || (NULL == outy) || (NULL == outz)) {
        return ST_ERR_NULL_PTR;
    }

    *outx = in1x + in2x;
    *outy = in1y + in2y;
    *outz = in1z + in2z;

    return ST_OK
}
```

Ya con la función que suma dos vectores vemos que:

1.  la función tiene demasiados parámetros para lo poco que hace,
2.  cada función que trabaje con vectores deberá tener igual cantidad de parámetros.

Sin embargo, veamos cómo se invoca a esta función, y el código relevante para ello:

``` c linenums="1"
...
float x1, y1, z1;
float x2, y2, z2;
float ox, oy, oz;
status_t st;
...
st = vector_suma(&ox, &oy, &oz, x1, y1, z1, x2, y2, z2);
```

Claramente, no es algo cómo para manipular, y por eso tenemos estructuras.

## ¿Qué son las estructuras?

Las estructuras son la herramienta que nos da el lenguaje de programación C para crear tipos compuestos de datos.
De este modo, podemos agregar variables que estén relacionadas en un nuevo tipo de dato, encapsulando la información.
Esto no sólo nos permite manipular las variables en bloque, sino que nos permite asignarle un nombre al conjunto para
hacer referencia a éste de una forma más sencilla, legible y coherente.

La sintaxis para definir una estructura es:

``` c linenums="1" title="Definición de estructuras"
struct <nombre> {
    <tipo de variable> <nombre de variable>;
    ...
    <tipo de variable> <nombre de variable>;
};
```

Una vez que tenemos la estructura definida, podemos declarar una variable según la sintaxis:

``` c linenums="1" title="Declaración de variables usando estructuras"
struct <nombre> variable;
```

Retomando el ejemplo de los vectores, para definir una estructura con las 3 componentes del vector escribiríamos:

``` c linenums="1" title="Ejemplo: estructura vector"
struct vector3 {
    double x;
    double y;
    double z;
} ;
```

obteniendo así un nuevo tipo llamado `struct vector3`.
Al igual que con cualquier variable, para declarar una variable del tipo `struct vector3` escribimos:

``` c linenums="1" title="Ejemplo: declaración de una variable de tipo `struct vector`"
struct vector3 vec1;
```

donde `vec1` es el nombre de la variable.
Reescribamos el prototipo de la función que suma vectores utilizando este nuevo conocimiento:

``` c linenums="1" title="Ejemplo: función que suma vectores (prototipo)"
status_t vector_suma(struct vector3 *out, struct vector3 v1, struct vector3 v2);
```

En este ejemplo vemos, en la definición del puntero, la misma sintaxis que utilizamos para todos los demás punteros que
hemos visto (por ejemplo, `#!c int *`).
Por lo tanto, podemos crear una variable de tipo `struct vector3` y tener un puntero a dicha variable con `struct
vector3 *`.

### Redefinición del nombre

Siempre que utilizamos estructuras trabajamos con nombres que comienzan con `struct`.
Si bien esto es claro y nos recuerda que el dato que utilizamos es una estructura, lo típico es definir un tipo nuevo a
partir de la estructura utilizando `#!c typedef`.
Tal y como vimos en otros casos, la definición del nuevo tipo lleva la sintaxis:

``` c
typedef <viejo tipo> <nuevo tipo>;
```

por lo que podemos definir la estructura como

``` c
typedef struct vector3 vector3_t;
```

Además, cuando se redefine el nombre como en estos casos, es posible definir la estructura y el nuevo nombre en la misma
sentencia, siguiendo la misma convención que antes:

``` c
typedef struct {
    double x;
    double y;
    double z;
} vector3_t;
```

Esto es similar a haber hecho

``` c
struct vector3 {
    double x;
    double y;
    double z;
};
typedef struct vector3 vector3_t;
```

y el prototipo de la función se vuelve más claro también:

``` c linenums="1" title="Ejemplo: función que suma vectores (prototipo)"
status_t vector_suma(vector3_t *out, vector3_t v1, vector3_t v2);
```

??? tip "Convenciones"

    En este caso, utilicé una convensión típica en la que se define un tipo nuevo con sufijo `_t`.
    Otra convensión utiliza camelCase, definiendo el tipo como `Vector3` en lugar de `vector3_t`, es decir:
    
    ``` c
    typedef struct Vector3 Vector3;
    ```
    
    En estos casos, suele utilizarse el camelCase incluso al definir la estructura, con la siguiente notación:
    
    ``` c
    struct Vector3 {
        double x;
        double y;
        double z;
    };
    ```
    
    o bien
    
    ``` c
    typedef struct {
        double x;
        double y;
        double z;
    } Vector3;
    ```

    con lo cual, el prototipo antes visto es

    ``` c linenums="1"
    Status vector_suma(Vector3 *out, Vector3 v1, Vector3 v2);
    ```

## ¿Cuánto espacio, cuánta memoria, ocupa una estructura?

Para comenzar, como tenemos un nuevo tipo, podemos saber en tiempo de compilación cuánto ocupa dicho tipo, la
estructura, utilizando `sizeof`: `#!c sizeof(struct <nombre>)`.
En el caso del ejemplo del vector, tenemos: `#!c sizeof(struct vector3)` o bien `#!c sizeof(vector3_t)`.

Dado que es una composición de elementos, una estructura ocupa **al menos** lo mismo que la suma del almacenamiento de
sus elementos pero, por cuestiones de alineamiento de los datos, puede ocupar más, es decir:

``` c
sizeof(struct vector3) >= 3 * sizeof(double)
```

para el caso del vector.

Ahora, volvamos sobre el prototipo de la función `vector_suma()`:

``` c
status_t vector_suma(struct vector3 *out, struct vector3 v1, struct vector3 v2);
```

Tanto los parámetros `v1` como `v2` se pasan por copia, es decir, toda la información de la estructura debe ser copiada
para pasársela a la función.
Esto es muy ineficiente.
Por eso, las estructuras **siempre** se pasan por puntero, y no únicamente cuando se desea modificarlas.
En este caso, si no se desea modificar la estructura, se pasa a través de un puntero a una estructura constante.
Entonces, el prototipo nos queda:

``` c
status_t vector_suma(struct vector3 *out, const struct vector3 *v1, const struct vector3 *v2);
```

que, por otro lado, es más simple de leer haciendo uso de la definición del tipo `vector3_t`:

``` c
status_t vector_suma(vector3_t *out, const vector3_t *v1, const vector3_t *v2);
```

## Acceso

Hemos visto cómo definir estructuras, pero no cómo acceder a sus miembros.
El operador que debemos utilizar es el `.`, un punto.
De este modo, si definimos las variables

``` c
struct vector3 v1;
vector3_t v2;
```

podemos acceder a sus elementos del siguiente modo:

``` c
v1.x = 3.5;     /* escritura del elemento x de v1 */
v1.y = v2.x;    /* lectura del elemento x de v2 y escritura de y en v1 */
v1.z = v2.z;    /* lectura de z en v2 y escritura de z en v1 */
```

Por otro lado, si en lugar de la estructura tenemos un puntero a la misma, se cumplen las mismas reglas que con todos
los punteros: podemos utilizar el operador de indirección (`*`):

``` c
vector3_t v1;
struct vector3 v2;
struct vector3 *pv1;
vector3_t *pv2;

pv1 = &v1;
pv2 = &v2;

(*pv1).x = 3.5;
(*pv1).y = (*v2).x;
(*pv1).z = (*v2).z;
```

Sin embargo, esta escritura se vuelve engorrosa cuando tenemos múltiples estructuras anidadas, por ejemplo:

``` c linenums="1"
typedef struct empleo {
    char *empresa;
    cargo_t cargo;
    double salario;
} empleo_t;

typedef struct empleado {
    char *nombre;
    char *apellido;
    empleo_t *empleo;
} empleado_t;
...
empleado_t empleado;
empleado_t *puntero = &empleado;
...
puts((*(*puntero).empleo).empresa);
```

por eso se utiliza el operador `->` para acceder a los miembros de una estructura cuando se posee un puntero a la misma.
El mismo ejemplo que antes, pero utilizando el operador `->` se convierte en:

``` c linenums="16"
puts(puntero->empleo->empresa);
```

Vemos que la notación es `<puntero a estructura> -> <miembro>`.
Como aclaración, dependiendo de la fuente que utilice el navegador podemos ver el operador como una flecha, pero en
realidad es un guión `-` y un `>` juntos.
