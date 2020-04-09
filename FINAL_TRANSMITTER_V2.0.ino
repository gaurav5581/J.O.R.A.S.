
#include <SPI.h>
#include <nRF24L01.h> 
#include <RF24.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; 

RF24 radio(9, 10); 


struct Data_to_be_sent {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
  byte ch5;
  byte ch6;
  byte ch7;
  };


Data_to_be_sent sent_data;



void setup()
{
  Serial.begin(9600);
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);

  
  sent_data.ch1 = 0;
  sent_data.ch2 = 0;
  sent_data.ch3 = 127;
  sent_data.ch4 = 127;
  sent_data.ch5 = 0;
  sent_data.ch6 = 0;
  sent_data.ch7 = 0;
  
}

/**************************************************/


void loop()
{
  
 
  sent_data.ch1 = map( analogRead(A1), 0, 1024, 0, 255); 
  sent_data.ch2 = map( analogRead(A0), 0, 1024, 0, 255);
  sent_data.ch3 = map( analogRead(A2), 0, 1024, 0, 255);
  sent_data.ch4 = map( analogRead(A3), 0, 1024, 0, 255);
  sent_data.ch5 = digitalRead(2);
  sent_data.ch6 = digitalRead(3);
  sent_data.ch7 = map( analogRead(A4), 0, 1024, 255, 0);
  
  radio.write(&sent_data, sizeof(Data_to_be_sent));


  Serial.println(sent_data.ch7);
}



