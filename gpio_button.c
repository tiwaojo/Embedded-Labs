// exampleApp.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <unistd.h>
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

int main(int argc, char *argv[]){

    printf("Testing the GPIO Pins");

    enum jetsonTX2GPIONumber redLED, pushButton;
    redLED = gpio398 ;     // Ouput
    pushButton = gpio397 ; // Input
    // Make the button and led available in user space
    gpioExport(pushButton) ;
    gpioExport(redLED) ;
    gpioSetDirection(pushButton,inputPin) ;
    gpioSetDirection(redLED,outputPin) ;
    // Reverse the button wiring; this is for when the button is wired
    // with a pull up resistor
    // gpioActiveLow(pushButton, true);


    // Flash the LED 5 times
    for(int i=0; i<5; i++){
        printf ("Setting the LED on");
        gpioSetValue(redLED, on);
        usleep(200000);         // on for 200ms
        printf("Setting the LED off");
        gpioSetValue(redLED, off);
        usleep(200000);         // off for 200ms
    }
	
    unsigned int value = low;
    int ledValue = low;
    //turn off LED
    gpioSetValue(redLED, low);

    while (getkey() !=27)
    {
	    gpioGetValue(pushButton, &value);
	    printf ("Button %d\n", value);
	    if (value==high && ledValue != high)
	    {
		    ledValue = high;
		    gpioSetValue(redLED, on);
	    }
	    else{
		    if(ledValue != low) {
			    ledValue = low;
			    gpioSetValue(redLED, off);
		    }
	    }
	    usleep(1000);
    }
    // Wait for the push button to be pressed
    //cout << "Please press the button! ESC key quits the program" << endl;

    printf("GPIO example finished.");
    gpioUnexport(redLED);     // unexport the LED
    gpioUnexport(pushButton);      // unexport the push button
    return 0;
}


