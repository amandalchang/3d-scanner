// Import Libraries
#include <Servo.h>

// Pin Defs
const int PAN_SERVO = 11;
const int TILT_SERVO = 12;
const int DIST_SENSE = A0;

int minAngle = 0; // Adjust these values so that the real-life servo actually goes to 0 degrees
int maxAngle = 180; // and 180 degrees
unsigned long previousSensorMillis = 0;
long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match

Servo panServo; // Creating servo object

void setup() {
  // put your setup code here, to run once:
  panServo.attach(PAN_SERVO);
  pinMode(DIST_SENSE, INPUT);

  Serial.begin(baudRate);     // NOTE2: Set the baudRate to 115200 for faster communication
}

void loop() {
  // Read the raw analog value (0-1023)
  int rawValue = analogRead(DIST_SENSE);

  // Convert the raw value to voltage (0-5V)
  float voltage = (rawValue / 1023.0) * 5.0;

  // Print the voltage value
  Serial.print("Voltage: ");
  Serial.print(voltage, 4); // Print with 2 decimal places
  Serial.println(" V");

  // Optional delay to slow down the readings
  delay(2000); // 1 second delay

  //   // Move the servo to 0 degrees (minimum position)
  // panServo.write(minAngle);
  // delay(1000); // Wait for 1 second

  // // Move the servo to 180 degrees (maximum position)
  // panServo.write(maxAngle);
  // delay(1000); // Wait for 1 second
}
