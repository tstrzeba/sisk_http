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
* File Name    : r_ether.h
* Version      : 1.02
* Description  : Ethernet module device driver
*******************************************************************************/
/******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 15.02.2010 1.00    First Release
*         : 03.03.2010 1.01    Buffer size is aligned on the 32-byte boundary.
*         : 04.06.2010 1.02    RX62N changes
******************************************************************************/

#ifndef	R_ETHER_H
#define	R_ETHER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdint.h>

/******************************************************************************
Typedef definitions
******************************************************************************/
struct Descriptor
{
    __evenaccess uint32_t	status;
#if __LIT                               
    /* Little endian */
    __evenaccess uint16_t	size;
    __evenaccess uint16_t	bufsize;
#else                                   
    /* Big endian */
    __evenaccess uint16_t	bufsize;
    __evenaccess uint16_t	size;

#endif
    int8_t					*buf_p;
    struct Descriptor		*next;
};

typedef struct Descriptor ethfifo;

/******************************************************************************
Macro definitions
******************************************************************************/
#define	BUFSIZE	  256                   /* Must be 32-bit aligned */
#define ENTRY     8                     /* Number of RX and TX buffers */

#define  ACT      0x80000000
#define  DL       0x40000000
#define  FP1      0x20000000
#define  FP0      0x10000000
#define  FE       0x08000000

#define  RFOVER   0x00000200
#define  RAD      0x00000100
#define  RMAF     0x00000080
#define  RRF      0x00000010
#define  RTLF     0x00000008
#define  RTSF     0x00000004
#define  PRE      0x00000002
#define  CERF     0x00000001

#define  TAD      0x00000100
#define  CND      0x00000008
#define  DLC      0x00000004
#define  CD       0x00000002
#define  TRO      0x00000001

/** 
* Renesas Ethernet API return defines
**/
#define R_ETHER_OK          0
#define R_ETHER_ERROR       -1

/*	Ether Interface definitions	*/
#define ETH_RMII_MODE	0
#define ETH_MII_MODE	1
/*	Select Ether Interface Mode 	*/
#define ETH_MODE_SEL	ETH_RMII_MODE

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
/** 
* Renesas Ethernet API prototypes
**/
int32_t R_Ether_Open(uint32_t ch, uint8_t mac_addr[]);
int32_t R_Ether_Close(uint32_t ch);
int32_t R_Ether_Write(uint32_t ch, void *buf, uint32_t len);
int32_t R_Ether_Read(uint32_t ch, void *buf);


/****************************************************/
/* Ethernet statistic collection data */
struct enet_stats
{
    uint32_t  rx_packets;      /* total packets received    */
    uint32_t  tx_packets;      /* total packets transmitted  */
    uint32_t  rx_errors;       /* bad packets received      */
    uint32_t  tx_errors;       /* packet transmit problems    */
    uint32_t  rx_dropped;      /* no space in buffers      */
    uint32_t  tx_dropped;      /* no space available      */
    uint32_t  multicast;       /* multicast packets received  */
    uint32_t  collisions;

    /* detailed rx_errors: */
    uint32_t  rx_length_errors;
    uint32_t  rx_over_errors;    /* receiver ring buffer overflow  */
    uint32_t  rx_crc_errors;     /* recved pkt with crc error  */
    uint32_t  rx_frame_errors;   /* recv'd frame alignment error  */
    uint32_t  rx_fifo_errors;    /* recv'r fifo overrun      */
    uint32_t  rx_missed_errors;  /* receiver missed packet    */

    /* detailed tx_errors */
    uint32_t  tx_aborted_errors;
    uint32_t  tx_carrier_errors;
    uint32_t  tx_fifo_errors;
    uint32_t  tx_heartbeat_errors;
    uint32_t  tx_window_errors;
};

struct ei_device
{
    const int8_t      *name;
    uint8_t           open;
    uint8_t           Tx_act;
    uint8_t           Rx_act;
    uint8_t           txing;        /* Transmit Active */
    uint8_t           irqlock;      /* EDMAC's interrupt disabled when '1'. */
    uint8_t           dmaing;       /* EDMAC Active */
    ethfifo           *rxcurrent;   /* current receive discripter */
    ethfifo           *txcurrent;   /* current transmit discripter */
    uint8_t           save_irq;     /* Original dev->irq value. */
    struct enet_stats stat;
    uint8_t           mac_addr[6];
};

#endif /* R_ETHER_H */

