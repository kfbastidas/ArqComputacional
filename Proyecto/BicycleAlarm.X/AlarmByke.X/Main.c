/*
 * File:   TECLADO4x4.c
 * Author: Juan Manuel Rivera de las nieves
 *
 * Created on 30 de julio de 2020, 12:36 PM
 */
#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include <stdio.h>
#include "Configuracion_Bits.h"
#include "LCD.h"

#define _XTAL_FREQ 8000000


uint8_t buffer_lcd[16];  // Buffer de entero 16 bits Almacena el formato de las variables a mostrar en la pantalla LCD.


#define TRIS_KEYPAD    TRISB        // Definimos TRIS_LED = Registro TRISB 
#define PORT_KEYPAD    PORTB        // Definimos PORT_KEYPAD = Regitro PORTB
#define LAT_KEYPAD     LATB         // Definimos LAT_LED = Registro LATB

#define FILA0       0                 
#define FILA1       1
#define FILA2       2
#define FILA3       3
#define COLUMNA0    4
#define COLUMNA1    5
#define COLUMNA2    6
#define COLUMNA3    7

uint8_t     contador=0;             //Cuenta el número de filas
uint8_t     n=1;                    //Desplaza los ceros de las filas.
char        K;                      //Acepta el valor de la tecla pulsada
uint8_t     C;                      //Número de Columnas.
uint8_t     F;                      //Número de Filas.

void AntiRebote(void);              //Función AntiRebote.
__bit Columnas(void);             //Función Columnas censa el cambio de estado.

char const TECLAS[4][4]={           //Distribución de teclado 
                        {'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','#','D'}};
__bit Columnas(void)              //Función Columnas censa el cambio de estado.
{
    if((PORT_KEYPAD&(1<<COLUMNA0))&&(PORT_KEYPAD&(1<<COLUMNA1))&&(PORT_KEYPAD&(1<<COLUMNA2))&&(PORT_KEYPAD&(1<<COLUMNA3)))
    
        return 0;
    else
        return 1;
}

void main(void)                     //Función Principal
{
    ADCON1bits.PCFG=0b1111;         // Deshabilitamos las entradas analógicas, activamos Puerto A y B entradas/salidas digitales.
    PORT_KEYPAD&(1<<COLUMNA0);
    PORT_KEYPAD&(1<<COLUMNA1);
    PORT_KEYPAD&(1<<COLUMNA2);
    PORT_KEYPAD&(1<<COLUMNA3);
    TRIS_KEYPAD&=~((1<<FILA0)|(1<<FILA1)|(1<<FILA2)|(1<<FILA3)); // Configuramos RB0, RB1, RB2, RB3 como salidas
    LAT_KEYPAD&((1<<FILA0)|(1<<FILA1)|(1<<FILA2)|(1<<FILA3));    // Inicializamos RB0, RB1, RB2, RB3  a nivel alto 1
    TRISD=0x00;                     // Configuramos el Puerto D como salida.     
    lcd_init();                     // Inicializamos la librería LCD
    lcd_clear();                    // Limpiamos la pantalla LCD
    lcd_gotoxy(1,1);
    lcd_putc("*****KEYPAD*****");
    lcd_gotoxy(2,1);
    lcd_putc("**PIC  18F4550**");
    __delay_ms(500);
    lcd_gotoxy(2,1);
    lcd_putc("Presione tecla: ");
    __delay_ms(500);
    
    
    while(1)                        // Bucle Infinito 
    {
      if(contador<4)                // Si contador es menor que 4
      {
          F=contador;               // F recibe 0,1,2,3 según contador incrementa.
          LAT_KEYPAD=~n;            // Invertimos el valor de n y lo cargamos en el Puerto B
          n=n<<1;                   // n desplaza su valor 1 bit a la izquierda.
          ++contador;               // Incrementamos el valor de contador en una unidad.
          Columnas();               // Detecta si hay cambios en las columnas.
      }
      else                          // Reiniciamos las variables a sus valores iniciales 
      {
          contador=0;
          LAT_KEYPAD=0xFF;
          n=1;
      }
      
      if(Columnas())                // Si hay un cambio en la columna (columnas=0)...
      {
          if((PORT_KEYPAD&(1<<COLUMNA0))==0)
          {
              C=0;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA1))==0)
          {
              C=1;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA2))==0)
          {
              C=2;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA3))==0)
          {
              C=3;
          }
          AntiRebote();             // LLamamos a la función AntiRebote        
      }
    }
    return;
}

void AntiRebote(void)               // Función AntiRebote
{
    while(PORT_KEYPAD&(1<<COLUMNA0)==0); //No realiza nada hasta que el pulsador esté inactivo 
    while(PORT_KEYPAD&(1<<COLUMNA1)==0);
    while(PORT_KEYPAD&(1<<COLUMNA2)==0);
    while(PORT_KEYPAD&(1<<COLUMNA3)==0);
    __delay_ms(30);
    K=TECLAS[F][C];                      // Asigna a K el valor de la tecla ubicada enla fila F, columna C.
    sprintf(buffer_lcd,"Tecla: %c",K);
    lcd_clear();
    lcd_gotoxy(1,1);
    lcd_putc("*****KEYPAD*****");
    lcd_gotoxy(2,1);
    lcd_putc(buffer_lcd);
    return;
}

