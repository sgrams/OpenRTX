/***************************************************************************
 *   Copyright (C) 2021 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN                             *
 *                         Frederik Saraci IU2NRO                          *
 *                         Silvano Seva IU2KWO,                            *
 *                         Federico Terraneo                               *
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

/***********************************************************************
* bsp.cpp Part of the Miosix Embedded OS.
* Board support package, this file initializes hardware.
************************************************************************/

#include <interfaces/gpio.h>
#include <interfaces/bsp.h>
#include <kernel/kernel.h>
#include <kernel/sync.h>
#include <hwconfig.h>
#include <UART0.h>

namespace miosix
{

//
// Initialization
//

void IRQbspInit()
{
    SIM->SCGC5 |= 0x3E00;   // Enable GPIO clock
}

void bspInit2()
{
    #ifdef PLATFORM_HD1
    // Initialise UART0 driver for stdio redirection
    gpio_setMode(UART_RX, INPUT);
    gpio_setMode(UART_TX, OUTPUT);
    gpio_setAlternateFunction(UART_RX, 0);
    gpio_setAlternateFunction(UART_TX, 0);
    uart0_init(115200);
    #endif
}

//
// Shutdown and reboot
//

void shutdown()
{
    reboot();
}

void reboot()
{
    disableInterrupts();
    miosix_private::IRQsystemReboot();
}

} //namespace miosix
