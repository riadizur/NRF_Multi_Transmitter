# NRF_Multi_Transmitter

ABOUT THIS PROJECT
In this tutorial, you will learn about nRF24L01 Arduino interfacing with the help of two examples. In the first example, we will send “Hello world” and a command to blink the LED connected to the other Arduino. In the second example, we will do the bidirectional control and will send the command from First Arduino to blink the LED on the second and then we will send the command from second Arduino to blink the LED on the first.
Before going in detail, first have a look at the specification of this module
nRF24L01 Module
The nFR24L01 is a transceiver module which means that it can both send and receive the data.
These modules are very cheap, smaller in size and has a lot of specifications. Some of the specifications of these modules are as follows
Specifications of nRF24L01 Module
Power consumption is around 12mA during transmission which is even lesser than the led.
It can operate with baud rates from 250Kbps up to 2 Mbps.
Its range can reach up to 100 meters if used in open space and with antenna.
It can both send and receive the data simultaneously. 
Each module can communicate with up to 6 other modules. 
It uses the 2.4 GHz band.
It can send 1 to 25 bytes of raw data at the transmission rate of 1 MB.
It has 125 different channels.
Pinout
The nRF24L01 module works with the Arduino through the SPI communication. The pinout of the module is as follows

The operating voltage of this module is from 1.9 to 3.6V but the other pins are 5V tolerant which means that the other pins can be directly connected to the Arduino.
The MOSI, MISO and the SCK are the SPI pins and these needs to be connected to the SPI pins of Arduino. Different Arduino’s have different SPI pins.
The CSN and CE are for setting the module in active mode and for switching between command and transmit mode. These can be connected to any digital pins of Arduino.

