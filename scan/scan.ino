// Import Libraries
#include <Servo.h>

// Pin Defs
const int BUTTON_PIN = 2; // the number of the pushbutton pin
const int PAN_SERVO = 10;
const int TILT_SERVO = 11;
const int DIST_SENSE = A0;

int minPhi = 60; // 90 is when the scanner faces away from the ledge of the box
int maxPhi = 120;
int minTheta = 45; // 90 is when the sensor is parallel to the ground
int maxTheta = 115;

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 25;   // the debounce time
unsigned long time_delay = 300;     // number of ms the sensor stops to measure
int resolution = 5;

int baudRate = 9600;

// Creating servo object
Servo panServo;
Servo tiltServo;

void setup()
{
  // setup servos
  panServo.attach(PAN_SERVO);
  tiltServo.attach(TILT_SERVO);

  // setup sensor
  pinMode(DIST_SENSE, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // initialize serial
  Serial.begin(baudRate); // NOTE2: Set the baudRate to 115200 for faster communication
}

void loop()
{
  unsigned long currentMillis = millis(); // setting up a delay timer
  // read the state of the switch into a local variable:
  int reading = digitalRead(BUTTON_PIN);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == LOW)
      {
        for (int i = minTheta; i <= maxTheta; i += resolution)
        {
          tiltServo.write(i);
          delay(time_delay);
          for (int j = minPhi; j <= maxPhi; j += resolution)
          {
            panServo.write(j);
            delay(time_delay);

            // Read the raw analog value from the dist sensor (0-1023)
            int rawValue = analogRead(DIST_SENSE);

            // Convert raw value to voltage (0-5V)
            float voltage = (rawValue / 1023.0) * 5.0;
            float distance = 194.7869 * exp(-1.1766 * voltage) - 5; // Voltage to distance minus offset from MATLAB

            Serial.print(distance, 4); // Print with 4 decimal places
            Serial.print(",");
            Serial.print(i);
            Serial.print(",");
            Serial.print(j);
            Serial.print("\n");
          }
        }
      }
    }
  }
  lastButtonState = reading;
}
