#include "SPI.h"

#define MISO_PIN 2
#define MOSI_PIN 3
#define SCLK_PIM 4
#define SS_PIN 5
#define ACK_PIN 6

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
  digitalWrite(SS, LOW);

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  SPI.transfer(',');


  SPI.endTransaction();
}
