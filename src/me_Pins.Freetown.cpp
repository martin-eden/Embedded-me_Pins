// Pins access core

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_Bits_Workmem.h>

using namespace me_Pins;

/*
  Get Mode port address
*/
TAddress Freetown::GetModePortAddress(
  TAddress BaseAddress
)
{
  return BaseAddress - 1;
}

/*
  Get Read port address
*/
TAddress Freetown::GetReadPortAddress(
  TAddress BaseAddress
)
{
  return BaseAddress - 2;
}

/*
  Get Write port address
*/
TAddress Freetown::GetWritePortAddress(
  TAddress BaseAddress
)
{
  return BaseAddress;
}

/*
  Set read mode
*/
void Freetown::SetReadMode(
  TPinLocation PinRef
)
{
  TAddress ModePortAddr = GetModePortAddress(PinRef.BaseAddress);

  me_Bits_Workmem::SetBitTo(ModePortAddr, PinRef.PinOffset, 0);
}

/*
  Enable saturation

  Enables input-pullup. Reading for unconnected pin will return HIGH.
*/
void Freetown::EnableSaturation(
  TPinLocation PinRef
)
{
  TAddress WritePortAddr = GetWritePortAddress(PinRef.BaseAddress);

  me_Bits_Workmem::SetBitTo(WritePortAddr, PinRef.PinOffset, 1);
}

/*
  Read pin value
*/
void Freetown::ReadPin(
  TUint_1 * PinValue,
  TPinLocation PinRef
)
{
  TAddress ReadPortAddr = GetReadPortAddress(PinRef.BaseAddress);

  me_Bits_Workmem::GetBit(PinValue, ReadPortAddr, PinRef.PinOffset);
}

/*
  Set write mode
*/
void Freetown::SetWriteMode(
  TPinLocation PinRef
)
{
  TAddress ModePortAddr = GetModePortAddress(PinRef.BaseAddress);

  me_Bits_Workmem::SetBitTo(ModePortAddr, PinRef.PinOffset, 1);
}

/*
  Drive pin to LOW or HIGH
*/
void Freetown::DrivePinTo(
  TPinLocation PinRef,
  TUint_1 PinValue
)
{
  TAddress WritePortAddr = GetWritePortAddress(PinRef.BaseAddress);

  me_Bits_Workmem::SetBitTo(WritePortAddr, PinRef.PinOffset, PinValue);
}

/*
  2025-08-19
*/
