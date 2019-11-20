#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); 

RF24 radio(9,8);                // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);      // Network uses that radio

const uint16_t this_node = 00;    // Address of our node in Octal format ( 04,031, etc)
const uint16_t other_node = 01;   // Address of the other node in Octal format

struct payload_t { 
  unsigned long ms;
  unsigned long counter;
};
char data;

void setup(void)
{
  Serial.begin(57600);
  pinMode(2,OUTPUT); 
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
  lcd.begin(20,4);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Genset 1");
  lcd.setCursor(0,1);
  lcd.print("Genset 2");
  lcd.setCursor(0,2);
  lcd.print("Genset 3");
}

char receive_data(){
  if ( network.available() ) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    return char(payload.ms);
  }
  else{
    return 0;
  }
}

char dataa[3];
unsigned long lastTime1, lastTime2, lastTime3;

void loop(void){
  
  network.update();
  char rx_data=receive_data();
  if(rx_data>0){
    data=rx_data; 
//    Serial.println(data);
    switch(data){
      case 'a':lastTime1=millis();break;
      case '1':lastTime1=millis();break;
      case 'b':lastTime2=millis();break;
      case '2':lastTime2=millis();break;
      case 'c':lastTime3=millis();break;
      case '3':lastTime3=millis();break;
      default:break;
    }
  }
  else{
    if(millis()-lastTime1>2000){
      dataa[0]='0';
      lcd.setCursor(13,0);
      lcd.print("Putus");
      lastTime1=millis();
    }
    if(millis()-lastTime2>2000){
      dataa[1]='0';
      lcd.setCursor(13,1);
      lcd.print("Putus");
      lastTime2=millis();
    }
    if(millis()-lastTime3>2000){
      dataa[2]='0';
      lcd.setCursor(13,2);
      lcd.print("Putus");
      lastTime3=millis();
    } 
  }
  if(data=='a' or data=='1'){
    dataa[0]=data;    
  }
  else if (data=='b' or data=='2'){
    dataa[1]=data;
  }
  else if (data=='c' or data=='3'){
    dataa[2]=data;
  }
  else{
    dataa[0]='0';
    dataa[1]='0';
    dataa[2]='0';
    Serial.println("Not Connected !");
  }
  
   if (dataa[0]=='a'){
    lcd.setCursor(9,0);
    lcd.print("ON");
   }
   else if (dataa[0]=='1'){
    lcd.setCursor(9,0);
    lcd.print("OFF");  
   }
   else if (dataa[1]=='b'){
    lcd.setCursor(9,1);
    lcd.print("ON");  
    }
  else if (dataa[1]=='2'){
    lcd.setCursor(9,1);
    lcd.print("OFF");  
    }
  else if (dataa[2]=='c'){
    lcd.setCursor(9,2);
    lcd.print("ON");  
    }
  else if (dataa[3]=='3'){
    lcd.setCursor(9,2);
    lcd.print("OFF");  
   }
   else{
     //
   }
  
  for(int x=0;x<3;x++){
    if(dataa[x]=='0'){
      Serial.print("Putus\t");
    }
    else{
      Serial.print(String(dataa[x])+"\t");
    }
  }
  Serial.println();
}
