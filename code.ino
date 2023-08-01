#include <GSMSim.h>

#define RX 7
#define TX 8
#define RESET 2
#define BAUD 9600

int sensorPin = A0; //pin for moisture sensor
int moistureMin = 630; //minimum level of moisture required in soil
int pumpPin = 6; //pin for water pump
int waterPin = A2; //pin for water level sensor
int minwaterLevel = 440; //minimum water level required in resevoir
int waterIndicator = 8; //pin for water level indicator
int minLight = 350; //min light level
GSMSim gsm;

/*
 * Also you can this types:
 * GSMSim gsm(RX, TX);
 * GSMSim gsm(RX, TX, RESET);
 * GSMSim gsm(RX, TX, RESET, LED_PIN, LED_FLAG);
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT); //sets pump as an output
  pinMode(sensorPin, INPUT); //sets moisture sensor as input
  pinMode(waterPin, INPUT); //sets water level sensor as input
  Serial.println("GSMSim Library - SMS Example");
  Serial.println("");
  delay(1000);

  gsm.start(); // baud default 9600
  //gsm.start(BAUD);

  Serial.println("Changing to text mode.");
  gsm.smsTextMode(true); // TEXT or PDU mode. TEXT is readable :)

  char * number = "+353858450807";
  char * message = "Garduino turned on!"; // message lenght must be <= 160. Only english characters.

  Serial.println("Sending Message --->");
  Serial.println(gsm.smsSend(number, message)); // if success it returns true (1) else false (0)
  delay(2000);

  Serial.println("Listing unread message(s).");
  Serial.println(gsm.smsListUnread()); // if not unread messages have it returns "NO_SMS"

  Serial.println("Read SMS on index no = 1");
  Serial.println(gsm.smsRead(1)); // if no message in that index, it returns IXDEX_NO_ERROR

}

void loop() {
  // put your main code here, to run repeatedly:
  int soilMoisture = analogRead(sensorPin); //reading from moisture sensor
  int waterLevel = analogRead(waterPin); //reads water level
  int lightLevel = analogRead(A1); //reads water level

  Serial.print("Soil Moisture: \t");
  Serial.println(soilMoisture);

  Serial.print("Water Level: \t");
  Serial.println(waterLevel);

  Serial.print("Light Level: \t");
  Serial.println(lightLevel);
  delay(100);

  if (soilMoisture > moistureMin) //to turn on pump if moisture too low
  {
    digitalWrite(6, HIGH);
    delay(400);
  } else //turns off pump when moisture level reached
  {
    digitalWrite(6, LOW);
  }

  if (waterLevel < minwaterLevel) //sends text + illuminates LED if water too low
  {
    digitalWrite(8, HIGH);
    Serial.println("GSMSim Library - SMS Example");
    Serial.println("");
    delay(1000);

    gsm.start(); // baud default 9600
    //gsm.start(BAUD);

    Serial.println("Changing to text mode.");
    gsm.smsTextMode(true); // TEXT or PDU mode. TEXT is readable :)

    char * number = "+353858450807";
    char * message = "Water is getting low!"; // message lenght must be <= 160. Only english characters.

    Serial.println("Sending Message --->");
    Serial.println(gsm.smsSend(number, message)); // if success it returns true (1) else false (0)
    delay(2000);

    Serial.println("Listing unread message(s).");
    Serial.println(gsm.smsListUnread()); // if not unread messages have it returns "NO_SMS"

    Serial.println("Read SMS on index no = 1");
    Serial.println(gsm.smsRead(1)); // if no message in that index, it returns IXDEX_NO_ERROR

  } else if (lightLevel < minLight) //sends text if light too low
  {
    Serial.println("GSMSim Library - SMS Example");
    Serial.println("");
    delay(1000);

    gsm.start(); // baud default 9600
    //gsm.start(BAUD);

    Serial.println("Changing to text mode.");
    gsm.smsTextMode(true); // TEXT or PDU mode. TEXT is readable :)

    char * number = "+353858450807";
    char * message = "Plant is not getting enough light!"; // message lenght must be <= 160. Only english characters.

    Serial.println("Sending Message --->");
    Serial.println(gsm.smsSend(number, message)); // if success it returns true (1) else false (0)
    delay(2000);

    Serial.println("Listing unread message(s).");
    Serial.println(gsm.smsListUnread()); // if not unread messages have it returns "NO_SMS"

    Serial.println("Read SMS on index no = 1");
    Serial.println(gsm.smsRead(1)); // if no message in that index, it returns IXDEX_NO_ERROR

  } else {
    digitalWrite(8, LOW);
  }

  delay(1000);

}
