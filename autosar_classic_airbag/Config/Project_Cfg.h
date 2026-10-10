#ifndef PROJECT_CFG_H
#define PROJECT_CFG_H

#include <stdint.h>

#define SYSCLK_HZ                 72000000UL
#define APB1_CLK_HZ               36000000UL

#define LIS331HH_I2C_ADDR         0x19U
#define LIS331HH_WHO_AM_I_REG     0x0FU
#define LIS331HH_CTRL_REG1        0x20U
#define LIS331HH_CTRL_REG4        0x23U
#define LIS331HH_OUT_X_L          0x28U
#define LIS331HH_WHO_AM_I_VALUE   0x32U
#define LIS331HH_CTRL1_VALUE      0x27U
#define LIS331HH_CTRL4_VALUE      0x10U
#define LIS331HH_SENSITIVITY_MG   6L

#define FORCE_THRESHOLD_MG        2500L
#define FORCE_THRESHOLD_SQ        (FORCE_THRESHOLD_MG * FORCE_THRESHOLD_MG)

#define I2C_TIMEOUT_CNT           100000UL
#define UART_TIMEOUT_CNT          100000UL
#define CAN_TIMEOUT_CNT           100000UL
#define CAN_ID_AIRBAG_TO_MAIN     0x111UL

#endif
