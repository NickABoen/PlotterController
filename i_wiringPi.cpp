/**
 * Wiring Pi pseudo interface for a raspberry pi
 * based GPIO interface library
 * https://www.wiringpi.com/reference/setup/
 */

#include <iostream>
#include <bitset>

/********************************/
/*        Setup Functions       */
/********************************/

int wiringPiSetup(void)
{
    std::cout << "{wiringPiSetup} Called wiringPiSetup" << std::endl;
    return 0;
}

int wiringPiSetupGpio(void)
{
    std::cout << "{wiringPiSetupGpio} Called wiringPiSetupGpio" << std::endl;
    return 0;
}

int wiringPiSetupPhys(void)
{
    std::cout << "{wiringPiSetupPhys} Called wiringPiSetupPhys" << std::endl;
    return 0;
}

int wiringPiSetupSys(void)
{
    std::cout << "{wiringPiSetupSys} Called wiringPiSetupSys" << std::endl;
    return 0;
}


/********************************/
/*         Core Functions       */
/********************************/

//Set mode of pin to INPUT, OUTPUT, PWM_OUTPUT, or GPIO_CLOCK
//Only pin 1 (BCM_GPIO 18) supports PWM_OUTPUT
//Only pin 7 (BCM_GPIO 4) supports GPIO_CLOCK
void pinMode(int pin, int mode)
{
    std::cout << "{pinMode} Set mode on pin [" << pin << "] to " << mode << std::endl;
}

//Sets pin to pull-up (PUD_UP), pull-down (PUD_DOWN), or neither (PUD_OFF) resistor mode
void pullUpDnControl(int pin, int pud)
{
    std::cout << "{pullUpDnControl} Set PUD on pin [" << pin << "] to " << pud << std::endl;
}

//Write HIGH or LOW (1 or 0) to the given pin
void digitalWrite(int pin, int value)
{
    std::cout << "{digitalWrite} Set pin [" << pin << "] = " << value << std::endl;
}

//Write value to PWM register for given pin
//only supported on a Raspberry Pi by pin 1, range 0-1024
void pwmWrite(int pin, int value)
{
    std::cout << "{pwmWrite}";
    if(pin == 1)
    {
        std::cout << "Set pwm on pin [" << pin << "] to " << value << std::endl;
    }
    else
    {
        std::cout << "Invalid PWM pin[" << pin << "]. Only pin 1 supports a PWM register." << std::endl;
    }
}

//Returns value read at given pin. HIGH or LOW
int digitalRead(int pin)
{
    std::cout << "{digitalRead} Read pin [" << pin << "]" << std::endl;
    return 0;
}

//Returns value read on supplied analog input pin.
int analogRead(int pin)
{
    std::cout << "{analogRead} Read pin [" << pin << "]" << std::endl;
    return 0;
}

//Writes given value to the supplied analog pin
void analogWrite(int pin, int value)
{
    std::cout << "{analogWrite} Set pin [" << pin << "] = " << value << std::endl;
}

/********************************/
/*    Raspberry Pi Specifics    */
/********************************/

//Writes the 8-bit byte supplied to the first 8 GPIO pins.
//Fastest way to set all 8 bits at once
void digitalWriteByte(int value)
{
    std::cout << "{digitalWriteByte} Write pins [8-1] to value [" << std::bitset<8>(value) << ']' << std::endl;
}

//Set PWM generator mode to balance (PWM_MODE_BAL) or mark:space (PWM_MODE_MS)
void pwmSetMode(int mode)
{
    std::cout << "{pwmSetMode} PWM set to [" << mode << ']' << std::endl;
}

//Sets range register on PWM generator. Default: 1024
void pwmSetRange(unsigned int range)
{
    std::cout << "{pwmSetRange} PWM range set to [" << range << ']' << std::endl;
}

//Sets divisor for the PWM clock
void pwmSetClock(int divisor)
{
    std::cout << "{pwmSetClock} PWM divisor set to [" << divisor << ']' << std::endl;
}

//Get's the board revision number. Either 1 or 2
int piBoardRev(void)
{
    std::cout << "{piBoardRev} Default pi board revision is 2" << std::endl;
    return 2;
}

//Returns BCM_GPIO pin number of supplied wiringPi pin
//Accounts for board revision
int wpiPinToGpio(int wPiPin)
{
    std::cout << "{wpiPinToPgio} Asked to convert wiringPi pin [" << wPiPin << "] to BCM_GPIO" << std::endl;
    return wPiPin;
}

//Returns the BCM_GPIO pin number of the supplied physical pin
//on P1 connector
int physPinToGpio(int physPin)
{
    std::cout << "{physPinToGPio} Asked to convert physical pin [" << physPin << "] to BCM_GPIO" << std::endl;
    return physPin;
}

// Sets the "strength" of the pad drivers for a group of pins.
// 3 groups with drive strength from 0 to 7. 
// Probably shouldn't use until it's fully understood
void setPadDrive(int group, int value)
{
    std::cout << "{setPadDrive} Setting pad drive of group [" << group << "] to [" << value << ']' << std::endl;
}

/********************************/
/*             Timing           */
/********************************/

//Milliseconds since program called Setup functions
unsigned int millis(void)
{
    std::cout << "{millis} Seconds since Setup functions called" << std::endl;
    return 100;
}

//Returns number of micro seconds since Setup functions called
unsigned int micros(void)
{
    std::cout << "{micros} Micro seconds since Setup functions called" << std::endl;
    return 100000;
}

//Pause for the given number of milliseconds
void delay(unsigned int howLong)
{
    std::cout << "{delay} Delay for [" << howLong << "] milliseconds." << std::endl;
}

// Pause for the given number of microseconds
void delayMicroseconds(unsigned int howLong)
{
    std::cout << "{delayMicroseconds} Delay for [" << howLong << "] microseconds." << std::endl;
}
