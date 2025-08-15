// [me_Pins] Test

/*
  Author: Martin Eden
  Last mod.: 2025-08-15
*/

/*
  This module is more like test than demo

  Pins are important shit.

  So code is lengthy and overcautious.
*/

#include <me_Pins.h>

#include <me_BaseTypes.h>
#include <me_Uart.h>
#include <me_Console.h>

/*
  Pause for given number of seconds

  Adoption candidate.
*/
void Sleep(
  TUint_1 NumSeconds
)
{
  if (NumSeconds > 60)
    return;

  if (NumSeconds == 0)
    return;

  TUint_2 NumMillis = (TUint_2) NumSeconds * 1000;

  delay(NumMillis);
}

/*
  Delay for given number of milliseconds

  Adoption candidate.
*/
void Delay(
  TUint_2 NumMillis
)
{
  if (NumMillis > 10000)
    return;

  if (NumMillis == 0)
    return;

  delay(NumMillis);
}

/*
  Print group opening. Helper. Adoption candidate

  Prints string with group prefix and increases indent.
*/
void Console_OpenGroup(
  const TAsciiz GroupName_Asciiz = NULL
)
{
  Console.Write("(");

  if (GroupName_Asciiz != NULL)
  {
    Console.Write(" ");
    Console.Write(GroupName_Asciiz);
  }

  Console.EndLine();

  Console.Indent();
}

/*
  Print group closing. Helper. Adoption candidate

  Decreases indent and prints string with group postfix.
*/
void Console_CloseGroup(
  const TAsciiz GroupName_Asciiz = NULL
)
{
  Console.Unindent();

  Console.Write(")");

  if (GroupName_Asciiz != NULL)
  {
    Console.Write(" ");
    Console.Write(GroupName_Asciiz);
  }

  Console.EndLine();
}

/*
  Annotate integer. Helper. Adoption candidate

  Prints prefix string and TUint_1.
*/
void Console_Annotate(
  TUint_1 Value,
  const TAsciiz Annotation
)
{
  Console.Write(Annotation);
  Console.Print(Value);
  Console.EndLine();
}

/*
  Annotate integer. Helper. Adoption candidate

  Prints prefix string and TUint_2.

  Fucking hate two things: duplicated code and templates.
*/
void Console_Annotate(
  TUint_2 Value,
  const TAsciiz Annotation
)
{
  Console.Write(Annotation);
  Console.Print(Value);
  Console.EndLine();
}

/*
  Run digital input test
*/
void RunDigitalInputTest(
  TUint_1 InputPinNumber
)
{
  const TUint_1 NumRuns = 12;
  const TUint_2 InterrunDelay_S = 2;

  me_Pins::TInputPin InputPin;

  Console_OpenGroup("Digital input test");

  {
    Console_OpenGroup("Settings");

    Console_Annotate(InputPinNumber, "Input pin number");
    Console_Annotate(NumRuns, "Number of runs");
    Console_Annotate(InterrunDelay_S, "Delay between runs (s)");

    Console_CloseGroup();
  }

  if (!InputPin.Init(InputPinNumber))
  {
    Console.Print("Pin setup failed");

    Console_CloseGroup();

    return;
  }

  for (TUint_1 RunNumber = 1; RunNumber <= NumRuns; ++RunNumber)
  {
    TUint_1 PinValue = 0;

    // Open group, print run number
    {
      Console.Write("( Run");
      Console.Print(RunNumber);
      Console.EndLine();

      Console.Indent();
    }

    // Read pin value
    if (!InputPin.Read(&PinValue))
    {
      Console.Print("Reading pin value failed");

      Console_CloseGroup();

      break;
    }
    else
      Console_Annotate(PinValue, "Pin value");

    Console_CloseGroup();

    Sleep(InterrunDelay_S);
  }

  Console_CloseGroup();
}

/*
  Run digital output test
*/
void RunDigitalOutputTest(
  TUint_1 OutputPinNumber
)
{
  /*
    We're just blinking pin

    Should use pin 13 for this. It's connected to onboard LED.
  */

  const TUint_1 NumRuns = 24;
  const TUint_1 InterrunDelay_S = 1;
  const TUint_2 TimeOff_Ms = 120;

  me_Pins::TOutputPin OutputPin;

  Console_OpenGroup("Digital output test");

  {
    Console_OpenGroup("Settings");

    Console_Annotate(OutputPinNumber, "Output pin number");
    Console.Print("Initial state is HIGH");
    Console_Annotate(TimeOff_Ms, "Time OFF (ms)");
    Console_Annotate(NumRuns, "Number of runs");
    Console_Annotate(InterrunDelay_S, "Delay between runs (s)");

    Console_CloseGroup();
  }

  if (!OutputPin.Init(OutputPinNumber))
  {
    Console.Print("Pin setup failed");

    Console_CloseGroup();

    return;
  }

  for (TUint_1 RunNumber = 1; RunNumber <= NumRuns; ++RunNumber)
  {
    Console_Annotate(RunNumber, "Run #");

    OutputPin.WriteZero();
    Delay(TimeOff_Ms);
    OutputPin.WriteOne();

    Sleep(InterrunDelay_S);
  }

  Console_CloseGroup();
}

/*
  Run tests
*/
void RunTests()
{
  const TUint_1 InputPinNumber = 13;
  const TUint_1 OutputPinNumber = 13;

  RunDigitalInputTest(InputPinNumber);
  RunDigitalOutputTest(OutputPinNumber);

  // No digital I/O test here. We're sick of writing this code.
}

void setup()
{
  me_Uart::Init(me_Uart::Speed_115k_Bps);

  Console_OpenGroup("[me_Pins] test");

  RunTests();

  Console_CloseGroup("Done");
}

void loop()
{
}

/*
  2025-08-01
  2025-08-15
*/
