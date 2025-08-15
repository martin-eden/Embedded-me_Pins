// [me_Pins] Test

/*
  Author: Martin Eden
  Last mod.: 2025-08-01
*/

/*
  This module is more like test than demo

  So code is lengthy and overcautious.
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_Console.h>

void RunTest()
{
  const TUint_1 NumRuns = 16;
  const TUint_2 InterrunDelay_Ms = 2000;

  const TUint_1 InputPinNumber = 8;
  const TBool Saturate = true;

  me_Pins::TInputPin InputPin;

  // Print test settings
  {
    Console.Print("( Settings");
    Console.Indent();

    // Print input pin setting
    {
      Console.Write("Input pin number");
      Console.Print(InputPinNumber);
      Console.EndLine();
    }

    // Print whether value saturation (input-pullup) is enabled
    {
      Console.Write("Saturate");
      Console.Print(Saturate);
      Console.EndLine();
    }

    // Print num runs
    {
      Console.Write("Number of runs");
      Console.Print(NumRuns);
      Console.EndLine();
    }

    // Print inter-run delay
    {
      Console.Write("Inter-runs delay (ms)");
      Console.Print(InterrunDelay_Ms);
      Console.EndLine();
    }

    Console.Unindent();
    Console.Print(")");
  }

  // Setup pin
  {
    if (!InputPin.Init(InputPinNumber))
      Console.Print("Pin setup failed");
    if (!InputPin.SetSaturation(Saturate))
      Console.Print("Setting saturation failed");
  }

  // Print state
  {
    TUint_1 RealPinNumber = 0;
    TBool RealSaturation = false;

    Console.Print("( State");
    Console.Indent();

    if (!InputPin.GetPinNumber(&RealPinNumber))
    {
      Console.Print("Getting pin number failed");
    }
    else
    {
      Console.Write("Pin number");
      Console.Print(RealPinNumber);
      Console.EndLine();
    }

    if (!InputPin.GetSaturation(&RealSaturation))
    {
      Console.Print("Getting saturation setting failed");
    }
    {
      Console.Write("Saturation");
      Console.Print(RealSaturation);
      Console.EndLine();
    }

    Console.Unindent();
    Console.Print(")");
  }

  for (TUint_1 RunNumber = 1; RunNumber <= NumRuns; ++RunNumber)
  {
    TUint_1 PinValue = 0;

    // Print run number, open group
    {
      Console.Write("( Run #");
      Console.Print(RunNumber);
      Console.EndLine();

      Console.Indent();
    }

    // Read pin value
    if (!InputPin.Read(&PinValue))
    {
      Console.Print("Reading pin value failed");
      // break;
    }
    else
    // Print pin value
    {
      Console.Write("Pin value");
      Console.Print(PinValue);
      Console.EndLine();
    }

    // Close group
    {
      Console.Unindent();
      Console.Print(")");
    }

    delay(InterrunDelay_Ms);
  }
}

void setup()
{
  me_Uart::Init(me_Uart::Speed_115k_Bps);

  Console.Print("( [me_Pins] test");
  Console.Indent();

  RunTest();

  Console.Unindent();
  Console.Print(") Done");
}

void loop()
{
}

/*
  2025-08-01
*/
