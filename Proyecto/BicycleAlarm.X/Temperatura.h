/* 
 * File:   Temperatura.h
 * Author: Rivera
 *
 * Created on 14 de diciembre de 2020, 08:15 PM
 */

#ifndef TEMPERATURA_H
#define	TEMPERATURA_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>         // include processor files - each processor file is guarded.  
#include <stdint.h>     // Incluimos librería que nos permitira trabajar con variables enteras

#define _XTAL_FREQ 8000000
#define tempe PORTAbits.RA3;



#ifdef	__cplusplus
}
#endif

#endif	/* TEMPERATURA_H */

