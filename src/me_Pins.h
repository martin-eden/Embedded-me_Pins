// Interface to pins. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

#include <me_BaseTypes.h>

namespace me_Pins
{
  /*
    Toolset for pin classes. Internal
  */
  class TBasePin
  {
    protected:
      TUint_1 BitOffset;

      TBool Init(TUint_1 PinNumber);

      TAddress GetModePortAddress();
      TAddress GetReadPortAddress();
      TAddress GetWritePortAddress();

    private:
      TAddress BaseAddress;

      TBool AdjustState(TUint_1 PinNumber);
  };

  /*
    Input pin
  */
  class TInputPin : protected TBasePin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Read(TUint_1 * BinaryValue);

    private:
      TBool IsArmed = false;

      void SetReadMode();
      void EnableSaturation();
  };

  /*
    Output pin
  */
  class TOutputPin : protected TBasePin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Write(TUint_1 BinaryValue);

    private:
      TBool IsArmed = false;

      void SetWriteMode();
      void DriveLow();
      void DriveHigh();
  };
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
*/
