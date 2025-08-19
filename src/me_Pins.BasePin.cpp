// ATmega328/P pins. Base pin class implementation

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
*/

#include "me_Pins.h"

#include <me_BaseTypes.h>
#include <me_UnoAddresses.h>

using namespace me_Pins;

/*
  Setup pin

  For correct pin number it updates internal state. Returns true.
  For wrong pin number it does nothing. Returns false.

  We need one item: pin number. We'll convert it to bit address.
  We're not storing pin number.
*/
TBool TBasePin::Init(
  TUint_1 PinNumber
)
{
  TAddress BaseAddr;
  TUint_1 BitOffs;
  TBool GotAddr;

  /*
    GetPinAddress() returns address of Write port.
    We will use it as our base address.
  */
  GotAddr =
    me_UnoAddresses::GetPinAddress(&BaseAddr, &BitOffs, PinNumber);

  if (!GotAddr)
    return false;

  this->PinRef.BaseAddress = BaseAddr;
  this->PinRef.PinOffset = BitOffs;

  return true;
}

/*
  2025-08-15
  2025-08-19
*/
