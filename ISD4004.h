// by hayun avi 14/2/2020

#ifndef ISD4004_h
#define ISD4004_h

#include <inttypes.h>
#include <SPI.h>

class ISD4004 //: public Print
 {
public:
  
  ISD4004(uint8_t ssPin);
  ISD4004(uint8_t ssPin,uint8_t intPin); 
		
  void initSPI(uint8_t _ssPin);
 void initSPI(uint8_t ssPin,uint8_t intPin);
 void Play(uint16_t Add);
 void PlayInt(uint16_t Add);
 void StartRecord(uint16_t Add);
 void StopRecord();
 uint8_t ReadStatus(); 
 
private:
  
  void spiSendOut(uint8_t value);
  void spiSendOutAddCode(uint16_t Add,uint8_t Cod);
   void spiDefault();  
 
  uint8_t _latchPin;
  uint8_t _eomPin;
  
  uint8_t _clockDivider;
  uint8_t _dataMode;
  uint8_t _bitOrder;
   
};

#endif
