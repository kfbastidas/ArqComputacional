/* 
 * File:   LCD.h
 * Author: Rivera
 *
 * Created on 7 de diciembre de 2020, 10:49 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h> // include processor files - each processor file is guarded.  
                //LCD Functions Developed by electroSome
#define _XTAL_FREQ 8000000

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7
void Lcd_Port(char a)
{
   if(a & 1)
      D4 = 1;
   else
      D4 = 0;

   if(a & 2)
      D5 = 1;
   else
      D5 = 0;

   if(a & 4)
      D6 = 1;
   else
      D6 = 0;

   if(a & 8)
      D7 = 1;
   else
      D7 = 0;
}
void Lcd_Cmd(char a)
{
   RS = 0;             // => RS = 0
   Lcd_Port(a);
   EN  = 1;             // => E = 1
        __delay_ms(4);
        EN  = 0;             // => E = 0
}

void lcd_clear()
{
   Lcd_Cmd(0);
   Lcd_Cmd(1);
}

void lcd_posCursor(char a, char b)
{
   char temp,z,y;
   if(a == 1)
   {
     temp = 0x80 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
   else if(a == 2)
   {
      temp = 0xC0 + b - 1;
      z = temp>>4;
      y = temp & 0x0F;
      Lcd_Cmd(z);
      Lcd_Cmd(y);
   }
}

void lcd_init() //Inicializacion el lcd.
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x03);
   __delay_ms(5);
  Lcd_Cmd(0x03);
   __delay_ms(11);
  Lcd_Cmd(0x03);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}

void lcd_write_char(char a) //Funcion escribir un caracter.
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   Lcd_Port(y>>4);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

void lcd_putc(char *a) //Borra todo lo que haya en el display.
{
   int i;
   for(i=0;a[i]!='\0';i++)
      lcd_write_char(a[i]);
}

void lcd_shift_right()
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x0C);
}

void lcd_shift_left() //Funcion cambiar a la derecha.
{
   Lcd_Cmd(0x01);
   Lcd_Cmd(0x08);
}

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation








#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

