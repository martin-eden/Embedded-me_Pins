// ATmega328/P pins. Input pin interface implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_WorkMemory.h>
#include <me_Bits.h>

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
  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, ModePortAddr);
  me_Bits::SetBitToZero(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, ModePortAddr);

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
  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, WritePortAddr);
  me_Bits::SetBitToOne(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, WritePortAddr);
}

/*
  Read pin value
*/
TBool TInputPin::Read(
  TUint_1 * BinaryValue
)
{
  if (!this->IsArmed)
    return false;

  TAddress ReadPortAddr = GetReadPortAddress();
  TUint_1 PortValues = 0;

  me_WorkMemory::GetByte(&PortValues, ReadPortAddr);
  me_Bits::GetBit(BinaryValue, PortValues, this->BitOffset);

  return true;
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
*/
