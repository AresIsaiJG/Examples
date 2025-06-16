# Bit-Field y estructuras: Explicación
Una estructura es una zona de memoria continua que puede reservar varias variables de diferentes tipos de datos, como se muestra a continuación:

```c
struct Ejemplo_Estructura
{
  uint8_t A;
  uint16_t B;
  uint32_t c;
  uint64_t D;
  char E[5];
  float F;
  bool G;
  struct Estructura_Interna;
};
```

```c
 /**
  * Example of use.
*/
 typedef struct
 {
     _IOb            Bit0:1;            /**< Bit 0 from Register */
     ReserBitField   NotUsed1:31;       /**< Bit 1:31 from Register */
 
 }REGx_1BitInputOutputStructBitField;
```
* It demonstrates the use of unions to access a record by bit field or by accessing the entire register. 
```c
 /**
  * Example of use.
*/
 typedef union
 {
     REGx_1BitInputOutputStructBitField      RegBits;        /**< Write-Read in one bit of the register. Used 0-0 bits */
     _IO                                     RegComplete;    /**< Write-Read in all the register */
 
 }REGx_1BitInputOutputUnion;
```
* It demonstrates the use of structures to declare multiple register and how to access them.
```c
 /**
  * Structure used to define GPIO Registers.
*/
 typedef struct
 {
     ReserMemoLoca                  Mem0[255];  /**< Reserved from 0x3F8 - 0x000 */
     REGx_8BitsInputOutputUnion     DATA;       /**< Offset: 0x3FC */
     REGx_8BitsInputOutputUnion     DIR;        /**< Offset: 0x400 */
     REGx_8BitsInputOutputUnion     IS;         /**< Offset: 0x404 */
     REGx_8BitsInputOutputUnion     IBE;        /**< Offset: 0x408 */
     REGx_8BitsInputOutputUnion     IEV;        /**< Offset: 0x40C */
     REGx_9BitsInputOutputUnion     IM;         /**< Offset: 0x410 */
     REGx_9BitsInputOutputUnion     RIS;        /**< Offset: 0x414 */
     REGx_9BitsInputOutputUnion     MIS;        /**< Offset: 0x418 */
     REGx_9BitsInputOutputUnion     ICR;        /**< Offset: 0x41C */
     REGx_8BitsInputOutputUnion     AFSEL;      /**< Offset: 0x420 */
     ReserMemoLoca                  Mem1[55];   /**< Reserved from 0x4FC - 0x424 */
     REGx_8BitsInputOutputUnion     DR2R;       /**< Offset: 0x500 */
     REGx_8BitsInputOutputUnion     DR4R;       /**< Offset: 0x504 */
     REGx_8BitsInputOutputUnion     DR8R;       /**< Offset: 0x508 */
     REGx_8BitsInputOutputUnion     ODR;        /**< Offset: 0x50C */
     REGx_8BitsInputOutputUnion     PUR;        /**< Offset: 0x510 */
     REGx_8BitsInputOutputUnion     PDR;        /**< Offset: 0x514 */
     REGx_8BitsInputOutputUnion     SLR;        /**< Offset: 0x518 */
     REGx_8BitsInputOutputUnion     DEN;        /**< Offset: 0x51C */
     _IO                            LOCK;       /**< Offset: 0x520 */
     REGx_8BitsInputOutputUnion     CR;         /**< Offset: 0x524 */
     REGx_8BitsInputOutputUnion     AMSEL;      /**< Offset: 0x528 */
     REGx_4FieldInputOutputUnion    PCTL;       /**< Offset: 0x52C */
     REGx_8BitsInputOutputUnion     ADCCTL;     /**< Offset: 0x530 */
     REGx_8BitsInputOutputUnion     DMACTL;     /**< Offset: 0x534 */
     REGx_1BitInputOutputUnion      SI;         /**< Offset: 0x538 */
     REGx_8BitsInputOutputUnion     DR12R;      /**< Offset: 0x53C */
     REGx_4BitsWakeGpioIOUnion      WAKEPEN;    /**< Offset: 0x540 */
     REGx_4BitsWakeGpioIOUnion      WAKELVL;    /**< Offset: 0x544 */
     REGx_4BitsWakeGpioIUnion       WAKESTAT;   /**< Offset: 0x548 */
     ReserMemoLoca                  Mem2[669];  /**< Reserved from 0xFBC - 0x54C */
     REGx_1BitPpGpioUnion           PP;         /**< Offset: 0xFC0 */
     REGx_2FieldPcGpioUnion         PC;         /**< Offset: 0xFC4 */
     ReserMemoLoca                  Mem3[2];    /**< Reserved from 0xFCC - 0xFC8 */
     REGx_8BitsInputOnlyUnion       PeriphID4;  /**< Offset: 0xFD0 */
     REGx_8BitsInputOnlyUnion       PeriphID5;  /**< Offset: 0xFD4 */
     REGx_8BitsInputOnlyUnion       PeriphID6;  /**< Offset: 0xFD8 */
     REGx_8BitsInputOnlyUnion       PeriphID7;  /**< Offset: 0xFDC */
     REGx_8BitsInputOnlyUnion       PeriphID0;  /**< Offset: 0xFE0 */
     REGx_8BitsInputOnlyUnion       PeriphID1;  /**< Offset: 0xFE4 */
     REGx_8BitsInputOnlyUnion       PeriphID2;  /**< Offset: 0xFE8 */
     REGx_8BitsInputOnlyUnion       PeriphID3;  /**< Offset: 0xFEC */
     REGx_8BitsInputOnlyUnion       PCellID0;   /**< Offset: 0xFF0 */
     REGx_8BitsInputOnlyUnion       PCellID1;   /**< Offset: 0xFF4 */
     REGx_8BitsInputOnlyUnion       PCellID2;   /**< Offset: 0xFF8 */
     REGx_8BitsInputOnlyUnion       PCellID3;   /**< Offset: 0xFFC */
 
 }GPIOx_TypeDef;
```

In the use's example, I enable two leds to show their correct operation.