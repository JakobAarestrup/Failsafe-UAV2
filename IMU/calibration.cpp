#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "I2C.hpp"
#include "IMU.hpp"
#include "LIS3MDL.hpp"
#include "LSM6DSOX.hpp"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include "I2C_v2.hpp"
//#include "Kalman.cpp"

#define DT 0.02 // [s/loop] loop period. 20ms (2s)

int mymillis()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

int main()
{

  I2C I1;
  I2C I2;
  IMU IMU1;
  int startofloop = mymillis();
  struct timeval tvBegin, tvEnd, tvDiff;
  gettimeofday(&tvBegin, NULL);

  I1.InitializeI2C();  // write to registers
  IMU1.calibrateIMU(); // gyroscope calibration and set hardcoded values for accelerometer and magnometer

  // Main loop
  while (1)
  {
    startofloop = mymillis();
    float ax = I1.ReadI2C_16bit(LSM6DSOX_ADDR2, LSM6DSOX_OUT_X_L_A);
    float ay = I1.ReadI2C_16bit(LSM6DSOX_ADDR2, LSM6DSOX_OUT_Y_L_A);
    float az = I1.ReadI2C_16bit(LSM6DSOX_ADDR2, LSM6DSOX_OUT_Z_L_A);
    float gx = I1.ReadI2C_16bit(LSM6DSOX_ADDR2, LSM6DSOX_OUT_X_L_G);
    float gy = I1.ReadI2C_16bit(LSM6DSOX_ADDR2, LSM6DSOX_OUT_Y_L_G);
    float gz = I1.ReadI2C_16bit(LSM6DSOX_ADDR2, LSM6DSOX_OUT_Z_L_G);
    /*  float mx = I2.ReadI2C_16bit(LIS3MDL_ADDR2, LIS3MDL_OUT_X_L);
     float my = I2.ReadI2C_16bit(LIS3MDL_ADDR2, LIS3MDL_OUT_Y_L);
     float mz = I2.ReadI2C_16bit(LIS3MDL_ADDR2, LIS3MDL_OUT_Z_L); */

    IMU1.ConvertACCData(ax, ay, az);
    IMU1.ConvertGyroData(gx, gy, gz);
    // IMU1.ConvertMagData(mx,my);

    while (mymillis() - startofloop < 20)
    {
      usleep(100);
    }
    printf("Loop Time %d\n", mymillis() - startofloop);
  }
  return 0;
}