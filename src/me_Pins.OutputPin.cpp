// Output pin implementation. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_Bits.h>

using namespace me_Pins;

/*
  Setup pin for writing
*/
TBool TOutputPin::Init(
  TUint_1 PinNumber
)
{
  this->IsArmed = false;

  if (!TBasePin::Init(PinNumber))
    return false;

  SetWriteMode();

  this->IsArmed = true;

  return true;
}

/*
  Set write mode, drive HIGH
*/
void TOutputPin::SetWriteMode()
{
  Freetown::SetWriteMode(this->PinRef);
  Freetown::DrivePinTo(this->PinRef, 1);
}

/*
  Set pin value
*/
TBool TOutputPin::Write(
  TUint_1 BitValue
)
{
  if (!this->IsArmed)
    return false;

  if (!me_Bits::CheckBitValue(BitValue))
    return false;

  Freetown::DrivePinTo(this->PinRef, BitValue);

  return true;
}

/*
  2025-08-15
  2025-08-19 Using [me_Bits_Workmem]
*/
