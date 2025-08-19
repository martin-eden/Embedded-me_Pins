// Interface to pins. ATmega328

/*
  Author: Martin Eden
  Last mod.: 2025-08-19
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
    Pin description for low-level functions
  */
  struct TPinLocation
  {
    TAddress BaseAddress;
    TUint_1 PinOffset;
  };

  /*
    Base class. Keeper of pin description
  */
  class TBasePin
  {
    protected:
      TPinLocation PinRef;

      TBool Init(TUint_1 PinNumber);
  };

  /*
    Binary input pin
  */
  class TInputPin : protected TBasePin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Read(TUint_1 * BitValue);

    protected:
      void SetReadMode();

    private:
      TBool IsArmed = false;
  };

  /*
    Binary output pin
  */
  class TOutputPin : protected TBasePin
  {
    public:
      TBool Init(TUint_1 PinNumber);
      TBool Write(TUint_1 BitValue);

    protected:
      void SetWriteMode();

    private:
      TBool IsArmed = false;
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
      TBool Read(TUint_1 * BitValue);
      TBool Write(TUint_1 BitValue);

    private:
      TBool IsArmed = false;
      TPinModes PinMode = TPinModes::Undefined;
  };

  /*
    Core access
  */
  namespace Freetown
  {
    TAddress GetModePortAddress(TAddress BaseAddress);
    TAddress GetReadPortAddress(TAddress BaseAddress);
    TAddress GetWritePortAddress(TAddress BaseAddress);

    void SetReadMode(TPinLocation PinRef);
    void EnableSaturation(TPinLocation PinRef);
    void ReadPin(TUint_1 * PinValue, TPinLocation PinRef);
    void SetWriteMode(TPinLocation PinRef);
    void DrivePinTo(TPinLocation PinRef, TUint_1 PinValue);
  }
}

/*
  2025-08-01
  2025-08-14
  2025-08-15
  2025-08-19 Design cleanup
*/
