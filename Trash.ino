#include <TinyStepper_28BYJ_48.h>

// Define the pins for the motor
const int MOTOR_IN1 = 8;
const int MOTOR_IN2 = 9;
const int MOTOR_IN3 = 10;
const int MOTOR_IN4 = 11;

// Define sensor pins
const int metalSensorRelay = 2; // Inductive
const int anySensorRelay = 3;   // Capacitive

// Initialize the stepper
TinyStepper_28BYJ_48 stepper;

void setup() {
  // Setup the stepper pins
  stepper.connectToPins(MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4);
  stepper.setSpeedInStepsPerSecond(500);
  stepper.setAccelerationInStepsPerSecondPerSecond(500);

  // Setup relay pins as inputs
  // Using INPUT_PULLUP assumes the relay COM is connected to GND
  pinMode(metalSensorRelay, INPUT_PULLUP);
  pinMode(anySensorRelay, INPUT_PULLUP);
}

void loop() {
  // 1. Detect if the capacitive sensor sees ANY item
  if (digitalRead(anySensorRelay) == LOW) {
    
    // 2. THE 1-SECOND VERIFICATION DELAY
    // Gives the item time to reach the metal sensor and the relay to click
    delay(1000); 

    // 3. DECIDE DIRECTION
    if (digitalRead(metalSensorRelay) == LOW) {
      // It's Metal! Turn 90 deg Right (approx 512 steps)
      stepper.moveRelativeInSteps(512);
      delay(2000); // Wait for item to slide off
      stepper.moveRelativeInSteps(-512); // Return to center
    } 
    else {
      // It's Non-Metallic. Turn 90 deg Left
      stepper.moveRelativeInSteps(-512);
      delay(2000); // Wait for item to slide off
      stepper.moveRelativeInSteps(512); // Return to center
    }

    // 4. CLEARANCE LOOP
    // Stay here until the item is physically removed from the sensors
    while(digitalRead(anySensorRelay) == LOW || digitalRead(metalSensorRelay) == LOW) {
      delay(100);
    }
  }
}
