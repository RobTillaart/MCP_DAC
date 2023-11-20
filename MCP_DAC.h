#pragma once
//
//    FILE: MCP_DAC.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.0
//    DATE: 2021-02-03
// PURPOSE: Arduino library for MCP_DAC
//     URL: https://github.com/RobTillaart/MCP_DAC


#include "Arduino.h"
#include "SPI.h"


#define MCP_DAC_LIB_VERSION       (F("0.3.0"))


///////////////////////////////////////////////////////////////
//
//  BASE CLASS
//
class MCP_DAC
{
public:

#if defined(ARDUINO_ARCH_RP2040)
  MCP_DAC(SPIClassRP2040 *mySPI = &SPI);
#else
  MCP_DAC(SPIClass *mySPI = &SPI);
#endif
  //       SW_SPI
  MCP_DAC(uint8_t dataOut, uint8_t clock);

  //       both HW and SW SPI. 
  void     begin(uint8_t select);

  //       returns 0 or 1
  uint8_t  channels();
  //       returns 255 (=8 bit) or 1023 (=10 bit) or 4095 (=12 bit)
  uint16_t maxValue();

  //       gain = 1 or 2
  bool     setGain(uint8_t gain = 1);
  uint8_t  getGain();

  bool     analogWrite(uint16_t value, uint8_t channel = 0);
  uint16_t lastValue(uint8_t channel = 0);
  void     fastWriteA(uint16_t value);
  void     fastWriteB(uint16_t value);

  bool     increment(uint8_t channel = 0);
  bool     decrement(uint8_t channel = 0);

  //       convenience wrappers
  //       percentage = 0..100.0%
  void     setPercentage(float percentage, uint8_t channel = 0);
  float    getPercentage(uint8_t channel = 0);

  //       trigger LDAC = LatchDAC pin - if not set it does nothing
  void     setLatchPin( uint8_t latchPin);
  void     triggerLatch();

  //       shutDown - Page 21  ==> write will wake up.
  void     shutDown();
  bool     isActive();

  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  uint32_t getSPIspeed();

  //
  //       MCP49xxx series only
  //
  //       see page 20 ==> not functional for MCP48xx series.
  void     setBufferedMode(bool mode = false);
  bool     getBufferedMode();

  // debugging
  void     reset();
  bool     usesHWSPI();


protected:
  uint8_t  _dataOut;              //  Data out Pin (MOSI)
  uint8_t  _clock;                //  Clock Pin (SCK)
  uint8_t  _select;               //  Chip Select Pin (CS)
  uint8_t  _latchPin = 255;       //  Latch-DAC Pin (LDAC)
  bool     _hwSPI;                //  Hardware SPI (true) or Software SPI (false)
  uint32_t _SPIspeed = 16000000;  //  SPI-Bus Frequency

  uint8_t  _channels;             //  Number of DAC-Channels of a given Chip
  uint16_t _maxValue;             //  Maximum value of a given Chip
  uint16_t _value[2];             //  Current value  (cache for performance)
  uint8_t  _gain;                 //  Programmable Gain Amplifier variable
  bool     _buffered = false;     //  Buffer for the Reference Voltage of the MCP49XX Series Chips
  bool     _active   = true;      //  Indicates shutDown mode.

  void     transfer(uint16_t data);
  uint8_t  swSPI_transfer(uint8_t d);

#if defined(ARDUINO_ARCH_RP2040)

  SPIClassRP2040 * mySPI;

#else

  SPIClass    * mySPI;

#endif

  SPISettings _spi_settings;
};



///////////////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//

#if defined(ARDUINO_ARCH_RP2040)

///////////////////////////////////////////////////////////////
//
//  MCP4800 Series
//

class MCP4801 : public MCP_DAC
{
public:
  MCP4801(SPIClassRP2040 *inSPI = &SPI);
  MCP4801(uint8_t dataOut, uint8_t clock);
};

class MCP4802 : public MCP_DAC
{
public:
  MCP4802(SPIClassRP2040 *inSPI = &SPI);
  MCP4802(uint8_t dataOut, uint8_t clock);
};

class MCP4811 : public MCP_DAC
{
public:
  MCP4811(SPIClassRP2040 *inSPI = &SPI);
  MCP4811(uint8_t dataOut, uint8_t clock);
};

class MCP4812 : public MCP_DAC
{
public:
  MCP4812(SPIClassRP2040 *inSPI = &SPI);
  MCP4812(uint8_t dataOut, uint8_t clock);
};

class MCP4821 : public MCP_DAC
{
public:
  MCP4821(SPIClassRP2040 *inSPI = &SPI);
  MCP4821(uint8_t dataOut, uint8_t clock);
};

class MCP4822 : public MCP_DAC
{
public:
  MCP4822(SPIClassRP2040 *inSPI = &SPI);
  MCP4822(uint8_t dataOut, uint8_t clock);
};

///////////////////////////////////////////////////////////////
//
//  MCP4900 Series
//

class MCP4901 : public MCP_DAC
{
public:
  MCP4901(SPIClassRP2040 *inSPI = &SPI);
  MCP4901(uint8_t dataOut, uint8_t clock);
};

class MCP4902 : public MCP_DAC
{
public:
  MCP4902(SPIClassRP2040 *inSPI = &SPI);
  MCP4902(uint8_t dataOut, uint8_t clock);
};

class MCP4911 : public MCP_DAC
{
public:
  MCP4911(SPIClassRP2040 *inSPI = &SPI);
  MCP4911(uint8_t dataOut, uint8_t clock);
};

class MCP4912 : public MCP_DAC
{
public:
  MCP4912(SPIClassRP2040 *inSPI = &SPI);
  MCP4912(uint8_t dataOut, uint8_t clock);
};

class MCP4921 : public MCP_DAC
{
public:
  MCP4921(SPIClassRP2040 *inSPI = &SPI);
  MCP4921(uint8_t dataOut, uint8_t clock);
};

class MCP4922 : public MCP_DAC
{
public:
  MCP4922(SPIClassRP2040 *inSPI = &SPI);
  MCP4922(uint8_t dataOut, uint8_t clock);
};


#else

///////////////////////////////////////////////////////////////
//
//  MCP4800 Series
//

class MCP4801 : public MCP_DAC
{
public:
  MCP4801(SPIClass *inSPI = &SPI);
  MCP4801(uint8_t dataOut, uint8_t clock);
};

class MCP4802 : public MCP_DAC
{
public:
  MCP4802(SPIClass *inSPI = &SPI);
  MCP4802(uint8_t dataOut, uint8_t clock);
};

class MCP4811 : public MCP_DAC
{
public:
  MCP4811(SPIClass *inSPI = &SPI);
  MCP4811(uint8_t dataOut, uint8_t clock);
};

class MCP4812 : public MCP_DAC
{
public:
  MCP4812(SPIClass *inSPI = &SPI);
  MCP4812(uint8_t dataOut, uint8_t clock);
};

class MCP4821 : public MCP_DAC
{
public:
  MCP4821(SPIClass *inSPI = &SPI);
  MCP4821(uint8_t dataOut, uint8_t clock);
};

class MCP4822 : public MCP_DAC
{
public:
  MCP4822(SPIClass *inSPI = &SPI);
  MCP4822(uint8_t dataOut, uint8_t clock);
};

///////////////////////////////////////////////////////////////
//
//  MCP4900 Series
//

class MCP4901 : public MCP_DAC
{
public:
  MCP4901(SPIClass *inSPI = &SPI);
  MCP4901(uint8_t dataOut, uint8_t clock);
};

class MCP4902 : public MCP_DAC
{
public:
  MCP4902(SPIClass *inSPI = &SPI);
  MCP4902(uint8_t dataOut, uint8_t clock);
};

class MCP4911 : public MCP_DAC
{
public:
  MCP4911(SPIClass *inSPI = &SPI);
  MCP4911(uint8_t dataOut, uint8_t clock);
};

class MCP4912 : public MCP_DAC
{
public:
  MCP4912(SPIClass *inSPI = &SPI);
  MCP4912(uint8_t dataOut, uint8_t clock);
};

class MCP4921 : public MCP_DAC
{
public:
  MCP4921(SPIClass *inSPI = &SPI);
  MCP4921(uint8_t dataOut, uint8_t clock);
};

class MCP4922 : public MCP_DAC
{
public:
  MCP4922(SPIClass *inSPI = &SPI);
  MCP4922(uint8_t dataOut, uint8_t clock);
};

#endif


//  -- END OF FILE --

