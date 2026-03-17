#ifndef __ADAFRUIT_SENSOR_CALIBRATION_EEPROM__
#define __ADAFRUIT_SENSOR_CALIBRATION_EEPROM__

#include "Adafruit_Sensor_Calibration.h"

#if defined(ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM)

#include <EEPROM.h>

#define EEPROM_CAL_SIZE 68

#ifdef ADAFRUIT_SENSOR_CALIBRATION_ACCEL_GYRO_ALIGN
#define EEPROM_ALIGN_CAL_SIZE 76
#define EEPROM_ALIGN_CAL_MAGIC_0 0xAA
#define EEPROM_ALIGN_CAL_MAGIC_1 0xC0
#endif

/**!  @brief Class for managing storing calibration in internal EEPROM memory
 * **/
class Adafruit_Sensor_Calibration_EEPROM : public Adafruit_Sensor_Calibration {
public:
  bool begin(uint8_t eeprom_addr = 60);

  bool saveCalibration(void);
  bool loadCalibration(void);
  bool printSavedCalibration(void);

private:
  uint16_t ee_addr = 0;
};

#endif

#endif // include once
