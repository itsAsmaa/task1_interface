
Asmaa Fares , Rebal Zabzda , jana sawalmeh , Doaa Hatu
Pin assignments
const int trigPin = 11;
const int echoPin = 10;
const int xPin = A4;  Joystick X-axis pin
const int greenLEDPin = 5;
const int yellowLEDPin = 4;
const int redLEDPin = 3;

 Distance thresholds (modifiable by joystick)
int greenThreshold = 20;  cm
int yellowThreshold = 10;  cm
void setup() {
   Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

   Begin Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
   Read distance from the ultrasonic sensor
  int distance = getDistance();

   Adjust distance thresholds based on joystick
  adjustThresholds();

   Display distance and thresholds for debugging
  Serial.print(Distance );
  Serial.print(distance);
  Serial.print( cm  Green Threshold );
  Serial.print(greenThreshold);
  Serial.print( cm  Yellow Threshold );
  Serial.print(yellowThreshold);
  Serial.println( cm);

   Control LEDs based on distance and thresholds
  if (distance  greenThreshold) {
    setLEDs(HIGH, LOW, LOW);  Green LED on
  } else if (distance  yellowThreshold) {
    setLEDs(LOW, HIGH, LOW);  Yellow LED on
  } else {
    setLEDs(LOW, LOW, HIGH);  Red LED on
  }

   Debugging to check which LED is supposed to be on
  Serial.print(Green LED State );
  Serial.print((distance  greenThreshold)  ON  OFF);
  Serial.print(  Yellow LED State );
  Serial.print((distance  yellowThreshold && distance = greenThreshold)  ON  OFF);
  Serial.print(  Red LED State );
  Serial.println((distance = yellowThreshold)  ON  OFF);

  delay(100);  Short delay for stability
}

 Function to get distance from ultrasonic sensor
int getDistance() {
   Send a pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

   Measure the time of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

   Calculate distance in cm (speed of sound = 34300 cms)
  int distance = duration  0.034  2;
  return distance;
}

 Function to adjust distance thresholds based on joystick position
void adjustThresholds() {
  int xValue = analogRead(xPin);

   Map joystick X value to a range of -2 to +2 (for sensitivity)
  int adjustment = map(xValue, 0, 1023, -2, 2);

   Adjust thresholds within a safe range
  greenThreshold = constrain(greenThreshold + adjustment, 20, 20);
  yellowThreshold = constrain(yellowThreshold + adjustment, 10, 10);
}

 Function to control LED states
void setLEDs(bool greenState, bool yellowState, bool redState) {
  digitalWrite(greenLEDPin, greenState);
  digitalWrite(yellowLEDPin, yellowState);
  digitalWrite(redLEDPin, redState);
}
