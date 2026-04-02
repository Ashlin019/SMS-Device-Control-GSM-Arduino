#include <SoftwareSerial.h>

#define SIM900_RX 8
#define SIM900_TX 7
#define LED_PIN 6

SoftwareSerial sim900(SIM900_RX, SIM900_TX); // RX, TX
String smsBuffer = "";

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  sim900.begin(9600);
  delay(1000);

  Serial.println("Initializing SIM900A...");

  sim900.println("AT");
  delay(1000);
  sim900.println("AT+CMGF=1");
  delay(1000);
  sim900.println("AT+CSCS=\"GSM\"");
  delay(1000);
  sim900.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  sim900.println("AT+CMGD=1,4");
  delay(1000);

  Serial.println("✅ SIM900A is ready. Send SMS: ON or OFF");
}

void loop() {
  while (sim900.available()) {
    char c = sim900.read();
    smsBuffer += c;
    Serial.write(c);

    // Check message content
    if (smsBuffer.indexOf("ON") != -1 || smsBuffer.indexOf("on") != -1) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("✅ LED turned ON");
      smsBuffer = "";
    }
    else if (smsBuffer.indexOf("OFF") != -1 || smsBuffer.indexOf("off") != -1) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("✅ LED turned OFF");
      smsBuffer = "";
    }

    if (smsBuffer.length() > 200) {
      smsBuffer = ""; // Clear junk
    }
  }
}
