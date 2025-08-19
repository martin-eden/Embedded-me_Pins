## What

(2025-08)

Pins input/output. ATmega328

## Code

* [Interface][Interface]
* [Implementation][Implementation]
* [Example][Example]
* [Notes][Notes]

## Requirements

  * arduino-cli
  * bash

## Install/remove

Easy way is to clone [GetLibs][GetLibs] repo and run it's code.

## Compile

Zero-warnings compilation:

```bash
arduino-cli compile --fqbn arduino:avr:uno --quiet --warnings all . --build-property compiler.cpp.extra_flags="-std=c++1z"
```

## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Interface]: src/me_Pins.h
[Implementation]: src/
[Example]: examples/me_Pins/me_Pins.ino
[Notes]: extras/Notes.txt

[GetLibs]: https://github.com/martin-eden/Embedded-Framework-GetLibs

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
