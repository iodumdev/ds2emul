#include <SPI.h>

#define SCLK_PIN 13
#define MISO_PIN 12
#define MOSI_PIN 11
#define SS_PIN 10
#define ACK_PIN 9

uint8_t pollCmd[5] ={0x01, 0x42, 0x00, 0x00, 0x00};
uint8_t enterConfigCmd[5] ={0x01, 0x43, 0x00, 0x01, 0x00};
uint8_t getInfoCmd1[9] ={0x01, 0x45, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
uint8_t getInfoCmd2[9] ={0x01, 0x46, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};

uint8_t *cmd;
uint8_t cmd_index;
uint8_t cmd_length;

void setup(void)
{
  pinMode(SS_PIN, OUTPUT);
  pinMode(ACK_PIN, INPUT);

  SPI.begin();
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV64);
  digitalWrite(SS_PIN, HIGH);

  cmd = getInfoCmd1;

  cmd_index = 0;
  cmd_length = 4;
}

void loop(void)
{
  digitalWrite(SS_PIN, LOW);

  switch(cmd_index){
    case 0:
      cmd = pollCmd;
      cmd_length = 5;
      cmd_index++;
      break;
      
    case 1:
      cmd = enterConfigCmd;
      cmd_length = 5;
      cmd_index++;
      break;

    case 2:
      cmd = getInfoCmd1;
      cmd_length = 9;
      cmd_index++;
      break;

    case 3:
      cmd = getInfoCmd2;
      cmd_length = 9;
      cmd_index = 0;
      break;
  }

  for(uint8_t i=0; i <= cmd_length - 1; i++)
  {
    delayMicroseconds(20);
    SPI.transfer(cmd[i]);
    delayMicroseconds(10);
  }
  
  digitalWrite(SS_PIN, HIGH);
  delay(20);
}
