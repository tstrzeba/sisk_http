/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/******************************************************************************
* File Name     : user-app.c
* Version       : 1.1 FP DH
* H/W Platform  : YRDKRX63N
* Description   : User application that controls the LEDs from a Web page
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 14.02.2012     1.00        First release
*         : 31.05.2012     1.10        Modified for e2studio, graphic reduced
*         							   to fit build < 128KB
*******************************************************************************/

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <string.h>
#include <stdlib.h> // strtoul()
#include <stdio.h>
#include "platform.h"
#include "user-app.h"
#include "uip.h"
#include "httpd-board-data.h"
#include "S12ADC.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define RDK_MAC_LOCATION             0x00107FF2
#define	AD_REF_VOLTAGE	330000	/* A/D reference voltage in 0.01mv units	*/
#define	REF_TEMP_VOLT	126000	/* reference temperature voltage 0.01mv unit	*/
#define	REF_TEMP_TEMP	250	/* reference temperature temp. 0.1°C	*/
#define	VOLT_TEMP_SLOPE	41	/* voltage/temperature slope 0.1mv/°C	*/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
char          LEDbuf[26];
unsigned char LEDflag;


/* MAC address configuration */
/* The factory assigned MAC address should be found in the data flash starting 
   at this location.*/
const struct uip_eth_addr * my_mac = (const struct uip_eth_addr *) RDK_MAC_LOCATION;

/**
* Device specific configuration parameters in flash are defined here.
* These parameters can be serial number, model name, etc.                           
*                                                                                   
* The size of this section is 64 bytes and all members must be                      
* defined as constants.                                                             
*                                                                                   
* Name              Size (bytes)    Info                                            
* -----            --------------  ------                                           
* my_mac              6             Must be unique per device                       
* my_ip               4             Default IP address if DHCP server not available 
* my_netmask          4             Default net mask                                
* my_default_router   4             Default router address                          
*/
#pragma section _FLASH_CONFIG_PARAMS
/* Initialize default MAC to Renesas range. First 4 bytes are used as validation
   filter. If the MAC read from data flash is not in this range, use this MAC. 
   */
const struct uip_eth_addr default_mac = {{0x00, 0x30, 0x55, 0x08, 0x00, 0x00}}; 

/* Default IP address configuration */
/* Please make sure this IP address in the same subnet with the DHCP server */
const uint8_t my_ip[4]             = {192, 168, 1, 10};
const uint8_t my_netmask[4]        = {255, 255, 255, 0};
const uint8_t my_default_router[4] = {192, 168, 1, 1};

/* Reserved  */
const uint8_t reserved[46] = {0};

#pragma section

static size_t returnPotentiometerValue(char* pBuff, const size_t maxLen) {
    size_t retLen = 0;
    if (NULL != pBuff) {
        return sprintf(pBuff, "%u \n", S12ADC_read_potentiometer());
    }
    return retLen;
}

static size_t returnPotentiometerValueJSON(char* pBuff, const size_t maxLen) {
    size_t retLen = 0;
    if (NULL != pBuff) {
        return sprintf(pBuff, "\"pot\":\"%u\"", S12ADC_read_potentiometer());
    }
    return retLen;
}

static size_t returnSwitchesStateJSON(char* pBuff, const size_t maxLen) {
    static const char* onStr = "Active";
    static const char* offStr = "Inactive";
    return snprintf(pBuff, maxLen,
            "\"sw1\":\"%s\","
            "\"sw2\":\"%s\","
            "\"sw3\":\"%s\""
            , (0 == SW1) ? onStr : offStr
            , (0 == SW2) ? onStr : offStr
            , (0 == SW3) ? onStr : offStr
    );
}


void init_user_app(void) {
    registerHttpdBoardDataGetter(returnPotentiometerValue, BOARD_DATA_POT);
    registerHttpdBoardDataGetter(returnPotentiometerValueJSON, BOARD_DATA_POT_JSON);
    registerHttpdBoardDataGetter(returnSwitchesStateJSON, BOARD_DATA_SWITCHES_JSON);
}

/******************************************************************************
* Function Name: user_app
* Description  : This is a simple user application that receives a         
*                message from LED Control Web page and turns on or off a   
*                group of LEDs on the Renesas RDK board.  On the Web page  
*                LEDs are named as A, B, and C to allow portability between
*                different boards. This code will require some understanding
*                of HTML and HTTP.                                           
* Arguments    : none
* Return Value : none
******************************************************************************/
void user_app(void)
{
    if (LEDflag)
    {
        uint8_t ledval;
        char *ptr1, *ptr2;

        LEDflag = 0;                   
        ledval = 0;
        ptr1 = LEDbuf;                  // pointer to command string

        // Scan buffer for 'LED' string and take action for each found one
        ptr2 = strstr(ptr1, "LED");

        while (NULL != ptr2) {
            // retrieve number from string like this: "LED3"
            char* outc;
            unsigned long int ledNumber;
            errno = 0;
            ledNumber = strtoul(ptr2+3, &outc, 10);
            if (0 == errno) {
                // LED number retrieved successfully
                // so get requested state

                // move ptr2 after "LEDx=" or after "LEDxx="
                const uint8_t skipChars = (ledNumber < 10) ? 5 : 6;
                ledval = strncmp(ptr2+skipChars, "On", 2) ? LED_OFF : LED_ON;

                // Change LED value
                switch (ledNumber) {
                case 4 :
                    LED4 = ledval; break;
                case 5 :
                    LED5 = ledval; break;
                case 6 :
                    LED6 = ledval; break;
                case 7 :
                    LED7 = ledval; break;
                case 8 :
                    LED8 = ledval; break;
                case 9 :
                    LED9 = ledval; break;
                case 10 :
                    LED10 = ledval; break;
                case 11 :
                    LED11 = ledval; break;
                case 12 :
                    LED12 = ledval; break;
                case 13 :
                    LED13 = ledval; break;
                case 14 :
                    LED14 = ledval; break;
                case 15 :
                    LED15 = ledval; break;
                default: break;
                }
            } // valid LED number

            // move pointer just after current "LED" string
            ptr1 = ptr2 + 3;
            ptr2 = strstr(ptr1, "LED");
        } // end while()
    }
}
