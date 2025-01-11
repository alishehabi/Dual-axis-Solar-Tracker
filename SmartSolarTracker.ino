#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Adafruit_INA219.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD with I2C address 0x27 and dimensions 16x2
Adafruit_INA219 ina219(0x40);       // Initialize INA219 current sensor

Servo azServo;  // Servo object for azimuth control
Servo tiltServo; // Servo object for tilt control

// Pin definitions for LDR sensors and servos
const byte EAST_PIN = A0;
const byte WEST_PIN = A1;
const byte NORTH_PIN = A2;
const byte SOUTH_PIN = A3;
const byte AZIMUTH_PIN = 9;
const byte TILT_PIN = 10;

int azAngle = 90;   // Initial azimuth angle (degrees)
int tiltAngle = 20; // Initial tilt angle (degrees)
float solarV, solarC, solarP; // Variables for INA219 measurements

int ewDiff; // Difference between east and west LDR readings
int nsDiff; // Difference between north and south LDR readings
int valEast, valWest, valNorth, valSouth; // LDR analog values
float voltageEast, voltageWest, voltageNorth, voltageSouth;

byte TOLERANCE = 12;          // Margin of error for LDR differences
const byte STEP = 1;          // Step size for servo angle adjustments (degrees)
const byte SAMPLES = 20;      // Number of samples for averaging LDR readings

const float avc = 5.0 / 1024.0; // Define the analog to voltage conversion factor

// Constants for servo angle limits
const byte MIN_AZ_ANGLE = 0;
const byte MAX_AZ_ANGLE = 180;
const byte MIN_TILT_ANGLE = 5;
const byte MAX_TILT_ANGLE = 90;

void setup() {

  Serial.begin(9600); // Initialize serial communication
  Wire.begin();       // Initialize I2C communication

  lcd.init();         // Initialize LCD
  lcd.backlight();    // Turn on LCD backlight

  // Initialize INA219 current sensor with retry mechanism
  if (!ina219.begin()) {
    lcd.print(F("INA219 error!")); // Display error message
    delay(5000);                   // Display message for 5 seconds
  }
  
  azServo.attach(AZIMUTH_PIN); // Attach azimuth servo to pin 9
  tiltServo.attach(TILT_PIN);  // Attach tilt servo to pin 10

  azServo.write(azAngle);   // Set initial azimuth servo position
  delay(500);               // Wait for 0.5 seconds
  tiltServo.write(tiltAngle); // Set initial tilt servo position
  delay(500);               // Wait for 0.5 seconds
}

void loop() {
  readLDR();   // Read LDR values and calculate differences
  adjustServo(azServo, azAngle, ewDiff, MIN_AZ_ANGLE, MAX_AZ_ANGLE); // Adjust azimuth servo
  adjustServo(tiltServo, tiltAngle, nsDiff, MIN_TILT_ANGLE, MAX_TILT_ANGLE); // Adjust tilt servo
  readSolar();  // Read power output from INA219 sensor
  displayLCD(); // Display voltage, current, and power on LCD
  logData();    // Log data for analysis
}

/*** READ LDR VALUES AND CALCULATE DIFFERENCES ***/
void readLDR() {

    long eastSum = 0, westSum = 0, northSum = 0, southSum = 0;

    for (int i = 0; i < SAMPLES; i++) {
        eastSum += analogRead(EAST_PIN);  // Sum east LDR readings
        westSum += analogRead(WEST_PIN);  // Sum west LDR readings
        northSum += analogRead(NORTH_PIN); // Sum north LDR readings
        southSum += analogRead(SOUTH_PIN); // Sum south LDR readings
        delay(5);  // Small delay between readings
    }

    valEast = eastSum / SAMPLES;   // Average east LDR readings
    valWest = westSum / SAMPLES;   // Average west LDR readings
    valNorth = northSum / SAMPLES; // Average north LDR readings
    valSouth = southSum / SAMPLES; // Average south LDR readings

    voltageEast = valEast * avc;   // Convert east LDR reading to voltage
    voltageWest = valWest * avc;   // Convert west LDR reading to voltage
    voltageNorth = valNorth * avc; // Convert north LDR reading to voltage
    voltageSouth = valSouth * avc; // Convert south LDR reading to voltage

    ewDiff = valEast - valWest;  // Calculate east-west difference
    nsDiff = valNorth - valSouth; // Calculate north-south difference

    int avgLight = (valEast + valWest + valNorth + valSouth) / 4; // Calculate average light intensity
    TOLERANCE = map(avgLight, 0, 1024, 5, 20); // Adjust tolerance based on light intensity
}

/*** ADJUST SERVO BASED ON LDR DIFFERENCES ***/
void adjustServo(Servo &servo, int &angle, int diff, int minAngle, int maxAngle) {
  int targetAngle = angle;

  // If the difference is greater than the tolerance, adjust the servo position
  if (diff > TOLERANCE && angle < maxAngle) {
    targetAngle = min(maxAngle, angle + STEP); // Move towards higher light intensity
  } 
  else if (diff < -TOLERANCE && angle > minAngle) {
    targetAngle = max(minAngle, angle - STEP); // Move towards higher light intensity
  }

  // If the target angle is different from the current angle, move the servo
  if (targetAngle != angle) {
    moveServoSmoothly(servo, angle, targetAngle); // Smoothly move the servo to the new angle
    angle = targetAngle; // Update current angle
  }
}

/*** SMOOTHLY MOVE SERVO TO TARGET ANGLE ***/
void moveServoSmoothly(Servo &servo, int currentAngle, int targetAngle) {
  int increment = (targetAngle > currentAngle) ? 1 : -1;

  for (int angle = currentAngle; angle != targetAngle; angle += increment) {
    servo.write(angle);
    delay(15); // Adjust delay for smoother/faster movement
  }
  servo.write(targetAngle); // Ensure final position is reached
}

/*** READ SOLAR PANEL VOLTAGE, CURRENT, AND POWER ***/
void readSolar() {
  float voltageSum = 0, currentSum = 0;

  // Take multiple readings and average them to reduce noise
  for (int i = 0; i < SAMPLES; i++) {
    voltageSum += ina219.getBusVoltage_V(); // Sum voltage readings
    currentSum += ina219.getCurrent_mA();   // Sum current readings
    delay(10);  // Small delay between readings
  }

  solarV = voltageSum / SAMPLES;         // Calculate average voltage
  solarC = (currentSum / SAMPLES) / 1000; // Calculate average current and convert to Amps

  solarP = solarV * solarC; // Calculate power in Watts
}

/*** DISPLAY VOLTAGE, CURRENT, AND POWER ON LCD ***/
void displayLCD() {
  // Convert voltage, current, and power to strings
  char voltageStr[7];
  char currentStr[7];
  char powerStr[7];
  dtostrf(solarV, -4, 1, voltageStr);  // Convert voltage to string
  dtostrf(solarC, -6, 2, currentStr);  // Convert current to string with 2 decimal places
  dtostrf(solarP, -6, 3, powerStr);    // Convert power to string

  lcd.clear();  // Clear LCD
  lcd.setCursor(0, 0);  // Set cursor to beginning
  
  // Display voltage and current on the first line
  lcd.print(F("V:"));
  lcd.setCursor(2, 0);
  lcd.print(voltageStr);
  lcd.setCursor(8, 0);
  lcd.print(F("C:"));
  lcd.setCursor(10, 0);
  lcd.print(currentStr);

  // Display power on the second line
  lcd.setCursor(0, 1);
  lcd.print(F("P:"));
  lcd.setCursor(2, 1);
  lcd.print(powerStr);
}

/*** LOG DATA FOR ANALYSIS ***/
void logData() {

  Serial.print(F("Time: ")); Serial.print(millis());
  
  Serial.print(F(", LDR East - Voltage: ")); Serial.print(voltageEast, 2); Serial.print(F(" V / Analog: ")); Serial.print(valEast);
  Serial.print(F(", LDR West - Voltage: ")); Serial.print(voltageWest, 2); Serial.print(F(" V / Analog: ")); Serial.print(valWest);
  Serial.print(F(", LDR North - Voltage: ")); Serial.print(voltageNorth, 2); Serial.print(F(" V / Analog: ")); Serial.print(valNorth);
  Serial.print(F(", LDR South - Voltage: ")); Serial.print(voltageSouth, 2); Serial.print(F(" V / Analog: ")); Serial.print(valSouth);

  Serial.print(F(", E-W Diff: ")); Serial.print(ewDiff);
  Serial.print(F(", N-S Diff: ")); Serial.println(nsDiff);

  Serial.print(F(", Solar Voltage: ")); Serial.print(solarV); Serial.print(F(" V"));
  Serial.print(F(", Solar Current: ")); Serial.print(solarC); Serial.print(F(" A"));
  Serial.print(F(", Solar Power: ")); Serial.print(solarP); Serial.print(F(" W"));
  delay(2000);
}