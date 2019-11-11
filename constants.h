// Motor speeds
static const float MOTOR_MAX = 0.71;
static const float MOTOR_MIN = 0.0;

// PID tuning parameters
static const float KP = 1;
static const float KI = 0;
static const float KD = 80;

// Optosensor parameters
static const uint8_t SENSOR_FIRST_INDEX = 0;
static const uint8_t SENSOR_COUNT = 5;
static const uint16_t NOISE_THRESHOLD = 60;
static const uint16_t LINE_DETECTION_THRESHOLD = 200;
static const uint16_t ABOVE_LINE_THRESHOLD = 850;

static const uint16_t RANGE_MIN = 0;
static const uint16_t RANGE_MAX = (SENSOR_COUNT - 1) * 1000;
static const uint16_t RANGE_CENTER = (RANGE_MIN + RANGE_MAX) / 2;
