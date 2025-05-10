/*
 * Copyright (c) 2018-2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== i2ctmp.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* Driver Header files */
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/Timer.h>

#include "bq25890.h"

/* Driver configuration */
#include "ti_drivers_config.h"

Timer_Handle ms_timer;
Timer_Params ms_timer_params;

void *mainThread(void *arg0)
{
    I2C_Handle i2c;
    I2C_Params i2cParams;
    I2C_Transaction i2cTransaction;

    /* Call driver init functions */
    Timer_init();
    I2C_init();

    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;
    i2c               = I2C_open(CONFIG_I2C_TMP, &i2cParams);

    // Setup the UART Port
    UART2_Handle uart;
    UART2_Params uart_params;
    UART2_Params_init(&uart_params);
    uart_params.baudRate = 115200;
    uart_params.readMode = UART2_Mode_BLOCKING;
    uart_params.writeMode = UART2_Mode_BLOCKING;
    uart = UART2_open(CONFIG_UART2_0, &uart_params);

    Timer_Params_init(&ms_timer_params);
    ms_timer_params.periodUnits = Timer_PERIOD_US;
    ms_timer_params.period = 1000;
    ms_timer_params.timerMode = Timer_ONESHOT_BLOCKING;
    ms_timer_params.timerCallback = NULL;
    ms_timer = Timer_open(CONFIG_TIMER_0, &ms_timer_params);

    char print_buff[100];
    uint16_t print_buff_len;
    size_t bytes_logged;
    int test_count = 0;

    BQ25890 bq25890 = BQ25890(i2c, ms_timer, uart);

    while(true)
    {
        print_buff_len = sprintf(print_buff, "Test count: %i\n\r", test_count);
        UART2_write(uart, print_buff, print_buff_len, &bytes_logged);
        test_count++;

        bq25890.set_wd_rst();
        //get bus voltages
        bq25890.print_bus_voltage();
        bq25890.print_bus_voltage_milli();
        //get battery voltage
        bq25890.print_battery_voltage();
        bq25890.print_battery_voltage_milli();
        //get status
        bq25890.print_charging_status();
        bq25890.print_vbus_status();
        bq25890.print_vbus_gd_status();
        bq25890.print_ntc_fault_status();
        //get system voltage
        bq25890.print_system_voltage();
        bq25890.print_system_voltage_milli();
        //get charge current
        bq25890.print_charge_current();
        bq25890.print_charge_current_milli();

        for(int i = 0; i < 1000000; i++)
            Timer_start(ms_timer);
    }
}
