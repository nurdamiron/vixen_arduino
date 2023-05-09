/* Tranmsitter code for the Arduino VIXEN Wireless lights controls

   If you have any issues with this code or suggestions please feel free to contact me.
                          Jody Payne
                   Knucklebuster620@live.com
 
 * Install the NRF24 library to your IDE

    NRF24 Pins
    
    GND    ->   GND
    VCC    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    SCK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

  #define MAX_CHANNELS 21//change to suite amount of channels max of 56
  RF24 radio (9, 10); //CE and CSN
  

int incomingByte[MAX_CHANNELS];
byte lights[MAX_CHANNELS+1];
int invertedByte[MAX_CHANNELS];
int lightByte1=0;
int lightByte2=0;
int lightByte3=0;
//int lightByte4=0;
//int lightByte5=0;
//int lightByte6=0;

//byte address1 = 53;
//byte address2 = 54;
byte address3 = 50;

struct Data_to_be_sent {    
  byte ch1;
  byte ch2;
  byte ch3;
//  byte ch4;
//  byte ch5;
//  byte ch6;
};

//Create a variable with the structure above and name it sent_data
Data_to_be_sent sent_data;


#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);


void setup(){
  
  Serial.begin(57600);
  lights[21]=1;
 //Begin the radio communication 
  radio.begin();
//  radio.setChannel(27);
//  radio.openWritingPipe(0xAABBCCDD11LL);
//  radio.openWritingPipe(address1);
//  radio.openWritingPipe(address2);
  radio.openWritingPipe(address3);
  radio.setPALevel(RF24_PA_MIN);//change to setting that best suits you (MIN, LOW, HIGH, MAX)
  radio.setDataRate(RF24_2MBPS);
//  radio.enableDynamicAck();                                  // Разрешаем выборочно отключать запросы подтверждения приема данных.
  radio.setAutoAck(false);
  radio.stopListening();
 

  sent_data.ch1 = 0;
  sent_data.ch2 = 0;
  sent_data.ch3 = 0;
//  sent_data.ch4 = 0;
//  sent_data.ch5 = 0;
//  sent_data.ch6 = 0;

  
 mySerial.begin(9600);
 mySerial.println("Hello, world?");
}

void loop(){
  
  
  
  
  if ((Serial.available() >= MAX_CHANNELS) && (Serial.read() == '+'))
  { 
    for (int i=0; i < MAX_CHANNELS; i ++)
    {    
      
      incomingByte[i] = Serial.read();
//      mySerial.print(incomingByte[i]);
  if (incomingByte[i] >= 200)
  (lights[i] = 1);
  if (incomingByte[i] <= 199)
  (lights[i] = 0);

mySerial.print(lights[i]);


    } 

    mySerial.println();

  

  }

  
//    for(int i=0;i<8;i++){
//  lights[i]=1;
//  }

  
lightByte1 = (lights[0] | (lights[1] << 1) | (lights[2] << 2) | (lights[3] << 3) | (lights[4] << 4) | (lights[5] << 5) | (lights[6] << 6) | (lights[21] << 7)); 
lightByte2 = (lights[7] | (lights[8] << 1) | (lights[9] << 2) | (lights[10] << 3) | (lights[11] << 4) | (lights[12] << 5) | (lights[13] << 6) | (lights[21] << 7)); 
lightByte3 = (lights[14] | (lights[15] << 1) | (lights[16] << 2) | (lights[17] << 3) | (lights[18] << 4) | (lights[19] << 5) | (lights[20] << 6) | (lights[21] << 7)); 
//lightByte4 = (lights[21] | (lights[22] << 1) | (lights[23] << 2) | (lights[24] << 3) | (lights[25] << 4) | (lights[26] << 5) | (lights[27] << 6) | (lights[27] << 7)); 
//lightByte5 = (lights[28] | (lights[29] << 1) | (lights[30] << 2) | (lights[31] << 3) | (lights[32] << 4) | (lights[33] << 5) | (lights[34] << 6) | (lights[34] << 7)); 
//lightByte6 = (lights[35] | (lights[36] << 1) | (lights[37] << 2) | (lights[38] << 3) | (lights[39] << 4) | (lights[40] << 5) | (lights[41] << 6) | (lights[41] << 7)); 


//lightByte1++;
//  mySerial.print(lights[35]);mySerial.print(" ");mySerial.print(lights[36]);mySerial.print(" ");mySerial.print(lights[37]);mySerial.print(" ");mySerial.print(lights[38]);mySerial.print(" ");mySerial.print(lights[39]);mySerial.print(" ");mySerial.print(lights[40]);mySerial.print(" ");mySerial.print(lights[41]);mySerial.println(" ");


//  mySerial.print(lights[0]);mySerial.print(" ");mySerial.print(lights[1]);mySerial.print(" ");mySerial.print(lights[2]);mySerial.print(" ");mySerial.print(lights[3]);mySerial.print(" ");mySerial.print(lights[4]);mySerial.print(" ");mySerial.print(lights[5]);mySerial.print(" ");mySerial.print(lights[6]);mySerial.println(" ");
  sent_data.ch1 = (lightByte1);
  sent_data.ch2 = (lightByte2);
  sent_data.ch3 = (lightByte3);
//  sent_data.ch4 = (lightByte4);
//  sent_data.ch5 = (lightByte5);
//  sent_data.ch6 = (lightByte6);


  
  radio.writeFast(&sent_data, sizeof(Data_to_be_sent));


}
