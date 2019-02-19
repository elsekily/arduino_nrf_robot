#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 5, 4, 3, 2);

RF24 radio(7, 8); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

int x[2];
int z=0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(15,0);
  lcd.print("Hello, Mr.Ashraf/Mr.AnwaR!!");
  lcd.setCursor(22,1);
  lcd.print("Ahmed elshiekh!");
  for(int i=0;i<41;i++){
    lcd.scrollDisplayLeft(); 
    delay(300);
  }
  lcd.clear();
  radio.begin();
  radio.setChannel(108);
  radio.stopListening();
  radio.openWritingPipe(pipe);
  radio.setPALevel(RF24_PA_MAX); 
}
void loop() 
{
  x[0]=(analogRead(0)/125)-4;
  x[1]=(analogRead(1)/125)-4;  
  radio.write(&x,sizeof(x));
  lcd.setCursor(4,0);
  if ( x[0]<=-2 &&x[1]>=-1 && x[1]<=1){lcd.print("forward");}
    else if (x[0]>=2 &&x[1]>=-1 && x[1]<=1){lcd.print("backward");}
    else if (x[1]>=2 &&x[0]>=-1 && x[0]<=1){lcd.print("left");}
    else if (x[1]<=-2 &&x[0]>=-1 && x[0]<=1){lcd.print("right");}
    else {lcd.print("stop");}
    z++;
    if(z%10==0){lcd.clear();}
     if(z==1000){z=0;}
    
  delay(5);
  
}

