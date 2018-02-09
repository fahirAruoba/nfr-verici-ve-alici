#include <LCD5110_Basic.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 alici(9, 10);
const uint64_t kanal = 0xE8E8F0F0E1LL;

int layer[3] = {A4, A3, A2};

int alinanVeriler[2];
bool alindi = false;

LCD5110 DEGERLERLCD(8, 7, 6, 4, 5);



extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t TinyFont[];

void setup()
{
  Serial.begin (9600);


  pinMode(layer[0], OUTPUT);
  pinMode(layer[1], OUTPUT);
  pinMode(layer[2], OUTPUT);



  digitalWrite(layer[0], 0);
  digitalWrite(layer[1], 0);
  digitalWrite(layer[2], 0);
  delay(1000);
  digitalWrite(layer[0], 1);//mavi
  delay(1000);
  digitalWrite(layer[1], 1);// kırmızı
   delay(1000);
  digitalWrite(layer[2], 1);//buzzer
   delay(1000);


  digitalWrite(layer[0], 0);
  digitalWrite(layer[1], 0);
  digitalWrite(layer[2], 0);
   
  DEGERLERLCD.InitLCD();
  DEGERLERLCD.clrScr(); 

  alici.begin();
  alici.openReadingPipe(1, kanal);
  alici.startListening();
}



void loop() {

  if ( alici.available() ) {

    DEGERLERLCD.clrScr(); //Ekran temizlenir
    alici.read( &alinanVeriler, sizeof(alinanVeriler) );
    alindi = true;
    if (alindi == true) {

      Serial.println("Veriler Aliniyor..");
      for (int i = 0; i < 2; i++) {
        Serial.println(alinanVeriler[i]);
      }

      int x_ekseni = alinanVeriler[0];
      int y_ekseni = alinanVeriler[1];

      Serial.print("x_ekseni=="); Serial.println(x_ekseni);
      Serial.print("y_ekseni=="); Serial.println(y_ekseni);
      Serial.println("-----------------------------------");

      if (x_ekseni == 7 )
      {
        DEGERLERLCD.setFont(SmallFont);
        DEGERLERLCD.print("ALGILAMA", CENTER, 0);
        DEGERLERLCD.print("6'dan Buyuk", CENTER, 15);


        DEGERLERLCD.print("Ses", LEFT, 30);
        DEGERLERLCD.print("Led", LEFT, 35);
        DEGERLERLCD.print("OFF", LEFT, 40);
        DEGERLERLCD.setFont(BigNumbers);       
        DEGERLERLCD.printNumI(x_ekseni, RIGHT, 20); 


        digitalWrite(layer[0], 0);
        digitalWrite(layer[1], 0);
        digitalWrite(layer[2], 0);

      }
      if (x_ekseni == 4 )
      {
        DEGERLERLCD.setFont(SmallFont);
        DEGERLERLCD.print("ALGILAMA", CENTER, 0);
        DEGERLERLCD.print("3-6 Arasi", CENTER, 15);

        DEGERLERLCD.print("Ses", LEFT, 30);
        DEGERLERLCD.print("Kesik", LEFT, 35);
        DEGERLERLCD.print("Mavi", LEFT, 40);
        DEGERLERLCD.setFont(BigNumbers);      
        DEGERLERLCD.printNumI(x_ekseni, RIGHT, 20); 

   
  digitalWrite(layer[0], 1);//mavi
  digitalWrite(layer[1], 0);// kırmızı
  digitalWrite(layer[2], 1);//buzzer
   delay(100);
  digitalWrite(layer[2], 0);//buzzer
   delay(50);
      }
      if (x_ekseni == 2 )
      {
        DEGERLERLCD.setFont(SmallFont);
        DEGERLERLCD.print("ALGILAMA", CENTER, 0);
        DEGERLERLCD.print("3'ten Kucuk", CENTER, 15);
        DEGERLERLCD.print("Ses", LEFT, 30);
        DEGERLERLCD.print("Surekli", LEFT, 35);
        DEGERLERLCD.print("Kirmizi", LEFT, 40);
        DEGERLERLCD.setFont(BigNumbers);      
        DEGERLERLCD.printNumI(x_ekseni, RIGHT, 20); 
   
  digitalWrite(layer[1], 1);// kırmızı
  digitalWrite(layer[0], 0);//mavi
  digitalWrite(layer[2], 1);//buzzer
      }
      delay(100);
      alindi = false;


    }
    delay(100);

  }
}





