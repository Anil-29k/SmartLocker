//#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
int in = 3;


#define RST_PIN 7   //D1 // Connect RST_PIN of RFID to D1
#define SDA_PIN 10  //D2 // Connect SDA_PIN of RFID to D2


MFRC522 rfid(SDA_PIN, RST_PIN);  // Create MFRC522 instance


void setup() {
  pinMode(in, OUTPUT);
  digitalWrite(in, HIGH);
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Init SPI bus
  rfid.PCD_Init();     // Init MFRC522
  Serial.println("RFID Ready");
}


void loop() {
  // Look for new cards
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("UID tag :");
    String content = "";


    // Read UID
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(rfid.uid.uidByte[i], HEX);
      content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfid.uid.uidByte[i], HEX));
    }


    Serial.println();
    //Serial.print("Message : ");
    content.toUpperCase(); 
    //Serial.println(content);


    if (content.substring(1) == "10 BF 22 2F") {
      Serial.println("ASSces Granted");
      delay(200);
      digitalWrite(in, LOW);
      delay(5000);
      digitalWrite(in, HIGH);
    } else {
      Serial.println("Assces Dinied");
      delay(1000);  
    }
  }
}
