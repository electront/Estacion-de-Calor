/******************************************************************************
 * Nombre Fichero:   lcd.h
 * Proposito:    Librer�a de funciones para controlar un display LCD con chip
 *             Hitachi HD44780 o compatible. La interface es de 4 bits.
 * Procesador:  ATmel AVR
 * Compiler:   IAR-C y AVR-GCC (WinAVR)
 * Autor:     Shawn Johnson. http://www.cursomicros.com.
 *
 *****************************************************************************/

#include "compiler.h"
#include <util/delay.h>


//****************************************************************************
//    CONFIGURACI�N DE LOS PINES DE INTERFACE
//****************************************************************************

// Define el puerto a donde se conectar� el bus de datos del LCD
// Se utilizar� el nible alto del puerto escogido (ejem. PC4-DC4,...,PC7-DC7)


#define  lcd_DATAout   PORTB      // Registro PORT del puerto
#define  lcd_DATAin    PINB       // Registro PIN del puerto
#define  lcd_DATAddr   DDRB       // Registro DDR del puerto

// Define el puerto a donde se conectar�n las l�neas de control del LCD
// E, RW y RS. Puede ser el mismo puerto del bus de datos.

#define  lcd_CTRLout   PORTB      // Registro PORT del puerto
#define  lcd_CTRLin    PINB       // Registro PIN del puerto
#define  lcd_CTRLddr   DDRB       // Registro DDR del puerto

// Define los n�meros de los pines del puerto anterior que corresponder�n a 
// las l�neas E, RW y RS del LCD.

#define  lcd_E         0          // Pin Enable
#define  lcd_RW        2       // Pin Read/Write
#define  lcd_RS        1          // Pin Register Select

//****************************************************************************
//    C�DIGOS DE COMANDO USUALES
//****************************************************************************
#define  LCD_CLEAR    0x01    // Limpiar Display
#define  LCD_RETHOM   0x02    // Cursor a inicio de l�nea 1
#define  LCD_LINE1    0x80    // L�nea 1 posici�n 0 //80
#define  LCD_LINE2    0xC0    // L�nea 2 posici�n 0 \\C0
#define  LCD_LINE3    0x94    // L�nea 3 posici�n 0 //94
#define  LCD_LINE4    0xD4    // L�nea 4 posici�n 0 \\D4

#define  LCD_DDRAM    0x80    // Direcci�n 0x00 de DDRAM //80
#define  LCD_CGRAM    0x40    // Direcci�n 0x00 de CGRAM  40
#define  LCD_CURSOR   0x0E    // Mostrar solo Cursor
#define  LCD_BLINK    0x0D    // Mostrar solo Blink
#define  LCD_CURBLK   0x0F    // Mostrar Cursor + Blink
#define  LCD_NOCURBLK 0x0C    // No mostrar ni Cursor ni Blink

//****************************************************************************
//    PROTOTIPOS DE FUNCIONES
//****************************************************************************
void lcd_init(void);                // Inicializa el LCD
void lcd_puts(const char * s);            // Env�a una cadena ram al LCD
void lcd_put(const char s);            // Env�a un caracter ram al LCD
void lcd_gotorc(char r, char c);    // Cursor a fila r, columna c
void lcd_clear(void);               // Limpia el LCD y regresa el cursor al inicio
void lcd_data(char dat);            // Env�a una instrucci�n de dato al LCD
void lcd_cmd(char com);             // Env�a una instrucci�n de comando al LCD
char lcd_read(char RS);             // Lee un dato del LCD
void lcd_write(char inst, char RS); // Escribe una instrucci�n en el LCD
void lcd_nibble(char nibble);
//void ldelay_ms(unsigned char );

