#define MS 12      // Middle Sensor
#define LS 13      // Left sensor
#define RS 11      // Right sensor

#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor

// PID constants
#define KP 1. // Proportional gain

// Function to read sensor values
int readSensor(int sensorPin) {
    return digitalRead(sensorPin);
}

// Function to adjust motor speeds using PID control
void pidController(int setpoint, int leftSensor, int rightSensor) {
    // Calculate error
    int error = setpoint - (leftSensor + rightSensor) / 2;

    // Calculate control signal
    float controlSignal = KP * error;

    // Adjust motor speeds based on the control signal
    int leftSpeed = 50 + controlSignal;
    int rightSpeed = 50 - controlSignal;

    // Apply motor control (adjust based on your motor control method)
    digitalWrite(LM1, leftSpeed > 0 ? HIGH : LOW);
    digitalWrite(LM2, leftSpeed > 0 ? LOW : HIGH);
    digitalWrite(RM1, rightSpeed > 0 ? HIGH : LOW);
    digitalWrite(RM2, rightSpeed > 0 ? LOW : HIGH);
}

void setup() {
    Serial.begin(9600);
    pinMode(MS, INPUT);
    pinMode(LS, INPUT);
    pinMode(RS, INPUT);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
}

void loop() {
    // Read sensor values
    int leftSensorValue = readSensor(LS);
    int rightSensorValue = readSensor(RS);
    int middleSensorValue = readSensor(MS);

    // Check if the robot is on a circle (customize as needed)
    if (leftSensorValue == HIGH && rightSensorValue == HIGH && middleSensorValue == LOW) {
        // Robot is on a circle, execute 180-degree turn and stop
        pidController(0, leftSensorValue, rightSensorValue);

        // Print sensor values for debugging
        Serial.print("LS: ");
        Serial.print(leftSensorValue);
        Serial.print(", RS: ");
        Serial.println(rightSensorValue);

        delay(10); // Adjust delay as needed
    } else {
        // Line following logic
        if (middleSensorValue) {
            // Middle Sensor On Line
            if (!leftSensorValue && !rightSensorValue) {
                // Move forward
                Serial.println("Move Forward");
                digitalWrite(LM1, LOW);
                digitalWrite(LM2, HIGH);
                digitalWrite(RM1, LOW);
                digitalWrite(RM2, HIGH);
            } else if (leftSensorValue && !rightSensorValue) {
                // Sharp Left
                Serial.println("Sharp Left");
                digitalWrite(LM1, LOW);
                digitalWrite(LM2, HIGH);
                digitalWrite(RM1, HIGH);
                digitalWrite(RM2, LOW);
            } else if (!leftSensorValue && rightSensorValue) {
                // Sharp Right
                Serial.println("Sharp Right");
                digitalWrite(LM1, HIGH);
                digitalWrite(LM2, LOW);
                digitalWrite(RM1, LOW);
                digitalWrite(RM2, HIGH);
            } else if (leftSensorValue && rightSensorValue) {
                // Stop
                Serial.println("Stop");
                digitalWrite(LM1, LOW);
                digitalWrite(LM2, LOW);
                digitalWrite(RM1, LOW);
                digitalWrite(RM2, LOW);
            }
        } else {
            // Turn logic
            if (leftSensorValue && !rightSensorValue) {
                // Turn left
                Serial.println("Turn Left");
                digitalWrite(LM1, LOW);
                digitalWrite(LM2, HIGH);
                digitalWrite(RM1, LOW);
                digitalWrite(RM2, LOW);
            } else if (!leftSensorValue && rightSensorValue) {
                // Turn right
                Serial.println("Turn Right");
                digitalWrite(LM1, LOW);
                digitalWrite(LM2, LOW);
                digitalWrite(RM1, LOW);
                digitalWrite(RM2, HIGH);
            } else if (!leftSensorValue && !rightSensorValue) {
                // Stop
                Serial.println("Stop");
                digitalWrite(LM1, LOW);
                digitalWrite(LM2, LOW);
                digitalWrite(RM1, LOW);
                digitalWrite(RM2, LOW);
            }
        }
        delay(5);
    }
}
