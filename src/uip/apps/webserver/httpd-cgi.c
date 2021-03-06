/**
 * \addtogroup httpd
 * @{
 */

/**
 * \file
 *         Web server script interface
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

/*
 * Copyright (c) 2001-2006, Adam Dunkels.
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
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: httpd-cgi.c,v 1.2 2006/06/11 21:46:37 adam Exp $
 *
 */

#include "uip.h"
#include "psock.h"
#include "httpd.h"
#include "httpd-cgi.h"
#include "httpd-fs.h"

#include <stdio.h>
#include <string.h>
#include "httpd-board-data.h"

HTTPD_CGI_CALL(file, "file-stats", file_stats);
HTTPD_CGI_CALL(tcp, "tcp-connections", tcp_stats);
HTTPD_CGI_CALL(net, "net-stats", net_stats);
HTTPD_CGI_CALL(board, "board-data", board_data);
HTTPD_CGI_CALL(all_board, "all-board-data", all_board_data);

extern const char* HttpdBoardDataErrorStr;
static const struct httpd_cgi_call *calls[] = { &file, &tcp, &net, &board, &all_board, NULL };

static char boardDataBuff[100] = {0};
/*---------------------------------------------------------------------------*/
static
PT_THREAD(nullfunction(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
httpd_cgifunction
httpd_cgi(char *name)
{
  const struct httpd_cgi_call **f;

  /* Find the matching name in the table, return the function. */
  for(f = calls; *f != NULL; ++f) {
    if(strncmp((*f)->name, name, strlen((*f)->name)) == 0) {
      return (*f)->function;
    }
  }
  return nullfunction;
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_file_stats(void *arg)
{
  char *f = (char *)arg;
  // Renesas -- return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE, "%5u", httpd_fs_count(f));
  return sprintf((char *)uip_appdata, "%5u", httpd_fs_count(f));
}
/*---------------------------------------------------------------------------*/
static
PT_THREAD(file_stats(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);

  PSOCK_GENERATOR_SEND(&s->sout, generate_file_stats, strchr(ptr, ' ') + 1);
  
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static const char closed[] =   /*  "CLOSED",*/
{0x43, 0x4c, 0x4f, 0x53, 0x45, 0x44, 0};
static const char syn_rcvd[] = /*  "SYN-RCVD",*/
{0x53, 0x59, 0x4e, 0x2d, 0x52, 0x43, 0x56,
 0x44,  0};
static const char syn_sent[] = /*  "SYN-SENT",*/
{0x53, 0x59, 0x4e, 0x2d, 0x53, 0x45, 0x4e,
 0x54,  0};
static const char established[] = /*  "ESTABLISHED",*/
{0x45, 0x53, 0x54, 0x41, 0x42, 0x4c, 0x49, 0x53, 0x48,
 0x45, 0x44, 0};
static const char fin_wait_1[] = /*  "FIN-WAIT-1",*/
{0x46, 0x49, 0x4e, 0x2d, 0x57, 0x41, 0x49,
 0x54, 0x2d, 0x31, 0};
static const char fin_wait_2[] = /*  "FIN-WAIT-2",*/
{0x46, 0x49, 0x4e, 0x2d, 0x57, 0x41, 0x49,
 0x54, 0x2d, 0x32, 0};
static const char closing[] = /*  "CLOSING",*/
{0x43, 0x4c, 0x4f, 0x53, 0x49,
 0x4e, 0x47, 0};
static const char time_wait[] = /*  "TIME-WAIT,"*/
{0x54, 0x49, 0x4d, 0x45, 0x2d, 0x57, 0x41,
 0x49, 0x54, 0};
static const char last_ack[] = /*  "LAST-ACK"*/
{0x4c, 0x41, 0x53, 0x54, 0x2d, 0x41, 0x43,
 0x4b, 0};

static const char *states[] = {
  closed,
  syn_rcvd,
  syn_sent,
  established,
  fin_wait_1,
  fin_wait_2,
  closing,
  time_wait,
  last_ack};
  

static unsigned short
generate_tcp_stats(void *arg)
{
  struct uip_conn *conn;
  struct httpd_state *s = (struct httpd_state *)arg;
    
  conn = &uip_conns[s->count];
  /*
  return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
		 "<tr><td>%d</td><td>%u.%u.%u.%u:%u</td><td>%s</td><td>%u</td><td>%u</td><td>%c %c</td></tr>\r\n",
		 htons(conn->lport),
		 htons(conn->ripaddr[0]) >> 8,
		 htons(conn->ripaddr[0]) & 0xff,
		 htons(conn->ripaddr[1]) >> 8,
		 htons(conn->ripaddr[1]) & 0xff,
		 htons(conn->rport),
		 states[conn->tcpstateflags & UIP_TS_MASK],
		 conn->nrtx,
		 conn->timer,
		 (uip_outstanding(conn))? '*':' ',
		 (uip_stopped(conn))? '!':' ');
  */	 
  return sprintf((char *)uip_appdata,
		 "<tr align=center><td>%d</td><td>%u.%u.%u.%u:%u</td><td>%s</td><td>%u</td><td>%u</td><td>%c %c</td></tr>\r\n",
		 htons(conn->lport),
		 htons(conn->ripaddr[0]) >> 8,
		 htons(conn->ripaddr[0]) & 0xff,
		 htons(conn->ripaddr[1]) >> 8,
		 htons(conn->ripaddr[1]) & 0xff,
		 htons(conn->rport),
		 states[conn->tcpstateflags & UIP_TS_MASK],
		 conn->nrtx,
		 conn->timer,
		 (uip_outstanding(conn))? '*':' ',
		 (uip_stopped(conn))? '!':' '); 		 
	
}
/*---------------------------------------------------------------------------*/
static
PT_THREAD(tcp_stats(struct httpd_state *s, char *ptr))
{
  
  PSOCK_BEGIN(&s->sout);

  for(s->count = 0; s->count < UIP_CONNS; ++s->count) {
    if((uip_conns[s->count].tcpstateflags & UIP_TS_MASK) != UIP_CLOSED) {
      PSOCK_GENERATOR_SEND(&s->sout, generate_tcp_stats, s);
    }
  }

  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
static unsigned short
generate_net_stats(void *arg)
{
  struct httpd_state *s = (struct httpd_state *)arg;
  /*
  return snprintf((char *)uip_appdata, UIP_APPDATA_SIZE,
		  "%5u\n", ((uip_stats_t *)&uip_stat)[s->count]);
  */
  return sprintf((char *)uip_appdata,
		  "%5u\n", ((uip_stats_t *)&uip_stat)[s->count]);

}

static
PT_THREAD(net_stats(struct httpd_state *s, char *ptr))
{
  PSOCK_BEGIN(&s->sout);

#if UIP_STATISTICS

  for(s->count = 0; s->count < sizeof(uip_stat) / sizeof(uip_stats_t);
      ++s->count) {
    PSOCK_GENERATOR_SEND(&s->sout, generate_net_stats, s);
  }
  
#endif /* UIP_STATISTICS */
  
  PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/



// BOARD DATA (specified in argument) CGI handle
/*---------------------------------------------------------------------------*/
static size_t runGetter(HttpdBoardDataGetterFuncType func, char* pStr, size_t maxLen) {

    uint32_t retVal = 0;

    if (NULL != func) {
        size_t len = func(pStr, maxLen);
        if (len > maxLen) {
            len = maxLen;
        }
        pStr[len] = '\0';
        retVal = len;
    } else {
        // send error msg

        // strlen doesn't count '\0' char
        const size_t len = strlen(HttpdBoardDataErrorStr);
        strncpy(pStr, HttpdBoardDataErrorStr, len);
        pStr[len] = '\0';
        retVal = len;
    }

    return retVal;
}

static unsigned short generate_board_data(void *arg)
{

    char* pArgStr = (char*)arg;
    unsigned short retVal = 0;
    size_t dataLen = 0;

    HttpdBoardDataGetterFuncType dataGetterFunc = NULL;
    // todo call from here the users functions that returns board specific data

    if (NULL != pArgStr) {
        if (0 == strncmp(pArgStr, "POT", 3)) {
             dataGetterFunc = getHttpdBoardDataGetter(BOARD_DATA_POT);
            dataLen = runGetter(dataGetterFunc, boardDataBuff, (sizeof(boardDataBuff)/sizeof(boardDataBuff[0]))-1);
            retVal = snprintf((char *)uip_appdata
                       , dataLen
                       , "%s"
                       , boardDataBuff);
        }
    } else {
        retVal = sprintf((char *)uip_appdata, "missing cgi argument\n");
    }

    return retVal;
}

static PT_THREAD(board_data(struct httpd_state *s, char *ptr))
{
    // convert received data to output buffer, as argument pass the pointer after
    // the space, this represents first character of argument
    const size_t ptr_len = strlen(ptr);
    char* pSpaceChar = strchr(ptr, ' ');
    char* forwardArg = NULL;

    PSOCK_BEGIN(&s->sout);

    // Properly handle situation when there is no argument after cgi script name
    if ((NULL != pSpaceChar) &&
            ((size_t)(pSpaceChar + 1 - ptr) <= ptr_len)) {
        // point to character just after the space
        forwardArg = pSpaceChar + 1;
    }
    PSOCK_GENERATOR_SEND(&s->sout, generate_board_data, forwardArg);

    PSOCK_END(&s->sout);
}

/*---------------------------------------------------------------------------*/


// ALL BOARD DATA CGI handle
/*---------------------------------------------------------------------------*/
static unsigned short generate_all_board_data(void *arg)
{
    unsigned short retVal = 0;
    const size_t safeBuffSize = (sizeof(boardDataBuff)/sizeof(boardDataBuff[0]))-1;
    HttpdBoardDataGetterFuncType dataGetterFunc = NULL;
    size_t dataLen = 0;

    // begin json
    *(char*)uip_appdata = '{';
    retVal += 1;
    const HttpdBoardDataGetterType whichData[] = {BOARD_DATA_POT_JSON, BOARD_DATA_SWITCHES_JSON};
    for (size_t i = 0; i < sizeof(whichData)/sizeof(whichData[0]); ++i) {
        // Get potentiometer value
        dataGetterFunc = getHttpdBoardDataGetter(whichData[i]);
        dataLen = runGetter(dataGetterFunc, boardDataBuff, safeBuffSize);
        retVal += snprintf((char *)uip_appdata + retVal
                   , dataLen + 2 /*+2 is required to copy the,character*/
                   , "%s,"
                   , boardDataBuff);
    }

    // end json
    // -1 is for OVERRIDE last comma, so don't update the retVal
    *(char*)((char*)uip_appdata+retVal-1) = '}';


    return retVal;
}

static PT_THREAD(all_board_data(struct httpd_state *s, char *ptr))
{
    // no cgi name argument expected

    PSOCK_BEGIN(&s->sout);

    PSOCK_GENERATOR_SEND(&s->sout, generate_all_board_data, NULL);

    PSOCK_END(&s->sout);
}
/*---------------------------------------------------------------------------*/
/** @} */
