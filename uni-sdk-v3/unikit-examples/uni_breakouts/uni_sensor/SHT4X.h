#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define SHT4x_DEFAULT_ADDR 0x44 /**< SHT4x I2C Address */
#define SHT4X_I2C_ADDRESS_44 0x44
#define SHT4x_NOHEAT_HIGHPRECISION                                             \
  0xFD /**< High precision measurement, no heater */
#define SHT4x_NOHEAT_MEDPRECISION                                              \
  0xF6 /**< Medium precision measurement, no heater */
#define SHT4x_NOHEAT_LOWPRECISION                                              \
  0xE0 /**< Low precision measurement, no heater */

#define SHT4x_HIGHHEAT_1S                                                      \
  0x39 /**< High precision measurement, high heat for 1 sec */
#define SHT4x_HIGHHEAT_100MS                                                   \
  0x32 /**< High precision measurement, high heat for 0.1 sec */
#define SHT4x_MEDHEAT_1S                                                       \
  0x2F /**< High precision measurement, med heat for 1 sec */
#define SHT4x_MEDHEAT_100MS                                                    \
  0x24 /**< High precision measurement, med heat for 0.1 sec */
#define SHT4x_LOWHEAT_1S                                                       \
  0x1E /**< High precision measurement, low heat for 1 sec */
#define SHT4x_LOWHEAT_100MS                                                    \
  0x15 /**< High precision measurement, low heat for 0.1 sec */
#define SHT4x_SOFTRESET 0x94 

#define SHT4x_READSERIAL 0x89 /**< Read Out of Serial Register */
#define SHT4x_SOFTRESET 0x94  /**< Soft Reset */

/** How precise (repeatable) the measurement will be */
typedef enum {
  SHT4X_HIGH_PRECISION,
  SHT4X_MED_PRECISION,
  SHT4X_LOW_PRECISION,
} sht4x_precision_t;

/** Optional pre-heater configuration setting */
typedef enum {
  SHT4X_NO_HEATER,
  SHT4X_HIGH_HEATER_1S,
  SHT4X_HIGH_HEATER_100MS,
  SHT4X_MED_HEATER_1S,
  SHT4X_MED_HEATER_100MS ,
  SHT4X_LOW_HEATER_1S ,
  SHT4X_LOW_HEATER_100MS ,
} sht4x_heater_t;

typedef struct {
    float humidity;         //Structure where the values of humidity
    float tempratureC;      // temprature in celsius
    float tempratureF;      // temprature in fahrenhite
} sht4x_data;                 //is stored into variable named after dht_data.

void sht4x_init(i2c_inst_t *INSTANCE);
void setPrecision(sht4x_precision_t prec);
sht4x_precision_t getPrecision(void);
void setHeater(sht4x_heater_t heat);
sht4x_heater_t getHeater(void);
bool getEvent(sht4x_data *data);
uint32_t readSerial(void);
static uint8_t crc8(const uint8_t *data, int len);
bool SHT_reset(void);