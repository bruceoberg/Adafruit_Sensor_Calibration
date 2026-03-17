#define ADAFRUIT_SENSOR_CALIBRATION_ACCEL_GYRO_ALIGN
#include "Adafruit_Sensor_Calibration.h"

// select either EEPROM or SPI FLASH storage:
#ifdef ADAFRUIT_SENSOR_CALIBRATION_USE_EEPROM
  Adafruit_Sensor_Calibration_EEPROM cal;
#else
  Adafruit_Sensor_Calibration_SDFat cal;
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  delay(100);
  Serial.println("Calibration filesys test");
  if (!cal.begin()) {
    Serial.println("Failed to initialize calibration helper");
    while (1) yield();
  }
  Serial.print("Has EEPROM: "); Serial.println(cal.hasEEPROM());
  Serial.print("Has FLASH: "); Serial.println(cal.hasFLASH());

  if (! cal.loadCalibration()) {
    Serial.println("No calibration loaded/found... will start with defaults");
  } else {
    Serial.println("Loaded existing calibration");
  }

  // in uTesla
  cal.mag_hardiron[0] = -3.35;
  cal.mag_hardiron[1] = -0.74;
  cal.mag_hardiron[2] = -40.79;

  // in uTesla
  cal.mag_softiron[0] = 0.965;
  cal.mag_softiron[1] = 0.018;
  cal.mag_softiron[2] = 0.010;  
  cal.mag_softiron[3] = 0.018;
  cal.mag_softiron[4] = 0.960;
  cal.mag_softiron[5] = 0.003;  
  cal.mag_softiron[6] = 0.010;
  cal.mag_softiron[7] = 0.003;
  cal.mag_softiron[8] = 1.080;
  // Earth total magnetic field strength in uTesla (dependent on location and time of the year),
  // visit: https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#igrfwmm)
  cal.mag_field = 45.00; // approximate value for locations along the equator

  // in Radians/s
  cal.gyro_zerorate[0] = 0.05;
  cal.gyro_zerorate[1] = -0.01;
  cal.gyro_zerorate[2] = -0.01;

  // in m/s^2
  cal.accel_zerog[0] = 0.10;
  cal.accel_zerog[1] = -0.04;
  cal.accel_zerog[2] = 0.15;

  // accel_align and gyro_align are 3x3 correction matrices (row-major).
  // Identity = no correction. These example values represent a small
  // misalignment -- replace with values from your calibration procedure.
  cal.accel_align[0] = 1.000; cal.accel_align[1] = 0.012; cal.accel_align[2] = -0.008;
  cal.accel_align[3] = 0.012; cal.accel_align[4] = 1.000; cal.accel_align[5] =  0.005;
  cal.accel_align[6] = -0.008; cal.accel_align[7] = 0.005; cal.accel_align[8] = 1.000;

  cal.gyro_align[0] = 1.000; cal.gyro_align[1] = -0.007; cal.gyro_align[2] =  0.003;
  cal.gyro_align[3] = -0.007; cal.gyro_align[4] =  1.000; cal.gyro_align[5] =  0.009;
  cal.gyro_align[6] =  0.003; cal.gyro_align[7] =  0.009; cal.gyro_align[8] =  1.000;

  if (! cal.saveCalibration()) {
    Serial.println("**WARNING** Couldn't save calibration");
  } else {
    Serial.println("Wrote calibration");
  }

  cal.printSavedCalibration();
}

void loop() {

}
