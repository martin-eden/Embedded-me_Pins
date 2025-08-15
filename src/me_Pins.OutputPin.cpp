// Output pin implementation. ATmega328

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
  Set write mode

  Internal
*/
void TOutputPin::SetWriteMode()
{
  TAddress ModePortAddr = GetModePortAddress();
  TUint_1 ByteValue = 0;

  me_WorkMemory::GetByte(&ByteValue, ModePortAddr);
  me_Bits::SetBitToOne(&ByteValue, this->BitOffset);
  me_WorkMemory::SetByte(ByteValue, ModePortAddr);
}

/*
  Set pin value
*/
TBool TOutputPin::Write(
  TUint_1 BinaryValue
)
{
  if (!this->IsArmed)
    return false;

  if (!me_Bits::Freetown::CheckBitValue(BinaryValue))
    return false;

  if (BinaryValue == 0)
    DriveLow();
  else if (BinaryValue == 1)
    DriveHigh();

  return true;
}

/*
  Drive pin to LOW. Internal
*/
void TOutputPin::DriveLow()
{
  TAddress WritePortAddr = GetWritePortAddress();
  TUint_1 PortValues = 0;

  me_WorkMemory::GetByte(&PortValues, WritePortAddr);
  me_Bits::SetBitToZero(&PortValues, this->BitOffset);
  me_WorkMemory::SetByte(PortValues, WritePortAddr);
}

/*
  Drive pin to HIGH. Internal
*/
void TOutputPin::DriveHigh()
{
  TAddress WritePortAddr = GetWritePortAddress();
  TUint_1 PortValues = 0;

  me_WorkMemory::GetByte(&PortValues, WritePortAddr);
  me_Bits::SetBitToOne(&PortValues, this->BitOffset);
  me_WorkMemory::SetByte(PortValues, WritePortAddr);
}

/*
  2025-08-15
*/
