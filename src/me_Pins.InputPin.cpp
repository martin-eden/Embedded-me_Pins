// ATmega328/P pins. Input pin interface implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>

using namespace me_Pins;

/*
  Setup pin for reading

  We need one item: pin number.

  We enable pin saturation. If somewhy you don't want it,
  call "SetSaturation(false)" afterwards.
*/
TBool TInputPin::Init(
  TUint_1 PinNumber
)
{
  this->IsArmed = false;

  if (!TBasePin::Init(PinNumber))
    return false;

  SetReadMode();

  this->IsArmed = true;

  return true;
}

/*
  Set read mode, enable saturation
*/
void TInputPin::SetReadMode()
{
  Freetown::SetReadMode(this->PinRef);
  Freetown::EnableSaturation(this->PinRef);
}

/*
  Read pin value
*/
TBool TInputPin::Read(
  TUint_1 * BitValue
)
{
  if (!this->IsArmed)
    return false;

  Freetown::ReadPin(BitValue, this->PinRef);

  return true;
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
  2025-08-19 Using [me_Bits_Workmem]
*/
