
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>


#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 


int lock = 10;

#define RST_PIN 9
#define SS_PIN 8


byte readCard[4];
String MasterTag = "97E3104E";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";


//Mobile phone number,need to change
#define PHONE_NUMBER "08131971666"  
 





#define Book_Taken1  "A Book is taken from shelf 1"
#define Book_Return1  "A Book have been return to shelf 1"

#define Book_Taken2  "A Book is taken from shelf 2"
#define Book_Return2  "A Book have been return to shelf 2"

#define Book_Taken3  "A Book is taken from shelf 3"
#define Book_Return3  "A Book have been return to shelf 3"

#define Book_Taken4  "A Book is taken from shelf 4"
#define Book_Return4  "A Book have been return to shelf 4"

#define Book_Taken5  "A Book is taken from shelf 5"
#define Book_Return5  "A Book have been return to shelf 5"

#define Book_Taken6  "A Book is taken from shelf 6"
#define Book_Return6  "A Book have been return to shelf 6"

#define Book_Taken7  "A Book is taken from shelf 7"
#define Book_Return7  "A Book have been return to shelf 7"

#define Book_Taken8  "A Book is taken from shelf 8"
#define Book_Return8  "A Book have been return to shelf 8"

#define Book_Taken9  "A Book is taken from shelf 9"
#define Book_Return9  "A Book have been return to shelf 9"

#define Book_Taken10  "A Book is taken from shelf 10"
#define Book_Return10  "A Book have been return to shelf 10"

#define Book_Taken11  "A Book is taken from shelf 11"
#define Book_Return11  "A Book have been return to shelf 11"

#define Book_Taken12  "A Book is taken from shelf 12"
#define Book_Return12  "A Book have been return to shelf 12"

#define Book_Taken13  "A Book is taken from shelf 13"
#define Book_Return13  "A Book have been return to shelf 13"

#define Book_Taken14  "A Book is taken from shelf 14"
#define Book_Return14  "A Book have been return to shelf 14"

#define Book_Taken15  "A Book is taken from shelf 15"
#define Book_Return15  "A Book have been return to shelf 15"

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

pinMode(lock,OUTPUT);

 
 //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.print("Sim808 init error\r\n");
  }  
  Serial.println("Sim808 init success");
  Serial.println("Start to send message ...");

  //******** define phone number and text **********
 
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

      digitalWrite(lock,HIGH);
 
    }
    else
    {


 digitalWrite(lock,LOW);

    }


    
  }



if (ldrStatus1 <= 200 && bookState1 == 0) {

bookState1++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken1); 
Serial.print("Darkness over here,turn on the LED : ");

Serial.println(ldrStatus1);

} else if(ldrStatus1 >= 200 && bookState1 == 1){

bookState1 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return1); 
Serial.print("There is sufficeint light , turn off the LED : ");

Serial.println(ldrStatus1);

}


if (ldrStatus2 <= 200 && bookState2 == 0) {

bookState2++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken2); 

} else if(ldrStatus2 >= 200 && bookState2 == 1){

bookState2 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return2); 

}


if (ldrStatus3 <= 200 && bookState3 == 0) {

bookState3++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken3); 

} else if(ldrStatus3 >= 200 && bookState3 == 1){

bookState3 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return3); 

}


if (ldrStatus4 <= 200 && bookState4 == 0) {

bookState4++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken4); 

} else if(ldrStatus4 >= 200 && bookState4 == 1){

bookState4 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return4); 

}


if (ldrStatus5 <= 200 && bookState5 == 0) {

bookState5++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken5); 

} else if(ldrStatus5 >= 200 && bookState5 == 1){

bookState5 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return5); 

}


if (ldrStatus6 <= 200 && bookState6 == 0) {

bookState6++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken6); 

} else if(ldrStatus6 >= 200 && bookState6 == 1){

bookState6 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return6); 

}


if (ldrStatus7 <= 200 && bookState7 == 0) {

bookState7++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken7); 

} else if(ldrStatus7 >= 200 && bookState5 == 7){

bookState7 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return7); 

}


if (ldrStatus8 <= 200 && bookState8 == 0) {

bookState8++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken8); 

} else if(ldrStatus8 >= 200 && bookState8 == 1){

bookState8 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return8); 

}


if (ldrStatus9 <= 200 && bookState9 == 0) {

bookState9++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken9); 

} else if(ldrStatus9 >= 200 && bookState9 == 1){

bookState9 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return9); 

}


if (ldrStatus10 <= 200 && bookState10 == 0) {

bookState10++;
 sim808.sendSMS(PHONE_NUMBER,Book_Taken10); 

} else if(ldrStatus10 >= 200 && bookState10 == 1){

bookState10 = 0; 
 sim808.sendSMS(PHONE_NUMBER,Book_Return10); 

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
