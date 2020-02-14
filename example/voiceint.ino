
#include <SPI.h>
#include <ISD4004.h>

#define recordPin  2
ISD4004 voice(9, 8); //ss,int

void setup() {
  pinMode(recordPin, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(recordPin)){
    delay(20);
    voice.StartRecord(0);
    while (!digitalRead(recordPin));
    voice.StopRecord();
    voice.PlayInt(0);
  }
}
