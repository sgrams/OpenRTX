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
#include <hwconfig.h>
#include "backlight.h"

void backlight_init()
{
    /*
     * Configure backlight PWM: 14.6kHz, 8 bit resolution
     */
    SIM->SCGC6 |= SIM_SCGC6_FTM1(1);           /* Enable clock                     */

    FTM1->CONTROLS[1].CnSC = FTM_CnSC_MSB(1)
                           | FTM_CnSC_ELSB(1); /* Edge-aligned PWM, clear on match */
    FTM1->CONTROLS[1].CnV  = 0;

    FTM1->MOD  = 0xFF;                         /* Reload value                     */
    FTM1->SC   = FTM_SC_PS(5)                  /* Prescaler divide by 32           */
               | FTM_SC_CLKS(1);               /* Enable timer                     */

    gpio_setMode(LCD_BKLIGHT, OUTPUT);
    gpio_setAlternateFunction(LCD_BKLIGHT, 1);
}

void backlight_terminate()
{
    gpio_clearPin(LCD_BKLIGHT);
    SIM->SCGC6 &= ~SIM_SCGC6_FTM1(1);
}

/*
 * This function is defined in platform.h
 */
void platform_setBacklightLevel(uint8_t level)
{
    FTM1->CONTROLS[1].CnV = level;
}
