/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/ 
#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include "platform.h"

#include "uip.h"
#include "uip_arp.h"
#include "r_ether.h"
#include "httpd.h"
#include "timer.h"
#include "user-app.h"


#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

/******************************************************************************
Imported global variables and functions
******************************************************************************/
extern const struct uip_eth_addr * my_mac;
extern const struct uip_eth_addr default_mac;

/******************************************************************************
local global variables and functions
******************************************************************************/
void display_uip_demo(void);
void display_ip_address(const uint16_t ipaddr[]);
void display_mac_address(uint8_t * mac_addr);
bool get_mac(struct uip_eth_addr * mac_addr);


/******************************************************************************
******************************************************************************/
/*----------------------------------------------------------------------------*/ 
int
main(void)
{
    int i;
    // Renesas -- uip_ipaddr_t ipaddr;
    struct timer periodic_timer, arp_timer;
    struct uip_eth_addr mac_addr;
    uint32_t ch = 0;

    lcd_initialize();
    display_uip_demo();

    timer_init();
    timer_set(&periodic_timer, CLOCK_SECOND / 2);
    timer_set(&arp_timer, CLOCK_SECOND * 10);

    /* Retrieve the MAC address and display result. */
    if (!get_mac(&mac_addr))
    {
        lcd_display(LCD_LINE5, "Using Default MAC:");    
    }   
    else
    {
        lcd_display(LCD_LINE5, "MAC Address = ");         
    }
    display_mac_address(mac_addr.addr);    

    // Renesas -- network_device_init();
    /* Wait until Ether device initailize succesfully. 
    Make sure Ethernet cable is plugged in. */ 
    while (R_ETHER_ERROR == R_Ether_Open(ch, (uint8_t*) &mac_addr.addr[0]));

    // Renesas ++ set Ethernet address
    uip_setethaddr(mac_addr);
    uip_init();

    // Renesas -- 
    //uip_ipaddr(ipaddr, 192,168,0,2);
    //uip_sethostaddr(ipaddr);
    dhcpc_init(&mac_addr.addr[0], 6);  
    httpd_init();

    while (1)
    {
        // Renesas -- uip_len = network_device_read();
        uip_len = R_Ether_Read(ch, (void *)uip_buf);
        if (uip_len > 0)
        {
            if (BUF->type == htons(UIP_ETHTYPE_IP))
            {
                uip_arp_ipin();
                uip_input();
                /* If the above function invocation resulted in data that
                should be sent out on the network, the global variable
                uip_len is set to a value > 0. */
                if (uip_len > 0)
                {
                    uip_arp_out();
                    // Renesas -- network_device_send();
                    R_Ether_Write(ch, (void *)uip_buf, (uint32_t)uip_len);
                }
            }
            else if (BUF->type == htons(UIP_ETHTYPE_ARP))
            {
                uip_arp_arpin();
                /* If the above function invocation resulted in data that
                should be sent out on the network, the global variable
                uip_len is set to a value > 0. */
                if (uip_len > 0)
                {
                    // Renesas -- network_device_send();
                    R_Ether_Write(ch, (void *)uip_buf, (uint32_t)uip_len);
                }
            }

        }
        else if (timer_expired(&periodic_timer))
        {
            timer_reset(&periodic_timer);
            for (i = 0; i < UIP_CONNS; i++)
            {
                uip_periodic(i);
                /* If the above function invocation resulted in data that
                should be sent out on the network, the global variable
                uip_len is set to a value > 0. */
                if (uip_len > 0)
                {
                    uip_arp_out();
                    // Renesas -- network_device_send();
                    R_Ether_Write(ch, (void *)uip_buf, (uint32_t)uip_len);
                }
            }

#if UIP_UDP
            for (i = 0; i < UIP_UDP_CONNS; i++)
            {
                uip_udp_periodic(i);
                /* If the above function invocation resulted in data that
                should be sent out on the network, the global variable
                uip_len is set to a value > 0. */
                if (uip_len > 0)
                {
                    uip_arp_out();
                    // Renesas -- network_device_send();
                    R_Ether_Write(ch, (void *)uip_buf, (uint32_t)uip_len);
                }
            }
#endif /* UIP_UDP */

            /* Call the ARP timer function every 10 seconds. */
            if (timer_expired(&arp_timer))
            {
                timer_reset(&arp_timer);
                uip_arp_timer();
            }
        }

        // Insert user aplications here.
        // Call WEB application that controls LEDs on the target board.
        user_app();

    }
    return 0;
}
/*---------------------------------------------------------------------------*/

// Renesas ++
/*******************************************************************************
* Function Name:    display_uip_demo
* Description  :    Clears the LCD and displays "uIP Demo" on line 1.    
* Arguments    :    None
* Return Value :    None
*******************************************************************************/
void display_uip_demo(void)
{
    lcd_clear();
    lcd_display(LCD_LINE1, "uIP Demo");
    printf("uIP Demo\r\n") ;
    
} /* End of function display_uip_demo(). */


// Renesas ++
/*******************************************************************************
* Function Name:    display_ip_address
* Description  :    Displays IP address in dotted decimal format. 
* Arguments    :    ipaddr - 
*                       pointer to array containing IP address to display
* Return Value :    None
*******************************************************************************/
void display_ip_address(const uint16_t * ipaddr)
{
    char dis_buf[16];
    char *p = (char *)ipaddr;

    lcd_display(LCD_LINE1, "uIP Demo");
    lcd_display(LCD_LINE3, "IP Addr =");

    sprintf(dis_buf, "%d.%d.%d.%d", *p, *(p+1), *(p+2), *(p+3));
    lcd_display(LCD_LINE4, (const uint8_t *)dis_buf);

    printf("IP Addr = %d.%d.%d.%d\r\n", *p, *(p+1), *(p+2), *(p+3)) ;
    
} /* End of function display_ip_address(). */


// Renesas ++
/*******************************************************************************
* Function Name:    display_mac_address
* Description  :    Displays MAC address in colon delimited hex format. 
* Arguments    :    mac_addr - 
*                       pointer to array containing MAC address to display
* Return Value :    None
*******************************************************************************/
void display_mac_address(uint8_t * mac_addr)
{
    uint8_t dis_buf[18];
    char *p = (char*)mac_addr;

    sprintf((char *)dis_buf, "%02X:%02X:%02X:%02X:%02X:%02X", *p, *(p+1), *(p+2), *(p+3), *(p+4), *(p+5));    
    lcd_display(LCD_LINE6, (const uint8_t *)dis_buf);

    printf("MAC Addr = %02X:%02X:%02X:%02X:%02X:%02X", *p, *(p+1), *(p+2), *(p+3), *(p+4), *(p+5)) ;
    
} /* End of function display_mac_address(). */


// Renesas ++
/*******************************************************************************
* Function Name:    get_mac
* Description  :    Obtains the ethernet MAC address.
* Arguments    :    mac_addr - 
*              :        pointer to structure into which MAC address will be written.
* Return Value :    true -
*              :        MAC in valid address range.
*              :    false -
*              :        MAC invalid or out of range.
*******************************************************************************/
bool get_mac(struct uip_eth_addr * mac_addr)
{
    uint32_t i;
    
    /* Enable reading from the data flash block that contains the MAC address. */
    FLASH.DFLRE1.WORD = 0xD280;
    
    /* Copy default mac address into location passed as argument.  */          
    memcpy(&mac_addr->addr[0], &default_mac.addr[0], sizeof(mac_addr->addr));
         
    /* Now check first 4 bytes of MAC in data flash to determine if it is in a valid range.
       If valid, copy in the remaining bytes, if not valid then just keep the default. */ 
    for (i = 0; i < sizeof(my_mac->addr); i++)
    {   /*  */
        if ((i < 4) && (my_mac->addr[i] != default_mac.addr[i]))
        {
            return false; /* Invalid MAC address discovered. */
        }
        else 
        {
            mac_addr->addr[i] = my_mac->addr[i]; 
        }
    }  
    
    return true; /* Valid MAC address was found. */
     
} /* End of function get_mac(). */
    
