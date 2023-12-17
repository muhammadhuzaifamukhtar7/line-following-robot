#define MS 12      // Middle Sensor
#define LS 13      // Left sensor
#define RS 11      // Right sensor

#define LM 2       // left motor
#define RM 3       // right motor

void setup()
{
  Serial.begin(9600);
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM, OUTPUT);
  pinMode(RM, OUTPUT);
}

void moveForward() {
  analogWrite(LM, 200);  // Adjust the speed as needed
  analogWrite(RM, 200);  // Adjust the speed as needed
  Serial.println("Move forward");
  delay(200);  // Delay for 200 milliseconds
}

void stopMotors() {
  digitalWrite(LM, LOW);
  digitalWrite(RM, LOW);
  Serial.println("Stop");
  delay(1000);  // Delay for 1000 milliseconds (1 second)
}

void turnLeft() {
  digitalWrite(LM, LOW);
  analogWrite(RM, 200);  // Adjust the speed as needed
  Serial.println("Turn left");
  delay(500);  // Delay for 500 milliseconds
}

void turnRight() {
  analogWrite(LM, 200);  // Adjust the speed as needed
  digitalWrite(RM, LOW);
  Serial.println("Turn right");
  delay(500);  // Delay for 500 milliseconds
}

void loop()
{
  if (digitalRead(MS)) {
    if (digitalRead(LS) && !digitalRead(RS)) // Turn left
    {
      turnLeft();
    }
    else if (!digitalRead(LS) && digitalRead(RS)) // Turn right
    {
      turnRight();
    }
    else if (digitalRead(LS) && digitalRead(RS)) // On the line
    {
      moveForward();
    }
    else // No line detected
    {
      stopMotors();
      // Perform a 90-degree turn based on your robot's geometry
      // Add code for turning left or right
    }
  }
  else // Middle sensor is not detecting the line
  {
    // Perform a 90-degree turn based on your robot's geometry
    // Add code for turning left or right
    stopMotors();
  }
}
