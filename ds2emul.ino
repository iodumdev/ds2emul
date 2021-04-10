#include "SPI.h"

#define MISO_PIN 2
#define MOSI_PIN 3
#define SCLK_PIM 4
#define SS_PIN 5
#define ACK_PIN 6

uint8_t cmd[8] ={0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

setup()
{
  pinMode(MISO_PIN, INPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(SCLK_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  pinMode(ACk_PIN, INPUT);

  SPI.begin();
  digitalWrite(SS_PIN, HIGH);
  
}

loop()
{
  digitalWrite(SS_PIN, LOW);
  bool error = false;

  for(uint8_t i=0; i<=7; i++)
  {
    SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE3));
    SPI.transfer(cmd[i]);
    SPI.endTransaction();
   
    uint8_t counter = 0;
    if(i == 7) break;
    while(!digitalRead(ACK_PIN))
    {
      counter++;
      if(counter >= 100)
      {
        error = true;
        break;
      }
      delay(10);
    }
    if(error) break;
  }
  
  digitalWrite(SS_PIN, HIGH);
  delay(10);
}
