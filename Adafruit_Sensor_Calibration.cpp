#include "Adafruit_Sensor_Calibration.h"

/**************************************************************************/
/*!
    @brief CRC16 calculation helper with 0xA001 seed
    @param crc Last byte's CRC value
    @param a The new byte to append-compute
    @returns New 16 bit CRC
*/
/**************************************************************************/
uint16_t Adafruit_Sensor_Calibration::crc16_update(uint16_t crc, uint8_t a) {
  int i;
  crc ^= a;
  for (i = 0; i < 8; i++) {
    if (crc & 1) {
      crc = (crc >> 1) ^ 0xA001;
    } else {
      crc = (crc >> 1);
    }
  }
  return crc;
}

Adafruit_Sensor_Calibration::Adafruit_Sensor_Calibration() {}

/**************************************************************************/
/*!
    @brief Calibrator that will apply known calibrations to an event
    @param  event Reference to a sensor event that we will modify in place
    @returns False if we could not calibrate this type (isn't supported)
*/
/**************************************************************************/
bool Adafruit_Sensor_Calibration::calibrate(sensors_event_t &event) {
  if (event.type == SENSOR_TYPE_MAGNETIC_FIELD) {
    // hard iron cal
    float mx = event.magnetic.x - mag_hardiron[0];
    float my = event.magnetic.y - mag_hardiron[1];
    float mz = event.magnetic.z - mag_hardiron[2];
    // soft iron cal
    event.magnetic.x =
        mx * mag_softiron[0] + my * mag_softiron[1] + mz * mag_softiron[2];
    event.magnetic.y =
        mx * mag_softiron[3] + my * mag_softiron[4] + mz * mag_softiron[5];
    event.magnetic.z =
        mx * mag_softiron[6] + my * mag_softiron[7] + mz * mag_softiron[8];
  } else if (event.type == SENSOR_TYPE_GYROSCOPE) {
    event.gyro.x -= gyro_zerorate[0];
    event.gyro.y -= gyro_zerorate[1];
    event.gyro.z -= gyro_zerorate[2];
#ifdef ADAFRUIT_SENSOR_CALIBRATION_ACCEL_GYRO_ALIGN
    float gx = event.gyro.x;
    float gy = event.gyro.y;
    float gz = event.gyro.z;
    event.gyro.x = gx * gyro_align[0] + gy * gyro_align[1] + gz * gyro_align[2];
    event.gyro.y = gx * gyro_align[3] + gy * gyro_align[4] + gz * gyro_align[5];
    event.gyro.z = gx * gyro_align[6] + gy * gyro_align[7] + gz * gyro_align[8];
#endif
  } else if (event.type == SENSOR_TYPE_ACCELEROMETER) {
    event.acceleration.x -= accel_zerog[0];
    event.acceleration.y -= accel_zerog[1];
    event.acceleration.z -= accel_zerog[2];
#ifdef ADAFRUIT_SENSOR_CALIBRATION_ACCEL_GYRO_ALIGN
    float ax = event.acceleration.x;
    float ay = event.acceleration.y;
    float az = event.acceleration.z;
    event.acceleration.x =
        ax * accel_align[0] + ay * accel_align[1] + az * accel_align[2];
    event.acceleration.y =
        ax * accel_align[3] + ay * accel_align[4] + az * accel_align[5];
    event.acceleration.z =
        ax * accel_align[6] + ay * accel_align[7] + az * accel_align[8];
#endif
  } else {
    return false;
  }
  return true;
}

/**************************************************************************/
/*!
    @brief Whether we're using EEPROM for storage
    @returns True if using EEPROM
*/
/**************************************************************************/
bool Adafruit_Sensor_Calibration::hasEEPROM(void) {
#if defined(ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM)
  return true;
#else
  return false;
#endif
}

/**************************************************************************/
/*!
    @brief Whether we're using SPI/QSPI Flash for storage
    @returns True if using FLASH
*/
/**************************************************************************/
bool Adafruit_Sensor_Calibration::hasFLASH(void) {
#if defined(ADAFRUIT_SENSOR_CALIBRATION_USE_FLASH)
  return true;
#else
  return false;
#endif
}
