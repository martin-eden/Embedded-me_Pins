// ATmega328/P pins. Digital input/output pin

/*
  Author: Martin Eden
  Last mod.: 2026-02-17
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>

using namespace me_Pins;

/*
  Setup pin

  Pin is initialized as input.
*/
TBool TIoPin::Init(
  TUint_1 PinNumber
)
{
  if (!TOutputPin::Init(PinNumber))
    return false;

  if (!TInputPin::Init(PinNumber))
    return false;

  SetMode(TPinModes::Input);

  return true;
}

/*
  Get pin mode
*/
TPinModes TIoPin::GetMode()
{
  return PinMode;
}

/*
  Set pin mode
*/
void TIoPin::SetMode(
  TPinModes PinMode
)
{
  this->PinMode = PinMode;

  if (PinMode == TPinModes::Input)
    TInputPin::SetReadMode();
  else if (PinMode == TPinModes::Output)
    TOutputPin::SetWriteMode();
}

/*
  Read pin value
*/
TUint_1 TIoPin::Read()
{
  if (PinMode != TPinModes::Input)
    SetMode(TPinModes::Input);

  return TInputPin::Read();
}

/*
  Write pin value
*/
TBool TIoPin::Write(
  TUint_1 BitValue
)
{
  /*
    There are lot of vague words in (Datasheet @18.2.3) about
    transitions Input-Pullup -> Output-Low and
    Input-Floating -> Output-High.

    Truth is that no action needed. Mentioned "must"'s will occur
    as effect of setting pin mode bit.
  */
  if (PinMode != TPinModes::Output)
    SetMode(TPinModes::Output);

  return TOutputPin::Write(BitValue);
}

/*
  2025-08-15
  2026-02-17
*/
