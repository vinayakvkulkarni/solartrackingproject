#include <Servo.h>

// Define servo object
Servo myservo;

// Define pins
int servoPin = 9;  // Digital pin for the servo motor

// Define constants and variables
const int LDR1Pin = A0;      // LDR 1 for tracking (facing front)
const int LDR2Pin = A1;      // LDR 2 for tracking (facing back)
const int thresholdTrack = 100; // Light intensity difference threshold for tracking (adjust as needed)
int centerPos = 90;        // Center position of the servo (adjust based on your servo's range)

void setup() {
  // Attach servo object to the pin
  myservo.attach(servoPin);

  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Read LDR values
  int ldr1Value = analogRead(LDR1Pin);
  int ldr2Value = analogRead(LDR2Pin);

  // Calculate difference in light readings
  int lightDiff = abs(ldr1Value - ldr2Value);

  // If the difference is below the threshold, assume panel is facing the sun.
  // Otherwise, adjust the servo position to minimize light difference.
  if (lightDiff < thresholdTrack) {
    Serial.println("Panel facing sun (light difference < threshold)");
  } else {
    if (ldr1Value > ldr2Value) { // LDR 1 detects more light, turn right
      myservo.write(++centerPos);
      Serial.println("Turning right (LDR 1 brighter)");
    } else if (ldr1Value < ldr2Value) { // LDR 2 detects more light, turn left
      myservo.write(--centerPos);
      Serial.println("Turning left (LDR 2 brighter)");
    }

    // Restrict servo movement to its valid range
    centerPos = constrain(centerPos, 0, 180);

    // Send the adjusted position to the servo
    myservo.write(centerPos);
  }

  // Delay between readings and adjustments
  delay(80); // Adjust delay as needed
}