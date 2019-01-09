/*
    __magneto5_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__magneto5_driver.h"
#include "__magneto5_hal.c"

/* ------------------------------------------------------------------- MACROS */

// register map
const uint8_t _MAGNETO5_REG_X_OUT_LOW          = 0x00;
const uint8_t _MAGNETO5_REG_X_OUT_HIGH         = 0x01;
const uint8_t _MAGNETO5_REG_Y_OUT_LOW          = 0x02;
const uint8_t _MAGNETO5_REG_Y_OUT_HIGH         = 0x03;
const uint8_t _MAGNETO5_REG_Z_OUT_LOW          = 0x04;
const uint8_t _MAGNETO5_REG_Z_OUT_HIGH         = 0x05;
const uint8_t _MAGNETO5_REG_STATUS             = 0x06;
const uint8_t _MAGNETO5_REG_INTERNAL_CONTROL_0 = 0x07;
const uint8_t _MAGNETO5_REG_INTERNAL_CONTROL_1 = 0x08;
const uint8_t _MAGNETO5_REG_PRODUCT_ID = 0x20;

// Check status
const uint8_t _MAGNETO_STATUS_MEASUREMENT_DONE  = 0x01;
const uint8_t _MAGNETO_STATUS_PUMP_ON           = 0x02;
const uint8_t _MAGNETO_STATUS_READ_DONE         = 0x04;
const uint8_t _MAGNETO_STATUS_SELFTEST_OK       = 0x08;

const uint8_t _MAGNETO5_ERROR = 0x00;
const uint8_t _MAGNETO5_PRODUCT_ID = 0x06;

// AXIS
const uint8_t _MAGNETO5_AXIS_X = 0x00;
const uint8_t _MAGNETO5_AXIS_Y = 0x02;
const uint8_t _MAGNETO5_AXIS_Z = 0x04;

// Config register 0
const uint8_t _MAGNETO5_CR0_RESET               = 0x40;
const uint8_t _MAGNETO5_CR0_SET                 = 0x20;
const uint8_t _MAGNETO5_CR0_REFILL_CAP          = 0x80;
const uint8_t _MAGNETO5_CR0_NO_BOOST            = 0x10;
const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_0  = 0x00;
const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_1  = 0x04;
const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_2  = 0x08;
const uint8_t _MAGNETO5_CR0_MEASUREMENT_MODE_3  = 0x0C;
const uint8_t _MAGNETO5_CR0_CONTINUOUS_MODE     = 0x02;
const uint8_t _MAGNETO5_CR0_TAKE_MEASUREMENT    = 0x01;

// Config register 1
const uint8_t _MAGNETO5_CR1_SOFT_RESET     = 0x80;
const uint8_t _MAGNETO5_CR1_TEMP_TEST      = 0x40;
const uint8_t _MAGNETO5_CR1_SELFTEST_XYZ   = 0x20;
const uint8_t _MAGNETO5_CR1_FACTORY_USE_X  = 0x10;
const uint8_t _MAGNETO5_CR1_FACTORY_USE_Y  = 0x08;
const uint8_t _MAGNETO5_CR1_FACTORY_USE_Z  = 0x04;
const uint8_t _MAGNETO5_CH0_16bits_8ms     = 0x00;
const uint8_t _MAGNETO5_CH1_16bits_4ms     = 0x01;
const uint8_t _MAGNETO5_CH2_14bits_2ms     = 0x02;
const uint8_t _MAGNETO5_CH3_12bits_1ms     = 0x03;










/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __MAGNETO5_DRV_I2C__
static uint8_t _slaveAddress;
#endif
static float _maxResolution;
static uint8_t _dataFlag;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

void _measureResolution(uint8_t setData);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

void _measureResolution(uint8_t setData)
{
      if (setData == _MAGNETO5_CH0_16bits_8ms)
      {
          _maxResolution = 2048.0;
          _dataFlag = 0;
      }
      else if (setData == _MAGNETO5_CH1_16bits_4ms)
      {
          _maxResolution = 2048.0;
          _dataFlag = 0;
      }
      else if (setData == _MAGNETO5_CH2_14bits_2ms)
      {
          _maxResolution = 512.0;
          _dataFlag = 2;
      }
      else if (setData == _MAGNETO5_CH3_12bits_1ms)
      {
          _maxResolution = 128.0;
          _dataFlag = 4;
      }
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __MAGNETO5_DRV_SPI__

void magneto5_spiDriverInit(T_MAGNETO5_P gpioObj, T_MAGNETO5_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MAGNETO5_DRV_I2C__

void magneto5_i2cDriverInit(T_MAGNETO5_P gpioObj, T_MAGNETO5_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __MAGNETO5_DRV_UART__

void magneto5_uartDriverInit(T_MAGNETO5_P gpioObj, T_MAGNETO5_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void magneto5_gpioDriverInit(T_MAGNETO5_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
}

/* ----------------------------------------------------------- IMPLEMENTATION */

uint8_t magneto5_setStatusReg()
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];

    writeReg[ 0 ] = _MAGNETO5_REG_STATUS;
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );

    return readReg[ 0 ];
}

uint8_t magneto5_getProductID( void )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];
    uint8_t statusRead;
    
    writeReg[ 0 ] = _MAGNETO5_REG_PRODUCT_ID;
    statusRead = magneto5_setStatusReg();
    
    if (statusRead & _MAGNETO_STATUS_READ_DONE)
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
        hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );
        
        if (readReg[ 0 ] != _MAGNETO5_PRODUCT_ID)
        {
            return _MAGNETO5_ERROR;
        }
        else
        {
            return  readReg[ 0 ];
        }
    }
    Delay_10ms();
}


void magneto5_getAxisData( int16_t *axisBuffer, uint8_t maxResolution )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 6 ];
    uint8_t readStatus;

    writeReg[ 0 ] = 0x00;

    magneto5_configRegister_0( _MAGNETO5_CR0_TAKE_MEASUREMENT | _MAGNETO5_CR0_REFILL_CAP);
    
    readStatus = magneto5_setStatusReg();
    magneto5_configRegister_1( maxResolution );
    _measureResolution( maxResolution );
    
    if (readStatus & ( _MAGNETO_STATUS_MEASUREMENT_DONE | _MAGNETO_STATUS_READ_DONE ))
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
        hal_i2cRead( _slaveAddress, readReg, 6, END_MODE_STOP );

        axisBuffer[0] = readReg[1];
        axisBuffer[0] = axisBuffer[0] << 8;
        axisBuffer[0] = axisBuffer[0] | readReg[0];
        
        axisBuffer[1] = readReg[3];
        axisBuffer[1] = axisBuffer[1] << 8;
        axisBuffer[1] = axisBuffer[1] | readReg[2];
        
        axisBuffer[2] = readReg[5];
        axisBuffer[2] = axisBuffer[2] << 8;
        axisBuffer[2] = axisBuffer[2] | readReg[4];
        
        axisBuffer[0] = axisBuffer[0] >> _dataFlag;
        axisBuffer[1] = axisBuffer[1] >> _dataFlag;
        axisBuffer[2] = axisBuffer[2] >> _dataFlag;
        magneto5_reset();
    }
}

float magneto5_getAxisValue(uint8_t axis, uint8_t maxResolution)
{
    int16_t axisData[3];
    float axisValue;
    
    magneto5_getAxisData(&axisData[0],maxResolution);
    
    if ( axis == _MAGNETO5_AXIS_X)
    {
        axisValue = (float)axisData[0]/_maxResolution;
    }
    else if ( axis == _MAGNETO5_AXIS_Y)
    {
        axisValue = (float)axisData[1]/_maxResolution;
    }
    else if ( axis == _MAGNETO5_AXIS_Z)
    {
        axisValue = (float)axisData[1]/_maxResolution;
    }
    
    return axisValue;
}

void magneto5_configRegister_0(uint8_t configData)
{
    uint8_t writeReg[ 2 ];

    writeReg[ 0 ] = _MAGNETO5_REG_INTERNAL_CONTROL_0;
    writeReg[ 1 ] = configData;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 2, END_MODE_STOP );
    Delay_100ms();
}

void magneto5_configRegister_1(uint8_t configData)
{
    uint8_t writeReg[ 2 ];

    writeReg[ 0 ] = _MAGNETO5_REG_INTERNAL_CONTROL_1;
    writeReg[ 1 ] = configData;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 2, END_MODE_STOP );
    Delay_100ms();
}

void magneto5_reset()
{
   uint8_t writeReg[ 2 ];

    writeReg[ 0 ] = _MAGNETO5_REG_INTERNAL_CONTROL_0;
    writeReg[ 1 ] = _MAGNETO5_CR0_RESET;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 2, END_MODE_STOP );

}







/* -------------------------------------------------------------------------- */
/*
  __magneto5_driver.c

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