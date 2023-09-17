// Pin Defs
const int DIST_SENSE = A0
long baudRate = 9600;       // NOTE1: The baudRate for sending & receiving programs must match

void setup() {
  // put your setup code here, to run once:
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
  delay(1000); // 1 second delay
}
