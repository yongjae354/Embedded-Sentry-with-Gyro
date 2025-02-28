#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "mbed.h"
#include "state.h"

// --- Register Addresses and Configuration Values ---
#define CTRL_REG1 0x20               // Control register 1 address
#define CTRL_REG1_CONFIG 0b01'10'1'1'1'1  // Configuration: ODR=100Hz, Enable X/Y/Z axes, power on
#define CTRL_REG4 0x23               // Control register 4 address
#define CTRL_REG4_CONFIG 0b0'0'01'0'00'0  // Configuration: High-resolution, 2000dps sensitivity

// SPI communication completion flag
#define SPI_FLAG 1

// Address of the gyroscope's X-axis output lower byte register
#define OUT_X_L 0x28

// Scaling factor for converting raw sensor data in dps (deg/s) to angular velocity in rps (rad/s)
// Combines sensitivity scaling and conversion from degrees to radians
#define DEG_TO_RAD (17.5f * 0.0174532925199432957692236907684886f / 1000.0f)

struct GyroData {
    float x, y, z;
    uint32_t timestamp;
};

extern GyroData keyGesture[1000];
extern GyroData enteredGesture[1000];

extern volatile bool isRecording;
extern volatile bool isEntering;


extern volatile int gestureIndex;

void init_gyroscope();
void sample_gyro_data(GyroData* InputGesture);
float dtw(const GyroData* gest1, const GyroData* gest2, int len1, int len2);
bool compareGest(const GyroData* keyGest, const GyroData* enteredGest, int keyLen, int enteredLen);

#endif