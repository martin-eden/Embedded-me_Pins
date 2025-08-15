// ATmega328/P pins. Interface implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_UnoAddresses.h>
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
  this->IsValidState = false;

  if (!AdjustState(PinNumber))
    return false;

  SetReadMode();

  EnableSaturation();

  this->IsValidState = true;

  return true;
}

/*
  Setup internal state

  For correct pin updates internal state. Returns true.
  For wrong pin does nothing. Returns false.

  We're not using pin number for work, we converting it
  to bit address.
*/
TBool TInputPin::AdjustState(
  TUint_1 PinNumber
)
{
  TAddress ByteAddr;
  TUint_1 BitOffs;
  TBool GotAddr;

  GotAddr =
    me_UnoAddresses::GetPinAddress(&ByteAddr, &BitOffs, PinNumber);

  if (!GotAddr)
    return false;

  this->WritePortAddress = ByteAddr;
  this->BitOffset = BitOffs;

  return true;
}

/*
  Get mode port address from base address

  Internal helper
*/
TAddress TInputPin::GetModePortAddress()
{
  // Pin mode port address is one before write port address (for ATmega328)
  return this->WritePortAddress - 1;
}

/*
  Get read port address. Internal helper
*/
TAddress TInputPin::GetReadPortAddress()
{
  return this->WritePortAddress - 2;
}

/*
  Get write port address. Internal helper
*/
TAddress TInputPin::GetWritePortAddress()
{
  return this->WritePortAddress;
}

/*
  Set read mode

  Internal
*/
void TInputPin::SetReadMode()
{
  TAddress ModePortAddr = GetModePortAddress();
  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, ModePortAddr);
  me_Bits::SetBitToZero(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, ModePortAddr);
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
  if (!this->IsValidState)
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
