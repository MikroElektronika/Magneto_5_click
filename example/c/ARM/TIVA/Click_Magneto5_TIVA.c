/*
Example for Magneto5 Click

    Date          : Mar 2018.
    Author        : MikroE Team

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initializes driver init and set measurement mode and channel
- Application Task - (code snippet) - Reads X / Y / Z data axis and logs to USBUART every 1 sec.

*/

#include "Click_Magneto5_types.h"
#include "Click_Magneto5_config.h"

uint8_t ProductID;
float X_axis;
float Y_axis;
float Z_axis;
char writeText[256];

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_MAGNETO5_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );

    mikrobus_logWrite( "___ System Init ___", _LOG_LINE );
    Delay_ms( 100 );
}

void applicationInit()
{
    magneto5_i2cDriverInit( (T_MAGNETO5_P)&_MIKROBUS1_GPIO, (T_MAGNETO5_P)&_MIKROBUS1_I2C, 0x30 );
}

void applicationTask()
{
    X_axis = magneto5_getAxisValue( _MAGNETO5_AXIS_X, _MAGNETO5_CH3_12bits_1ms);
    Y_axis = magneto5_getAxisValue( _MAGNETO5_AXIS_Y, _MAGNETO5_CH3_12bits_1ms );
    Z_axis = magneto5_getAxisValue( _MAGNETO5_AXIS_Z, _MAGNETO5_CH3_12bits_1ms );

    FloatToStr( X_axis, writeText );
    mikrobus_logWrite( "-- X axis : ", _LOG_TEXT );
    mikrobus_logWrite( writeText, _LOG_LINE );

    FloatToStr( Y_axis, writeText );
    mikrobus_logWrite( "-- Y axis : ", _LOG_TEXT );
    mikrobus_logWrite( writeText, _LOG_LINE );

    FloatToStr( Z_axis, writeText );
    mikrobus_logWrite( "-- Z axis : ", _LOG_TEXT );
    mikrobus_logWrite( writeText, _LOG_LINE );

    mikrobus_logWrite( " --------------- ", _LOG_LINE );
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}