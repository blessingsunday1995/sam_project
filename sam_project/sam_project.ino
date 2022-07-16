
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>


#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 


#define RST_PIN 9
#define SS_PIN 8


byte readCard[4];
String MasterTag = "97E3104E";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";


//Mobile phone number,need to change
#define PHONE_NUMBER "187*******39"  
 
//The content of messages sent
 char arr2[5][20] = { {"first string"},
                                          {"second string"},
                                          {"third string"},
                                          {"fourth string"},
                                          {"fifth string"} 
                                          
                                          };





#define MESSAGE  "hello,world"

const int ldrPin1 = A0; // analog pin 0
const int ldrPin2= A1; // analog pin 0
const int ldrPin3= A2; // analog pin 0
const int ldrPin4= A3; // analog pin 0
const int ldrPin5= A4; // analog pin 0
const int ldrPin6= A5; // analog pin 0
const int ldrPin7= A6; // analog pin 0
const int ldrPin8= A7; // analog pin 0
const int ldrPin9= A8; // analog pin 0
const int ldrPin10= A9; // analog pin 0


int bookState1 =0;
int bookState2 =0;
int bookState3 =0;
int bookState4 =0;
int bookState5 =0;
int bookState6 =0;
int bookState7 =0;
int bookState8 =0;
int bookState9 =0;
int bookState10 =0;



#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

   // Initiating
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
  // Here LDR sensor is determined as input.
pinMode(ldrPin1, INPUT);
pinMode(ldrPin2, INPUT);
pinMode(ldrPin3, INPUT);
pinMode(ldrPin4, INPUT);
pinMode(ldrPin5, INPUT);
pinMode(ldrPin6, INPUT);
pinMode(ldrPin7, INPUT);
pinMode(ldrPin8, INPUT);
pinMode(ldrPin9, INPUT);
pinMode(ldrPin10, INPUT);

 
 //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }  
  Serial.println("Sim808 init success");
  Serial.println("Start to send message ...");

  //******** define phone number and text **********
  sim808.sendSMS(PHONE_NUMBER,MESSAGE); 
}

void loop() {
  //nothing to do
int ldrStatus1 = analogRead(ldrPin1);
int ldrStatus2 = analogRead(ldrPin2);
int ldrStatus3 = analogRead(ldrPin3);
int ldrStatus4 = analogRead(ldrPin4);
int ldrStatus5 = analogRead(ldrPin5);
int ldrStatus6 = analogRead(ldrPin6);
int ldrStatus7 = analogRead(ldrPin7);
int ldrStatus8 = analogRead(ldrPin8);
int ldrStatus9 = analogRead(ldrPin9);
int ldrStatus10 = analogRead(ldrPin10);




 //Wait until new tag is available
  while (getID()){
  
    if (tagID == MasterTag || "97E3104E") 
    {


 
    }
    else
    {




    }


    
  }



if (ldrStatus1 <= 200 && bookState1 == 0) {

bookState1++;
Serial.print("Darkness over here,turn on the LED : ");

Serial.println(ldrStatus1);

} else {

bookState1 = 0; 
Serial.print("There is sufficeint light , turn off the LED : ");

Serial.println(ldrStatus1);

}

  
}





//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
