/***************************************************************************
 *   Copyright (C) 2022 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <interfaces/platform.h>
#include <interfaces/gpio.h>
#include <stddef.h>
#include <UART0.h>
#include "hwconfig.h"

void platform_init()
{
    /* Configure GPIOs */
    gpio_setMode(GREEN_LED, OUTPUT);
    gpio_setMode(RED_LED,   OUTPUT);

    /*
     * Initialise UART0 driver
     */
    gpio_setMode(UART_RX, INPUT);
    gpio_setMode(UART_TX, OUTPUT);
    gpio_setAlternateFunction(UART_RX, 0);
    gpio_setAlternateFunction(UART_TX, 0);
    uart0_init(115200);
}

void platform_terminate()
{
    gpio_clearPin(RED_LED);
    gpio_clearPin(GREEN_LED);

    uart0_terminate();
}

uint16_t platform_getVbat()
{
    /* TODO */
    return 0;
}

uint8_t platform_getMicLevel()
{
    /* TODO */
    return 0;
}

uint8_t platform_getVolumeLevel()
{
    /* TODO */
    return 0;
}

int8_t platform_getChSelector()
{
    /* TODO */
    return 0;
}

bool platform_getPttStatus()
{
    /* TODO */
    return false;
}

bool platform_pwrButtonStatus()
{
    /* TODO */
    return false;
}

void platform_ledOn(led_t led)
{
    switch(led)
    {
        case GREEN:
            gpio_setPin(GREEN_LED);
            break;

        case RED:
            gpio_setPin(RED_LED);
            break;

        default:
            break;
    }
}

void platform_ledOff(led_t led)
{
    switch(led)
    {
        case GREEN:
            gpio_clearPin(GREEN_LED);
            break;

        case RED:
            gpio_clearPin(RED_LED);
            break;

        default:
            break;
    }
}

void platform_beepStart(uint16_t freq)
{
    /* TODO */

    (void) freq;
}

void platform_beepStop()
{
    /* TODO */
}

const void *platform_getCalibrationData()
{
    /* TODO */
    return NULL;
}

const hwInfo_t *platform_getHwInfo()
{
    /* TODO */
    return NULL;
}

void platform_setBacklightLevel(uint8_t level)
{
    /* TODO */
}