#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); 

RF24 radio(9,8);
RF24Network network(radio);

const uint16_t this_node = 00;    // Alamat Node RX dalam bilangan Octal
const uint16_t other_node = 01;   // Alamat Node TX dalam bilangan Octal

struct payload_t { 
  unsigned long ms;
  unsigned long counter;
};

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

void(* resetFunc) (void) = 0;

char dataa[3];
unsigned long lastTime1, lastTime2, lastTime3;

void loop(void){
  
  network.update();
  char data;
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
    lcd.setCursor(13,0);
    lcd.print("Connect");
  }
  else if (data=='b' or data=='2'){
    dataa[1]=data;
    lcd.setCursor(13,0);
    lcd.print("Connect");
  }
  else if (data=='c' or data=='3'){
    dataa[2]=data;
    lcd.setCursor(13,0);
    lcd.print("Connect");
  }
  else{
    dataa[0]='0';
    dataa[1]='0';
    dataa[2]='0';
    resetFunc();
    Serial.println("All Transmitter is not Connected !");
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
  if(!(dataa[0]=='0' and dataa[1]=='0' and dataa[2]=='0')){
    for(int x=0;x<3;x++){
      if(dataa[x]=='0'){
        Serial.print("Putus\t");
      }
      else{
        Serial.print("Connect\t"+String(dataa[0])+"\t");
      }
    }
    Serial.println();
  }
}
