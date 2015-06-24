#include "unity.h"
#include <stdint.h>
#include <stdio.h>
#include "mock_Signal.h"
#include "Communication.h"
#define setLow    setPinLow_Expect(IO_PIN);                  \
                  setPinLow_Expect(CLOCK_PIN);               \
                  setPinHigh_Expect(CLOCK_PIN);                
                  
#define setHigh   setPinHigh_Expect(IO_PIN);                 \
                  setPinLow_Expect(CLOCK_PIN);               \
                  setPinHigh_Expect(CLOCK_PIN);                 
                  
#define readHigh    setPinHigh_Expect(CLOCK_PIN);             \
                    setPinLow_Expect(CLOCK_PIN);              \
                    readPin_ExpectAndReturn(IO_PIN,1);

#define readLow     setPinHigh_Expect(CLOCK_PIN);              \
                    setPinLow_Expect(CLOCK_PIN);              \
                    readPin_ExpectAndReturn(IO_PIN,0);
                    
                    
void setUp(void){}

void tearDown(void){}

void test_sendBitLow(void){
  setPinLow_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
	sendBitLow(IO_PIN);  
}

void test_sendBitHigh(void){
  setPinHigh_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
	sendBitHigh(IO_PIN);
}

void test_readBit(void){
  setPinHigh_Expect(CLOCK_PIN);
  setPinLow_Expect(CLOCK_PIN);
  readPin_ExpectAndReturn(IO_PIN,0);
  uint8_t testInt = readBit(IO_PIN);
  
  TEST_ASSERT_EQUAL(0,testInt);
}

void test_writeTurnAround(void){
  setPinToOutput_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
  writeTurnAroundIO(IO_PIN);
}
void test_readTurnAround(void){
  setPinToInput_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
  readTurnAroundIO(IO_PIN);
}

/**
 *  Send a command to the External Memory first
 *  Then send the address of the register to write
 *  send the data to that register
 *    1. set pin output
 *    2. send command
 *    3. send Address
 *    4. send data
 *
 *  Let the data to send = 0xC0, and send it to address 0xDEAD
 *  then writeData() should send out 0xCDDEADC0
 *
 */
void test_writeData_given_0xCD_and_address_0xDEAD_and_data_0xC0_should_sendOut_0xCDDEADC0(void){
//mock for writeTurnAround
  setPinToOutput_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
//START with Command 0xCD
  setHigh;
  setLow;
  setHigh;
  setHigh;
  setLow;
  setLow;
  setHigh;
  setHigh;
// *********Address 0xDEAD
  setHigh;
  setLow;
  setHigh;
  setHigh;
  setLow;
  setHigh;
  setLow;
  setHigh;
  setLow;
  setHigh;
  setHigh;
  setHigh;
  setHigh;
  setLow;
  setHigh;
  setHigh;
//**********Data 0xC0
  setLow;
  setLow;
  setLow;
  setLow;
  setLow;
  setLow;
  setHigh;
  setHigh;
  writeData(0xCD,0xDEAD,0xC0);
}

/**
 *  Send a command to the External Memory first
 *  Then send the address of the register to read
 *  get the data from the same pin
 *    1. set pin output
 *    2. send command
 *    3. send Address
 *    4. set pin as Input
 *    5. read data
 *    6. return the data
 *
 *  Let the data read = 0xBE, then readData()
 *  should return decimal 190 = 0xBE;
 *
 */
void test_readData_given_0xAB_and_address_0xFACE_should_sent_0xABFACE_and_turn_around_and_receive_0xBE(void){
//mocking for writeTurnAround
  setPinToOutput_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
//********Start with Command 0xAB
  setHigh;
  setHigh;
  setLow;
  setHigh;
  setLow;
  setHigh;
  setLow;
  setHigh;
//*******Address 0xFACE
  setLow;
  setHigh;
  setHigh;
  setHigh;
  setLow;
  setLow;
  setHigh;
  setHigh;
  setLow;
  setHigh;
  setLow;
  setHigh;
  setHigh;
  setHigh;
  setHigh;
  setHigh;
//**********Mocking for readTurnAround
  setPinToInput_Expect(IO_PIN);
  setPinLow_Expect(CLOCK_PIN);
  setPinHigh_Expect(CLOCK_PIN);
//************Data received
  readLow;
  readHigh;
  readHigh;
  readHigh;
  readHigh;
  readHigh;
  readLow;
  readHigh;

	uint8_t testData = readData(0xAB,0xFACE);
  
  TEST_ASSERT_EQUAL(190,testData);
}