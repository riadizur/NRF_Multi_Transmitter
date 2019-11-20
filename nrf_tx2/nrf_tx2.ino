#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(9,8);                    // nRF24L01(+) radio attached using Getting Started board 

RF24Network network(radio);          // Network uses that radio

const uint16_t this_node = 01;        // Address of our node in Octal format
const uint16_t other_node = 00;       // Address of the other node in Octal format

const unsigned long interval = 2000; //ms  // How often to send 'hello world to the other unit

unsigned long last_sent;             // When did we last send?
unsigned long packets_sent;          // How many have we sent already


struct payload_t {                  // Structure of our payload
  unsigned long ms;
  unsigned long counter;
};

void setup(void)
{
  Serial.begin(57600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,INPUT);
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ this_node);
}

void send_data(char data){
    payload_t payload = { data, 4 };
    RF24NetworkHeader header(/*to node*/ other_node);
    bool ok = network.write(header,&payload,sizeof(payload));

    //Indikator Status Pengiriman data, jika berhasil LED di pin 2 Aktif
    //Jika gagal LED di pin 3 Aktif
    if (ok){
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
    }
    else{
      digitalWrite(3,HIGH);
      digitalWrite(2,LOW);
    }
    delay(15);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    delay(10); 
}
void loop() {
  network.update(); 
  if(digitalRead(5)==LOW){
    send_data('c');
  }
  else {
    send_data('3');
  }
}
