// Interface to pins. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

/*
  Scope

  Some legs of microcontroller are called "pins".

  Those pieces of wire can sense voltage or provide voltage and current.

  Voltage sensed can be read as 10-bit "analog" signal
  or 1-bit "digital" signal.

  These are "analog input" and "digital input".

  Not all pins can do "analog input".

  Emitted voltage can only be 5V or 0V, 1-bit signal.

  That's "digital output".

  Arduino framework uses pulses to emulate "analog output".
  That is emulation  and out of scope of this library.

  Here we providing API for digital input and digital output.

  Analog input will probably be done as separate library.
*/

/*
  Class structure

  From software pins are referenced by integer number.
  To make hardware work we need bit address (byte address
  and bit offset).

  Base class (Base Pin) converts pin number to bit address.

  Derived class (Input Pin) provides digital input.
  Derived class (Output Pin) provides digital output.

  Union class (IO Pin) provides digital input/output.
  It tracks pin mode.
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

      TBool SetupState(TUint_1 PinNumber);
  };

  /*
    Binary input pin
  */
  class TInputPin : protected TBasePin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Read(TUint_1 * BinaryValue);

    protected:
      void SetReadMode();

    private:
      TBool IsArmed = false;

      void EnableSaturation();
  };

  /*
    Binary output pin
  */
  class TOutputPin : protected TBasePin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Write(TUint_1 BinaryValue);
      TBool WriteOne();
      TBool WriteZero();

    protected:
      void SetWriteMode();

    private:
      TBool IsArmed = false;

      void DriveLow();
      void DriveHigh();
  };

  enum TPinModes
  {
    Undefined,
    Input,
    Output
  };

  /*
    Binary input/output pin
  */
  class TIoPin : protected TInputPin, protected TOutputPin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Read(TUint_1 * BinaryValue);
      TBool Write(TUint_1 BinaryValue);

    private:
      TBool IsArmed = false;

      TPinModes PinMode = TPinModes::Undefined;
  };
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
*/
