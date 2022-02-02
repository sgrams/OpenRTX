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

#define BUS_CLOCK 59904000  /* Bus clock, 59.904MHz */

void uart0_init(unsigned int baudrate)
{
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);

    const unsigned int quot = (2*BUS_CLOCK)/baudrate;
    unsigned int ratio      = quot/2 + (quot & 1);

    UART0->BDH = ratio >> 8;
    UART0->BDL = ratio & 0xFF;

    UART0->C2  = UART_C2_TE(1);  /* Enable transmission */
}

void uart0_terminate()
{
    SIM->SCGC4 &= ~SIM_SCGC4_UART0(1);
}

ssize_t uart0_readBlock(void *buffer, size_t size, off_t where)
{
    (void) buffer;
    (void) size;
    (void) where;

    return 0;
}

ssize_t uart0_writeBlock(void *buffer, size_t size, off_t where)
{
    (void) where;

    const char *buf = ((const char*) buffer);
    for(size_t i = 0; i < size; i++)
    {
        while((UART0->S1 & UART_S1_TDRE_MASK) == 0) ;
        UART0->D = *buf++;
    }

    return size;
}