// Interface to pins. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

#include <me_BaseTypes.h>

namespace me_Pins
{
  class TInputPin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Read(TUint_1 * BinaryValue);

      TBool SetPinNumber(TUint_1 PinNumber);
      TBool GetPinNumber(TUint_1 * PinNumber);

      // Value saturation (aka input-pullup)
      TBool SetSaturation(TBool SaturationEnabled);
      TBool GetSaturation(TBool * SaturationEnabled);

    private:
      TBool IsValidState;
      TUint_1 PinNumber;
      TAddress WritePortAddress;
      TUint_1 BitOffset;
      TBool SaturationEnabled;

      void SetReadMode();
      void SetSaturationOn();
      void SetSaturationOff();
  };

  class TOutputPin
  {
    public:
    private:
  };
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
*/
