/* 
 * File:   Main.c
 * Author: techm
 *
 * Created on 12 novembre 2021, 10:01
 */
#include "glcd.h"
#include <stdio.h>
#include <stdlib.h>

#pragma config FOSC = HS 		//oscillator HS
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config WDT = OFF 		//Disable watchDog
#pragma config LVP = OFF 		//Disable low voltage programmig
#pragma config DEBUG = ON	
/*
 * 
 */
interrupt pushed(void){
    
}
int main(void) {

glcd_Init(GLCD_ON);
while(1)
{ // Clear the screen
    glcd_FillScreen(0);
    // Set the cursor and write a string


    }
}

