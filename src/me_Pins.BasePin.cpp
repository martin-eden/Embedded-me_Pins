// ATmega328/P pins. Base pin class implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-22
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>

using namespace me_Pins;

/*
  Setup pin

  For correct pin number it updates internal state, returns true.
  For wrong pin number it returns false.
*/
TBool TBasePin::Init(
  TUint_1 PinNumber
)
{
  return Freetown::InitPinRecord(&this->PinRef, PinNumber);
}

/*
  2025-08-15
  2025-08-19
  2025-08-22
*/
