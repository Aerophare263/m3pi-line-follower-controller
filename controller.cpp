#include "mbed.h"
#include "m3pi.h"
#include "physcom.h"

physcom::M3pi robot;

void toRange(float &var, const float min, const float max) {
  if (var > max) {
    var = max;
  } else if (var < min) {
    var = min;
  }
}

float getLinePosition(const int *sensorData, const int *sensorDataOld,
                      const float &linePositionOld) {
  bool lineDetected = false;
  uint32_t average = 0;
  uint16_t sum = 0;
  uint8_t noiseThreshold = 100;

  uint16_t rangeMin = 0;
  uint16_t rangeMax = 4000;
  uint16_t rangeCenter = (rangeMax + rangeMin) / 2;

  for (uint8_t i = 0; i < 5; i++) {
    // Ignore values below noise threshold
    if (sensorData[i] > noiseThreshold) {
      // Was line detected at all?
      if (sensorData[i] > 300) lineDetected = true;

      average += sensorData[i] * 1000 * i;
      sum += sensorData[i];
    }
  }

  // If no line is detected we set an extremum line position based on old data
  if (!lineDetected) {
  {
    if (linePositionOld < (rangeCenter / (rangeMin + rangeMax))) {
      return 1;
    } else {
      return 0;
    }
  }
  float linePosition = average / static_cast<float>(sum);
  // Normalize and return
  return (((linePosition / rangeMax) * 2) - 1);
}

bool handleTJunction(const int *optoData) {
  bool shouldStop = true;
  for (size_t i = 0; i < 5; i++) {
    if (optoData[i] < 700) {
      shouldStop = false;
    }
  }
  return shouldStop;
}

int main() {
{

  // Motor speeds
  const float MOTOR_MAX = 0.3;
  const float MOTOR_MIN = 0.0;

  // PID tuning parameters
  const uint8_t KP = 1;
  const uint8_t KI = 0.5;
  const uint8_t KD = 3.5;

  wait_ms(1000);

  robot.sensor_auto_calibrate();

  float motorR;
  float motorL;
  float baseSpeed = MOTOR_MAX;

  float linePosition = 0.0;
  float linePositionOld = 0.0;
  float controlVariable;

  int sensorData[5];
  int sensorDataOld[5] = {0, 0, 0, 0, 0};

  float derivative, proportional, integral = 0;

  while (true) {
    // Get sensor data into "sensorData"
    robot.calibrated_sensors(sensorData);

    // Stop at T junction
    if (handleTJunction(sensorData)) {
      return 0;
    }

    // Get the position of the line.
    linePosition = getLinePosition(sensorData, sensorDataOld, linePositionOld);

    // PID computation
    // -------------------------------------------------------------------------
    // Compute P, I, and D terms
    proportional = linePosition;
    derivative = linePosition - linePositionOld;
    integral += proportional;

    // Remember the last position.
    linePositionOld = linePosition;

    // Compute the controller output (PID output)
    controlVariable = (proportional * KP) + (integral * KI) + (derivative * KD);
    // -------------------------------------------------------------------------

    // Compute new speeds
    motorR = baseSpeed - controlVariable;
    motorL = baseSpeed + controlVariable;
    toRange(motorR, MOTOR_MIN, MOTOR_MAX);
    toRange(motorL, MOTOR_MIN, MOTOR_MAX);

    // Control motors
    robot.activate_motor(0, motorL);
    robot.activate_motor(1, motorR);
  }
}
