#ifndef CONFIG_H
#define CONFIG_H

// Projector
#define PROJECTOR_I2C_SLAVE_ADDRESS 27
#define PROJECTOR_LED_ADDRESS 0x52
#define PROJECTOR_CHECK_LED_ADDRESS 0X53
#define PROJECTOR_PWM_ADDRESS 0x54
#define PROJECTOR_OPEN_LED_SENSOR_ADDRESS 0XA0
#define PROJECTOR_OPEN_LED_SENSOR_COMMAND 0x03
#define PROJECTOR_OPEN_LED_COMMAND 0x07
#define PROJECTOR_OPEN_CLOSE_COMMAND 0x00
#define PROJECTOR_WAIT_AFTER_CURE_TIME 500
#define PROJECTOR_CURE_TIME 1200
#define PROJECTOR_ERROR_COUNTER 5
#define PROJECTOR_ERROR_MESSAGE -2
#define PROJECTOR_READ_LIGHT_ADDRESS 0x29
#define PROJECTOR_READ_LIGHT_COMMAND 0xB4
#define PROJECTOR_READ_CURRENT_ADDRESS 0X55
#define PROJECTOR_READ_LED_ADDRESS 0x1B
#define LED_SENSOR_VALUE 800
#define MAX_VALUE_PROXIMITY 100

// MLX90614
#define MLX_I2C_SLAVE_ADDRESS 90

// SERIAL
#define COMMAND_COMPLETE_MESSAGE 1
#define COMMAND_RECEIVED_MESSAGE 2
#define SERIAL_BAUDRATE 115200
#define SERIAL_LINE_BUFFER_SIZE 96

#endif
