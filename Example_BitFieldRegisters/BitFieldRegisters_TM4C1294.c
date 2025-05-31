/**
 ******************************************************************************
 * @Title           :   Standard for C Programing
 * @Filename        :   main.c
 * @Author(s)       :   Isai J. Garcia
 * @Origin Date     :   01/02/2025
 * @Version         :   1.0.0
 * @Compiler        :   GCC
 * @Target          :   TM4C1294NCPDT
 * @Notes           :   This software was design as a example of use of unions,
 *                      Bit-Field and structures in registers
 *
 ******************************************************************************
 * @brief
 * Table with some comments on each version
 * --- Version ---     Date     ---                   Comments              ---
 * ---  1.0.0  ---  12/02/2025  --- Create file. Generate structures,       ---
 * ---         ---              --- unions for GPIO Registers distribution. ---
 * ---         ---              ---                                         ---
 * ---  1.0.1  ---  31/05/2025  --- Finished the commentaries.              ---
 * ---         ---              ---                                         ---
 * ---  1.x.x  ---  dd/mm/aaaa  --- Comment example                         ---
 * ---         ---              ---                                         ---
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025.
 * All rights reserved.
 *
 * This software is for student use and for research purposes only. It must not
 * be used for commercial purposes or to obtain any benefit of any kind. It can
 * only be modified by the developers.
 *
 ******************************************************************************
 */

 /**
 * Type Definitions Used to define Bit's Registers and Complete Registers in a structure
 * */
 typedef volatile const unsigned int     _Ib;            /**< Input-Only Definition of bit(s) */
 typedef volatile unsigned int           _IOb;           /**< Input-Output Definition of bit(s) */
 typedef volatile unsigned int           _Ob;            /**< Output-Only Definition of bit(s) */
 typedef const unsigned int              ReserBitField;  /**< Used to declare Bits that must not be used on a Register */
 
 typedef volatile const unsigned int     _I;             /**< Input-Only Definition of Complete Register */
 typedef volatile unsigned int           _IO;            /**< Input-Output Definition of Complete Register */
 typedef volatile unsigned int           _O;             /**< Output-Only Definition of Complete Register */
 typedef const unsigned int              ReserMemoLoca;  /**< Used to declare a Memory Location that must not be used */
 
 /**
  * Enumerations used to Define Base Directions of the Peripherals
  * */
 typedef enum
 {
     SYSCTL_BASE = 0x400FE000       /**< System Control Base Direction */
 
 }SYSCTLx_MemoryDirection;
 
 typedef enum
 {
     GPIOA_BASE  =   0x40058000,    /**< GPIOA Base Direction */
     GPIOB_BASE  =   0x40059000,    /**< GPIOB Base Direction */
     GPIOC_BASE  =   0x4005A000,    /**< GPIOC Base Direction */
     GPIOD_BASE  =   0x4005B000,    /**< GPIOD Base Direction */
 
     GPIOE_BASE  =   0x4005C000,    /**< GPIOE Base Direction */
     GPIOF_BASE  =   0x4005D000,    /**< GPIOF Base Direction */
     GPIOG_BASE  =   0x4005E000,    /**< GPIOG Base Direction */
     GPIOH_BASE  =   0x4005F000,    /**< GPIOH Base Direction */
 
     GPIOJ_BASE  =   0x40060000,    /**< GPIOJ Base Direction */
     GPIOK_BASE  =   0x40061000,    /**< GPIOK Base Direction */
     GPIOL_BASE  =   0x40062000,    /**< GPIOL Base Direction */
     GPIOM_BASE  =   0x40063000,    /**< GPIOM Base Direction */
 
     GPION_BASE  =   0x40064000,    /**< GPION Base Direction */
     GPIOP_BASE  =   0x40065000,    /**< GPIOP Base Direction */
     GPIOQ_BASE  =   0x40066000     /**< GPIOQ Base Direction */
 
 }GPIOx_MemoryDirection;
 
 /**
  * Structures used on Registers of 8, 9,.. bits with Bit Field.
  * Input Output Direction
  * */
 typedef struct
 {
     _IOb            Bit0:1;            /**< Bit 0 from Register */
     ReserBitField   NotUsed1:31;       /**< Bit 1:31 from Register */
 
 }REGx_1BitInputOutputStructBitField;
 
 typedef struct
 {
     _IOb            Bit0:1;            /**< Bit 0 from Register */
     _IOb            Bit1:1;            /**< Bit 1 from Register */
     _IOb            Bit2:1;            /**< Bit 2 from Register */
     _IOb            Bit3:1;            /**< Bit 3 from Register */
     _IOb            Bit4:1;            /**< Bit 4 from Register */
     _IOb            Bit5:1;            /**< Bit 5 from Register */
     _IOb            Bit6:1;            /**< Bit 6 from Register */
     _IOb            Bit7:1;            /**< Bit 7 from Register */
     ReserBitField   NotUsed1:24;       /**< Bit 8:31 from Register */
 
 }REGx_8BitsInputOutputStructBitField;
 
 typedef struct
 {
     _IOb            Bit0:1;            /**< Bit 0 from Register */
     _IOb            Bit1:1;            /**< Bit 1 from Register */
     _IOb            Bit2:1;            /**< Bit 2 from Register */
     _IOb            Bit3:1;            /**< Bit 3 from Register */
     _IOb            Bit4:1;            /**< Bit 4 from Register */
     _IOb            Bit5:1;            /**< Bit 5 from Register */
     _IOb            Bit6:1;            /**< Bit 6 from Register */
     _IOb            Bit7:1;            /**< Bit 7 from Register */
     _IOb            Bit8:1;            /**< Bit 8 from Register */
     ReserBitField   NotUsed1:23;       /**< Bit 9:31 from Register */
 
 }REGx_9BitsInputOutputStructBitField;
 
 typedef struct
 {
     _IOb            Field0:2;          /**< Field 0:1 from Register */
     _IOb            Field1:2;          /**< Field 2:3 from Register */
     _IOb            Field2:2;          /**< Field 4:5 from Register */
     _IOb            Field3:2;          /**< Field 6:7 from Register */
     _IOb            Field4:2;          /**< Field 8:9 from Register */
     _IOb            Field5:2;          /**< Field 10:11 from Register */
     _IOb            Field6:2;          /**< Field 12:13 from Register */
     _IOb            Field7:2;          /**< Field 14:15 from Register */
     _IOb            Field8:2;          /**< Field 16:17 from Register */
     _IOb            Field9:2;          /**< Field 18:19 from Register */
     _IOb            Field10:2;         /**< Field 20:21 from Register */
     _IOb            Field11:2;         /**< Field 22:23 from Register */
     _IOb            Field12:2;         /**< Field 24:25 from Register */
     _IOb            Field13:2;         /**< Field 26:27 from Register */
     _IOb            Field14:2;         /**< Field 28:29 from Register */
     _IOb            Field15:2;         /**< Field 30:31 from Register */
 }REGx_2FieldInputOutputStructBitField;
 
 typedef struct
 {
     _IOb            Field0:4;          /**< Field 0:3 from Register */
     _IOb            Field1:4;          /**< Field 4:7 from Register */
     _IOb            Field2:4;          /**< Field 8:11 from Register */
     _IOb            Field3:4;          /**< Field 12:15 from Register */
     _IOb            Field4:4;          /**< Field 16:19 from Register */
     _IOb            Field5:4;          /**< Field 20:23 from Register */
     _IOb            Field6:4;          /**< Field 24:27 from Register */
     _IOb            Field7:4;          /**< Field 28:31 from Register */
 
 }REGx_4FieldInputOutputStructBitField;
 
/**
* Structures used on Registers of 8, 9,.. bits with Bit Field. Input Only Direction
* */
 typedef struct
 {
     _Ib            Bit0:1;             /**< Bit 0 from Register */
     ReserBitField  NotUsed1:31;        /**< Bit 1:31 from Register */
 
 }REGx_1BitPpGpioStructBitField;
 
 typedef struct
 {
     _Ib            Bit0:1;             /**< Bit 0 from Register */
     _Ib            Bit1:1;             /**< Bit 1 from Register */
     _Ib            Bit2:1;             /**< Bit 2 from Register */
     _Ib            Bit3:1;             /**< Bit 3 from Register */
     _Ib            Bit4:1;             /**< Bit 4 from Register */
     _Ib            Bit5:1;             /**< Bit 5 from Register */
     _Ib            Bit6:1;             /**< Bit 6 from Register */
     _Ib            Bit7:1;             /**< Bit 7 from Register */
     ReserBitField  NotUsed1:24;        /**< Bit 8:31 from Register */
 
 }REGx_8BitsInputOnlyStructBitField;
 
 /**
  * Special Structures used on Registers of different bits with Bit Field.
  * */
 typedef struct
 {
     _IOb            Field0:2;          /**< Field 0:1 from Register */
     _IOb            Field1:2;          /**< Field 2:3 from Register */
     _IOb            Field2:2;          /**< Field 4:5 from Register */
     _IOb            Field3:2;          /**< Field 6:7 from Register */
     _IOb            Field4:2;          /**< Field 8:9 from Register */
     _IOb            Field5:2;          /**< Field 10:11 from Register */
     _IOb            Field6:2;          /**< Field 12:13 from Register */
     _IOb            Field7:2;          /**< Field 14:15 from Register */
     ReserBitField   NotUsed1:16;       /**< Bit 16:31 from Register */

 }REGx_2FieldPcGpioStructBitField;
 
 typedef struct
 {
     ReserBitField   NotUsed1:4;        /**< Bit 0:3 from Register */
     _Ib             Bit4:1;            /**< Bit 4 from Register */
     _Ib             Bit5:1;            /**< Bit 5 from Register */
     _Ib             Bit6:1;            /**< Bit 6 from Register */
     _Ib             Bit7:1;            /**< Bit 7 from Register */
     ReserBitField   NotUsed2:24;       /**< Bit 8:31 from Register */
 
 }REGx_4BitsWakeGpioIStructBitField;
 
 typedef struct
 {
     ReserBitField   NotUsed1:4;        /**< Bit 0:3 from Register */
     _IOb            Bit4:1;            /**< Bit 4 from Register */
     _IOb            Bit5:1;            /**< Bit 5 from Register */
     _IOb            Bit6:1;            /**< Bit 6 from Register */
     _IOb            Bit7:1;            /**< Bit 7 from Register */
     ReserBitField   NotUsed2:24;       /**< Bit 8:31 from Register */
 
 }REGx_4BitsWakeGpioIOStructBitField;
 
 /**
  * Unions used on Input Output Registers definitions.
  * */
 typedef union
 {
     REGx_1BitInputOutputStructBitField      RegBits;        /**< Write-Read in one bit of the register. Used 0-0 bits */
     _IO                                     RegComplete;    /**< Write-Read in all the register */
 
 }REGx_1BitInputOutputUnion;
 
 typedef union
 {
     REGx_8BitsInputOutputStructBitField     RegBits;        /**< Write-Read in one bit of the register. Used 0-7 bits */
     _IO                                     RegComplete;    /**< Write-Read in all the register */
 
 }REGx_8BitsInputOutputUnion;
 
 typedef union
 {
     REGx_9BitsInputOutputStructBitField     RegBits;        /**< Write-Read in one bit of the register. Used 0-8 bits */
     _IO                                     RegComplete;    /**< Write-Read in all the register */
 
 }REGx_9BitsInputOutputUnion;
 
 typedef union
 {
     REGx_2FieldInputOutputStructBitField    RegBits;        /**< Write-Read in a 4 Bit Field of the register. Used 0-31 bits */
     _IO                                     RegComplete;    /**< Write-Read in all the register */
 
 }REGx_2FieldInputOutputUnion;
 
 typedef union
 {
     REGx_4FieldInputOutputStructBitField    RegBits;        /**< Write-Read in a 4 Bit Field of the register. Used 0-31 bits */
     _IO                                     RegComplete;    /**< Write-Read in all the register */
 
 }REGx_4FieldInputOutputUnion;
 
 /**
  * Unions used on Input Output Registers definitions.
  * */
 typedef union
 {
     REGx_1BitPpGpioStructBitField       RegBits;        /**< Read-Only in one bit of the register. Used 0-0 bits */
     _I                                  RegComplete;    /**< Read-Only in all the register */
 
 }REGx_1BitPpGpioUnion;
 
 typedef union
 {
     REGx_8BitsInputOnlyStructBitField   RegBits;        /**< Read-Only in one bit of the register. Used 0-7 bits */
     _I                                  RegComplete;    /**< Read-Only in all the register */
 
 }REGx_8BitsInputOnlyUnion;
 
 /**
  * Special Unions used on Registers of not equal bits with Bit Field.
  * */
 typedef union
 {
     REGx_2FieldPcGpioStructBitField     RegBits;        /**< Write-Read in a 2 Bit Field of the register. Used 0-31 bits */
     _IO                                 RegComplete;    /**< Write-Read in all the register */
 
 }REGx_2FieldPcGpioUnion;
 
 typedef union
 {
     REGx_4BitsWakeGpioIStructBitField   RegBits;        /**< Write-Read in one bit of the register. Used 4-7 bits */
     _I                                  RegComplete;    /**< Write-Read in all the register */
 
 }REGx_4BitsWakeGpioIUnion;
 
 typedef union
 {
     REGx_4BitsWakeGpioIOStructBitField  RegBits;        /**< Write-Read in one bit of the register. Used 4-7 bits */
     _IO                                 RegComplete;    /**< Write-Read in all the register */
 
 }REGx_4BitsWakeGpioIOUnion;
 
 /**
  * Structures used to define Peripherals.
  * From the register to the base: (RegisterDirection - DirBase)/4 + 1. The 4 is to translate to Items in an array
  * Example: The Peripheral Register map starts at 0x3FC offset.
  * Operation: (0x3F8-0x000)/4 + 1 = 0xFF = 255 Items of 32 bits must be reserved in the array
  * */
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
 
 /**
  * Structure to define the GPIO subset.
  * */
 typedef struct
 {
     GPIOx_TypeDef GPIOA;   /**< Structure of Registers for GPIOA */
     GPIOx_TypeDef GPIOB;   /**< Structure of Registers for GPIOB */
     GPIOx_TypeDef GPIOC;   /**< Structure of Registers for GPIOC */
     GPIOx_TypeDef GPIOD;   /**< Structure of Registers for GPIOD */
     GPIOx_TypeDef GPIOE;   /**< Structure of Registers for GPIOE */
     GPIOx_TypeDef GPIOF;   /**< Structure of Registers for GPIOF */
     GPIOx_TypeDef GPIOG;   /**< Structure of Registers for GPIOG */
     GPIOx_TypeDef GPIOH;   /**< Structure of Registers for GPIOH */

     GPIOx_TypeDef GPIOJ;   /**< Structure of Registers for GPIOJ */
     GPIOx_TypeDef GPIOK;   /**< Structure of Registers for GPIOK */
     GPIOx_TypeDef GPIOL;   /**< Structure of Registers for GPIOL */
     GPIOx_TypeDef GPIOM;   /**< Structure of Registers for GPIOM */
     GPIOx_TypeDef GPION;   /**< Structure of Registers for GPION */
     GPIOx_TypeDef GPIOP;   /**< Structure of Registers for GPIOP */
     GPIOx_TypeDef GPIOQ;   /**< Structure of Registers for GPIOQ */
 }Periph_TypeDef;

 /**
  * Structure to define the System Control Registers without Bit-field for:
  * -   RCGC:   Give clock to a Peripheral.
  * -   PR:     Monitor that the clock has stabilized in a Peripheral.
  * */
 typedef struct
 {
     ReserMemoLoca Memory[384];         /**< Reserved from 0x5FC - 0x000 */
     _IO RCGCWD;                        /**< Offset: 0x600 */
     _IO RCGCTIMER;                     /**< Offset: 0x604 */
     _IO RCGCGPIO;                      /**< Offset: 0x608 */
     _IO RCGCDMA;                       /**< Offset: 0x60C */
     _IO RCGCEPI;                       /**< Offset: 0x610 */
     _IO RCGCHIB;                       /**< Offset: 0x614 */
     _IO RCGCUART;                      /**< Offset: 0x618 */
     _IO RCGCSSI;                       /**< Offset: 0x61C */
     _IO RCGCI2C;                       /**< Offset: 0x620 */
     ReserMemoLoca Memory0;             /**< Reserved from 0x624 - 0x624 */
     _IO RCGCUSB;                       /**< Offset: 0x628 */
     ReserMemoLoca Memory1;             /**< Reserved from 0x62C - 0x62C */
     _IO RCGCEPHY;                      /**< Offset: 0x630 */
     _IO RCGCCAN;                       /**< Offset: 0x634 */
     _IO RCGCADC;                       /**< Offset: 0x638 */
     _IO RCGCACMP;                      /**< Offset: 0x63C */
     _IO RCGCPWM;                       /**< Offset: 0x640 */
     _IO RCGCQEI;                       /**< Offset: 0x644 */
     ReserMemoLoca Memory2[4];          /**< Reserved from 0x654 - 0x648 */
     _IO RCGCEEPROM;                    /**< Offset: 0x658 */
     ReserMemoLoca Memory3[6];          /**< Reserved from 0x670 - 0x65C */
     _IO RCGCCCM;                       /**< Offset: 0x674 */
     ReserMemoLoca Memory4[9];          /**< Reserved from 0x698 - 0x678 */
     _IO RCGCEMAC;                      /**< Offset: 0x69C */
     ReserMemoLoca Memory5[216];        /**< Reserved from 0x9FC - 0x700 */
     _IO PRWD;                          /**< Offset: 0xA00 */
     _IO PRTIMER;                       /**< Offset: 0xA04 */
     _IO PRGPIO;                        /**< Offset: 0xA08 */
     _IO PRPRDMA;                       /**< Offset: 0xA0C */
     _IO PREPI;                         /**< Offset: 0xA10 */
     _IO PRHIB;                         /**< Offset: 0xA14 */
     _IO PRUART;                        /**< Offset: 0xA18 */
     _IO PRSSI;                         /**< Offset: 0xA1C */
     _IO PRI2C;                         /**< Offset: 0xA20 */
     ReserMemoLoca Memory6;             /**< Reserved from 0xA24 - 0xA24 */
     _IO PRUSB;                         /**< Offset: 0xA28 */
     ReserMemoLoca Memory7;             /**< Reserved from 0xA2C - 0xA2C */
     _IO PREPHY;                        /**< Offset: 0xA30 */
     _IO PRCAN;                         /**< Offset: 0xA34 */
     _IO PRADC;                         /**< Offset: 0xA38 */
     _IO PRACMP;                        /**< Offset: 0xA3C */
     _IO PRPWM;                         /**< Offset: 0xA40 */
     _IO PRQEI;                         /**< Offset: 0xA44 */
     ReserMemoLoca Memory8[4];          /**< Reserved from 0xA54 - 0xA48 */
     _IO PREEPROM;                      /**< Offset: 0xA58 */
     ReserMemoLoca Memory9[6];          /**< Reserved from 0xA70 - 0xA5C */
     _IO PRCCM;                         /**< Offset: 0xA74 */
     ReserMemoLoca Memory10[9];         /**< Reserved from 0xA98 - 0xA78 */
     _IO PREMAC;                        /**< Offset: 0xA9C */
 }SYSCTL_TypeDef;
 
 /**
  * Function to enable LEDs in port N
  * */
 void GPIO_Data(Periph_TypeDef * PERIPHx)
 {
     PERIPHx->GPION.DATA.RegComplete ^= 0x03;
 
 }

 /**
  * Function to configure port N as output
  * */
 void GPIO_Config(GPIOx_TypeDef *GPIOx_)
 {
     GPIOx_->DIR.RegBits.Bit0 |= 1;
     GPIOx_->DIR.RegBits.Bit1 |= 1;
     GPIOx_->DEN.RegBits.Bit0 |= 1;
     GPIOx_->DEN.RegBits.Bit1 |= 1;
 
 }

 /**
  * Function to give clock to GPIO with a value
  * */
 void GPIO_SetEnable(SYSCTL_TypeDef * _SYSCTL, unsigned int value)
 {
     _SYSCTL->RCGCGPIO |= value;
     while( (_SYSCTL->PRGPIO&value) == 0x0000 );
 }

 /**
  * Main function of program
  * */
 int main(void)
 {
     SYSCTL_TypeDef * SYSCTL = (SYSCTL_TypeDef *)(SYSCTL_BASE);
     static Periph_TypeDef * const PERIPH = (Periph_TypeDef *)(GPIOA_BASE);
     static GPIOx_TypeDef * const GPION = (GPIOx_TypeDef *)(GPION_BASE);

     GPIO_SetEnable(SYSCTL, 0X1020);
     GPIO_Config(GPION);

     PERIPH->GPION.DATA.RegBits.Bit0 = 0;
     (*PERIPH).GPION.DATA.RegBits.Bit1 = 0;

     GPION->DATA.RegComplete ^= 0x03;

     while(1);
 
 }
 
