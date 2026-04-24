# Arduino EEPROM Writer for 28256 / 27256 / AT28C16 
## Overview

This project explains how **Arduino Uno** can be used to write and read data from **28256 / 27256 / AT28C16 EEPROM** for testing and program loading.

At first, the EEPROM writing idea was considered manually by setting address lines, data lines, and then pulsing **WE LOW → HIGH** by hand. That became tedious and error-prone. Because of that, the workflow was changed to use **Arduino Uno** to automate address control, data writing, write-enable pulsing, and verification.

This note explains:

- why Arduino was used
- how the pins are connected
- how to write only a small test range first
- how to read the data back
- what to be careful about in hardware
- how Proteus simulation fits into the workflow

---

## Important Clarification

In this setup:

- **Arduino Uno is used only for EEPROM write/read**
- it does **not** generate the NE555 hardware clock
- it does **not** control the D flip-flops in the datapath
- the processor clock and datapath remain independent

So Arduino is only used for **memory programming and verification**, while the rest of the processor hardware works separately.

---

## Special Note About the EEPROM Used

Originally, the design idea was developed using **28256 / 27256 EEPROM**, and the writing/reading process was understood using those chips.

Later, during practical hardware collection:

- **28256 / 27256 were not easily available in the local market**
- but **AT28C16** was available

So in hardware, **AT28C16** was used.

Also:

- in **Proteus**, **28256 was not available**
- so **27256** was used there for simulation because it is close enough for the design context

That means the same basic Arduino-based write/read idea was discussed in the context of **28256 / 27256 / AT28C16**, even though the actual chip used in hardware may differ.

---

## Why Arduino Was Used

At first, EEPROM writing was considered manually:

1. set the address lines
2. set the data lines
3. keep `CE = LOW`
4. keep `OE = HIGH`
5. pulse `WE` from LOW to HIGH
6. wait for write completion

This works in theory, but it becomes difficult in practice because:

- WE pulsing by hand is inconvenient
- timing errors are easy to make
- verifying many bytes is slow

So the process was simplified using Arduino.

Arduino makes it possible to:

- set address bits automatically
- place the data byte automatically
- pulse `WE` correctly
- wait the required write time
- read back the stored value for verification

---

## EEPROM Used

This note is based on the EEPROM writing method for **28256 / 27256 / AT28C16**.

### Notes

- **28256 / 27256 / AT28C16** are EEPROM devices used for storing instruction/program bytes
- **27256** was used in Proteus because **28256 was not available there**
- **AT28C16** was found and used in hardware when **28256 / 27256** were not available in the market
- only a **small address range** was used during initial tests

In the simplified setup, only:

- `A0–A3` are controlled from Arduino
- higher address lines are tied LOW

That means only **16 addresses** were actively tested in the beginner version.

---

## Simplified Addressing Method

For beginner testing, only the lowest 4 address bits are controlled.

### Active Arduino-controlled addresses
- `A0`
- `A1`
- `A2`
- `A3`

### Fixed LOW address lines
- higher unused address lines = `0`

This means the test only uses addresses:

- `0x0` to `0xF`

This makes wiring much easier and reduces mistakes.

---

## Arduino Uno to EEPROM Connections

## Pin Connection Table

### Example simplified connection for 28256 / 27256 style testing

| Function | EEPROM Pin | Arduino Pin |
|---|---:|---|
| Address A0 | 9 | D2 |
| Address A1 | 8 | D3 |
| Address A2 | 7 | D4 |
| Address A3 | 6 | D5 |
| Address A4–A14 | remaining higher address pins | GND |
| Data D0 | 11 | D6 |
| Data D1 | 12 | D7 |
| Data D2 | 13 | D8 |
| Data D3 | 15 | D9 |
| Data D4 | 16 | D10 |
| Data D5 | 17 | D11 |
| Data D6 | 18 | D12 |
| Data D7 | 19 | D13 |
| CE | 20 | A0 |
| OE | 22 | A1 |
| WE | 27 | A2 |
| VCC | 28 | 5V |
| GND | 14 | GND |

> For **AT28C16**, the exact address pin count is smaller than 28256 / 27256, but the same **basic write/read process** is followed: set address, set data, control `CE/OE/WE`, pulse write, and verify by read-back.

---

## Text Wiring Diagram

```text
Arduino Uno          EEPROM (28256 / 27256 / AT28C16)
-----------          -------------------------------
D2   ------------->  A0
D3   ------------->  A1
D4   ------------->  A2
D5   ------------->  A3

GND  ------------->  Higher unused address lines

D6   ------------->  D0
D7   ------------->  D1
D8   ------------->  D2
D9   ------------->  D3
D10  ------------->  D4
D11  ------------->  D5
D12  ------------->  D6
D13  ------------->  D7

A0   ------------->  CE
A1   ------------->  OE
A2   ------------->  WE

5V   ------------->  VCC
GND  ------------->  GND





---

How Write Operation Works

To write one byte:

Arduino sets the address on A0–A3
Arduino sets the data on D0–D7
CE goes LOW
OE stays HIGH
WE is pulsed LOW briefly, then returned HIGH
Arduino waits about 10 ms
write completes

This automates the process that would otherwise be done manually.

How Read Operation Works

To read one byte:

Arduino sets the address on A0–A3
data pins are changed to input mode
CE goes LOW
OE goes LOW
WE stays HIGH
Arduino reads the data lines
values are shown in Serial Monitor

This is mainly used to verify that the EEPROM write was successful.

----------------------------

Proteus Note

When using 28256 / 27256 / AT28C16 in Proteus, the memory device must also be connected with the correct program contents.

That means:

the HEX file must be attached/loaded into the EEPROM inside Proteus
otherwise the chip will not output the expected stored instruction/data bytes

So in simulation, not only the wiring matters, but also loading the correct HEX file into the EEPROM model.

-----------------------------

Problems Faced
1. Manual writing was tedious

The WE LOW → HIGH pulse became inconvenient to do by hand.

2. Timing matters

Unlike SRAM, EEPROM requires write-cycle delay.

3. Pin confusion

Address-line numbering had to be corrected carefully.

4. Proteus limitation

28256 was not available in Proteus, so 27256 was used in simulation instead.

5. Market availability difference

The design understanding was based on 28256 / 27256, but in the market AT28C16 was available and used in hardware.

6. Need for clear separation

Arduino had to be used only for EEPROM programming, while the NE555 and flip-flop clock system remained independent.

7. Proteus setup dependency

Even with correct wiring, simulation will not work properly unless the correct HEX file is connected to the EEPROM inside Proteus.

---