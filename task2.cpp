/*
 * The MIT License (MIT)

Copyright (c) 2015-2018 Jetsonhacks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// displayExample.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <iostream>
#include <termios.h>
#include <time.h>
//#include <JHLEDBackpack.h>
#include "src/JHLEDBackpack.h"


int getkey() {
	int character;
	struct termios orig_term_attr;
	struct termios new_term_attr;

	/* set the terminal to raw mode */
	tcgetattr(fileno(stdin), &orig_term_attr);
	memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
	new_term_attr.c_lflag &= ~(ECHO | ICANON);
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
	//HT16K33* displayMatrix = new HT16K33();
	HT16K33 displayMatrix;
	// Default I2C Bus 1
	int err = displayMatrix.openHT16K33();
	if (err < 0) {
		printf("Error: %d", displayMatrix.error);
	}
	else {
		printf("HT16K33 Device Address: 0x%02X\n", displayMatrix.kI2CAddress);
		printf("HT16K33 Device Bus: 0x%02X\n", displayMatrix.kI2CBus);
		displayMatrix.begin();
		displayMatrix.clear();

		printf("Hit ESC key to exit\n");
		// Minutes and seconds - Start a 9:50 to show an exciting time change at 10:00!
		uint16_t counter = 590;
		auto start = std::chrono::system_clock::now();

		time_t currTime;
		struct tm* localTime;
		// Get the current time

		bool drawDots = false;
		while (displayMatrix.error >= 0 && getkey() != 27) {
			time(&currTime);
			localTime = localtime(&currTime);
			// display as hours and minutes
			int hours = localTime->tm_min;
			int minutes = localTime->tm_sec;
			// printf("Counter: %d\n", counter);
			displayMatrix.writeDigitNum(0, (hours / 10), drawDots);
			displayMatrix.writeDigitNum(1, hours % 10, drawDots);
			displayMatrix.drawColon(true);
			displayMatrix.writeDigitNum(3, (minutes / 10) % 10, drawDots);
			displayMatrix.writeDigitNum(4, minutes % 10, drawDots);
			displayMatrix.writeDisplay();
			counter++;
			sleep(1);
		}

	}
}