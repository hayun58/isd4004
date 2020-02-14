
#include <SPI.h>
#include <ISD4004.h>

#define recordPin  2
ISD4004 voice(9);

void setup() {
  pinMode(recordPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(recordPin)){
    delay(20);
    voice.StartRecord(0);
    while (!digitalRead(recordPin));
    voice.StopRecord();
    voice.Play(0);
  }
}
