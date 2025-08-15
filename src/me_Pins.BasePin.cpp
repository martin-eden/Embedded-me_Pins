// ATmega328/P pins. Base pin class implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_UnoAddresses.h>

using namespace me_Pins;

/*
  Setup pin
*/
TBool TBasePin::Init(
  TUint_1 PinNumber
)
{
  if (!SetupState(PinNumber))
    return false;

  return true;
}

/*
  Setup internal state. Internal

  For correct pin number it updates internal state. Returns true.
  For wrong pin number it does nothing. Returns false.

  We need one item: pin number. We'll convert it to bit address.
  We're not storing pin number.
*/
TBool TBasePin::SetupState(
  TUint_1 PinNumber
)
{
  TAddress ByteAddr;
  TUint_1 BitOffs;
  TBool GotAddr;

  /*
    GetPinAddress() returns address of Write port.
    We will use it as our base address.
  */
  GotAddr =
    me_UnoAddresses::GetPinAddress(&ByteAddr, &BitOffs, PinNumber);

  if (!GotAddr)
    return false;

  this->BaseAddress = ByteAddr;
  this->BitOffset = BitOffs;

  return true;
}

/*
  Get Mode port address. Internal helper
*/
TAddress TBasePin::GetModePortAddress()
{
  return this->BaseAddress - 1;
}

/*
  Get Read port address. Internal helper
*/
TAddress TBasePin::GetReadPortAddress()
{
  return this->BaseAddress - 2;
}

/*
  Get Write port address. Internal helper
*/
TAddress TBasePin::GetWritePortAddress()
{
  return this->BaseAddress;
}

/*
  2025-08-15
*/
