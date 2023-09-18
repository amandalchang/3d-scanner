// Import Libraries
#include <Servo.h>

// Pin Defs
const int PAN_SERVO = 10;
const int TILT_SERVO = 12;

int minAngle = 0; // Adjust these values so that the real-life servo actually goes to 0 degrees
int maxAngle = 180; // and 180 degrees
int homeAngle = -2;
unsigned long previousSensorMillis = 0;
int baudRate = 9600;

Servo panServo; // Creating servo object

void setup() {
  // put your setup code here, to run once:
  panServo.attach(PAN_SERVO);
  homeAngle = panServo.read();
  Serial.begin(baudRate);     // NOTE2: Set the baudRate to 115200 for faster communication
}

void loop() {
  // Move the servo to 0 degrees (minimum position)
  panServo.write(0);
  delay(3000); // Wait for 1 second

  // Serial.println("The angle is: ");
  // Serial.print(homeAngle);

  // Move the servo to 180 degrees (maximum position)
  panServo.write(90);
  delay(3000); // Wait for 1 second

    // Move the servo to 180 degrees (maximum position)
  panServo.write(180);
  delay(3000); // Wait for 1 second
}
