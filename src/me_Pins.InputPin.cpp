// ATmega328/P pins. Input pin interface implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_Bits_Workmem.h>

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

  Internal
*/
void TInputPin::SetReadMode()
{
  TAddress ModePortAddr = GetModePortAddress();

  me_Bits_Workmem::SetBitToZero(ModePortAddr, this->BitOffset);

  EnableSaturation();
}

/*
  Enable saturation

  Enables input-pullup. Reading for unconnected pin will return HIGH.

  Internal
*/
void TInputPin::EnableSaturation()
{
  TAddress WritePortAddr = GetWritePortAddress();

  me_Bits_Workmem::SetBitToOne(WritePortAddr, this->BitOffset);
}

/*
  Read pin value
*/
TBool TInputPin::Read(
  TUint_1 * BitValue
)
{
  TAddress ReadPortAddr = GetReadPortAddress();

  if (!this->IsArmed)
    return false;

  return
    me_Bits_Workmem::GetBit(BitValue, ReadPortAddr, this->BitOffset);
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
  2025-08-19 Using [me_Bits_Workmem]
*/
