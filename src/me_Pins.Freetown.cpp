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
  TAddress BaseAddress,
  TUint_1 PinOffset
)
{
  TAddress ModePortAddr = GetModePortAddress(BaseAddress);

  me_Bits_Workmem::SetBitTo(ModePortAddr, PinOffset, 0);
}

/*
  Enable saturation

  Enables input-pullup. Reading for unconnected pin will return HIGH.
*/
void Freetown::EnableSaturation(
  TAddress BaseAddress,
  TUint_1 PinOffset
)
{
  TAddress WritePortAddr = GetWritePortAddress(BaseAddress);

  me_Bits_Workmem::SetBitTo(WritePortAddr, PinOffset, 1);
}

/*
  Read pin value
*/
void Freetown::ReadPin(
  TUint_1 * PinValue,
  TAddress BaseAddress,
  TUint_1 PinOffset
)
{
  TAddress ReadPortAddr = GetReadPortAddress(BaseAddress);

  me_Bits_Workmem::GetBit(PinValue, ReadPortAddr, PinOffset);
}

/*
  Set write mode
*/
void Freetown::SetWriteMode(
  TAddress BaseAddress,
  TUint_1 PinOffset
)
{
  TAddress ModePortAddr = GetModePortAddress(BaseAddress);

  me_Bits_Workmem::SetBitTo(ModePortAddr, PinOffset, 1);
}

/*
  Drive pin to LOW or HIGH
*/
void Freetown::DrivePinTo(
  TAddress BaseAddress,
  TUint_1 PinOffset,
  TUint_1 PinValue
)
{
  TAddress WritePortAddr = GetWritePortAddress(BaseAddress);

  me_Bits_Workmem::SetBitTo(WritePortAddr, PinOffset, PinValue);
}

/*
  2025-08-19
*/
