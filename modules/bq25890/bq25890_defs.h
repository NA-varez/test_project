#ifndef BQ25890_DEFS_H_
#define BQ25890_DEFS_H_

/*
BQ25890 Definitions -can be found at following link, with starting at page 36
https://www.ti.com/lit/ds/symlink/bq25892.pdf?ts=1705114720023&ref_url=https%253A%252F%252Fwww.google.com%252F

Written in accordance to document Revision D/October 2022
*/

#include <stdint.h>
#include <stddef.h>

/* Register Address Name Defintions */
// REG00
#define HIZ_MODE_EN_REG             UINT8_C(0x00)
#define ILIM_PIN_EN_REG             UINT8_C(0x00)
#define ILIM_REG                    UINT8_C(0x00)

// REG01
#define OTG_HOT_TEMP_REG            UINT8_C(0x01)
#define OTG_COLD_TEMP_REG           UINT8_C(0x01)
#define INPUT_VOLTAGE_OFFSET_REG    UINT8_C(0x01)

// REG02
#define ADC_CONV_START_REG          UINT8_C(0x02)
#define ADC_CONV_RATE_REG           UINT8_C(0x02)
#define BOOST_FREQ_SEL_REG          UINT8_C(0x02)
#define ICO_EN_REG                  UINT8_C(0x02)
#define HVDCP_EN_REG                UINT8_C(0x02)
#define MAX_CHG_EN                  UINT8_C(0x02)
#define FORCE_DPDM_REG              UINT8_C(0x02)
#define AUTO_DPDM_EN                UINT8_C(0x02)

// REG03
#define BAT_LOADEN                  UINT8_C(0x03)
#define WATCH_DOG_RST_REG           UINT8_C(0x03)
#define OTG_CONFIG_REG              UINT8_C(0x03)
#define CHG_CONFG                   UINT8_C(0x03)
#define MIN_SYS_VLIM_REG            UINT8_C(0x03)

// REG04
#define EN_PUMPX_REG                UINT8_C(0x04)
#define FAST_CHG_CURR_LIM_REG       UINT8_C(0x04)

// REG05
#define PRECHG_CURR_LIM_REG         UINT8_C(0x05)
#define TERM_CURR_LIM_REG           UINT8_C(0x05)

// REG06
#define CHG_VOLTAGE_LIM_REG         UINT8_C(0x06)
#define BAT_PRECHG_LOW_V_REG        UINT8_C(0x06)
#define BAT_RECHG_V_OFFSET_REG      UINT8_C(0x06)

// REG07
#define CHG_TERM_EN_REG             UINT8_C(0x07)
#define STAT_PIN_REG                UINT8_C(0x07)
#define WATCHDOG_TMR_REG            UINT8_C(0x07)
#define EN_CHG_SAFETY_TMR_REG       UINT8_C(0x07)
#define FAST_CHG_TMR_REG            UINT8_C(0x07)
#define JEITA_LOW_TEMP_CURR_REG     UINT8_C(0x07)

// REG08
#define IR_COMP_RES_REG             UINT8_C(0x08)
#define IR_COMP_V_CLAMP_REG         UINT8_C(0x08)
#define THERM_THRES_REG             UINT8_C(0x08)

// REG09
#define FORCE_ICO_REG               UINT8_C(0x09)
#define TMR_THERM_DPM_REG           UINT8_C(0x09)
#define BATFET_DIS_REG              UINT8_C(0x09)
#define JETITA_VSET_REG             UINT8_C(0x09)
#define BATFET_DLY_REG              UINT8_C(0x09)
#define BATFET_RST_EN_REG           UINT8_C(0x09)
#define PUMPX_UP_REG                UINT8_C(0x09)
#define PUMPX_DN_REG                UINT8_C(0x09)

// REG0A
#define BOOST_VOLT_REG              UINT8_C(0x0A)
#define BOOST_CURR_LIM_REG          UINT8_C(0x0A)

// REG0B
#define VBUS_STAT_REG               UINT8_C(0x0B)              
#define CHRG_STAT_REG               UINT8_C(0x0B)
#define PG_STAT_REG                 UINT8_C(0x0B)
#define VSYS_STAT_REG               UINT8_C(0x0B)

// REG0C
#define WATCH_DOG_FAULT_REG         UINT8_C(0x0C)
#define BOOST_FAULT_REG             UINT8_C(0x0C)
#define CHRG_FAULT_REG              UINT8_C(0x0C)
#define BAT_FAULT_REG               UINT8_C(0x0C)
#define NTC_FAULT_REG               UINT8_C(0x0C)

// REG0D
#define FORCE_VINDPM_REG            UINT8_C(0x0D)
#define VINDPM_REG                  UINT8_C(0x0D)

// REG0E
#define THERM_REGU_REG              UINT8_C(0x0E)
#define BAT_VOLT_REG               UINT8_C(0x0E)

// REG0F
#define VSYS_VOLT_REG               UINT8_C(0x0F)

// REG10
#define TEMP_VOLT_REG               UINT8_C(0x10)

// REG11
#define VBUS_ATTCH_REG              UINT8_C(0x11)
#define VBUS_VOLT_REG               UINT8_C(0x11)

// REG12
#define CHG_CURR_REG                UINT8_C(0x12)

// REG13
#define VINDPM_STAT_REG             UINT8_C(0x13)
#define IINDPM_STAT_REG             UINT8_C(0x13)
#define IINDPM_CURR_LIM_REG         UINT8_C(0x13)

// REG14
#define REGISTERS_RST_REG           UINT8_C(0x14)
#define ICO_STAT_REG                UINT8_C(0x14)
#define DEV_CFG_REG                 UINT8_C(0x14)
#define TS_PROF_REG                 UINT8_C(0x14)
#define DEV_REV_REG                 UINT8_C(0x14)

/* Register Reading Conversion Constants */
/* ADC Battery Voltage Constants */
#define BAT_VOLTAGE_LSB             UINT16_C(20)    // 20 mV
#define BAT_VOTLAGE_OFFSET          UINT16_C(2304)  // 2.304 V

#define BAT_VOLTAGE_MASK            UINT8_C(0x7F)

/* ADC System Voltage Constants */
#define SYS_VOLTAGE_LSB             UINT8_C(20)    // 20 mV
#define SYS_VOLTAGE_OFFSET          UINT16_C(2304)  // 2.304 V

#define SYS_VOLTAGE_MASK            UINT8_C(0x7F)

/* ADC VBUS Voltage Constants */
#define VBUS_VOLTAGE_LSB            UINT16_C(100)   // 100 mV
#define VBUS_VOLTAGE_OFFSET         UINT16_C(2600)  // 2.6 V

#define BUS_VOLTAGE_MASK            UINT8_C(0x7F)

/* ADC Charge Current Constants */
#define CHG_CURR_LSB                UINT8_C(50)    // 50 mA
#define CHG_CURR_OFFSET             UINT8_C(0x00)   // 0 mA

#define CHG_CURR_MASK               UINT8_C(0x7F)

/* Status Constant Names and Masks*/
/* VBUS Status */
// Constants
#define VBUS_STAT_NO_INPUT          UINT8_C(0x00)
#define VBUS_STAT_USB_SDP           UINT8_C(0x20)
#define VBUS_STAT_USB_CDP           UINT8_C(0x40)
#define VBUS_STAT_USB_DCP           UINT8_C(0x60)
#define VBUS_STAT_MAX_CHARGE        UINT8_C(0x80)
#define VBUS_STAT_UNKNOWN_ADPT      UINT8_C(0xA0)
#define VBUS_STAT_NON_STD_ADPT      UINT8_C(0xC0)
#define VBUS_STAT_OTG               UINT8_C(0xE0)

// Mask
#define VBUS_STATUS_MASK            UINT8_C(0xE0)

/* VBUS GD Status */
#define VBUS_ATTACHED               UINT8_C(0x80)
#define VBUS_NOT_ATTACHED           UINT8_C(0x00)

#define VBUS_ATTCH_MASK             UINT8_C(0x80)

/* Charging Status */
// Constants
#define CHG_STATUS_NOT_CHARGING     UINT8_C(0x00)
#define CHG_STATUS_PRE_CHARGE       UINT8_C(0x08)
#define CHG_STATUS_FAST_CHARGING    UINT8_C(0x10)
#define CHG_STATUS_CHARGE_TERM      UINT8_C(0x18)

/* Input Current Limit With ICO*/
// Constants
#define INPUT_CURRENT_LIM_LSB       UINT16_C(50)
#define INPUT_CURRENT_LIM_OFFSET    UINT16_C(100)

// Mask
#define INPUT_CURRENT_LIM_MASK      UINT8_C(0x3F)

// Mask
#define CHG_STATUS_MASK             UINT8_C(0x18)

/* Watchdog Fault */
// Constants
#define WATCHDOG_FAULT_NORMAL       UINT8_C(0x00)
#define WATCHDOG_FAULT_TMR_EXPR     UINT8_C(1 << 7)

/* ADC Conversion */
// Masks
#define CONV_START_MASK             UINT8_C(0x80)

// Mask
#define WATCHDOG_FAULT_MASK         UINT8_C(1 << 7)     

/* Boost Mode Fault */
// Constants
#define BOOST_FAULT_NORMAL          UINT8_C(0x00)
#define BOOST_FAULT_VBUS_OVERLOADED UINT8_C(1 << 6)

// Mask
#define BOOST_FAULT_MASK            UINT8_C(1 << 6)

/* Charge Fault */
// Constants
#define CHRG_FAULT_NORMAL           UINT8_C(0x00)
#define CHRG_FAULT_INPUT_FAULT      UINT8_C(1 << 4)
#define CHRG_FAULT_THERM_SHTDN      UINT8_C(1 << 5)
#define CHRG_FAULT_SAFETY_TMR_EXPR  UINT8_C(3 << 4)

// Mask
#define CHRG_FAULT_MASK             UINT8_C(3 << 4)

/* Battery Fault */
// Constants
#define BAT_FAULT_NORMAL            UINT8_C(0x00)
#define BAT_FAULT_OVP               UINT8_C(0x08)

// Mask
#define BAT_FAULT_MASK              UINT8_C(0x08)

/* NTC Fault */
// Constants
#define NTC_FAULT_TS_NORMAL         UINT8_C(0b000)
#define NTC_FAULT_TS_WARM           UINT8_C(0b010)
#define NTC_FAULT_TS_COOL           UINT8_C(0b011)
#define NTC_FAULT_TS_COLD           UINT8_C(0b101)
#define NTC_FAULT_TS_HOT            UINT8_C(0b110)          

// NTC Fault Status Postiive Bit Mask
#define NTC_FAULT_MASK              UINT8_C(0x07)

/* ICO Status */
// Constants
#define ICO_STAT_IN_PROGRESS        UINT8_C(0x00)
#define ICO_STAT_MAX_DETECTED       UINT8_C(1 << 6)

#define ICO_STAT_MASK               UINT8_C(1 << 6)

/* Device Configuration */
#define DEVICE_CONFIG_BQ25890       UINT8_C(3 << 3)
#define DEVICE_CONFIG_BQ25892       UINT8_C(0x00)

#define DEVICE_CONFIG_MASK          UINT8_C(7 << 3)          

/* DPDM Handshake */
// Masks
#define FORCE_DPDM_MASK             UINT8_C(0x02);

/* Watch Dog Configuration */
// Masks
#define WD_RST_MASK                 UINT8_C(0x40)

/* Stat Light/Pin */
// Masks
#define STAT_PIN_OFF_MASK           UINT8_C(0xBF)
#define STAT_PIN_ON_MASK            UINT8_C(0x40)

/* Temperature Profile */
// Constants
#define JEITA_TS_PROFILE            UINT8_C(1 << 2)

#define JEITA_TS_PROFILE_MASK       UINT8_C(1 << 2)

/* Device Revision */
#define DEVICE_REVISION             UINT8_C(0x01)

#define DEVICE_REV_MASK             UINT8_C(0x03)


/* Device Reset */
#define REG_RST_MASK                UINT8_C(0x80)

/* BAT FET Disable */
#define BATFET_DIS_MASK             UINT8_C(0x20)

#endif