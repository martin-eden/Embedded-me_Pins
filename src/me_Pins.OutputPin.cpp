// Output pin implementation. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2026-02-20
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>

using namespace me_Pins;

/*
  Setup pin for writing, drive LOW
*/
TBool TOutputPin::Init(
  TUint_1 PinNumber
)
{
  if (!TBasePin::Init(PinNumber))
    return false;

  SetWriteMode();

  return true;
}

/*
  Set output mode, drive LOW
*/
void TOutputPin::SetWriteMode()
{
  ModeBit.Set();
  WriteBit.Clear();
}

/*
  Drive pin to binary value
*/
TBool TOutputPin::Write(
  TUint_1 BitValue
)
{
  return WriteBit.SetTo(BitValue);
}

/*
  2025 # # #
  2026-02-17
*/
