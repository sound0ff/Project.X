/* 
 * File:   Main.c
 * Author: techm
 *
 * Created on 12 novembre 2021, 10:01
 */
#include "glcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <pic18.h>
#define _XTAL_FREQ 8000000
#pragma config FOSC = HS 		//oscillator HS
#pragma config PWRT = OFF
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config BOR = OFF
#pragma config WDT = OFF 		//Disable watchDog
#pragma config DEBUG = OFF
#pragma config PBADEN =OFF

/*
 * 
 */
volatile int value = 0;
volatile int posX = 56;
volatile int posY = 30;
void Delay_Ms(unsigned int ms) {
    int i, count;
    for (i = 1; i <= ms; i++) {
        count = 150;
        while (count != 1) {
            count--;
        }
    }
}

void bruit() {
    int i;
    for (i = 0; i < 50; i++) {
        LATEbits.LATE1 = 1; /* BUZZER ON                       */
        Delay_Ms(1); /* Delay Fuction Is Called 500Ms   */
        LATEbits.LATE1 = 0; /* BUZZER OFF                      */
        Delay_Ms(1);
    }
}

void exec(void) {
    if ((PORTCbits.RC0) ){
        bruit();
        if (value == 0)value = 1;
        else if (value==1) value = 0;
    }
    if (PORTAbits.RA0) {
        bruit();
        if (posY==30){
            posY=44;
        }
    }
    if(PORTAbits.RA1) {
        bruit();
        if (posY==44){
            posY=30;
        }
    }
    if(PORTAbits.RA5) {
        bruit();
        if (value == 2){
            value = 1;
        }
        else if ((posY==44) && (value ==1)){
            value=2;
        }
    }
    INTCONbits.TMR0IF = 0;
}

void __interrupt() pushed(void) {
    if (INTCONbits.TMR0IF == 1) {
        exec();
    }
}

void init() {
    TRISEbits.TRISE1 = 0;
    TRISCbits.TRISC0 = 1;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA5 = 1;
    PORTA = 0x0;
    PORTC = 0x0;
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 0;

    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    TMR0 = 0x0;
}

int main(void) {
    
    glcd_Init(GLCD_ON);
    init();
    glcd_FillScreen(0);
    while (1) {
        
        if (value == 1) {
            glcd_Image(MENU);
            glcd_Rect(posX, posY, posX+37, posY+9 ,1);
        }
        if (value==0){
            glcd_FillScreen(0);
        }
        if (value==2){
            glcd_Image(CREDITS);
        }
    }
}

