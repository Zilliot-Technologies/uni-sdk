#include <stdio.h>
#include "pico/stdlib.h"
#include "SHT4X.h"

uint8_t _heater;
float _temperature;
uint8_t _precision;
float _humidity;
i2c_inst_t *SHT4X_INSTANCE;

void sht4x_init(i2c_inst_t *INSTANCE)
{
    SHT4X_INSTANCE = INSTANCE ;
}

void setPrecision(sht4x_precision_t prec)
 { 
    _precision = prec;
 }

sht4x_precision_t getPrecision(void)
 {
    return _precision; 
 }

void setHeater(sht4x_heater_t heat)
 {
    _heater = heat;
 }

sht4x_heater_t getHeater(void)
 {
    return _heater;
 }

bool getEvent(sht4x_data *data) {

  uint8_t readbuffer[6];
  uint8_t cmd = SHT4x_NOHEAT_HIGHPRECISION;
  uint16_t duration = 10;

  if (_heater == SHT4X_NO_HEATER) {
    if (_precision == SHT4X_HIGH_PRECISION) {
      cmd = SHT4x_NOHEAT_HIGHPRECISION;
      duration = 10;
    }
    if (_precision == SHT4X_MED_PRECISION) {
      cmd = SHT4x_NOHEAT_MEDPRECISION;
      duration = 5;
    }
    if (_precision == SHT4X_LOW_PRECISION) {
      cmd = SHT4x_NOHEAT_LOWPRECISION;
      duration = 2;
    }
  }

  if (_heater == SHT4X_HIGH_HEATER_1S) {
    cmd = SHT4x_HIGHHEAT_1S;
    duration = 1100;
  }
  if (_heater == SHT4X_HIGH_HEATER_100MS) {
    cmd = SHT4x_HIGHHEAT_100MS;
    duration = 110;
  }

  if (_heater == SHT4X_MED_HEATER_1S) {
    cmd = SHT4x_MEDHEAT_1S;
    duration = 1100;
  }
  if (_heater == SHT4X_MED_HEATER_100MS) {
    cmd = SHT4x_MEDHEAT_100MS;
    duration = 110;
  }

  if (_heater == SHT4X_LOW_HEATER_1S) {
    cmd = SHT4x_LOWHEAT_1S;
    duration = 1100;
  }
  if (_heater == SHT4X_LOW_HEATER_100MS) {
    cmd = SHT4x_LOWHEAT_100MS;
    duration = 110;
  }

  if (!i2c_write_blocking(SHT4X_INSTANCE,SHT4X_I2C_ADDRESS_44,&cmd,1,false)) {
    return false;
  }
  sleep_ms(duration);
  if (!i2c_read_blocking(SHT4X_INSTANCE,SHT4X_I2C_ADDRESS_44,readbuffer,6,false)) {
    return false;
  }

  if (readbuffer[2] != crc8(readbuffer, 2) ||
      readbuffer[5] != crc8(readbuffer + 3, 2))
    return false;

  float t_ticks = (uint16_t)readbuffer[0] * 256 + (uint16_t)readbuffer[1];
  float rh_ticks = (uint16_t)readbuffer[3] * 256 + (uint16_t)readbuffer[4];
  _temperature = -45 + 175 * t_ticks / 65535;
  _humidity = -6 + 125 * rh_ticks / 65535;

  _humidity > 100 ? _humidity = 100 : _humidity ;
  _humidity < 0 ? _humidity=0 :_humidity ;

  // return values to structure
  data->tempratureC=_temperature;
  data->humidity =_humidity;
  return true;
}

uint32_t readSerial(void) {
  uint8_t cmd = SHT4x_READSERIAL;
  uint8_t reply[6];

  if (!i2c_write_blocking(SHT4X_INSTANCE,SHT4X_I2C_ADDRESS_44,&cmd,1,false)) {
    return false;
  }
  sleep_ms(10);
  if (!i2c_read_blocking(SHT4X_INSTANCE,SHT4X_I2C_ADDRESS_44,reply,6,false)) {
    return false;
  }

  if ((crc8(reply, 2) != reply[2]) || (crc8(reply + 3, 2) != reply[5])) {
    return false;
  }

  uint32_t serial = 0;
  serial = reply[0];
  serial <<= 8;
  serial |= reply[1];
  serial <<= 8;
  serial |= reply[3];
  serial <<= 8;
  serial |= reply[4];

  return serial;
}

uint8_t crc8(const uint8_t *data, int len) 
{
  /*
   *
   * CRC-8 formula from page 14 of SHT spec pdf
   *
   * Test data 0xBE, 0xEF should yield 0x92
   *
   * Initialization data 0xFF
   * Polynomial 0x31 (x8 + x5 +x4 +1)
   * Final XOR 0x00
   */

  const uint8_t POLYNOMIAL = 0x31;
  uint8_t crc = 0xFF;

  for (int j = len; j; --j) {
    crc ^= *data++;

    for (int i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
  }
  return crc;
}

bool SHT_reset(void) 
{
  uint8_t cmd = SHT4x_SOFTRESET;
  if (i2c_write_blocking(SHT4X_INSTANCE,SHT4X_I2C_ADDRESS_44,&cmd,1,false)) {
    return 0;
  }
  sleep_ms(1);
  return 1;
}



