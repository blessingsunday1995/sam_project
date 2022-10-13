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

int setValue = 270;
int setValue2 = 100;


MFRC522 mfrc522(9, 8); // MFRC522 mfrc522(SS_PIN, RST_PIN)




char initial_password[4] = {'1', '2', '3', '4'};  // Variable to store initial password
String tagUID =  "77 8F D5 A6";  // String to store UID of tag. Change it with your tag's UID
char password[4];   // Variable to store users password
boolean RFIDMode = true; // boolean to change modes
boolean NormalMode = true; // boolean to change modes
char key_pressed = 0; // Variable to store incoming keys
uint8_t i = 0;  // Variable used for counter

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
#define PHONE_NUMBER "07060580015"






#define Book_Taken1 "A Book is taken from shelf 1"
#define Book_Return1 "A Book have been return to shelf 1"

const int ldrPin1 = A0;   // analog pin 0



int bookState1 = 0;




#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX, PIN_RX);
DFRobot_SIM808 sim808(&mySerial);  //Connect RX,TX,PWR,


void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

  // Initiating
  SPI.begin();         // SPI bus
  mfrc522.PCD_Init();  // MFRC522
  // Here LDR sensor is determined as input.
  pinMode(ldrPin1, INPUT);


  pinMode(lock1, OUTPUT);
  pinMode(lock2, OUTPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);



  //******** Initialize sim808 module *************
  // while (!sim808.init()) {
  //   delay(1000);
  //   Serial.print("Sim808 init error\r\n");
  //   digitalWrite(redLed, HIGH);
  // }
  // Serial.println("Sim808 init success");
  // digitalWrite(redLed, LOW);


  //******** define phone number and text **********
}

void loop() {
  //nothing to do
  int ldrStatus1 = analogRead(ldrPin1);



// System will first look for mode
  if (NormalMode == true) {
    
    // System will first look for mode
    if (RFIDMode == true) {
      // Function to receive message

 

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
        Serial.println("Tag mached. ");
        Serial.println("Enter Password");
      
          digitalWrite(greenLed, HIGH);
        delay(1000);
         digitalWrite(greenLed, LOW);
 
        RFIDMode = false; // Make RFID mode false
      }
      else
      {
        Serial.print("Wrong Tag Shown");
        Serial.println("  Access Denied ");
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
          Serial.print("Password Accepted");
         
         digitalWrite(greenLed, HIGH);

         digitalWrite(lock1, HIGH);
          digitalWrite(lock2, HIGH);
      delay(3000);
      digitalWrite(greenLed, LOW);
       digitalWrite(lock2, LOW);
        digitalWrite(lock1, LOW);
          
          
      
          i = 0;
          RFIDMode = true; // Make RFID mode true
        }
        else    // If password is not matched
        {
          Serial.println("Wrong Password");
              
        
      digitalWrite(redLed, HIGH);
    
      delay(3000);
      digitalWrite(redLed, LOW);
     
          
  
          i = 0;
          RFIDMode = true;  // Make RFID mode true
        }
         
         
     
      }
    }
  }





  // if (ldrStatus1 >= setValue && bookState1 == 0) {

  //   bookState1++;
  //   sim808.sendSMS(PHONE_NUMBER, Book_Taken1);
  //   Serial.print("Darkness over here,turn on the LED : ");

  //   Serial.println(ldrStatus1);

  // } else if (ldrStatus1 <= setValue2 && bookState1 == 1) {

  //   bookState1 = 0;
  //   sim808.sendSMS(PHONE_NUMBER, Book_Return1);
  //   Serial.print("There is sufficeint light , turn off the LED : ");

  //   Serial.println(ldrStatus1);
  // }

}
