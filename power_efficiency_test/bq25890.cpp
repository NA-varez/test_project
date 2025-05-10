#include "bq25890.h"
#include "bq25890_defs.h"
#include <stdio.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/Timer.h>

BQ25890::BQ25890(I2C_Handle i2c_port, Timer_Handle ms_timer, UART2_Handle uart)
{  //change to i2c handle, look at how gnss code did, done
    this->i2c_port = i2c_port;
    this->ms_timer = ms_timer;
    this->uart = uart;
}

void BQ25890::set_wd_rst() // no changes required
{
    uint8_t wd_rst;
    read_register(0x03, &wd_rst); //removed &wd_rst

    wd_rst |= WD_RST_MASK;
    write_register(0x03, wd_rst);
}

void BQ25890::set_start_conv() //ncr
{
    uint8_t conv_st_reg;
    read_register(ADC_CONV_START_REG, &conv_st_reg);//removed

    conv_st_reg |= CONV_START_MASK;
    write_register(ADC_CONV_START_REG, conv_st_reg);
}

uint8_t BQ25890::get_start_conv() //ncr
{
    uint8_t conv_st_reg;
    read_register(ADC_CONV_START_REG, &conv_st_reg);//removed

    return (conv_st_reg & CONV_START_MASK);
}

void BQ25890::complete_adc_conversion() //change sleep_ms, d
{
    set_start_conv();
 
    uint8_t retries = 0;
    while(get_start_conv() && retries < 20)
    {
        busy_wait_ms(50);
        retries++;
    }
}

void BQ25890::busy_wait_ms(uint32_t ms_wait)// i think done
{
    for(uint32_t i = 0; i < ms_wait; i++)
        Timer_start(ms_timer);
}

void BQ25890::force_dpdm_detect() //ncr
{
    uint8_t reg02_res;
    read_register(FORCE_DPDM_REG, &reg02_res);

    reg02_res |= FORCE_DPDM_MASK;
    write_register(FORCE_DPDM_REG, reg02_res);
}

void BQ25890::kill_self() //ncr
{
    uint8_t reg09_res;
    read_register(BATFET_DIS_REG, &reg09_res);

    reg09_res |= BATFET_DIS_MASK;
    write_register(BATFET_DIS_REG, reg09_res);
}

// Important Status Registers
uint8_t BQ25890::get_vbus_status() //ncr
{
    uint8_t vbus_status;
    read_register(VBUS_STAT_REG, &vbus_status);

    vbus_status &= VBUS_STATUS_MASK;
    return vbus_status;
}

void BQ25890::print_vbus_status() //change prints to uart calls
{
    uint8_t vbus_status = get_vbus_status();
    uint32_t status     = UART2_STATUS_SUCCESS;

    switch (vbus_status)
    {
        case VBUS_STAT_NO_INPUT:
            print_buff_len = sprintf(print_buff, "VBUS Status: No Input\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_USB_SDP:
            print_buff_len = sprintf(print_buff, "VBUS Status: USB Host Standard Downstream Port (SDP)\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_USB_CDP:
            print_buff_len = sprintf(print_buff, "VBUS Status: USB Host Charging Downstream Port (CDP)\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_USB_DCP:
            print_buff_len = sprintf(print_buff, "VBUS Status: USB Host Dedicated Charging Port (DCP)\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_MAX_CHARGE:
            print_buff_len = sprintf(print_buff, "VBUS Status: Adjustable HVDCP (MaxCharge)\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_UNKNOWN_ADPT:
            print_buff_len = sprintf(print_buff, "VBUS Status: Unknown Adapter\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_NON_STD_ADPT:
            print_buff_len = sprintf(print_buff,"VBUS Status: Non-Standard Adapter\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_STAT_OTG:
            print_buff_len = sprintf(print_buff,"VBUS Status: OTG\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;

    }
}

uint8_t BQ25890::get_vbus_gd_status() //ncr
{
    uint8_t vbus_gd_status;
    read_register(VBUS_ATTCH_REG, &vbus_gd_status);

    vbus_gd_status &= VBUS_ATTCH_MASK;
    return vbus_gd_status;
}

void BQ25890::print_vbus_gd_status() //change prints
{
    uint8_t vbus_gd_status = get_vbus_gd_status();
    switch (vbus_gd_status)
    {
        case VBUS_ATTACHED:
            print_buff_len = sprintf(print_buff,"VBUS Attached\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case VBUS_NOT_ATTACHED:
            print_buff_len = sprintf(print_buff,"VBUS Not Attached\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
    }
}

uint8_t BQ25890::get_charging_status() //ncr
{
    uint8_t chg_status;
    read_register(CHRG_STAT_REG, &chg_status);

    chg_status &= CHG_STATUS_MASK;
    return chg_status;
}

void BQ25890::print_charging_status() //change prints
{
    uint8_t chg_status = get_charging_status();
    switch (chg_status)
    {
        case CHG_STATUS_NOT_CHARGING:
            print_buff_len = sprintf(print_buff,"Charging Status: Not Currently Charging\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case CHG_STATUS_PRE_CHARGE:
            print_buff_len = sprintf(print_buff,"Charging Status: Pre-charging\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case CHG_STATUS_FAST_CHARGING:
            print_buff_len = sprintf(print_buff,"Charging Status: Fast-charging\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case CHG_STATUS_CHARGE_TERM:
            print_buff_len = sprintf(print_buff,"Charging Status: Charging Terminated / Done\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
    }
}

uint16_t BQ25890::get_input_current_lim_w_ico() //ncr
{
    uint8_t input_current_limit;
    read_register(IINDPM_CURR_LIM_REG, &input_current_limit);

    input_current_limit &= INPUT_CURRENT_LIM_MASK;
    uint16_t conv_input_curr_lim = (input_current_limit * INPUT_CURRENT_LIM_LSB) + INPUT_CURRENT_LIM_OFFSET;

    return conv_input_curr_lim;
}

void BQ25890::print_input_current_lim_w_ico() //print
{
    print_buff_len = sprintf(print_buff,"Input Current Limit (A): %f\n\r", get_input_current_lim_w_ico() / 1000.0f);
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

void BQ25890::print_input_current_lim_w_ico_milli() //print, use as case
{
    print_buff_len = sprintf(print_buff, "Input Current Limit (mA): %i\n\r", get_input_current_lim_w_ico());
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

uint8_t BQ25890::get_bat_fault_status() //ncr
{
    uint8_t bat_fault_status;
    read_register(BAT_FAULT_REG, &bat_fault_status);

    bat_fault_status &= BAT_FAULT_MASK;

    return bat_fault_status;
}

void BQ25890::print_bat_fault_status() //print
{
    uint8_t bat_fault_status = get_bat_fault_status();
    switch (bat_fault_status)
    {
        case BAT_FAULT_NORMAL:
            print_buff_len = sprintf(print_buff,"Battery Fault: No Fault\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case BAT_FAULT_OVP:
            print_buff_len = sprintf(print_buff,"Battery Fault: Over Voltage Protection\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
    }
}

uint8_t BQ25890::get_ntc_fault_status() //ncr
{
    uint8_t ntc_fault_status;
    read_register(NTC_FAULT_REG, &ntc_fault_status);

    ntc_fault_status &= NTC_FAULT_MASK;
    
    return ntc_fault_status;
}

void BQ25890::print_ntc_fault_status() //print
{
    uint8_t ntc_fault_status = get_ntc_fault_status();
    switch (ntc_fault_status)
    {
        case NTC_FAULT_TS_NORMAL:
            print_buff_len = sprintf(print_buff,"NTC Fault Status: Normal\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case NTC_FAULT_TS_WARM:
            print_buff_len = sprintf(print_buff,"NTC Fault Status: Warm\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case NTC_FAULT_TS_COOL:
            print_buff_len = sprintf(print_buff,"NTC Fault Status: Cool\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case NTC_FAULT_TS_COLD:
            print_buff_len = sprintf(print_buff,"NTC Fault Status: Cold\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
        case NTC_FAULT_TS_HOT:
            print_buff_len = sprintf(print_buff,"NTC Fault Status: Hot\n\r");
            UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
            break;
    }
}

void BQ25890::turn_off_stat_light() //ncr
{
    uint8_t curr_stat_reg;
    read_register(STAT_PIN_REG, &curr_stat_reg);

    curr_stat_reg |= STAT_PIN_ON_MASK;
    write_register(STAT_PIN_REG, curr_stat_reg);
}

void BQ25890::turn_on_stat_light() //ncr
{
    uint8_t curr_stat_reg;
    read_register(STAT_PIN_REG, &curr_stat_reg);

    curr_stat_reg &= STAT_PIN_OFF_MASK;
    write_register(STAT_PIN_REG, curr_stat_reg);
}

/*
   ADC reading and standard output 
   formatting functions. 
   Everything from chip is in millivolts
*/
/* Battery Voltage Functions */
uint16_t BQ25890::get_battery_voltage() //ncr
{
    complete_adc_conversion();

    uint8_t batt_voltage;
    read_register(BAT_VOLT_REG, &batt_voltage);

    batt_voltage &= BAT_VOLTAGE_MASK;

    uint16_t conv_batt_voltage = (batt_voltage * BAT_VOLTAGE_LSB) + BAT_VOTLAGE_OFFSET;

    return conv_batt_voltage;
}

void BQ25890::print_battery_voltage() //print
{
    print_buff_len = sprintf(print_buff, "Battery Voltage (V): %f\n\r", get_battery_voltage() / (1000.0f));
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

void BQ25890::print_battery_voltage_milli() //print
{
    print_buff_len = sprintf(print_buff, "Battery Voltage (mV): %i\n\r", get_battery_voltage());
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

/* System Voltage Functions */
uint16_t BQ25890::get_system_voltage() //ncr
{
    uint8_t sys_voltage;
    read_register(VSYS_VOLT_REG, &sys_voltage);

    sys_voltage &= SYS_VOLTAGE_MASK;
    uint16_t conv_sys_voltage = (sys_voltage * SYS_VOLTAGE_LSB) + SYS_VOLTAGE_OFFSET;

    return conv_sys_voltage;
}

void BQ25890::print_system_voltage() //print
{
    print_buff_len = sprintf(print_buff, "System Voltage (V): %f\n\r", get_system_voltage() / (1000.0f));
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

void BQ25890::print_system_voltage_milli() //print
{
    print_buff_len = sprintf(print_buff, "System Voltage (mV): %i\n\r", get_system_voltage());
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

/* Bus Voltage Functions */
uint16_t BQ25890::get_bus_voltage() //ncr
{
    uint8_t bus_voltage;
    read_register(VBUS_VOLT_REG, &bus_voltage);

    bus_voltage &= BUS_VOLTAGE_MASK;

    uint16_t conv_bus_voltage = (bus_voltage * VBUS_VOLTAGE_LSB) + VBUS_VOLTAGE_OFFSET;

    return conv_bus_voltage;
}

void BQ25890::print_bus_voltage() //print
{
    print_buff_len = sprintf(print_buff, "Bus Voltage/USB Voltage (V): %f\n\r", get_bus_voltage() / (1000.0f));
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

void BQ25890::print_bus_voltage_milli() //print
{
    print_buff_len = sprintf(print_buff, "Bus Voltage/USB Voltage (mV): %i\n\r", get_bus_voltage());
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

uint16_t BQ25890::get_charge_current() //ncr
{
    uint8_t chg_current;
    read_register(CHG_CURR_REG, &chg_current);

    chg_current &= CHG_CURR_MASK;
    uint16_t conv_chg_current = (chg_current * CHG_CURR_LSB) + CHG_CURR_OFFSET;

    return conv_chg_current;
}

void BQ25890::print_charge_current() //print
{
    print_buff_len = sprintf(print_buff, "Charge Current (A): %f\n\r", get_charge_current() / (1000.0f));
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

void BQ25890::print_charge_current_milli() //print
{
    print_buff_len = sprintf(print_buff, "Charge Current (mA): %i\n\r", get_charge_current());
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}
// Simple and Easy Reading functions to test out
uint8_t BQ25890::get_ico_status() //ncr
{
    uint8_t ico_stat;
    read_register(ICO_STAT_REG, &ico_stat);

    return (ico_stat & ICO_STAT_MASK);
}

uint8_t BQ25890::get_dev_config() //ncr
{
    uint8_t dev_conf;
    read_register(DEV_CFG_REG, &dev_conf);

    return (dev_conf & DEVICE_CONFIG_MASK);
}

uint8_t BQ25890::get_dev_rev() //ncr
{
    uint8_t dev_rev;
    read_register(DEV_REV_REG, &dev_rev);

    return (dev_rev & DEVICE_REV_MASK);
}

// Reset all registers
void BQ25890::reset_registers() //ncr
{
    uint8_t reg_reset_wr = REG_RST_MASK;
    write_register(REGISTERS_RST_REG, reg_reset_wr);

    uint8_t reg_reset_res = REG_RST_MASK;
    while( reg_reset_res & REG_RST_MASK ) // Register is set to zero once reset is complete, so wait till that happens
        read_register(REGISTERS_RST_REG, &reg_reset_res);
}

void BQ25890::print_all_registers() //print
{
    for(int i = 0; i < 21; i++)
    {
        uint8_t reg_result;
        read_register(i, &reg_result);
        print_buff_len = sprintf(print_buff, "REG%02x: 0b%02x\n\r", i, reg_result);
        UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
    }
}

// All registers are of size 1 byte and don't need variable length for read and write
void BQ25890::read_register(uint8_t reg_addr, uint8_t* read_data) // i2c_write_blocking and i2c_read_blocking changed to ti versions and prints, see i2ctmp
{
    transaction.targetAddress = i2c_addr;
    transaction.writeBuf = &reg_addr;
    transaction.writeCount = 1;
    transaction.readBuf = read_data;
    transaction.readCount = 1;
    //write to i2c
    I2C_transfer(i2c_port, &transaction);
}

void BQ25890::write_register(uint8_t reg_addr, uint8_t write_data) //same as above //
{
    uint8_t buff[2];
    buff[0]= reg_addr;
    buff[1] = write_data;

    //transaction  setup
    transaction.targetAddress = i2c_addr;
    transaction.writeBuf = buff;
    transaction.writeCount = 2;
    transaction.readCount = 0;
    //write to i2c
    I2C_transfer(i2c_port, &transaction);
}

void BQ25890::print_test_count(uint32_t test_count)
{
    print_buff_len = sprintf(print_buff, "test count : %i\n\r", test_count);
    UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
}

