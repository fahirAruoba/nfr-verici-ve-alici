
#include  <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"  

RF24 verici(9, 10);    
const uint64_t kanal = 0xE8E8F0F0E1LL; 

int mesaj[1];

const byte echo = 7;
const byte trig = 6;
int sure = 0;
int mesafe = 0;


void setup()
{
  Serial.begin(9600);
  verici.begin();      
  verici.openWritingPipe(kanal);  


  pinMode(echo , INPUT);
  pinMode(trig , OUTPUT);
}

void loop()
{


  digitalWrite(trig , HIGH);
  digitalWrite(trig , LOW);
  sure = pulseIn(echo , HIGH);
  mesafe = (sure / 2) / 28.5 ;
  Serial.print("mesafe"); Serial.println(mesafe);
  if (mesafe <= 3)
  {
    mesaj[0] = 2;
    verici.write(mesaj, 1);  


  }
  else if ((mesafe > 3 ) && (mesafe <= 6 ))

  {
    mesaj[0] = 4;
    verici.write(mesaj, 1);   


  }

  else if (mesafe > 6 )

  {
    mesaj[0] = 7;
    verici.write(mesaj, 1);   

  }
}






