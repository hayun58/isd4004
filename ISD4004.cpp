
//written by Avi Hayun

#include "ISD4004.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

ISD4004::ISD4004(uint8_t ssPin) 
{
	initSPI(ssPin);  
}

ISD4004::ISD4004(uint8_t ssPin,uint8_t intPin)
{
	initSPI(ssPin,intPin);
}

void ISD4004::initSPI(uint8_t ssPin) 
{
	// initialize SPI:

	_latchPin = ssPin;
	pinMode (_latchPin, OUTPUT); //just in case _latchPin is not 10 or 53 set it to output 
	//otherwise SPI.begin() will set it to output but just in case		
	SPI.begin(); 	
	spiDefault();
}

void ISD4004::initSPI(uint8_t ssPin,uint8_t intPin)
{
	// initialize SPI:

	_latchPin = ssPin;
	_eomPin=intPin;
	pinMode (_latchPin, OUTPUT); //just in case _latchPin is not 10 or 53 set it to output
	pinMode(_eomPin,INPUT_PULLUP);

	//otherwise SPI.begin() will set it to output but just in case
	SPI.begin();
	spiDefault();
}

void ISD4004::spiSendOut(uint8_t value) 
{
	//just in case you are using SPI for more then one device
	//set bitOrder, clockDivider and dataMode each time

	SPI.setClockDivider(SPI_CLOCK_DIV32);
	SPI.setBitOrder(LSBFIRST);
	SPI.setDataMode(_dataMode); 

	digitalWrite(_latchPin, LOW);
	SPI.transfer(value);
	digitalWrite(_latchPin, HIGH); 
}


void ISD4004::spiSendOutAddCode(uint16_t Add,uint8_t Cod)
{
	//just in case you are using SPI for more then one device
	//set bitOrder, clockDivider and dataMode each time
	
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	SPI.setBitOrder(_bitOrder);
	SPI.setBitOrder(LSBFIRST);
	digitalWrite(_latchPin, LOW);
	SPI.transfer(Add);
	SPI.transfer(Add>>8);
	SPI.transfer(Cod);
	digitalWrite(_latchPin, HIGH);
}

void ISD4004::Play(uint16_t Add)
{
	Add=(Add*5)/2; //sec
	spiSendOut(0x20); //powerup
	delay(60);    //60msec
	spiSendOutAddCode(Add,0xe0); //send address+setplay

	delay(110);//Tstop
	spiDefault();
}

void ISD4004::PlayInt(uint16_t Add)
{
	Add=(Add*5)/2; //sec

	spiSendOut(0x20); //powerup
	delay(60);    //60msec
	spiSendOutAddCode(Add,0xe0); //send address+setplay

	while(digitalRead(_eomPin));
	spiSendOut(0x10);  //stoppowerdown

	delay(110);//Tstop
	spiDefault();
}


void ISD4004::StartRecord(uint16_t Add)
{	
	Add=(Add*5)/2; //sec
	delay(20);

	spiSendOut(0x20); //powerup
	delay(60);    //60msec
	spiSendOut(0x20);  //powerup
	delay(110);
	spiSendOutAddCode(Add,0xa0); //send address+setrec

	spiDefault();
}

void ISD4004::StopRecord()
{
	spiSendOut(0x10);  //stoppowerdown
	delay(110); //Tstop

	spiDefault();
}


uint8_t ISD4004::ReadStatus()
{
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	SPI.setBitOrder(_bitOrder);
	SPI.setBitOrder(LSBFIRST);

	digitalWrite(_latchPin, LOW);
	uint8_t Status = SPI.transfer(0);

	digitalWrite(_latchPin, HIGH);

	return Status;
}

void ISD4004::spiDefault()
{
	//set clockDivider to SPI_CLOCK_DIV2 by default which is 8MHz
	_clockDivider = SPI_CLOCK_DIV2;
	SPI.setClockDivider(_clockDivider);

	//set data mode to SPI_MODE0 by default
	_dataMode = SPI_MODE0;
	SPI.setDataMode(_dataMode);

	//set bitOrder to MSBFIRST by default
	_bitOrder = MSBFIRST;
	SPI.setBitOrder(_bitOrder);
}

