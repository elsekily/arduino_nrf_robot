#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;
int x[2];
void forward();
void backward();
void right();
void left();
void stopp();

void setup() 
{
  Serial.begin(9600);  
  pinMode(22, OUTPUT);//1
  pinMode(23, OUTPUT);//1
  pinMode(24, OUTPUT);//2
  pinMode(25, OUTPUT);//2
  pinMode(26, OUTPUT);//3
  pinMode(27, OUTPUT);//3
  pinMode(28, OUTPUT);//4
  pinMode(29, OUTPUT);//4
  radio.begin();
  radio.setChannel(108);
  radio.openReadingPipe(1, pipe); //
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
}

void loop() {
  radio.startListening();  
  if (radio.available())
  {
    radio.read(&x, sizeof(x));
    if ( x[0]<=-2 &&x[1]>=-1 && x[1]<=1){forward();}
    else if (x[0]>=2 &&x[1]>=-1 && x[1]<=1){backward();}
    else if (x[1]>=2 &&x[0]>=-1 && x[0]<=1){left();}
    else if (x[1]<=-2 &&x[0]>=-1 && x[0]<=1){right();}
    else {stopp();}
    Serial.println("one");
  }
  delay(5);
}
void forward()
{
  digitalWrite(23,HIGH);//1
  digitalWrite(22,LOW);//1
  digitalWrite(25,HIGH);//2
  digitalWrite(24,LOW);//2
  digitalWrite(27,HIGH);//3
  digitalWrite(26,LOW);//3
  digitalWrite(28,HIGH);//4
  digitalWrite(29,LOW);//4
}
void backward()
{
  digitalWrite(23,LOW);//1
  digitalWrite(22,HIGH);//1
  digitalWrite(25,LOW);//2
  digitalWrite(24,HIGH);//2
  digitalWrite(27,LOW);//3
  digitalWrite(26,HIGH);//3
  digitalWrite(28,LOW);//4
  digitalWrite(29,HIGH);//4
}
void right()
{
  digitalWrite(22,LOW);//1
  digitalWrite(23,HIGH);//1
  digitalWrite(25,LOW);//2
  digitalWrite(24,HIGH);//2
  digitalWrite(26,LOW);//3
  digitalWrite(27,HIGH);//3
  digitalWrite(28,LOW);//4
  digitalWrite(29,HIGH);//4  
}
void left()
{
  digitalWrite(23,LOW);//1
  digitalWrite(22,HIGH);//1
  digitalWrite(24,LOW);//2
  digitalWrite(25,HIGH);//2
  digitalWrite(27,LOW);//3
  digitalWrite(26,HIGH);//3
  digitalWrite(29,LOW);//4
  digitalWrite(28,HIGH);//4
}
void stopp()
{
  digitalWrite(22,LOW);//1
  digitalWrite(23,LOW);//1
  digitalWrite(24,LOW);//2
  digitalWrite(25,LOW);//2
  digitalWrite(26,LOW);//3
  digitalWrite(27,LOW);//3
  digitalWrite(28,LOW);//4
  digitalWrite(29,LOW);//4
}
