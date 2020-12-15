/*
 * File:   Main.c
 * Author: Rivera
 *
 * Created on 07 de Diciembre de 2020, 7:12 PM
 */

#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include <stdio.h>
#include "Configuracion_Bits.h"
#include "Teclado.h"
#include "LCD.h"
#include "Utilidades.h"

#define _XTAL_FREQ 8000000


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


int buffer_lcd[16];  // Buffer de entero 16 bits Almacena el formato de las variables a mostrar en la pantalla LCD.
int  contador=0;             //Cuenta el número de filas
int  n=1;                    //Desplaza los ceros de las filas.
char tecla;  //Acepta el valor de la tecla pulsada Caracter Incognito
char dato[16];                        //Vector que guarda el password.
int  numColumnas;                      //Número de Columnas.
int  posDato=0;
int  numFilas;                      //Número de Filas.
int  numVeces=2;
char const password[] = {'1','2','3','A'};

void antiRebote(void);              //Función AntiRebote.
bit Columnas(void);             //Función Columnas censa el cambio de estado.
int i;
void capturar_password(void);

char const TECLAS[4][4]={           //Distribución de teclado 
                        {'1','2','3','A'},
                        {'4','5','6','B'},
                        {'7','8','9','C'},
                        {'*','0','#','D'}};
bit Columnas(void)              //Función Columnas censa el cambio de estado.
{
    if((PORT_KEYPAD&(1<<COLUMNA0))&&(PORT_KEYPAD&(1<<COLUMNA1))&&(PORT_KEYPAD&(1<<COLUMNA2))&&(PORT_KEYPAD&(1<<COLUMNA3)))
    
        return 0;
    else
        return 1;
}

void main(void)                     //Función Principal
{
    OSCCON = 0x72 ;        /* Utilice un oscilador interno de frecuencia de 8MHz */
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
    lcd_posCursor(1,1);
    lcd_putc("BICYCLE ALARM");
    __delay_ms(500);
    lcd_clear(); 
    lcd_posCursor(1,1);
    lcd_putc("Password;");
    __delay_ms(500);
    
      
    while(1)                        // Bucle Infinito 
    {
//        imprimir(password,3,2);
        capturar_password();
    }
    return;
}

void antiRebote(void)               // Función AntiRebote
{
    while(PORT_KEYPAD&(1<<COLUMNA0)==0); //No realiza nada hasta que el pulsador esté inactivo 
    while(PORT_KEYPAD&(1<<COLUMNA1)==0);
    while(PORT_KEYPAD&(1<<COLUMNA2)==0);
    while(PORT_KEYPAD&(1<<COLUMNA3)==0);
    __delay_ms(300);
    dato[posDato]=TECLAS[numFilas][numColumnas];       // Asigna a passsword el valor de la tecla ubicada enla fila numFilas, columna numColumnas.
//    tecla = TECLAS[numFilas][numColumnas]; 
    tecla = '*';
//    if(tecla_OK(dato[posDato])== 1)
//        {
//            imprimir(dato, posDato-1,numVeces);
//            return;
//        }
    if(dato[posDato] =='D'){
        lcd_clear();
//        for(i=0;i<posDato-1; i++){
//        lcd_write_char(dato[i]);
//        lcd_posCursor(numVeces,1);
//        numVeces++;
//        }
          imprimir(dato, posDato-1,numVeces);
        return;
        }
    lcd_write_char(tecla);
//     __delay_ms(30);
    //lcd_clear();
    //lcd_gotoxy(1,1);
    //lcd_putc("*****KEYPAD*****");
     lcd_posCursor(numVeces,1);

//    lcd_putc(buffer_lcd);
    
    posDato++;
    
    
}
void capturar_password(void)
{
     if(contador<4)                // Si contador es menor que 4
      {
          numFilas=contador;               //numFilas recibe 0,1,2,3 según contador incrementa.
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
              numColumnas=0;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA1))==0)
          {
              numColumnas=1;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA2))==0)
          {
              numColumnas=2;
          }
          else if((PORT_KEYPAD&(1<<COLUMNA3))==0)
          {
              numColumnas=3;
          }
         antiRebote();             // LLamamos a la función AntiRebote 
         numVeces++;
      } 
}

