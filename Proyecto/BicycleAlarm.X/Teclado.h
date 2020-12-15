/* 
 * File:   Teclado.h
 * Author: Rivera
 *
 * Created on 7 de diciembre de 2020, 10:50 PM
 */

#ifndef TECLADO_H
#define	TECLADO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>         // include processor files - each processor file is guarded.  
#include <stdint.h>     // Incluimos librería que nos permitira trabajar con variables enteras

#define _XTAL_FREQ 8000000
#define KEYPAD4x4TRIS   TRISB
#define KEYPAD4x4PORT   PORTB
#define KEYPAD4x4LAT    LATB

/*FILAS*/
#define Fila1 PORTBbits.RB0 //Asignacion delos puertos RB a sus respectivas columnas.
#define Fila2 PORTBbits.RB1
#define Fila3 PORTBbits.RB2
#define Fila4 PORTBbits.RB3

/*COLUMAS*/
#define Columna1 0x10           // Bits RB4 al RB7 0001
#define Columna2 0x20           // Bits RB4 al RB7 0010
#define Columna3 0x40           // Bits RB4 al RB7 0100
#define Columna4 0x80           // Bits RB4 al RB7 1000

void Keypad_Init(void);         // Función que inicializa el Teclado Matricial 4x4
int Boton_Presionado(void); // Función que nos mostrará que boton fue presionado del teclado matricial
//int Boton_Clic(void);  
int Decodificar_Boton(int key);
//int Tecla_Clic(void);
int Tecla_Presionada(void);

//int Tecla_Clic(void)
//{
//    int key;
//    do
//    {
//        key=Boton_Clic();
//    }
//    while(key==0);
//    key=Decodificar_Boton(key);
//    return key;
//}

int Tecla_Presionada(void)
{   
//    char tecla='';
    int key;
    do
    {
        key=Boton_Presionado();
    }
    while(key==0);
    key = Decodificar_Boton(key);
    return key;
}

void Keypad_Init(void)          
{
    KEYPAD4x4TRIS=0x0F;         // Configuramos RB7 a RB4 como salidas y RB3 a RB0 como entradas
}

int Boton_Presionado(void)
{
    int boton=0;
    KEYPAD4x4LAT=Columna1;
        if(Fila1==1) boton=1;
        if(Fila2==1) boton=5;
        if(Fila3==1) boton=9;
        if(Fila4==1) boton=13;
   
    KEYPAD4x4LAT=Columna2;
        if(Fila1==1) boton=2;
        if(Fila2==1) boton=6;
        if(Fila3==1) boton=10;
        if(Fila4==1) boton=14;
    
    KEYPAD4x4LAT=Columna3;
        if(Fila1==1) boton=3;
        if(Fila2==1) boton=7;
        if(Fila3==1) boton=11;
        if(Fila4==1) boton=15;
    
    KEYPAD4x4LAT=Columna4;
        if(Fila1==1) boton=4;
        if(Fila2==1) boton=8;
        if(Fila3==1) boton=12;
        if(Fila4==1) boton=16;
    
    return boton;
}

//int Boton_Clic(void)
//{
//   int boton=0;
//    KEYPAD4x4LAT=Columna1;
//        if(Fila1==1) boton=1; //Asignacion de las teclas selecionadas en numeros.
//        if(Fila2==1) boton=5;
//        if(Fila3==1) boton=9;
//        if(Fila4==1) boton=13;
//    while(Fila1==1 || Fila2==1 || Fila3==1 || Fila4==1);
//    
//    KEYPAD4x4LAT=Columna2;
//        if(Fila1==1) boton=2;
//        if(Fila2==1) boton=6;
//        if(Fila3==1) boton=10;
//        if(Fila4==1) boton=14;
//    while(Fila1==1 || Fila2==1 || Fila3==1 || Fila4==1);
//    
//    KEYPAD4x4LAT=Columna3;
//        if(Fila1==1) boton=3;
//        if(Fila2==1) boton=7;
//        if(Fila3==1) boton=11;
//        if(Fila4==1) boton=15;
//    while(Fila1==1 || Fila2==1 || Fila3==1 || Fila4==1);
//    
//    KEYPAD4x4LAT=Columna4;
//        if(Fila1==1) boton=4;
//        if(Fila2==1) boton=8;
//        if(Fila3==1) boton=12;
//        if(Fila4==1) boton=16;
//    
//    while(Fila1==1 || Fila2==1 || Fila3==1 || Fila4==1);
//    return boton; 
//}


int Decodificar_Boton(int key)
{
//   char tecla='';
   int tecla=0;
   switch(key)
   {
       case 1: tecla-'1';
       break;
       case 2: tecla-'2';
       break;
       case 3: tecla-'3';
       break;
       case 4: tecla-'A';
       break;
       
       case 5: tecla-'4';
       break;
       case 6: tecla-'5';
       break;
       case 7: tecla-'6';
       break;
       case 8: tecla-'B';
       break;
       
       case 9:  tecla-'7';
       break;
       case 10: tecla-'8';
       break;
       case 11: tecla-'9';
       break;
       case 12: tecla-'C';
       break;
       
       case 13: tecla-'*';
       break;
       case 14: tecla-'0';
       break;
       case 15: tecla-'#';
       break;
       case 16: tecla-'D';
       break;
   }
    
   return tecla;  
}



#ifdef	__cplusplus
}
#endif

#endif	/* TECLADO_H */

