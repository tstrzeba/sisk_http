/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * $Id: clock-arch.c,v 1.2 2006/06/12 08:00:31 adam Exp $
 */

/**
 * \file
 *         Implementation of architecture-specific clock functionality
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

//Renesas
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 17.02.2012                 Ported to YRDKRX63N              
*******************************************************************************/
/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "platform.h"

#include "clock-arch.h"

#pragma interrupt int_cmt0_isr(vect=VECT(CMT0,CMI0))

#define TICK_INTERVAL 9375
clock_time_t timer_clock_ticks = 0;


/**
 * System timer tick initialization
 *
 * This function initializes a timer interrupt with 100ms tick. 
 *
 */
void  timer_init(void)
{
#if defined(MCU_RX63N) || defined(MCU_RX630) || defined(MCU_RX631)
    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA50B;	 
#endif      
    /* Take the CMT out of the stop state */     
    MSTP(CMT0) = 0 ;
#if defined(MCU_RX63N) || defined(MCU_RX630) || defined(MCU_RX631)
    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA500;	 
#endif 
  
    /* Configure CMT0 for a 100ms interval */
    CMT.CMSTR0.BIT.STR0 = 0 ;           // Stop the clock 
                                        // Trigger 10 uS from now
    CMT0.CMCOR = CMT0.CMCNT + TICK_INTERVAL ;
    //CMT0.CMCR.BIT.CMIE = 1 ;            // Enable interrupts, clock = PCLK/8 (6.25 MHz)
    CMT0.CMCR.WORD = 0x0043;            // Enable interrupt, clock = PCLK/512
    IPR(CMT0, CMI0) = 0x01 ;            // Set timer interrupt priority
    IEN(CMT0, CMI0) = 1 ;               // Enable the interrupt in the ICU
    CMT.CMSTR0.BIT.STR0 = 1 ;           // Start the clock running
  
}

/**
 * System timer tick 
 *
 * This function is called from timer interrupt to increment a 
 * system timer tick.  Also an LED on the target board is 
 * toggled to show activity. 
 *
 */
void int_cmt0_isr(void)
{
#if PLATFORM_RSK63N==1    
    LED3 = ~LED0 ;
#elif PLATFORM_RDK63N==1
    LED4 = ~LED4 ;
#endif    	      

    timer_clock_ticks++;
}


/*---------------------------------------------------------------------------*/
clock_time_t
clock_time(void)
{
  return timer_clock_ticks;
}
/*---------------------------------------------------------------------------*/

