#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define BMP_ADDRESS 0x14
#define CHIP_ID_REG 0x00
#define MODE_REG 0x03
#define ACC_REGISTER (uint8_t*) 0x04


#define sleep_mode 0x00
#define normal_mode 0x02
#define low_power_mode 0x01

#define wakeup_int 0
#define orient_int 1
#define gen1_int 2
#define gen2_int 3
#define int_overrun 4
#define ffull_int 5
#define fwm_int 6
#define drdy int 7

#define step_int_en 0
#define stap_int_en 2
#define dtap_int_en 3
#define actch_int_en 4
#define latch_int_en 7
#define orient_int_en 9
#define gen1_int_en 10
#define gen2_int_en 11
#define ffull_int_en 13
#define fwm_int_en 14
#define drdy_int_en 15

#define axis_x 1
#define axis_y 2
#define axis_xy 3
#define axis_z 4
#define axis_xz 5
#define axis_yz 6
#define axis_xyz 7

#define step_int1 0
#define step_int2 4
#define tap_int1 2
#define tap_int2 6
#define actch_int1 3
#define actch_int2 7

typedef enum{
    CHANGE_ORIENT,
    INT1,
    INT2,
    TAP_CONFIG,
    STEP_CONFIG,
}config_t;

typedef struct
{
int X;
int Y;
int Z;
}ACC;

typedef struct
{
uint8_t AXIS_SELECT;
uint8_t DATA_SRC;
uint8_t ORIENT_REF_UPDATE;
uint8_t STABILITY_MODE;
uint8_t ORIENT_TRESH;
uint8_t STABILITY_TRESH;
uint8_t ORIENT_DUR;
uint16_t ORIENT_REF_X;
uint16_t ORIENT_REF_Y;
uint16_t ORIENT_REF_Z;
} Param_orient_change;

typedef struct
{
uint8_t AXIS_SELECT;
bool DATA_SRC;
uint8_t GEN1_REF_UPDATE;
uint8_t GEN1_ACT_HYST;
bool CRITERION_SEL;
bool COMB_SEL;
uint8_t GEN_INT1_TRESH;
uint16_t GEN_INT1_DUR;
uint16_t INT1_REF_X;
uint16_t INT1_REF_Y;
uint16_t INT1_REF_Z;
} Param_genint1;

typedef struct
{
uint8_t AXIS_SELECT;
uint8_t DATA_SRC;
uint8_t GEN2_REF_UPDATE;
uint8_t GEN2_ACT_HYST;
bool CRITERION_SEL;
bool COMB_SEL;
uint8_t GEN_INT2_TRESH;
uint16_t GEN_INT2_DUR;
uint16_t INT2_REF_X;
uint16_t INT2_REF_Y;
uint16_t INT2_REF_Z;
} Param_genint2;

typedef struct 
{
uint8_t AXIS_SELECT;
uint8_t SAMPLES;
uint8_t REF_UPDATE;
uint8_t TRESHOLD;
uint8_t REF_X;
uint8_t REF_Y;
uint8_t REF_Z;
} param_wakeup;

void initBMP(i2c_inst_t *INSTANCE);
void enablestep(void);
void set_G_range(uint8_t range);
void filt1_BW(bool state);
void softreset(void);
void clearstepcount(void);
void stepstate(void);
void conf_orientation_change(Param_orient_change *this );
void conf_genint1(Param_genint1 *this );
void conf_genint2(Param_genint2 *this );
void fifoflush(void);
void setmode(int8_t mode);
void readACC(ACC *this);
int stepcount(void);
void set_interrupt(int interrupt,bool state);
void mapinterrupt1(u_int8_t inter,bool state);
void mapinterrupt2(uint8_t inter,bool state);
void mapinterrupt12 (uint8_t inter,bool state);
void setautolowpower(uint16_t treshold , uint8_t timeout,bool genint,bool dataready);
void setautowakeup(uint16_t treshold,bool wakeup_timeout,bool wake_int);
void configwakeup(param_wakeup *this);
void config_tap(uint8_t axis , uint8_t sensitivity ,uint8_t quiet_dt,uint8_t quiet,uint8_t tics_th);
void check_tap(void);






