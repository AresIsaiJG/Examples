# Bit-Field, uniones y estructuras: Explicación
## Recordatorio de estructuras

Una estructura es una zona de memoria continua que puede reservar variables de diferentes tipos de datos, como se muestra a continuación:

```c
struct EstructuraBasica
{
  uint8_t A;
  uint16_t B;
  uint32_t C;
  bool D;
  uint64_t E;
  char F[5];
  float G;
  struct Estructura_Interna;

};
```

La estructura nos indica que se deben reservar 11 localidades de memoria continúa con una palabra de 64 bits, como mínimo, para almacenar todas las variables definidas
(por ser un ejemplo, no se sabe la cantidad de localidades de memoria a reservar para la estructura).

## Explicación básica de bit-field

Ahora bien, un bit-field es, literalmente, un campo o un intervalo de bits, como su traducción del inglés lo indica.
Generalmente los nuevos campos de bits son reservados en una misma localidad de memoria, siempre y cuando se respete la longitud de bits definidos con los campos que se van declarando.
Esto quiere decir que para una variable "x", ahora se pueden fraccionar sus bits, a fin de optimizar el uso de memoria. 


Cómo muestra de estó, se tiene el siguiente ejemplo:

```c
/**
* Reutilizando la variable uint8_t A.
*/
struct BitField_A
{
  uint8_t A_UnBit : 1; //Se reserva un bit de los 8 que se declaran para A, en este caso el menos significativo (bit 0).
  uint8_t A_DosBit : 2; //Se reservan dos bits de los 7 que sobran en A, en este caso del bit 1 al 2 (bit 1:2).
  uint8_t A_CincoBit : 5; //Se reservan los bits sobran en A, en este caso del bit 3 al 7 (bit 3:7).

};
```
Con esto en mente, la estructura **BitField_A** simplemente contiene una variable "A" de tipo *uint8_t* (nos interesa resaltar que son ***8 bits*** los reservados en la estructura), es decir, en la nueva estructura reservamos una sola variable de 8 bits, para los cuales definimos una cantidad específica de bits con cada nueva variable, a través de **" : x_NúmerodeBits"**. 

### Puntos importantes a destacar:

- Los " : " sirven para indicar que se hará uso de una *n* cantidad de bits.  
- El uso de bit-field solo se implementa con ***estructuras***, debido a la reserva de memoria continua.
- El bit-Field permite ahorrar recursos, ya que hace más eficiente el uso de memoria.
- Siempre se debe respetar la relación entre el tipo de dato y la cantidad de bits que se ocupan.
- Por lo regular se ocupa con tipos de dato *int*, *uint*, *char*.

### Ejemplo de uso

Vamos a suponer que se quiere optimizar el uso de memoria en la siguiente estructura:

```c
struct Ejemplo_EstructuraBitField
{
  uint8_t A; //Una localidad reservada para ocupar 8 bits
  uint16_t B; //Una localidad reservada para ocupar 16 bits
  uint32_t C; //Una localidad reservada para ocupar 32 bits
  bool D; //Una localidad reservada para ocupar 1 bit

};
```
En total son 4 localidades reservadas; sin embargo, no todos los bits de todas las variables se utilizan, de modo que *B* solo ocupa 5 bits y *C* ocupa 16 bits.
En otras palabras, necesitamos 30 bits en total.
Bajo esta idea, podemos utiliziar bit-field para optimizar el uso de localidades, como se muestra a continuación.

```c
struct Ejemplo_EstructuraBitField
{
  uint32_t A : 8; //Se reserva del bit 0 al 7 (bit 0:7).
  uint32_t B : 5; //Se reserva del bit 8 al 12 (bit 8:12).
  uint32_t C : 16; //Se reserva del bit 13 al 29 (bit 13:29).
  uint32_t D : 1; //Solo se usa el bit 30 (bit 30).

};
```
Con la estructura Ejemplo logramos reducir de 4 a 1 las localidades de memoria utilizadas; además, se redujo el uso de bits que algunas variables no ocupaban.
De este modo, ahora podemos definir en EstructuraBasica:

```c
struct EstructuraBasica
{
  struct Ejemplo_EstructuraBitField Nueva_BitField; //Contiene las variables A - D
  uint64_t E;
  char F[5];
  float G;
  struct Estructura_Interna;

};
```

## Recordatorio de uniones
Una unión permite declarar dos o más tipos de dato bajo una misma localidad de memoria, en donde la variable con el tipo de dato más grande es la que da la pauta de la cantidad de memoria a reservar.

### Ejemplo de uso

Supongamos que queremos utilizar dos variables en una misma localidad: A (tipo uint8_t) y B (tipo uint32_t).
La unión nos permite realizar esto cómo se muestra a continuación:

```c
union Ejemplo
{
    uint32_t B; // 32 bits
    uint8_t A;  // 8 bits (ocupa el byte menos significativo de B)

};
```
Entonces, bajo está idea, podemos utilizarla a través de:

```c
//Código anterior
  union Ejemplo Union1; //Declaramos la unión
  
  Union1.B = 0; // Pone todos los bits a 0: B = 0x00000000
  Union1.A = 0xF1; // Modifica solo el byte menos significativo de B: B = 0x000000F1
  Union1.B = 0xAF8; // Sobrescribe completamente los 32 bits: B = 0x00000AF8
//Código posterior
```

Al final B fue sobreescrito con el último valor.