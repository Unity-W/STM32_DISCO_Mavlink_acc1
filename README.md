# STM32_DISCO_Mavlink_acc1
This example reads the accelerometers of the STM32F407VG-DISCOVERY board.
Then it´s send those to MAVLINK using message “ATTITUDE”

Mavlink messages can be read by the QGC using an USART connection (using PB6 & PB7 pin). 

USART is set to 57400baud. A FDTI cable is required.
### IDE -> CrossStudio v3.6
###"zip" file attached includes all necesary files organised as the root folder
