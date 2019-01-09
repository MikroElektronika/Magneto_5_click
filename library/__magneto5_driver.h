/*
    __magneto5_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __magneto5_driver.h
@brief    Magneto5 Driver
@mainpage Magneto5 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   MAGNETO5
@brief      Magneto5 Click Driver
@{

| Global Library Prefix | **MAGNETO5** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Mar 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _MAGNETO5_H_
#define _MAGNETO5_H_

/** 
 * @macro T_MAGNETO5_P
 * @brief Driver Abstract type 
 */
#define T_MAGNETO5_P    const uint8_t*

/** @defgroup MAGNETO5_COMPILE Compilation Config */              /** @{ */

//  #define   __MAGNETO5_DRV_SPI__                            /**<     @macro __MAGNETO5_DRV_SPI__  @brief SPI driver selector */
   #define   __MAGNETO5_DRV_I2C__                            /**<     @macro __MAGNETO5_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __MAGNETO5_DRV_UART__                           /**<     @macro __MAGNETO5_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup MAGNETO5_VAR Variables */                           /** @{ */

// register map
extern const uint8_t _MAGNETO5_REG_X_OUT_LOW;
extern const uint8_t _MAGNETO5_REG_X_OUT_HIGH;
extern const uint8_t _MAGNETO5_REG_Y_OUT_LOW;
extern const uint8_t _MAGNETO5_REG_Y_OUT_HIGH;
extern const uint8_t _MAGNETO5_REG_Z_OUT_LOW;
extern const uint8_t _MAGNETO5_REG_Z_OUT_HIGH;
extern const uint8_t _MAGNETO5_REG_STATUS;
extern const uint8_t _MAGNETO5_REG_INTERNAL_CONTROL_0;
extern const uint8_t _MAGNETO5_REG_INTERNAL_CONTROL_1;
extern const uint8_t _MAGNETO5_REG_PRODUCT_ID;

// Check status
extern const uint8_t _MAGNETO_STATUS_MEASUREMENT_DONE;
extern const uint8_t _MAGNETO_STATUS_PUMP_ON;
extern const uint8_t _MAGNETO_STATUS_READ_DONE;
extern const uint8_t _MAGNETO_STATUS_SELFTEST_OK;

extern const uint8_t _MAGNETO5_ERROR;
extern const uint8_t _MAGNETO5_PRODUCT_ID;

// AXIS
extern const uint8_t _MAGNETO5_AXIS_X;
extern const uint8_t _MAGNETO5_AXIS_Y;
extern const uint8_t _MAGNETO5_AXIS_Z;

// Config register 0
extern const uint8_t _MAGNETO5_CR0_RESET;
extern const uint8_t _MAGNETO5_CR0_SET;
extern const uint8_t _MAGNETO5_CR0_REFILL_CAP;
extern const uint8_t _MAGNETO5_CR0_NO_BOOST;
extern const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_0;
extern const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_1;
extern const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_2;
extern const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_3;
extern const uint8_t _MAGNETO5_CR0_CONTINUOUS_MODE;
extern const uint8_t _MAGNETO5_CR0_TAKE_MEASUREMENT;

// Config register 1
extern const uint8_t _MAGNETO5_CR1_SOFT_RESET;
extern const uint8_t _MAGNETO5_CR1_TEMP_TEST;
extern const uint8_t _MAGNETO5_CR1_SELFTEST_XYZ;
extern const uint8_t _MAGNETO5_CR1_FACTORY_USE_X;
extern const uint8_t _MAGNETO5_CR1_FACTORY_USE_Y;
extern const uint8_t _MAGNETO5_CR1_FACTORY_USE_Z;
extern const uint8_t _MAGNETO5_CH0_16bits_8ms;
extern const uint8_t _MAGNETO5_CH1_16bits_4ms;
extern const uint8_t _MAGNETO5_CH2_14bits_2ms;
extern const uint8_t _MAGNETO5_CH3_12bits_1ms;

                                                                       /** @} */

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup MAGNETO5_INIT Driver Initialization */              /** @{ */

#ifdef   __MAGNETO5_DRV_SPI__
void magneto5_spiDriverInit(T_MAGNETO5_P gpioObj, T_MAGNETO5_P spiObj);
#endif
#ifdef   __MAGNETO5_DRV_I2C__
void magneto5_i2cDriverInit(T_MAGNETO5_P gpioObj, T_MAGNETO5_P i2cObj, uint8_t slave);
#endif
#ifdef   __MAGNETO5_DRV_UART__
void magneto5_uartDriverInit(T_MAGNETO5_P gpioObj, T_MAGNETO5_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void magneto5_gpioDriverInit(T_MAGNETO5_P gpioObj);
                                                                       /** @} */
/** @defgroup MAGNETO5_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Functions reads status register
 *
 * @return  value it reads from the status register
 *
 * The function is used to check if the chip is ready to read data and measurment data.
 */
uint8_t magneto5_setStatusReg( void );

/**
 * @brief Functions reads product ID from register
 *
 * @return  Product ID (0x06 ok)
 */
uint8_t magneto5_getProductID( void );

/**
 * @brief Functions for reset data
 */
void magneto5_reset( void );

/**
 * @brief Functions reads axis data
 *
 * @param[in] axisBuffer        buffer in which axis data will be written.
 * @param[in] maxResolution     maximum resolution axis value
 *
 */
void magneto5_getAxisData( int16_t *axisBuffer, uint8_t maxResolution );

/**
 * @brief Functions reads axis data value
 *
 * @param[in] axis              axis which be read
 * @param[in] maxResolution     maximum resolution axis value
 *
 * @return float axis value
 *
 */
float magneto5_getAxisValue(uint8_t axis, uint8_t maxResolution);

/**
 * @brief Functions sets configuration register 0
 *
 * @param[in] configData   data which be set
 *
 * Options for set:
      Take measurement,
      Continuous Measurement Mode,
      Frequency in continuous measurement mode (1.5Hz, 13Hz, 25Hz or 50 Hz),
      No Boost ( disable the charge pump )
      SET / RESET
      Refill Cap
 
 */
void magneto5_configRegister_0(uint8_t configData);

/**
 * @brief Functions sets configuration register 1
 *
 * @param[in] configData   data which be set
 *
 * Options for set:
      X/Y/Z channel measurements,
      Self Test,
      Temperature test,
      Soft reset

 */
void magneto5_configRegister_1(uint8_t configData);






                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Magneto5_STM.c
    @example Click_Magneto5_TIVA.c
    @example Click_Magneto5_CEC.c
    @example Click_Magneto5_KINETIS.c
    @example Click_Magneto5_MSP.c
    @example Click_Magneto5_PIC.c
    @example Click_Magneto5_PIC32.c
    @example Click_Magneto5_DSPIC.c
    @example Click_Magneto5_AVR.c
    @example Click_Magneto5_FT90x.c
    @example Click_Magneto5_STM.mbas
    @example Click_Magneto5_TIVA.mbas
    @example Click_Magneto5_CEC.mbas
    @example Click_Magneto5_KINETIS.mbas
    @example Click_Magneto5_MSP.mbas
    @example Click_Magneto5_PIC.mbas
    @example Click_Magneto5_PIC32.mbas
    @example Click_Magneto5_DSPIC.mbas
    @example Click_Magneto5_AVR.mbas
    @example Click_Magneto5_FT90x.mbas
    @example Click_Magneto5_STM.mpas
    @example Click_Magneto5_TIVA.mpas
    @example Click_Magneto5_CEC.mpas
    @example Click_Magneto5_KINETIS.mpas
    @example Click_Magneto5_MSP.mpas
    @example Click_Magneto5_PIC.mpas
    @example Click_Magneto5_PIC32.mpas
    @example Click_Magneto5_DSPIC.mpas
    @example Click_Magneto5_AVR.mpas
    @example Click_Magneto5_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __magneto5_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */