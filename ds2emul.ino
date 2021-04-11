#include <SPI.h>

#define SCLK_PIN 13
#define MISO_PIN 12
#define MOSI_PIN 11
#define SS_PIN 10
#define ACK_PIN 9

uint8_t cmd[5] ={0x01, 0x42, 0x00, 0x00, 0x00};

void setup(void)
{
  pinMode(SS_PIN, OUTPUT);
  pinMode(ACK_PIN, INPUT);

  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV64);
  digitalWrite(SS_PIN, HIGH);
  
}

void loop(void)
{
  digitalWrite(SS_PIN, LOW);
  bool error = false;

  for(uint8_t i=0; i<=4; i++)
  {
    //SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE3));
    SPI.transfer(cmd[i]);
    //SPI.endTransaction();
   /*
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
    */
    delay(10);
  }
  
  digitalWrite(SS_PIN, HIGH);
  delay(10);
}
