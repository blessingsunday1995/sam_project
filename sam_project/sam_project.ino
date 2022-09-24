#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>


#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Keypad.h>

int greenLed = 14;
int redLed = 15;
// int errorLed = 16; 



int lock1 = 18;
int lock2 = 19;

int setValue = 200;


MFRC522 mfrc522(9, 8); // MFRC522 mfrc522(SS_PIN, RST_PIN)
// #define RST_PIN 8
// #define SS_PIN 9


byte readCard[4];
String tagUID = "77 8F D5 A6";  // REPLACE this Tag ID with your Tag ID!!!
String tagID = "";
boolean RFIDMode = true; // boolean to change modes
char initial_password[4] = {'1', '2', '3', '4'};  // Variable to store initial password
char password[4];                                   // Variable to store users password
char key_pressed = 0;                               // Variable to store incoming keys
uint8_t i = 0;                                      // Variable used for counter


// defining how many rows and columns our keypad have
const byte rows = 4;
const byte columns = 4;

// Keypad pin map
char hexaKeys[rows][columns] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Initializing pins for keypad
byte row_pins[rows] = { 7, 6, 5, 4 };
byte column_pins[columns] = { 20, 21, 23, 22 };


// Create instance for keypad
Keypad keypad_key = Keypad(makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

//Mobile phone number,need to change
#define PHONE_NUMBER "08131971666"






#define Book_Taken1 "A Book is taken from shelf 1"
#define Book_Return1 "A Book have been return to shelf 1"

#define Book_Taken2 "A Book is taken from shelf 2"
#define Book_Return2 "A Book have been return to shelf 2"

#define Book_Taken3 "A Book is taken from shelf 3"
#define Book_Return3 "A Book have been return to shelf 3"

#define Book_Taken4 "A Book is taken from shelf 4"
#define Book_Return4 "A Book have been return to shelf 4"

#define Book_Taken5 "A Book is taken from shelf 5"
#define Book_Return5 "A Book have been return to shelf 5"

#define Book_Taken6 "A Book is taken from shelf 6"
#define Book_Return6 "A Book have been return to shelf 6"

#define Book_Taken7 "A Book is taken from shelf 7"
#define Book_Return7 "A Book have been return to shelf 7"

#define Book_Taken8 "A Book is taken from shelf 8"
#define Book_Return8 "A Book have been return to shelf 8"

#define Book_Taken9 "A Book is taken from shelf 9"
#define Book_Return9 "A Book have been return to shelf 9"

#define Book_Taken10 "A Book is taken from shelf 10"
#define Book_Return10 "A Book have been return to shelf 10"

#define Book_Taken11 "A Book is taken from shelf 11"
#define Book_Return11 "A Book have been return to shelf 11"

#define Book_Taken12 "A Book is taken from shelf 12"
#define Book_Return12 "A Book have been return to shelf 12"

#define Book_Taken13 "A Book is taken from shelf 13"
#define Book_Return13 "A Book have been return to shelf 13"

#define Book_Taken14 "A Book is taken from shelf 14"
#define Book_Return14 "A Book have been return to shelf 14"

#define Book_Taken15 "A Book is taken from shelf 15"
#define Book_Return15 "A Book have been return to shelf 15"

const int ldrPin1 = A0;   // analog pin 0
const int ldrPin2 = A1;   // analog pin 0
const int ldrPin3 = A2;   // analog pin 0
const int ldrPin4 = A3;   // analog pin 0
const int ldrPin5 = A4;   // analog pin 0
const int ldrPin6 = A5;   // analog pin 0
const int ldrPin7 = A6;   // analog pin 0
const int ldrPin8 = A7;   // analog pin 0
const int ldrPin9 = A8;   // analog pin 0
const int ldrPin10 = A9;  // analog pin 0


int bookState1 = 0;
int bookState2 = 0;
int bookState3 = 0;
int bookState4 = 0;
int bookState5 = 0;
int bookState6 = 0;
int bookState7 = 0;
int bookState8 = 0;
int bookState9 = 0;
int bookState10 = 0;



#define PIN_TX 16
#define PIN_RX 3
SoftwareSerial mySerial(PIN_TX, PIN_RX);
DFRobot_SIM808 sim808(&mySerial);  //Connect RX,TX,PWR,

// Create instances
//MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

  // Initiating
  SPI.begin();         // SPI bus
  //mfrc522.PCD_Init();  // MFRC522
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

  pinMode(lock1, OUTPUT);
  pinMode(lock2, OUTPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  // pinMode(errorLed, OUTPUT);


  //******** Initialize sim808 module *************
  while (!sim808.init()) {
    delay(1000);
    Serial.print("Sim808 init error\r\n");
    digitalWrite(redLed, HIGH);
  }
  Serial.println("Sim808 init success");
  digitalWrite(redLed, LOW);


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

  Serial.println("worling");

// System will first look for mode
  if (RFIDMode == true) {
  

    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    //Reading from the card
    String tag = "";
    for (byte j = 0; j < mfrc522.uid.size; j++)
    {
      tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
      tag.concat(String(mfrc522.uid.uidByte[j], HEX));
    }
    tag.toUpperCase();

    //Checking the card
    if (tag.substring(1) == tagUID)
    {
      // If UID of tag is matched.
     
      digitalWrite(greenLed, HIGH);
      delay(500);
      digitalWrite(greenLed, LOW);

      RFIDMode = false; // Make RFID mode false
    }

    else
    {
      // If UID of tag is not matched.
  
      digitalWrite(redLed, HIGH);
      delay(3000);
      digitalWrite(redLed, LOW);
     
    }
  }

  // If RFID mode is false, it will look for keys from keypad
  if (RFIDMode == false) {
    key_pressed = keypad_key.getKey(); // Storing keys
    if (key_pressed)
    {
      password[i++] = key_pressed; // Storing in password variable
    
    }
    if (i == 4) // If 4 keys are completed
    {
      delay(200);
      if (!(strncmp(password, initial_password, 4))) // If password is matched
      {
     
       
        digitalWrite(lock1,HIGH); // Door Opened
        digitalWrite(lock2, HIGH);
        digitalWrite(greenLed, HIGH);
        delay(3000);
        digitalWrite(lock1,LOW);
        digitalWrite(lock2,LOW);
        digitalWrite(greenLed, LOW);
       // sg90.write(0); // Door Closed
  
        i = 0;
        RFIDMode = true; // Make RFID mode true
      }
      else    // If password is not matched
      {
    
        digitalWrite(redLed, HIGH);
        delay(3000);
        digitalWrite(redLed, LOW);
        i = 0;
        RFIDMode = true;  // Make RFID mode true
      }
    }
  }





  if (ldrStatus1 <= setValue && bookState1 == 0) {

    bookState1++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken1);
    Serial.print("Darkness over here,turn on the LED : ");

    Serial.println(ldrStatus1);

  } else if (ldrStatus1 >= setValue && bookState1 == 1) {

    bookState1 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return1);
    Serial.print("There is sufficeint light , turn off the LED : ");

    Serial.println(ldrStatus1);
  }


  if (ldrStatus2 <= setValue && bookState2 == 0) {

    bookState2++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken2);

  } else if (ldrStatus2 >= setValue && bookState2 == 1) {

    bookState2 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return2);
  }


  if (ldrStatus3 <= setValue && bookState3 == 0) {

    bookState3++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken3);

  } else if (ldrStatus3 >= setValue && bookState3 == 1) {

    bookState3 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return3);
  }


  if (ldrStatus4 <= setValue && bookState4 == 0) {

    bookState4++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken4);

  } else if (ldrStatus4 >= setValue && bookState4 == 1) {

    bookState4 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return4);
  }


  if (ldrStatus5 <= setValue && bookState5 == 0) {

    bookState5++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken5);

  } else if (ldrStatus5 >= setValue && bookState5 == 1) {

    bookState5 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return5);
  }


  if (ldrStatus6 <= setValue && bookState6 == 0) {

    bookState6++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken6);

  } else if (ldrStatus6 >= setValue && bookState6 == 1) {

    bookState6 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return6);
  }


  if (ldrStatus7 <= setValue && bookState7 == 0) {

    bookState7++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken7);

  } else if (ldrStatus7 >= setValue && bookState5 == 7) {

    bookState7 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return7);
  }


  if (ldrStatus8 <= setValue && bookState8 == 0) {

    bookState8++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken8);

  } else if (ldrStatus8 >= setValue && bookState8 == 1) {

    bookState8 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return8);
  }


  if (ldrStatus9 <= setValue && bookState9 == 0) {

    bookState9++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken9);

  } else if (ldrStatus9 >= setValue && bookState9 == 1) {

    bookState9 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return9);
  }


  if (ldrStatus10 <= setValue && bookState10 == 0) {

    bookState10++;
    sim808.sendSMS(PHONE_NUMBER, Book_Taken10);

  } else if (ldrStatus10 >= setValue && bookState10 == 1) {

    bookState10 = 0;
    sim808.sendSMS(PHONE_NUMBER, Book_Return10);
  }
}
