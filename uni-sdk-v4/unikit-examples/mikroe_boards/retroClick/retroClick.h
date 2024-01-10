#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "string.h"
/**
 * @brief 8800 Retro Register Address Map.
 * @details Specified register address map of 8800 Retro Click driver.
 */
#define C8800RETRO_REG_DIGIT_0              0x01
#define C8800RETRO_REG_DIGIT_1              0x02
#define C8800RETRO_REG_DIGIT_2              0x03
#define C8800RETRO_REG_DIGIT_3              0x04
#define C8800RETRO_REG_DIGIT_4              0x05
#define C8800RETRO_REG_DIGIT_5              0x06
#define C8800RETRO_REG_DIGIT_6              0x07
#define C8800RETRO_REG_DIGIT_7              0x08
#define C8800RETRO_REG_DECODE_MODE          0x09
#define C8800RETRO_REG_GLOBAL_INTENSITY     0x0A
#define C8800RETRO_REG_SCAN_LIMIT           0x0B
#define C8800RETRO_REG_SHUTDOWN             0x0C
#define C8800RETRO_REG_SELF_ADDRESSING      0x2D
#define C8800RETRO_REG_FEATURE              0x0E
#define C8800RETRO_REG_DISPLAY_TEST_MODE    0x0F
#define C8800RETRO_REG_DIG0_DIG1_INTENSITY  0x10
#define C8800RETRO_REG_DIG2_DIG3_INTENSITY  0x11
#define C8800RETRO_REG_DIG4_DIG5_INTENSITY  0x12
#define C8800RETRO_REG_DIG6_DIG7_INTENSITY  0x13
#define C8800RETRO_REG_DIAG_DIGIT_0         0x14
#define C8800RETRO_REG_DIAG_DIGIT_1         0x15
#define C8800RETRO_REG_DIAG_DIGIT_2         0x16
#define C8800RETRO_REG_DIAG_DIGIT_3         0x17
#define C8800RETRO_REG_DIAG_DIGIT_4         0x18
#define C8800RETRO_REG_DIAG_DIGIT_5         0x19
#define C8800RETRO_REG_DIAG_DIGIT_6         0x1A
#define C8800RETRO_REG_DIAG_DIGIT_7         0x1B
#define C8800RETRO_REG_KEYA                 0x1C
#define C8800RETRO_REG_KEYB                 0x1D

/*! @} */ // c8800retro_reg

/**
 * @defgroup c8800retro_set 8800 Retro Registers Settings
 * @brief Settings for registers of 8800 Retro Click driver.
 */

/**
 * @addtogroup c8800retro_set
 * @{
 */

/**
 * @brief 8800 Retro shutdown register settings.
 * @details Specified settings for shutdown register of 8800 Retro Click driver.
 */
#define C8800RETRO_SHUTDOWN_RESET           0x00
#define C8800RETRO_SHUTDOWN                 0x80
#define C8800RETRO_NORMAL_OPERATION_RESET   0x01
#define C8800RETRO_NORMAL_OPERATION         0x81

/**
 * @brief 8800 Retro decode mode register settings.
 * @details Specified settings for decode mode register of 8800 Retro Click driver.
 */
#define C8800RETRO_NO_DECODE                0x00
#define C8800RETRO_DECODE_0                 0x01
#define C8800RETRO_DECODE_0_2               0x07
#define C8800RETRO_DECODE_0_5               0x3F
#define C8800RETRO_DECODE_0_2_5             0x25

/**
 * @brief 8800 Retro self addressing register settings.
 * @details Specified settings for self addressing register of 8800 Retro Click driver.
 */
#define C8800RETRO_FACTORY_SET_ADDRESS      0x00
#define C8800RETRO_USER_SET_ADDRESS         0x01

/**
 * @brief 8800 Retro intensity register settings.
 * @details Specified settings for intensity register of 8800 Retro Click driver.
 */
#define C8800RETRO_INTENSITY_1              0x00
#define C8800RETRO_INTENSITY_2              0x01
#define C8800RETRO_INTENSITY_3              0x02
#define C8800RETRO_INTENSITY_4              0x03
#define C8800RETRO_INTENSITY_5              0x04
#define C8800RETRO_INTENSITY_6              0x05
#define C8800RETRO_INTENSITY_7              0x06
#define C8800RETRO_INTENSITY_8              0x07
#define C8800RETRO_INTENSITY_9              0x08
#define C8800RETRO_INTENSITY_10             0x09
#define C8800RETRO_INTENSITY_11             0x0A
#define C8800RETRO_INTENSITY_12             0x0B
#define C8800RETRO_INTENSITY_13             0x0C
#define C8800RETRO_INTENSITY_14             0x0D
#define C8800RETRO_INTENSITY_15             0x0E
#define C8800RETRO_INTENSITY_16             0x0F

/**
 * @brief 8800 Retro scan limit register settings.
 * @details Specified settings for scan limit register of 8800 Retro Click driver.
 */
#define C8800RETRO_SCAN_LIMIT_0             0x00
#define C8800RETRO_SCAN_LIMIT_0_1           0x01
#define C8800RETRO_SCAN_LIMIT_0_2           0x02
#define C8800RETRO_SCAN_LIMIT_0_3           0x03
#define C8800RETRO_SCAN_LIMIT_0_4           0x04
#define C8800RETRO_SCAN_LIMIT_0_5           0x05
#define C8800RETRO_SCAN_LIMIT_0_6           0x06
#define C8800RETRO_SCAN_LIMIT_0_7           0x07

/**
 * @brief 8800 Retro keypad flags.
 * @details Specified keypad flags of 8800 Retro Click driver.
 */
#define C8800RETRO_KEY_NONE                 0x0000
#define C8800RETRO_KEY_A1                   0x8000
#define C8800RETRO_KEY_A2                   0x4000
#define C8800RETRO_KEY_A3                   0x2000
#define C8800RETRO_KEY_A4                   0x1000
#define C8800RETRO_KEY_B1                   0x0800
#define C8800RETRO_KEY_B2                   0x0400
#define C8800RETRO_KEY_B3                   0x0200
#define C8800RETRO_KEY_B4                   0x0100
#define C8800RETRO_KEY_C1                   0x0080
#define C8800RETRO_KEY_C2                   0x0040
#define C8800RETRO_KEY_C3                   0x0020
#define C8800RETRO_KEY_C4                   0x0010
#define C8800RETRO_KEY_D1                   0x0008
#define C8800RETRO_KEY_D2                   0x0004
#define C8800RETRO_KEY_D3                   0x0002
#define C8800RETRO_KEY_D4                   0x0001

/**
 * @brief 8800 Retro scroll settings.
 * @details Specified settings for scroll mode of 8800 Retro Click driver.
 */
#define C8800RETRO_SCROLL_SPEED_SLOW        300
#define C8800RETRO_SCROLL_SPEED_MEDIUM      150
#define C8800RETRO_SCROLL_SPEED_FAST        50
#define C8800RETRO_SCROLL_HORIZONTAL_LEFT   0
#define C8800RETRO_SCROLL_HORIZONTAL_RIGHT  1
#define C8800RETRO_SCROLL_VERTICAL_UP       2
#define C8800RETRO_SCROLL_VERTICAL_DOWN     3

/**
 * @brief 8800 Retro Click configuration object.
 * @details Configuration object definition of 8800 Retro Click driver.
 */
typedef struct
{
    uint8_t  scl;                                 /**< Clock pin descriptor for I2C driver. */
    uint8_t  sda;                                 /**< Bidirectional data pin descriptor for I2C driver. */
    i2c_inst_t *inst;
    uint8_t  int_pin;                             /**< Interupt Request pin. */

    uint32_t  i2c_speed;                             /**< I2C serial speed. */
    uint8_t   i2c_address;                           /**< I2C slave address. */

} c8800retro_cfg_t;

/**
 * @defgroup c8800retro_map 8800 Retro MikroBUS Map
 * @brief MikroBUS pin mapping of 8800 Retro Click driver.
 */

/**
 * @addtogroup c8800retro_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 8800 Retro Click to the selected MikroBUS.
 */

void dispWriteReg ( c8800retro_cfg_t *ctx, uint8_t reg, uint8_t data_in );
void dispDefaultConfig(c8800retro_cfg_t *config);
void initDisplay(c8800retro_cfg_t *config);
int display_char ( c8800retro_cfg_t *ctx, uint8_t char_index );
void clear_display ( c8800retro_cfg_t *ctx );
void display_image ( c8800retro_cfg_t *ctx, uint8_t *p_image );
void display_string ( c8800retro_cfg_t *ctx, uint8_t scroll_mode, uint16_t scroll_speed_ms, uint8_t *text );
