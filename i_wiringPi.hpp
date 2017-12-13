#ifndef I_WIRINGPI_HPP
#define I_WIRINGPI_HPP

/**
 * Wiring Pi pseudo interface for a raspberry pi
 * based GPIO interface library
 * https://www.wiringpi.com/reference/setup/
 */

/********************************/
/*        Setup Functions       */
/********************************/

int wiringPiSetup(void);
int wiringPiSetupGpio(void);
int wiringPiSetupPhys(void);
int wiringPiSetupSys(void);

/********************************/
/*         Core Functions       */
/********************************/

//Set mode of pin to INPUT, OUTPUT, PWM_OUTPUT, or GPIO_CLOCK
//Only pin 1 (BCM_GPIO 18) supports PWM_OUTPUT
//Only pin 7 (BCM_GPIO 4) supports GPIO_CLOCK
void pinMode(int pin, int mode);

//Sets pin to pull-up (PUD_UP), pull-down (PUD_DOWN), or neither (PUD_OFF) resistor mode
void pullUpDnControl(int pin, int pud);

//Write HIGH or LOW (1 or 0) to the given pin
void digitalWrite(int pin, int value);

//Write value to PWM register for given pin
//only supported on a Raspberry Pi by pin 1, range 0-1024
void pwmWrite(int pin, int value);

//Returns value read at given pin. HIGH or LOW
int digitalRead(int pin);

//Returns value read on supplied analog input pin.
int analogRead(int pin);

//Writes given value to the supplied analog pin
void analogWrite(int pin, int value);

/********************************/
/*    Raspberry Pi Specifics    */
/********************************/

//Writes the 8-bit byte supplied to the first 8 GPIO pins.
//Fastest way to set all 8 bits at once
void digitalWriteByte(int value);

//Set PWM generator mode to balance (PWM_MODE_BAL) or mark:space (PWM_MODE_MS)
void pwmSetMode(int mode);

//Sets range register on PWM generator. Default: 1024
void pwmSetRange(unsigned int range);

//Sets divisor for the PWM clock
void pwmSetClock(int divisor);

//Get's the board revision number. Either 1 or 2
int piBoardRev(void);

//Returns BCM_GPIO pin number of supplied wiringPi pin
//Accounts for board revision
int wpiPinToGpio(int wPiPin);

//Returns the BCM_GPIO pin number of the supplied physical pin
//on P1 connector
int physPinToGpio(int physPin);

// Sets the "strength" of the pad drivers for a group of pins.
// 3 groups with drive strength from 0 to 7. 
// Probably shouldn't use until it's fully understood
void setPadDrive(int group, int value);

/********************************/
/*             Timing           */
/********************************/

//Milliseconds since program called Setup functions
unsigned int millis(void);

//Returns number of micro seconds since Setup functions called
unsigned int micros(void);

//Pause for the given number of milliseconds
void delay(unsigned int howLong);

// Pause for the given number of microseconds
void delayMicroseconds(unsigned int howLong);

#endif
