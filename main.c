/* Project "mavlink-acc1" 302DL*****************************************************
This example reads the accelerometers 302DL of the STM32-DISCOVERY board
and send it to the MAVLINK message “ATTITUDE” that can be read by the ground station 
QGC using an USART connection (using PB6 & PB7 pin). 
USART is set to 57400baud. A FDTI cable is required.
********************************************* Copyright Angel Fernandez. April 2016
*/

#include "stm32f4xx.h"
#define TM_DISCO_STM32F4_DISCOVERY
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include <cross_studio_io.h>
#include <misc.h>
#include <stm32f4xx_usart.h>
#include "mavlink.h"
#include "af_usart.h" //AF configuration of STM32-DISCO

int main(void) {

        TM_LIS302DL_LIS3DSH_t  Axes_Data;//structure to read accelerometer (X,Y,Z)
	
	SystemInit();       /* system init */
	TM_DISCO_LedInit(); /* Initialize LEDs */
        ConfigureUsart1(57600); // setup USART1 with a baudrate of 57600. That gives 300Hz refresh rate

        mavlink_system_t mavlink_system; // MAVLINK initialize 
        mavlink_message_t msg;  //structura "MAVLINK message"
        uint8_t buf[MAVLINK_MAX_PACKET_LEN]; // array de 263 elementos máximo

        /* initialize accelerometer 302DL */ 
	TM_LIS302DL_LIS3DSH_Init(TM_LIS302DL_Sensitivity_2_3G, TM_LIS302DL_Filter_2Hz);      

   while (1) {

        //HEARTBEAT
        mavlink_msg_heartbeat_pack(23, 200, &msg, 2, 14, 64, 5, 4); 
        uint16_t len = mavlink_msg_to_send_buffer(buf, &msg); // Copy the message to the buffer   
        for(int i = 0 ; i < len ; i++) {
          USART_SendData(USART1,buf[i]);      
          while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);   //Loop until the end of transmission
        }

        //ATTITUDE 
        //                      (sys,comp,&msg,time,     roll,                    pitch,        yaw,roll_speed,pitch_speed,yaw_speed)
        mavlink_msg_attitude_pack(23,200, &msg,1000000, (Axes_Data.Y)*3.1416/1000, -(Axes_Data.X)*3.1416/1000,0 ,0 ,0 ,0 ); 
        len = mavlink_msg_to_send_buffer(buf, &msg); // Copy the message to the buffer   
        for(int i = 0 ; i < len ; i++) {
          USART_SendData(USART1,buf[i]);      
          while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);   //Loop until the end of transmission
        }

	/* Read axes data from initialized accelerometer */
	TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		
                if            (Axes_Data.X > 200) {TM_DISCO_LedOn(LED_ORANGE);
                    } else if (Axes_Data.X <-200) {TM_DISCO_LedOn(LED_BLUE);
                    } else {
			TM_DISCO_LedOff(LED_BLUE);
                        TM_DISCO_LedOff(LED_ORANGE);
                    }                      
		
                if            (Axes_Data.Y > 200) {TM_DISCO_LedOn(LED_RED);
                    } else if (Axes_Data.Y <-200) {TM_DISCO_LedOn(LED_GREEN);
                    } else {
			TM_DISCO_LedOff(LED_RED);
                        TM_DISCO_LedOff(LED_GREEN);
                    }
    }

}









