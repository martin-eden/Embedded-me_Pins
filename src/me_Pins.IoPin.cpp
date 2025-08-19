// ATmega328/P pins. Digital input/output pin

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>

using namespace me_Pins;

/*
  Why do we have overridden Read() and Write()?

  Leg of microcontroller aka "pin" at one time can either sense signal
  (be in input mode) or provide signal (be in output mode).

  Switching between modes is done in wrappers for Read() and Write().
*/

/*
  Setup pin

  Pin is initialized as input.
*/
TBool TIoPin::Init(
  TUint_1 PinNumber
)
{
  this->IsArmed = false;

  if (!TOutputPin::Init(PinNumber))
    return false;

  if (!TInputPin::Init(PinNumber))
    return false;

  this->PinMode = TPinModes::Input;

  this->IsArmed = true;

  return true;
}

/*
  Read pin value
*/
TBool TIoPin::Read(
  TUint_1 * BitValue
)
{
  if (!this->IsArmed)
    return false;

  if (this->PinMode != TPinModes::Input)
  {
    TInputPin::SetReadMode();

    this->PinMode = TPinModes::Input;
  }

  return TInputPin::Read(BitValue);
}

/*
  Write pin value
*/
TBool TIoPin::Write(
  TUint_1 BitValue
)
{
  if (!this->IsArmed)
    return false;

  /*
    There are lot of vague words in (Datasheet @18.2.3) about
    transitions Input-Pullup -> Output-Low and
    Input-Floating -> Output-High.

    Truth is that no action needed. Mentioned "must"'s will occur
    as effect of setting pin mode bit.
  */
  if (this->PinMode != TPinModes::Output)
  {
    TOutputPin::SetWriteMode();

    this->PinMode = TPinModes::Output;
  }

  return TOutputPin::Write(BitValue);
}

/*
  2025-08-15
*/
