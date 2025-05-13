#ifndef BQ25890_H
#define BQ25890_H

/*
BQ25890 Register Addresses - can be found at following link, with starting at page 36
https://www.ti.com/lit/ds/symlink/bq25892.pdf?ts=1705114720023&ref_url=https%253A%252F%252Fwww.google.com%252F
*/
#include <stdio.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/Timer.h>

class BQ25890 {
    public:
        // Constructor
        BQ25890(I2C_Handle i2c_port, Timer_Handle ms_timer, UART2_Handle uart);

        // Write Methods
        // Stat of host mode
        void set_wd_rst();
        void set_start_conv();
        uint8_t get_start_conv();

        void force_dpdm_detect();

        // Self turnoff/kill
        void kill_self();

        // Main funcitons
        uint8_t get_vbus_status();
        void print_vbus_status();

        uint8_t get_vbus_gd_status();
        void print_vbus_gd_status();

        uint8_t get_charging_status();
        void print_charging_status();

        uint16_t get_input_current_lim_w_ico();
        void print_input_current_lim_w_ico();
        void print_input_current_lim_w_ico_milli();

        uint8_t get_bat_fault_status();
        void print_bat_fault_status();

        uint8_t get_ntc_fault_status();
        void print_ntc_fault_status();

        void turn_off_stat_light();
        void turn_on_stat_light();

        /* ADC Functions */
        // Battery Voltage Functions
        uint16_t get_battery_voltage();
        void print_battery_voltage();
        void print_battery_voltage_milli();

        // System Voltage Functions
        uint16_t get_system_voltage();
        void print_system_voltage();
        void print_system_voltage_milli();

        // USB VBUS Voltage Functions
        uint16_t get_bus_voltage();
        void print_bus_voltage();
        void print_bus_voltage_milli();

        // Charge Current Functions
        uint16_t get_charge_current();
        void print_charge_current();
        void print_charge_current_milli();

        // Simple Device IC Constants for testing
        uint8_t get_ico_status();
        uint8_t get_dev_config();
        uint8_t get_dev_rev();

        //timer functions
        void busy_wait_ms(uint32_t ms_wait);
        void print_test_count(uint32_t time_count);

        void reset_registers();

        void print_all_registers();
    private:
        // Private class variables
        static const uint8_t i2c_addr = 0x6A;

        //print buff to print to uart
        char print_buff[100];
        uint16_t print_buff_len;
        size_t bytes_logged;

        //for i2c
        I2C_Transaction transaction;
        I2C_Handle i2c_port;

        //for uart
        UART2_Handle uart;

        //for timer
        Timer_Handle ms_timer;

        // Private class functions
        void complete_adc_conversion();
        void read_register(uint8_t reg_addr, uint8_t* read_data);
        void write_register(uint8_t reg_addr, uint8_t write_data);
};

#endif
