// ATmega328/P pins. Base pin class implementation

/*
  Author: Martin Eden
  Last mod.: 2026-02-20
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>
#include <me_Bits.h>

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
  me_Bits::TBitLocation WriteBitLoc;
  me_Bits::TBitLocation ReadBitLoc;
  me_Bits::TBitLocation ModeBitLoc;

  if (!Freetown::CheckPinNumber(PinNumber))
    return false;

  Freetown::GetWritePinBit(&WriteBitLoc, PinNumber);
  WriteBit.SetLocation(WriteBitLoc);

  ReadBitLoc.Address = Freetown::GetReadPortAddress(WriteBitLoc.Address);
  ReadBitLoc.BitOffset = WriteBitLoc.BitOffset;
  ReadBit.SetLocation(ReadBitLoc);

  ModeBitLoc.Address = Freetown::GetModePortAddress(WriteBitLoc.Address);
  ModeBitLoc.BitOffset = WriteBitLoc.BitOffset;
  ModeBit.SetLocation(ModeBitLoc);

  return true;
}

/*
  2025 # # #
  2026-02-17
*/
