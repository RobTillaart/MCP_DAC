//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-02-03
// PURPOSE: unit tests for the MCP_DAC
//          https://github.com/RobTillaart/MCP_DAC
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)

#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "MCP_DAC.h"


unittest_setup()
{
}

unittest_teardown()
{
}


unittest(test_constructor)
{
  fprintf(stderr, "VERSION: %s\n", (char *) MCP_DAC_LIB_VERSION);
  MCP4921 MCP;

  fprintf(stderr, "test default values\n");
  assertEqual(4095, MCP.maxValue());
  assertEqual(0, MCP.lastValue());
  assertEqual(1, MCP.channels());

}


unittest(test_gain)
{
  fprintf(stderr, "VERSION: %s\n", (char *) MCP_DAC_LIB_VERSION);
  MCP4921 MCP;

  assertEqual(1, MCP.getGain());

  MCP.setGain(2);
  assertEqual(2, MCP.getGain());

  MCP.setGain(0);
  assertEqual(2, MCP.getGain());

  MCP.setGain();
  assertEqual(1, MCP.getGain());
}


unittest(test_SPI_speed)
{
  fprintf(stderr, "VERSION: %s\n", (char *) MCP_DAC_LIB_VERSION);
  MCP4921 MCP;

  MCP.setSPIspeed(1000000);
  assertEqual(1000000, MCP.getSPIspeed());

  MCP.setSPIspeed(2000000);
  assertEqual(2000000, MCP.getSPIspeed());

  MCP.setSPIspeed(3000000);
  assertEqual(3000000, MCP.getSPIspeed());

  MCP.setSPIspeed(4000000);
  assertEqual(4000000, MCP.getSPIspeed());
}


unittest(test_active)
{
  fprintf(stderr, "VERSION: %s\n", (char *) MCP_DAC_LIB_VERSION);
  MCP4921 MCP;

  assertTrue(MCP.isActive());

  MCP.shutDown(true);
  assertFalse(MCP.isActive());

  MCP.reset();
  assertTrue(MCP.isActive());
}


unittest(test_buffered_mode)
{
  fprintf(stderr, "VERSION: %s\n", (char *) MCP_DAC_LIB_VERSION);
  MCP4921 MCP;

  assertFalse(MCP.getBufferedMode());

  MCP.setBufferedMode(true);
  assertTrue(MCP.getBufferedMode());

  MCP.setBufferedMode(false);
  assertFalse(MCP.getBufferedMode());
}


unittest_main()

// --------
