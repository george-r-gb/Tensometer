#include <HX711.h>

HX711 scale;

const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;

const float CALIBRATION_FACTOR = 10000;

enum State {
  IDLE,
  RUNNING,
  WAITING,
  RESET
};

State currentState = IDLE;
float maxload = 0.0; // Variable to track the maximum load
int numHandleTurns = 0; // Variable to store the number of handle turns

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();
  Serial.println("Type 'start' to start recording measurements, then type 'end' to stop");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.equals("start")) {
      currentState = RUNNING;
    } else if (input.equals("end")) {
      currentState = WAITING;
      Serial.println("Enter the number of handle turns:");
    } else if (input.equals("reset")) {
      currentState = RESET;
      Serial.println("Programme reset, type 'start' to start recording measurements, then type 'end' to stop");
    } else if (currentState == WAITING) {
      numHandleTurns = input.toInt();
      currentState = IDLE;
      Serial.print("Maximum load: ");
      Serial.println(maxload);
      Serial.println("Type 'reset' to reset the programme");
      maxload = 0.0; // Reset maximum load after printing
    }
  }

  switch (currentState) {
    case IDLE:
      // Code is idle, do nothing
      break;

    case RUNNING:
      float load = scale.get_units();
      Serial.println(load);
      
      // Update maximum load if necessary
      if (load > maxload) {
        maxload = load;
      }
      
      delay(100);
      break;

    case RESET:
      currentState = IDLE;
      scale.tare();
      Serial.flush(); // Clear serial buffer

      // Clear serial monitor
      Serial.write("\033[2J");
      Serial.write("\033[H");

      break;
  }
}
