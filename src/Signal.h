#ifndef Signal_H
#define Signal_H

#define IO_PIN  4
#define CLOCK_PIN  5

/**
 *@brief Set pin to high
 *@param pinNo is the pin to set high
 */
void setPinHigh(int pinNo);

/**
 *@brief Set pin to low
 *@param pinNo is the pin to set low
 */
void setPinLow(int pinNo);
 
/**
 *@brief Read pin state
 *@param pinNo is the pin to read from
 *@return 1 if it is high, otherwise 0
 */
int readPin(int pinNo);

/**
 *@brief Set pin output
 *@param pinNo is the pin set as output
 */
void setPinToOutput(int pinNo);

/**
 *@brief Set pin input
 *@param pinNo is the pin set as input
 */
void setPinToInput(int pinNo);

#endif // Signal_H
