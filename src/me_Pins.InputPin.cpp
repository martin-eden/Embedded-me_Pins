// ATmega328/P pins. Input pin interface implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-22
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>

using namespace me_Pins;

/*
  Setup pin for reading

  Signal for not connected pins is HIGH.
*/
TBool TInputPin::Init(
  TUint_1 PinNumber
)
{
  if (!TBasePin::Init(PinNumber))
    return false;

  SetReadMode();

  return true;
}

/*
  Set read mode

  Enables input-pullup. Reading for unconnected pin will return HIGH.
*/
void TInputPin::SetReadMode()
{
  ModeBit.Clear();
  WriteBit.Set();
}

/*
  Read pin value
*/
TUint_1 TInputPin::Read()
{
  return ReadBit.Get();
}

/*
  2025 # # # #
  2026-02-17
*/
