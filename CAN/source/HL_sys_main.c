/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "../include/HL_sys_common.h"
#include "../include/HL_system.h"

/* USER CODE BEGIN (1) */
#include "../include/HL_can.h"

/* Include ESM header file - types, definitions and function declarations for system driver */
#include "../include/HL_esm.h"

#define  D_SIZE 9

uint8  tx_data[D_SIZE]  = {'H','E','L','L','O','A','B','C','\0'};
uint8  rx_data[D_SIZE] = {0};
uint32 error = 0;

uint32 checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize);
/* USER CODE END */


/* USER CODE BEGIN (2) */
/* USER CODE END */
#include<stdio.h>

void main(void)
{

	/* initialize can 1 and 2   */
//	    _enable_IRQ_interrupt_();	//enable interrupts
	    canInit(); /* can1 -> can2 */

	    /* transmit on can2 */
	    canTransmit(canREG2, canMESSAGE_BOX1, tx_data);
	    fflush(stdout);
	    printf("Transmitted\n");
	    fflush(stdout);

	    /*... wait until message receive on can2 */
	    while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX1));
	    canGetData(canREG1, canMESSAGE_BOX1, rx_data);  /* receive on can2  */
	    fflush(stdin);
	    fflush(stdout);
	    printf("Recieved:\n");
	    fflush(stdout);
	    printf("%s\n", rx_data);


	    /* ... run forever */
	    while(1);

}

/* USER CODE BEGIN (4) */
uint32 checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize)
{
   uint32 err=0;
   uint32 cnt=psize;

   while(cnt--)
   {
     if((*src_packet++) != (*dst_packet++))
     {
        err++;           /*  data error  */
     }
   }
   return (err);
}
/* USER CODE END */
