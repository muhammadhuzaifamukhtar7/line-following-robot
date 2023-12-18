#define LS A0     // Left Sensor
#define RS A1      // Right Sensor

#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor

#define ENA 6       // enable A for left motor
#define ENB 7       // enable B for right motor

int baseSpeed = 100;  // Adjust this value as needed for your motors

void setup()
{
  Serial.begin(9600);
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set initial enable values
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

void loop()
{
  // Read sensor values
  int middleSensor = digitalRead(MS);
  int leftSensor = digitalRead(LS);
  int rightSensor = digitalRead(RS);

  // Line Following Logic
  if (leftSensor == HIGH) {
    // On Black Line with Left Sensor
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    Serial.println("Move Left");
  } else if (rightSensor == HIGH) {
    // On Black Line with Right Sensor
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    Serial.println("Move Right");
  } else {
    // No sensor detecting a black line, move forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    Serial.println("Move Forward");
  }

  delay(5);
}
