/* Receiver code for the Arduino VIXEN Wireless lights controls

   If you have any issues with this code or suggestions please feel free to contact me.
                          Jody Payne
                   Knucklebuster620@live.com
 
 * Install the NRF24 library to your IDE

    NRF24 Pins
    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   A1
    CSN    ->   A0
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12
*/
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D9 9
#define D10 10


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  //CE and CSN pins

byte address = 50;
//byte address = 54;

// The sizeof this struct should not exceed 32 bytes
struct Received_data {
  byte ch1;
  byte ch2;
  byte ch3;
//  byte ch4;
//  byte ch5;
//  byte ch6;
};

Received_data received_data;


int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;
//int ch4_value = 0;
//int ch5_value = 0;
//int ch6_value = 0;


void reset_the_Data() 
{
  // 'safe' values to use when NO radio input is detected
  received_data.ch1 = 0;
  received_data.ch2 = 0;
  received_data.ch3 = 0;
//  received_data.ch4 = 0;
//  received_data.ch5 = 0;
//  received_data.ch6 = 0;
}



/**************************************************/

void setup()
{    
  Serial.begin(57600);
    pinMode(D10, OUTPUT);
    pinMode(D9, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D2, OUTPUT);
    digitalWrite(D10, LOW);
    digitalWrite(D9, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D2, LOW);
  
  //We reset the received values
  reset_the_Data();

  //Once again, begin and radio configuration
  radio.begin();
//  radio.setChannel(27);  
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
//  radio.enableDynamicPayloads();
  radio.setAutoAck(false);
//  radio.openReadingPipe (0,0xAABBCCDD11LL);                 // Открываем 1 трубу с адресом 0xAABBCCDD11, для приема данных.
  radio.startListening();

}

/**************************************************/

unsigned long lastRecvTime = 0;

//We create the function that will read the data each certain time
void receive_the_data()
{
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(Received_data));
  lastRecvTime = millis(); //Here we receive the data
}
}
/**************************************************/

void loop(){
  receive_the_data();
  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    reset_the_Data();
    //Go up and change the initial values if you want depending on
    //your aplications.
  } 

  
  ch1_value = received_data.ch1;
  ch2_value = received_data.ch2;
  ch3_value = received_data.ch3;
//  ch4_value = received_data.ch4;
//  ch5_value = received_data.ch5;
//  ch6_value = received_data.ch6;

Serial.print(bitRead(ch2_value, 0));Serial.print("   ");Serial.print(bitRead(ch2_value, 1));Serial.print("   ");Serial.print(bitRead(ch2_value, 2));Serial.print("   ");
Serial.print(bitRead(ch2_value, 3));Serial.print("   ");Serial.print(bitRead(ch2_value, 4));Serial.print("   ");Serial.print(bitRead(ch2_value, 5));Serial.print("   ");
Serial.print(bitRead(ch2_value, 6));Serial.print("   ");Serial.print(bitRead(ch2_value, 7));Serial.println("   ");
 
 if bitRead(ch2_value, 0)
    digitalWrite(D10, HIGH);
    else
    digitalWrite(D10, LOW);
    
 if bitRead(ch2_value, 1)
    digitalWrite(D9, HIGH);
    else
    digitalWrite(D9, LOW);
    
 if bitRead(ch2_value, 2)
    digitalWrite(D6, HIGH);
    else
    digitalWrite(D6, LOW);
    
 if bitRead(ch2_value, 3)
    digitalWrite(D5, HIGH);
    else
    digitalWrite(D5, LOW);
    
 if bitRead(ch2_value, 4)
    digitalWrite(D4, HIGH);
    else
    digitalWrite(D4, LOW);
    
 if bitRead(ch2_value, 5)
    digitalWrite(D3, HIGH);
    else
    digitalWrite(D3, LOW);

 if bitRead(ch2_value, 6)
    digitalWrite(D2, HIGH);
    else
    digitalWrite(D2, LOW);
     

}//Loop end
