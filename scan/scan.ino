// Import Libraries
#include <Servo.h>

// Pin Defs
// const int buttonPin = 2;  // the number of the pushbutton pin
const int PAN_SERVO = 10;
const int TILT_SERVO = 11;
const int DIST_SENSE = A0;

int minPhi = 20; // Adjust these values so that the real-life servo actually goes to 0 degrees
int maxPhi = 90; // and 180 degrees
int minTheta = 60;
int maxTheta = 130;

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 25;    // the debounce time; increase if the output flickers
unsigned long prevMillis = 0;
unsigned long time_delay = 300; // number of milliseconds the sensor stops to measure
unsigned long serial_delay = 1000; // number of milliseconds between printing serial voltages
int resolution = 10; // number of degrees the sensor moves each time

int baudRate = 9600;

// Creating servo object
Servo panServo;
Servo tiltServo;

void runScan();

void setup() {
  // setup servos
  panServo.attach(PAN_SERVO);
  tiltServo.attach(TILT_SERVO);

  // setup sensor
  pinMode(DIST_SENSE, INPUT);

  // servo initial conditions
  int homeAngles[2] = {panServo.read(), tiltServo.read()};

  // initialize serial
  Serial.begin(baudRate);     // NOTE2: Set the baudRate to 115200 for faster communication
}

void loop() {
  unsigned long currentMillis = millis(); // setting up a delay timer
//  // read the state of the switch into a local variable:
//  // int reading = digitalRead(buttonPin);
//  panServo.write(0);
//  delay(1000);
//  int thetaRange[10] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
//  for (int i = 0; i < 10; i = i + 1) {
//    panServo.write(thetaRange[i]);
//    delay(1000);
//    int rawValue = analogRead(DIST_SENSE);
//    float voltage = (rawValue / 1023.0) * 5.0;
//    Serial.print("Voltage: ");
//    Serial.print(voltage, 4); // Print with 2 decimal places
//    Serial.println(" V");
//    Serial.print("Angle: ");
//    Serial.println(thetaRange[i]); // Print with 2 decimal places
//  } 
//  
  for (int j = minTheta; j <= maxTheta; j += resolution){
     tiltServo.write(j);
     delay(time_delay);
     for (int i = minPhi; i <= maxPhi; i += resolution){
      panServo.write(i);
      delay(time_delay);
      int rawValue = analogRead(DIST_SENSE);
      float voltage = (rawValue / 1023.0) * 5.0;
      float distance = 194.7869*exp(-1.1766*voltage); // Voltage to distance from MATLAB
      Serial.print(distance, 4); // Print with 4 decimal places
      Serial.print(",");
      Serial.print(i);
      Serial.print(",");
      Serial.println(j);
//       if (currentMillis - prevMillis >= time_delay) {
//         prevMillis = currentMillis; // resets the count
//         panServo.write(i);
//       }
     }
//     if (currentMillis - prevMillis >= time_delay) {
//       prevMillis = currentMillis; // resets the count
//     }
  }
//  
  
  // If the switch changed, due to noise or pressing:
  // if (reading != lastButtonState) {
  //   // reset the debouncing timer
  //   lastDebounceTime = millis();
  // }

  // if ((millis() - lastDebounceTime) > debounceDelay) {
  //   // whatever the reading is at, it's been there for longer than the debounce
  //   // delay, so take it as the actual current state if the button state has changed:
  //   if (reading != buttonState) {
  //     buttonState = reading;

  //     if (buttonState == HIGH) {
  //         for (int j = minTheta; j <= maxTheta; j += resolution){
  //           for (int i = minPhi; i <= maxPhi; i += resolution){
  //             if (currentMillis - prevMillis >= time_delay) {
  //               prevMillis = currentMillis; // resets the count
  //               panServo.write(i);
  //             }
  //           }
  //           if (currentMillis - prevMillis >= time_delay) {
  //             prevMillis = currentMillis; // resets the count
  //             tiltServo.write(j);
      
  //           }
  //         }
  //     }
  //   }
  // }
  // lastButtonState = reading;
  
  // Read the raw analog value from the distance sensor (0-1023)
  // int rawValue = analogRead(DIST_SENSE);

  // // // Convert the raw value to voltage (0-5V)
  // float voltage = (rawValue / 1023.0) * 5.0;

  // // Print the voltage value to serial
  // if ((currentMillis - prevMillis) >= serial_delay) {
  //   prevMillis = currentMillis;
  //   Serial.print("Voltage: ");
  //   Serial.print(voltage, 4); // Print with 2 decimal places
  //   Serial.println(" V");
  // }
  }
