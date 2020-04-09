#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 

#define IN_11  14          
#define IN_12  15          
#define IN_21  16          
#define IN_22  17                   


const uint64_t pipeIn = 0xE8E8F0F0E1LL;     
RF24 radio(9, 10);  


struct Received_data {
  byte ch1;
  byte ch2;
  byte ch3;
  byte ch4;
  byte ch5;
  byte ch6;
  byte ch7;
};

Received_data received_data;

Servo channel_1;
Servo channel_2;
Servo channel_3;
Servo channel_4;
Servo channel_5;
Servo channel_6;
Servo channel_7;

int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;
int ch4_value = 0;
int ch5_value = 0;
int ch6_value = 0;
int ch7_value = 0;

void reset_the_Data() 
{
  
  received_data.ch1 = 0;      
  received_data.ch2 = 0;
  received_data.ch3 = 0;
  received_data.ch4 = 0;
  received_data.ch5 = 0;
  received_data.ch6 = 0;
  
}






void setup()
{
  Serial.begin(9600);

  
  
  channel_1.attach(2);
  channel_2.attach(3);
  channel_3.attach(4);
  channel_4.attach(5);
  channel_5.attach(6);
  channel_6.attach(7);
  channel_7.attach(8);
  
  
  reset_the_Data();

  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  
  
  radio.startListening();

  pinMode(IN_11, OUTPUT);
  pinMode(IN_12, OUTPUT);
  pinMode(IN_21, OUTPUT);
  pinMode(IN_22, OUTPUT);
  
  
    
  
}

/**************************************************/

unsigned long lastRecvTime = 0;


void receive_the_data()
{
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(Received_data));
  lastRecvTime = millis(); 
}
}



void loop()
{
  
  receive_the_data();

  unsigned long now = millis();

  int x = map(received_data.ch7, 0, 255, 100, 255);
  

if ((received_data.ch1 > 118 && received_data.ch1 < 138) && (received_data.ch2 > 118 && received_data.ch2 < 138)) {
    
    digitalWrite(IN_11, LOW);
    digitalWrite(IN_12, LOW);
    digitalWrite(IN_21, LOW);
    digitalWrite(IN_22, LOW);
    
    
    ch1_value = 0;
    ch2_value = 0;
  }

  if (received_data.ch1 < 118) {
    
    digitalWrite(IN_11, LOW);
    digitalWrite(IN_12, HIGH);
    digitalWrite(IN_21, LOW);
    digitalWrite(IN_22, HIGH);
    
    
    
    ch1_value = x;
    ch2_value = x;
  }

else if (received_data.ch1 > 138) {
    
    digitalWrite(IN_11, HIGH);
    digitalWrite(IN_12, LOW);
    digitalWrite(IN_21, HIGH);
    digitalWrite(IN_22, LOW);
    
    ch1_value = x;
    ch2_value = x;
  }
  
  

  if (received_data.ch2 < 118) {
    
    digitalWrite(IN_11, LOW);
    digitalWrite(IN_12, HIGH);
    digitalWrite(IN_21, HIGH);
    digitalWrite(IN_22, LOW);
    
    
    ch1_value =  x;
    ch2_value =  x;
    // Confine the range from 0 to 255
   
  }
  if (received_data.ch2 > 138) {
   
    digitalWrite(IN_11, HIGH);
    digitalWrite(IN_12, LOW);
    digitalWrite(IN_21, LOW);
    digitalWrite(IN_22, HIGH);
    
        
    ch1_value =  x;
    ch2_value =  x;
   
  }
  
    if (ch2_value < 100) {
    ch2_value = 0;
  }
  if (ch1_value < 100) {
    ch1_value = 0;
  }

 
 
 if(received_data.ch5 == 1)
 {   
    digitalWrite(6, HIGH);
    
 }  


 else
{   
    digitalWrite(6, LOW);
    
    
 }  
 


    
  ch3_value = map(received_data.ch3,0,255,1400,2500);
  ch4_value = map(received_data.ch4,0,255,500,3000);



 
  analogWrite(2,ch1_value);  
  analogWrite(3,ch2_value);  
  channel_3.writeMicroseconds(ch3_value);
  channel_4.writeMicroseconds(ch4_value);  
  
  

 Serial.println(received_data.ch5);
  
}

