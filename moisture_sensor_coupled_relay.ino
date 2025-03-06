const int sensorPin = A0;  // Analog pin connected to soil moisture sensor
const int relayPin = 8;    // Digital pin connected to relay control pin
const int threshold = 800; // Moisture level threshold (adjust based on your sensor)

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  delay(1000);
}

void loop() {
  delay(2000);
  int sensorValue = analogRead(sensorPin);

  // Check if soil moisture is below threshold (wet)
  if (sensorValue > threshold) {
    digitalWrite(relayPin, LOW); // Deactivate relay (turn off connected device)
    Serial.println("Soil is wet, deactivating relay.");
  } else {
    digitalWrite(relayPin, HIGH); // activate relay (turn on connected device)
    Serial.println("Soil is dry, activating relay.");
  }

  delay(2000); // Delay between readings (adjust as needed)
}