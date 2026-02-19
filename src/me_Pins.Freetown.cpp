// Pins access core

/*
  Author: Martin Eden
  Last mod.: 2026-02-19
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>
#include <me_Bits_Workmem.h>

using namespace me_Pins;

TBool Freetown::CheckPinNumber(
  TUint_1 PinNumber
)
{
  return (PinNumber <= 19);
}

/*
  Return write bit location for pin by pin number

  Specific to ATmega328
*/
TBool Freetown::GetWritePinBit(
  me_Bits_Workmem::TBitLocation * PinBit,
  TUint_1 PinNumber
)
{
  if (!CheckPinNumber(PinNumber))
    return false;

  /*
    Addresses of Write ports

    They are used as base address.
  */
  enum PortAddresses:TAddress
  {
    PortB = 37,
    PortC = 40,
    PortD = 43,
  };

  if (PinNumber <= 7)
  {
    PinBit->Address = PortAddresses::PortD;
    PinBit->BitOffset = PinNumber;
  }
  else if ((PinNumber >= 8) && (PinNumber <= 13))
  {
    PinBit->Address = PortAddresses::PortB;
    PinBit->BitOffset = PinNumber - 8;
  }
  else if ((PinNumber >= 14) && (PinNumber <= 19))
  {
    PinBit->Address = PortAddresses::PortC;
    PinBit->BitOffset = PinNumber - 14;
  }

  return true;
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
  2025-08-19
  2025-08-22 Imported [me_UnoAddresses]
  2026-02-17
*/
