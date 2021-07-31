//
//    FILE: MCP4921_VSPI.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test MCP4921 lib
//    DATE: 2021-07-31
//     URL: https://github.com/RobTillaart/MCP4921
//

#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif

#include "MCP_DAC.h"

MCP4921 MCP;  // HW SPI


volatile int x;
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  MCP.selectVSPI();     // needs to be called before begin()
                        // uses default VSPI SCLK=14, MISO=12, MOSI=13, SELECT=15
  MCP.begin(15);
  
  Serial.print("MCP_DAC_LIB_VERSION: ");
  Serial.println(MCP_DAC_LIB_VERSION);
  Serial.println();
  Serial.print("CHANNELS:\t");
  Serial.println(MCP.channels());
  Serial.print("MAXVALUE:\t");
  Serial.println(MCP.maxValue());
  delay(100);

  performance_test();

  Serial.println("\nDone...");
}


void performance_test()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  start = micros();
  for (uint16_t value = 0; value < MCP.maxValue(); value++)
  {
    x = MCP.analogWrite(value, 0);
  }
  stop = micros();
  Serial.print(MCP.maxValue());
  Serial.print(" x MCP.analogWrite():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / (MCP.maxValue() + 1.0) );
  delay(10);

  start = micros();
  for (uint16_t value = 0; value < MCP.maxValue(); value++)
  {
    MCP.fastWriteA(value);
  }
  stop = micros();
  Serial.print(MCP.maxValue());
  Serial.print(" x MCP.fastWriteA():\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println((stop - start) / (MCP.maxValue() + 1.0) );
  delay(10); 
}


void loop()
{
}


// -- END OF FILE --
