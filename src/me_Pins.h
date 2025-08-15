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

    private:
      TBool IsValidState;
      TAddress WritePortAddress;
      TUint_1 BitOffset;

      TAddress GetModePortAddress();
      TAddress GetReadPortAddress();
      TAddress GetWritePortAddress();

      TBool AdjustState(TUint_1 PinNumber);
      void SetReadMode();
      void EnableSaturation();
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
