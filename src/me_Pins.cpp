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

  if (!SetPinNumber(PinNumber))
    return false;

  SetSaturationOn();

  SetReadMode();

  this->IsValidState = true;

  return true;
}

/*
  Set read mode

  Internal
*/
void TInputPin::SetReadMode()
{
  // Pin mode port address is one before write port address (for ATmega328)
  TAddress ModePortAddr = this->WritePortAddress - 1;

  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, ModePortAddr);
  me_Bits::SetBitToZero(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, ModePortAddr);
}

/*
  Get pin number
*/
TBool TInputPin::GetPinNumber(
  TUint_1 * PinNumber
)
{
  if (!this->IsValidState)
    return false;

  *PinNumber = this->PinNumber;

  return true;
}

/*
  Set pin number

  For correct pin updates internal state. Returns true.
  For wrong pin does nothing. Returns false.
*/
TBool TInputPin::SetPinNumber(
  TUint_1 PinNumber
)
{
  TAddress ByteAddr;
  TUint_1 BitOffs;
  TBool GotAddress;

  GotAddress =
    me_UnoAddresses::GetPinAddress(&ByteAddr, &BitOffs, PinNumber);

  if (!GotAddress)
    return false;

  this->PinNumber = PinNumber;
  this->WritePortAddress = ByteAddr;
  this->BitOffset = BitOffs;

  return true;
}

/*
  Enable/disable saturation
*/
TBool TInputPin::SetSaturation(
  TBool SaturationEnabled
)
{
  if (!this->IsValidState)
    return false;

  if (SaturationEnabled)
    SetSaturationOn();
  else
    SetSaturationOff();

  return true;
}

/*
  Enable saturation

  Enables input-pullup. Reading for unconnected pin will return HIGH.

  Internal
*/
void TInputPin::SetSaturationOn()
{
  // WritePort[Bit] = 1

  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, this->WritePortAddress);
  me_Bits::SetBitToOne(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, this->WritePortAddress);

  this->SaturationEnabled = true;
}

/*
  Disable saturation

  Disables input-pullup. Reading for unconnected pin will return
  random value.

  Internal
*/
void TInputPin::SetSaturationOff()
{
  // WritePort[Bit] = 0

  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, this->WritePortAddress);
  me_Bits::SetBitToZero(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, this->WritePortAddress);

  this->SaturationEnabled = false;
}

/*
  Return saturation
*/
TBool TInputPin::GetSaturation(
  TBool * SaturationEnabled
)
{
  if (!this->IsValidState)
    return false;

  *SaturationEnabled = this->SaturationEnabled;

  return true;
}

/*
  Read pin value
*/
TBool TInputPin::Read(
  TUint_1 * BinaryValue
)
{
  // Reading port address is two before write port address (for ATmega328)
  TAddress ReadPortAddr = this->WritePortAddress - 2;

  TUint_1 PortValues = 0;

  if (!this->IsValidState)
    return false;

  me_WorkMemory::GetByte(&PortValues, ReadPortAddr);
  me_Bits::GetBit(BinaryValue, PortValues, this->BitOffset);

  return true;
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
*/
