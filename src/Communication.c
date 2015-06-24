#include "Communication.h"
#include "Signal.h"
#include <stdio.h>
#include <stdint.h>

void sendBitHigh(int pinNo){
  setPinHigh(pinNo);
  setPinLow(CLOCK_PIN);
  setPinHigh(CLOCK_PIN);
}

void sendBitLow(int pinNo){
  setPinLow(pinNo);
  setPinLow(CLOCK_PIN);
  setPinHigh(CLOCK_PIN);
}

uint32_t readBit(int pinNo){
  setPinHigh(CLOCK_PIN);
  setPinLow(CLOCK_PIN);
  uint32_t thisBit = readPin(pinNo);
  return thisBit;
}

void readTurnAroundIO(int pinNo){
  setPinToInput(pinNo);
  setPinLow(CLOCK_PIN);
  setPinHigh(CLOCK_PIN);
}

void writeTurnAroundIO(int pinNo){
  setPinToOutput(pinNo);
  setPinLow(CLOCK_PIN);
  setPinHigh(CLOCK_PIN);
}

void writeData(uint8_t cmd, uint16_t address, uint8_t data){
  uint16_t tempAdd;
  uint8_t  tempData, tempCmd;
  int i;

//Set pin to output  
  writeTurnAroundIO(IO_PIN);
//Send Command (0xCD)
  for(i=0;i<8;i++){  
    tempCmd = cmd & 0x01;
    cmd = cmd >> 1;
    if(tempCmd == 1)
      sendBitHigh(IO_PIN);
    else
      sendBitLow(IO_PIN);
  }
//Send Address (0xDEAD)
  for(i=0;i<16;i++){  
    tempAdd = address & 0x0001;
    address = address >> 1;
    if(tempAdd == 1)
      sendBitHigh(IO_PIN);
    else
      sendBitLow(IO_PIN);
  }
//Send Data (0xC0)
  for(i=0;i<8;i++){  
    tempData = data & 0x01;
    data = data >> 1;
    
    if(tempData == 1)
      sendBitHigh(IO_PIN);
    else
      sendBitLow(IO_PIN);
  }
}

uint8_t readData(uint8_t cmd, uint16_t address){
  uint8_t reading, nextRead, tempCmd, tempAdd;
  uint8_t receivedData = 0x00;
  int i;
//Set pin to output  
  writeTurnAroundIO(IO_PIN);
//Send Command (0xCD)
  for(i=0;i<8;i++){  
    tempCmd = cmd & 0x01;
    cmd = cmd >> 1;
    if(tempCmd == 1)
      sendBitHigh(IO_PIN);
    else
      sendBitLow(IO_PIN);
  }
//Send Address (0xDEAD)
  for(i=0;i<16;i++){  
    tempAdd = address & 0x0001;
    address = address >> 1;
    
    if(tempAdd == 1)
      sendBitHigh(IO_PIN);
    else
      sendBitLow(IO_PIN);
  }
  
  readTurnAroundIO(IO_PIN);
  
  for(i=0;i<8;i++){
    reading = readBit(IO_PIN);
    receivedData = receivedData | (reading<<i);
  }
  return receivedData;
}










