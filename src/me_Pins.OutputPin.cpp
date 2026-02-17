// Output pin implementation. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2026-02-17
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>
#include <me_Bits_Workmem.h>

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
  2025-08-15
  2025-08-19 Using [me_Bits_Workmem]
  2025-08-22
  2026-02-17
*/
