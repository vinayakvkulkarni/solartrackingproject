#include <Servo.h>

// Define servo objects for tracking and opening/closing
Servo myservoTrack;
Servo servo1OpenClose;
Servo servo2OpenClose;

// Define pins
int servoPinTrack = 8;           // Digital pin for tracking servo
int servoPin1OpenClose = 10;     // Digital pin for opening/closing servo 1  
int servoPin2OpenClose = 9;      // Digital pin for opening/closing servo 2

// Define constants and variables
const int LDR1Pin = A0;       
   // LDR 1 for tracking (facing front)
const int LDR2Pin = A1;          // LDR 2 for tracking (facing back)
const int ldrOpenClosePin = A2;  // LDR for opening/closing
const int thresholdTrack = 50;   // Light intensity difference threshold for tracking
const int thresholdOpenClose = 50; // Light intensity threshold for opening/closing panels
const int initialTrackingPosition = 90; // Initial position for tracking servo

// Initial positions for opening/closing panels
int initialServo1Angle = 0;
int initialServo2Angle = 180;

// State variables
bool panelsAreOpen = false;
bool servoReturned = false;

void setup() {
  // Attach tracking servo
  myservoTrack.attach(servoPinTrack);

  // Attach opening/closing servos
  servo1OpenClose.attach(servoPin1OpenClose);
  servo2OpenClose.attach(servoPin2OpenClose);
  
  // Initialize initial positions
  myservoTrack.write(initialTrackingPosition);
  servo1OpenClose.write(initialServo1Angle);
  servo2OpenClose.write(initialServo2Angle);

  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Check light level for opening panels
  int ldrValueOpenClose = analogRead(ldrOpenClosePin);
  
  // Open panels if light level is high and panels are not open
  if (ldrValueOpenClose > thresholdOpenClose && !panelsAreOpen) {
    Serial.println("Light level high, opening panels");
    openPanels();
    panelsAreOpen = true;
    servoReturned = false;
  }

  // Track sun if panels are open
  if (panelsAreOpen) {
    trackSun();
    ldrValueOpenClose = analogRead(ldrOpenClosePin); // Update light level for opening/closing
    if (ldrValueOpenClose <= thresholdOpenClose) {
      Serial.println("Light level low, returning to initial positions");
      returnTrackingServo(); // Return tracking servo first
      delay(1000); // Ensure tracking servo has enough time to return
      servoReturned = true;
    }
  }

  // Close panels if tracking servo has returned and panels are open
  if (servoReturned && panelsAreOpen) {
    closePanels();
    panelsAreOpen = false;
    Serial.println("Panels closed");
  }

  delay(50); // Adjust delay between checks (optional)
}

void trackSun() {
  int ldr1Value = analogRead(LDR1Pin);
  int ldr2Value = analogRead(LDR2Pin);

  // Calculate difference in light readings
  int lightDiff = ldr1Value - ldr2Value;

  // If the difference is below the threshold, assume panel is facing the sun.
  // Otherwise, adjust the servo position to minimize light difference.
  if (abs(lightDiff) < thresholdTrack) {
    Serial.println("Panel facing sun (light difference < threshold)");
  } else {
    int step = (lightDiff > 0) ? 1 : -1; // Determine direction based on light difference
    int currentPos = myservoTrack.read();
    int newPos = constrain(currentPos + step, 30, 150);

    // Send the adjusted position to the servo
    myservoTrack.write(newPos);
    delay(60); // Increased delay for slower and smoother movement
  }

  // Delay between readings and adjustments
  delay(200); // Adjust delay as needed
}

void openPanels() {
  // Open panels using servo1 and servo2
  for (int angle = initialServo1Angle; angle <= 180; angle++) {
    servo1OpenClose.write(angle);
    delay(30); // Slow down the speed of rotation
  }

  delay(200); // Delay for 2 seconds

  // Rotate servo2 to 0 degrees
  for (int angle = initialServo2Angle; angle >= 0; angle--) {
    servo2OpenClose.write(angle);
    delay(30); // Slow down the speed of rotation
  }
  delay(200); // Delay after opening
}

void closePanels() {
  // Close panels using servo1 and servo2
  for (int angle = 0; angle <= 180; angle++) {
    servo2OpenClose.write(angle);
    delay(30); // Slow down the speed of rotation
  }
  delay(200); // Delay for 2 seconds

  // Rotate servo1 back to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    servo1OpenClose.write(angle);
    delay(30); // Slow down the speed of rotation
  }
  delay(200);
}

void returnTrackingServo() {
  // Return tracking servo to initial position
  int currentPos = myservoTrack.read();
  Serial.print("Returning tracking servo from ");
  Serial.print(currentPos);
  Serial.println(" to initial position (90)");

  if (currentPos != initialTrackingPosition) {
    int step = (initialTrackingPosition > currentPos) ? 1 : -1; // Determine the direction of movement
    while (currentPos != initialTrackingPosition) {
      currentPos += step;
      myservoTrack.write(currentPos);
      delay(30); // Delay for smoother movement
      Serial.print("Current position: ");
      Serial.println(currentPos);
    }
  }
  Serial.println("Tracking servo returned to initial position");
}
