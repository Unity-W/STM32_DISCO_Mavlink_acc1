# STM32_DISCO_Mavlink_acc1
This example reads the accelerometers of the STM32-DISCOVERY board and send it to the MAVLINK message “ATTITUDE”
that can be read by the QGC using an USART connection (using PB6 & PB7 pin). 
USART is set to 57400baud. A FDTI cable is required.
