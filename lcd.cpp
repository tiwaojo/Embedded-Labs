#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
//#include <JHLEDBackpack.h>
#include "src/JHLEDBackpack.h"
#include "jetsonGPIO.h"



int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}


int main() {
	
    	HT16K33 *displayMatrix = new HT16K33() ;
    // Default I2C Bus 1
    int err = displayMatrix->openHT16K33();
    if (err < 0){
        printf("Error: %d", displayMatrix->error);
    } else {
        printf("HT16K33 Device Address: 0x%02X\n",displayMatrix->kI2CAddress) ;
        printf("HT16K33 Device Bus: 0x%02X\n",displayMatrix->kI2CBus) ;
        displayMatrix->begin() ;
        displayMatrix->clear() ;

        displayMatrix->writeDigitNum(0,1) ;
        displayMatrix->writeDigitNum(1,2) ;
        // 2 is the colon
        displayMatrix->writeDigitNum(3,3) ;
        displayMatrix->writeDigitNum(4,4) ;
//Your code is here











        
    // Turn off the display oscillator
    //
    gpioUnexport(pushButton2);
    displayMatrix->end() ;
    displayMatrix->closeHT16K33();
}
