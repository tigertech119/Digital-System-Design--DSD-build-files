\# Instruction Fetch (IF) Stage Design Using TTL ICs and EEPROM



\## Overview



This project presents the design and implementation of the \*\*Instruction Fetch (IF) Stage\*\* of a simple processor at hardware level using standard TTL ICs, EEPROM, and clock generation circuits.



The IF stage is responsible for:



\- holding the current instruction address in the \*\*Program Counter (PC)\*\*

\- incrementing the PC value to fetch the next instruction

\- reading the instruction from memory

\- providing the fetched instruction to the next stage of the processor



This design was first tested in simulation and later implemented in hardware.



\---



\## Objectives



The goals of this project were:



\- to understand how the \*\*Instruction Fetch stage\*\* works at hardware level

\- to build a working \*\*Program Counter\*\*

\- to increment the PC using an adder

\- to fetch instructions from memory using EEPROM

\- to generate clock pulses for synchronous operation

\- to use this IF stage as the first part of a complete CPU datapath



\---



\## Main Functional Blocks



The IF stage consists of the following blocks:



1\. \*\*Program Counter (PC) Register\*\*

2\. \*\*PC Increment Unit\*\*

3\. \*\*Instruction Memory\*\*

4\. \*\*Clock Generation Circuit\*\*



\---



\## Components Used



\- \*\*74LS174\*\* – Hex D Flip-Flop (used as Program Counter register)

\- \*\*74LS83 / 7483\*\* – 4-bit Full Adder (used for PC increment)

\- \*\*AT28C16 EEPROM\*\* – instruction memory

\- \*\*NE555 Timer\*\* – clock pulse generation

\- \*\*74LS04\*\* – NOT gate / clock inversion

\- \*\*Arduino UNO\*\* – used for programming EEPROM

\- \*\*Breadboard, jumper wires, LEDs, resistors, power supply\*\*



\---



\## How It Works



\### 1. Program Counter (PC)



The Program Counter stores the current instruction address.



\- The PC was implemented using \*\*74LS174\*\*

\- The current address is held in flip-flops

\- On each clock pulse, the PC updates to the next address



\### 2. PC Increment



To move to the next instruction, the PC value is incremented.



\- A \*\*74LS83 full adder\*\* was used

\- The current PC value is given as one input

\- A constant value is added to generate the next PC value

\- In this small implementation, the idea is effectively \*\*PC + 1\*\*



\### 3. Instruction Memory



The instruction memory stores the program bytes.



\- \*\*AT28C16 EEPROM\*\* was used

\- Instructions were pre-written into EEPROM using \*\*Arduino UNO\*\*

\- EEPROM output provides the instruction for the current PC address



\### 4. Clock Circuit



A stable clock is required so the PC updates correctly.



\- \*\*NE555 timer\*\* was used for clock generation

\- \*\*74LS04\*\* was used where inverted clock timing was needed

\- Proper timing was important because flip-flop triggering behavior affected the output



\---



\## Addressing Method



Only a small number of addresses were used in this design.



\- \*\*A0 to A3\*\* = active address lines

\- \*\*higher address lines\*\* were tied LOW

\- This allows a small instruction space such as \*\*16 instructions\*\*



So the IF stage fetches instructions from the first small block of EEPROM memory.



\---



\## Inputs and Outputs



\### Inputs



\- Clock pulse

\- Reset / initialization

\- EEPROM contents programmed beforehand



\### Outputs



\- Current PC address

\- Fetched instruction byte from EEPROM



\---



\## Instruction Fetch Flow



The IF stage follows this basic flow:



1\. PC holds current instruction address

2\. Address is sent to EEPROM

3\. EEPROM outputs the instruction byte

4\. Adder calculates next address

5\. On the next clock pulse, PC updates to the new address

6\. Process repeats



\---



\## Instruction Memory Programming



The EEPROM does not come preloaded with instructions, so it had to be programmed externally.



\### Programming method



\- \*\*Arduino UNO\*\* was used to write instruction bytes into EEPROM

\- Instructions were written address by address

\- EEPROM was then connected back into the hardware circuit for execution



This allowed the IF stage to fetch predefined instructions sequentially.



\---



\## Design Notes



\### Why EEPROM was used



EEPROM was selected because:



\- it can store instructions permanently

\- data remains even after power is removed

\- it is suitable for a simple hardware-level processor design



\### Why Arduino UNO was used



Arduino UNO was used only for:



\- writing program data into EEPROM

\- reading back values for verification



It was \*\*not\*\* the main processor of the project. The IF stage itself runs using the TTL hardware design.



\---



\## Problems Faced



Several difficulties appeared during implementation.



\### 1. Negative-edge / timing behavior of flip-flops



The \*\*74LS174\*\* required careful clock handling.



\- output update did not initially happen as expected

\- simulation and real hardware behavior were not always identical

\- timing and reset behavior had to be observed carefully



\### 2. PC increment issues



The adder sometimes gave incorrect results when:



\- carry lines were not set correctly

\- constant inputs were not tied properly

\- floating pins were present



\### 3. Clock pulse issues



Using \*\*NE555\*\* introduced practical problems:



\- clock was initially too fast

\- manual observation became difficult

\- pulse timing was not always ideal



\### 4. Need for inverted clock



A \*\*74LS04 NOT gate\*\* was used to generate inverted clock where needed.



This helped avoid timing conflicts and improved stage synchronization.



\### 5. EEPROM wiring issues



EEPROM required careful connection of:



\- address pins

\- data pins

\- control pins such as `CE`, `OE`, and `WE`



Any floating or incorrect connection caused wrong instruction output.



\### 6. Arduino programming issues



During EEPROM programming:



\- some Arduino pins caused conflicts

\- write timing had to be checked carefully

\- address/data mapping needed verification multiple times



\### 7. Proteus limitations



The exact EEPROM model was not always convenient in simulation, so testing in Proteus and testing in hardware did not behave exactly the same.



\---



\## Learning Outcomes



From this project, the following concepts became clearer:



\- how a Program Counter works

\- how instruction addresses are generated

\- how memory is read using address lines

\- how an adder helps move to the next instruction

\- why clock timing is critical in synchronous circuits

\- how EEPROM can be used as instruction memory

\- how IF stage becomes the starting point of a processor datapath



\---



\## Future Work



This IF stage can be extended into a larger processor by connecting it to:



\- \*\*ID stage\*\* for opcode decoding

\- \*\*Register file\*\*

\- \*\*ALU / EX stage\*\*

\- \*\*MEM stage\*\*

\- \*\*WB stage\*\*



This project acts as the first building block for a complete CPU design.



\---



\## Repository Structure Suggestion



```text

if-stage/

│

├── README.md

├── images/

│   ├── circuit\_diagram.png

│   ├── hardware\_photo.jpg

│   └── timing\_test.png

├── proteus/

│   └── if\_stage\_design.pdsprj

├── arduino/

│   └── eeprom\_writer.ino

└── docs/

&#x20;   ├── notes.md

&#x20;   └── instruction\_table.pdf



SRAM6116 TUTORIAL LINKS

https://youtu.be/ayEx26BPP4M?si=8L577QQGfqZQNsOo


