# Bit-Field y estructuras: Explicación
## Recordatorio de estructuras

Una estructura es una zona de memoria continua que puede reservar variables de diferentes tipos de datos, como se muestra a continuación:

```c
struct Ejemplo_Estructura
{
  uint8_t A;
  uint16_t B;
  uint32_t C;
  uint64_t D;
  char E[5];
  float F;
  bool G;
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

## Puntos importantes a destacar:

- Los " : " sirven para indicar que se hará uso de una *n* cantidad de bits.  
- El uso de bit-field solo se implementa con ***estructuras***, debido a la reserva de memoria continua.
- El bit-Field permite ahorrar recursos, ya que hace más eficiente el uso de memoria.
- Siempre se debe respetar la relación entre el tipo de dato y la cantidad de bits que se ocupan.
- Por lo regular se ocupa con tipos de dato *int*, *uint*, *char*.

## Ejemplo de uso

Vamos a suponer que se quiere optimizar el uso de memoria en la siguiente estructura:

```c
struct Ejemplo_Estructura
{
  bool A; //Una localidad reservada para ocupar 1 bit
  uint8_t B; //Una localidad reservada para ocupar 8 bits
  uint16_t C; //Una localidad reservada para ocupar 16 bits
  uint32_t D; //Una localidad reservada para ocupar 32 bits

};
```
En total son 4 localidades reservadas; sin embargo, no todos los bits de todas las variables se utilizan, de modo que *C* solo ocupa 5 bits y *D* ocupa 16 bits.
En otras palabras, necesitamos 30 bits en total.
Bajo esta idea, podemos utiliziar bit-field para optimizar el uso de localidades, como se muestra a continuación.

```c
struct Ejemplo
{
  uint32_t A : 1; //Solo se usa el bit menos significativo (bit 0).
  uint32_t B : 8; //Se reserva del bit 1 al 8 (bit 1:8).
  uint32_t C : 5; //Se reserva del bit 9 al 13 (bit 9:13).
  uint32_t D : 16; //Se reserva del bit 1 al 8 (bit 14:30).

};
```
Con la estructura Ejemplo logramos reducir de 4 a 1 las localidades de memoria utilizadas; además, se redujo el uso de bits que algunas variables no ocupaban.
