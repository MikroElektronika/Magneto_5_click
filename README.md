![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Magneto5 Click

- **CIC Prefix**  : MAGNETO5
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : Mar 2018.

---

### Software Support

We provide a library for the Magneto5 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2361/magneto-5-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

This library consists of some generic functions for working with the click board.

Key functions :

- ```void magneto5_reset( void );``` - Used to software reset the sensor.
- ```float magneto5_getAxisValue(uint8_t axis, uint8_t maxResolution);``` - Function returns the calculated gaus value.
- ```void magneto5_getAxisData( int16_t *axisBuffer, uint8_t maxResolution );``` - Used for reading of the raw axis data from registers.

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initializes driver init and set measurement mode and channel
- Application Task - (code snippet) - Reads X / Y / Z data axis and logs to USBUART every 1 sec.


```.c
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
```

${EXAMPLE_ADDITIONAL_FUNCTIONS}

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2361/magneto-5-click) page.

Other mikroE Libraries used in the example:

- UART Library
- Conversions Library
- C_String Library
- I2C Library

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

---
---
