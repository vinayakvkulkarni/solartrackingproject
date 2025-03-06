#include <Servo.h>

// Define servo objects
Servo servo1;
Servo servo2;

// Define pins for servo motors
int servoPin1 = 10;
int servoPin2 = 9;

// Define pin for LDR sensor
int ldrPin = A0; // Change this to the analog pin connected to your LDR sensor
const int sensorPin = A1;  // Analog pin connected to soil moisture sensor
const int relayPin = 8;    // Digital pin connected to relay control pin
const int threshold = 800; // Moisture level threshold (adjust based on your sensor)
void setup() {
  // Attach servo objects to the respective pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Initialize servo positions
  servo1.write(0); // Change the angle as per your requirement
  servo2.write(180); // Change the angle as per your requirement
  
  // Wait for setup
  delay(30);
   pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  delay(10);

}
void loop() {
  delay(50);
  // Read the analog value from the LDR sensor
  int ldrValue = analogRead(ldrPin);

  while (analogRead(ldrPin) <= 100) {
      // Do nothing until light level increases
  }
  ldrValue = analogRead(ldrPin);
  delay(200);
  
  if (ldrValue > 100) { // Adjust this threshold value based on your environment
    // Light level is high, proceed with servo movements
    delay(2000);
    // Rotate servo1 to 180 degrees
    for (int angle = 0; angle <= 180; angle++) {
      servo1.write(angle);
      delay(20); // Adjust speed of rotation
    }

    delay(200); // Delay for 2 seconds

    // Rotate servo2 to 180 degrees
    for (int angle = 180; angle >= 0; angle--) {
      servo2.write(angle);
      delay(20); // Adjust speed of rotation
    }
    delay(200);
  
  int sensorValue = analogRead(sensorPin);

  // Check if soil moisture is below threshold (wet)
  if (sensorValue < threshold) {
    digitalWrite(relayPin, LOW); // Deactivate relay (turn off connected device)
    Serial.println("Soil is wet, deactivating relay.");
  } else {
    digitalWrite(relayPin, HIGH); // activate relay (turn on connected device)
    Serial.println("Soil is dry, activating relay.");
  }

  delay(2000); // Delay between readings (adjust as needed)

  }
}