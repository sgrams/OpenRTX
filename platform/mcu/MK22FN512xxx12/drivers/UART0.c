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

#include <hwconfig.h>
#include "UART0.h"

void uart0_init(unsigned int baudrate)
{
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);

    /*
     * Port baud rate is set using a 13-bit counter with 5-bit fractional part
     * for fine tuning. From reference manual we have that equation for baud
     * rate is: baud = clk/(16*(SBR[12:0] + BRFD)).
     *
     * UART0 uses as input clock source the core clock, running at 119.808MHz.
     * Values for SBR and BRFD can be easily calculated using 13.5 fixed point
     * math.
     *
     * See also K22F Sub-Family Reference Manual at page 1279.
     */

    uint32_t ratio = (119808000 << 5) / (16 * baudrate);

    /* Set fractional part */
    UART0->C4 = ratio & 0x1F;

    /* Discard fraction and set integer part */
    ratio >>= 5;
    UART0->BDH = ratio >> 8;
    UART0->BDL = ratio & 0xFF;

    UART0->C2  = UART_C2_TE(1);  /* Enable transmission */
}

void uart0_terminate()
{
    SIM->SCGC4 &= ~SIM_SCGC4_UART0(1);
}

ssize_t uart0_readBlock(void *buffer, const size_t size)
{
    (void) buffer;
    (void) size;

    return 0;
}

ssize_t uart0_writeBlock(const void *buffer, const size_t size)
{
    const char *buf = ((const char*) buffer);
    for(size_t i = 0; i < size; i++)
    {
        while((UART0->S1 & UART_S1_TDRE_MASK) == 0) ;
        UART0->D = *buf++;
    }

    return size;
}
