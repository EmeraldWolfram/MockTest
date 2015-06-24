#ifndef Communication_H
#define Communication_H
#define ReadMemory = 0xAB
#define WriteMemory = 0xCD
#include <stdint.h>


void sendBitHigh(int pinNo);
void sendBitLow(int pinNo);
uint32_t readBit(int pinNo);
void readTurnAroundIO(int pinNo);
void writeTurnAroundIO(int pinNo);

void writeData(uint8_t cmd, uint16_t address, uint8_t data);
uint8_t readData(uint8_t cmd, uint16_t address);


#endif // Communication_H
