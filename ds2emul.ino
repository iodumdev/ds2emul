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
uint8_t getInfoCmd3[9] ={0x01, 0x46, 0x00, 0x01, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
uint8_t getInfoCmd4[9] ={0x01, 0x47, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
uint8_t getInfoCmd5[9] ={0x01, 0x4C, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
uint8_t getInfoCmd6[9] ={0x01, 0x4C, 0x00, 0x01, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
uint8_t mapMotorCmd[9] ={0x01, 0x4D, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t findButtonsCmd[9] ={0x01, 0x41, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
uint8_t exitConfigCmd[9] ={0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};

uint8_t *cmd_seq[] = {pollCmd, enterConfigCmd, getInfoCmd1, getInfoCmd2, getInfoCmd3, getInfoCmd4, getInfoCmd5, getInfoCmd6, mapMotorCmd, findButtonsCmd, exitConfigCmd};

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

  cmd = pollCmd;

  cmd_index = 0;
  cmd_length = 5;
}

void loop(void)
{
  digitalWrite(SS_PIN, LOW);

  switch(cmd_index){
    
   case 0:
   case 1:
      cmd = cmd_seq[cmd_index++];
      cmd_length = 5;
      break;
      
    case 10:
      cmd = cmd_seq[cmd_index];
      cmd_length = 9;
      cmd_index = 0;
      break;
      
   default:
      cmd = cmd_seq[cmd_index++];
      cmd_length = 9;
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
