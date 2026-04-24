

\# 1-Bit ALU Design Using Logic Gates and Multiplexer



\## Overview



This project presents the design and implementation of a \*\*1-bit Arithmetic Logic Unit (ALU)\*\* built at the hardware level using digital ICs, logic gates, and multiplexers. The ALU was first developed as the foundation of a larger CPU datapath project. Later stages such as IF, ID, EX, MEM, and WB were planned around this ALU design.



The purpose of this ALU is to perform multiple arithmetic and logical operations on 1-bit inputs and produce the selected result through a multiplexer-based output selection method.



This design was first tested conceptually and then prepared for extension into a wider ALU for future processor stages.



\---



\## Objective



The main objectives of this project were:



\* to understand ALU operation at gate level

\* to design a working \*\*1-bit ALU\*\*

\* to support multiple arithmetic and logical functions in a single unit

\* to select the desired operation using selector bits

\* to use this ALU as the base for future \*\*8-bit ALU replication\*\*



\---



\## Inputs and Outputs



\### Inputs



\* `A` = first 1-bit operand

\* `B` = second 1-bit operand

\* `Cin` = carry-in / borrow-in input

\* `S3 S2 S1 S0` = 4-bit selector lines for choosing the operation



\### Outputs



\* `F` = selected function result

\* `Cout` = carry-out / borrow-out depending on operation



\---



\## Main Design Idea



Different arithmetic and logical operation outputs were generated separately using logic gates. Then a \*\*multiplexer\*\* was used to choose which output would appear as the final ALU output.



Initially, the design was planned with a \*\*16-to-1 multiplexer\*\* because the ALU supports \*\*16 operations\*\*. However, during hardware collection, \*\*16×1 MUX was not available in the local market\*\*, and only \*\*8×1 MUX\*\* was available. Because of that, the design needed practical adjustment during hardware consideration.



The original design logic still follows the idea of selecting among 16 possible operations using the 4 selector bits.



\---



\## Operations Supported



The ALU supports the following 16 operations:



| Selector | Operation    |

| -------- | ------------ |

| `0000`   | ADD          |

| `0001`   | SUBTRACT     |

| `0010`   | MULTIPLY     |

| `0011`   | LEFT SHIFT   |

| `0100`   | RIGHT SHIFT  |

| `0101`   | ROTATE LEFT  |

| `0110`   | ROTATE RIGHT |

| `0111`   | AND          |

| `1000`   | OR           |

| `1001`   | XOR          |

| `1010`   | XNOR         |

| `1011`   | NAND         |

| `1100`   | NOR          |

| `1101`   | GREATER THAN |

| `1110`   | EQUAL        |

| `1111`   | LESS THAN    |



\---



\## Arithmetic Logic Used



\### 1. Addition



For addition, the ALU uses full adder logic.



\#### Sum



\[

S = A \\oplus B \\oplus Cin

]



\#### Carry-out



\[

Cout = AB + ACin + BCin

]



\---



\### 2. Subtraction



For subtraction, the ALU uses subtractor logic.



\#### Difference



\[

D = A \\oplus B \\oplus Bin

]



\#### Borrow-out



\[

Bout = BBin + A'B + A'Bin

]



In the 1-bit ALU design, `Cin` is used as the borrow input during subtraction mode.



\---



\## Comparator Operations



The ALU also includes comparison outputs for:



\* Greater Than

\* Equal

\* Less Than



For 1-bit inputs, these are easy to generate directly from comparator logic.



Example for 1-bit:



\* `A > B`

\* `A = B`

\* `A < B`



These outputs are also connected to the multiplexer so that one of them can be selected as the final ALU result.



\---



\## How It Was Built



The ALU was built by dividing the problem into small blocks:



1\. \*\*Adder block\*\* for addition

2\. \*\*Subtractor block\*\* for subtraction

3\. \*\*Logic blocks\*\* for AND, OR, XOR, NAND, NOR, XNOR

4\. \*\*Comparator block\*\* for GT, EQ, LT

5\. \*\*Shift / Rotate / Multiply outputs\*\*

6\. \*\*Multiplexer\*\* to choose one final output from all operation outputs



Each operation was generated first, then all outputs were routed to the MUX inputs. The selector bits `S3 S2 S1 S0` determine which operation result appears at output `F`.



\---



\## Important Observation About 1-Bit Design



While the 1-bit ALU works correctly as a basic design, some operations behave differently in 1-bit form compared to multi-bit form.



\### In 1-bit ALU, some operations become identical or trivial



\#### Multiply



For 1-bit input:



\* `A × B` behaves the same as `A AND B`



So in a 1-bit ALU, multiplication does not show the true behavior of multi-bit multiplication.



\#### Shift Left / Shift Right



For a single bit:



\* shifting usually gives `0`

\* because there is no neighboring bit to move into place



\#### Rotate Left / Rotate Right



For a single bit:



\* rotation gives the same bit back

\* because one bit rotates into itself



\#### Compare



For 1-bit:



\* compare is simple and valid

\* but when extended to 8-bit, direct per-bit comparison is not enough for proper magnitude comparison



\---



\## Difficulties Faced



Several practical and design-level issues appeared during this project:



\### 1. Multiplexer availability issue



The original plan used a \*\*16×1 MUX\*\*, but in the local market only \*\*8×1 MUX\*\* was available. This created a hardware implementation limitation and required redesign thinking for operation selection.



\### 2. 1-bit vs multi-bit behavior



At 1-bit level, some operations seem correct, but later become problematic when replicated:



\* multiply

\* shift left / right

\* rotate left / right

\* greater than / less than for multi-bit numbers



\### 3. Future expansion complexity



Although add/sub and bitwise logic can be replicated easily, not every function scales correctly just by copying the 1-bit ALU block.



\---



\## Notes for Future 8-Bit Expansion



This 1-bit ALU was intended as the base unit for an \*\*8-bit ALU\*\* by replication. While some operations extend naturally, others require modification.



\### Operations that replicate correctly



These work well by simply repeating the 1-bit ALU 8 times:



\* ADD

\* SUBTRACT

\* AND

\* OR

\* XOR

\* XNOR

\* NAND

\* NOR



These operations are either carry-chain based or bitwise independent.



\### Operations that need extra modification in 8-bit ALU



\#### 1. Shift operations



Left shift and right shift cannot be done correctly by isolated 1-bit slices only.

They require \*\*cross-bit wiring\*\* so each bit receives data from its neighboring bit.



\#### 2. Rotate operations



Rotate left and rotate right also require special interconnection between slices, because end bits wrap around.



\#### 3. Multiply



True 8-bit multiplication cannot be achieved by simple 1-bit replication.

It needs a dedicated multiplier structure, such as:



\* partial products

\* adder tree

\* or another multiplier design



\#### 4. Greater Than / Less Than / Equal



For 8-bit comparison, per-bit comparator replication is not enough for proper magnitude comparison.

It needs either:



\* subtraction + Zero/Borrow-based flag logic

\* or a dedicated magnitude comparator design



\---



\## Learning Outcomes



From this project, the following concepts became clearer:



\* how arithmetic logic is built from gates

\* how a multiplexer can act as the operation selector of an ALU

\* the difference between 1-bit functionality and real multi-bit processor behavior

\* why some operations scale naturally and others require datapath-level redesign

\* how an ALU becomes the foundation of a processor execution stage



\---





\---



\## Future Work



This project can be extended into:



\* 4-bit ALU

\* 8-bit ALU

\* EX stage of a CPU

\* full datapath integration with register file and control unit

\* Zero flag and comparison logic for branch instructions



\---



==========================================================================================



\---



\# 1-Bit ALU Design Using Logic Gates and Multiplexer



\## Overview



This project presents the design and implementation of a \*\*1-bit Arithmetic Logic Unit (ALU)\*\* built at hardware level using logic gates, basic digital ICs, and a multiplexer-based output selection method. This ALU was designed as the \*\*foundation block of a larger CPU project\*\*, where later stages such as IF, ID, EX, MEM, and WB were planned around this ALU.



The main idea was to generate different arithmetic and logical outputs separately, then use selector bits to choose the required operation as the final ALU output.



This 1-bit ALU supports \*\*16 operations\*\* and was later considered for replication into an \*\*8-bit ALU\*\*.



\---



\## Objectives



The goals of this project were:



\- to understand ALU design at gate level

\- to implement a working \*\*1-bit ALU\*\*

\- to perform multiple arithmetic and logical operations using one unit

\- to select operations using selector lines

\- to use this ALU as the base for future multi-bit datapath design



\---



\## Inputs and Outputs



\### Inputs



\- `A` = first 1-bit operand  

\- `B` = second 1-bit operand  

\- `Cin` = carry-in / borrow-in input  

\- `S3 S2 S1 S0` = 4-bit selector lines  



\### Outputs



\- `F` = selected ALU output  

\- `Cout` = carry-out / borrow-out depending on operation  



\---



\## Main Design Method



The ALU was built by creating separate outputs for arithmetic, logical, shift, rotate, multiply, and compare operations. After generating these outputs, they were connected to a multiplexer so that only one selected operation appears at the final output.



\### Basic design flow



1\. Generate output for \*\*ADD\*\*

2\. Generate output for \*\*SUB\*\*

3\. Generate outputs for logic operations like \*\*AND, OR, XOR\*\*

4\. Generate comparator outputs like \*\*GT, EQ, LT\*\*

5\. Generate outputs for \*\*shift, rotate, multiply\*\*

6\. Feed all outputs into a multiplexer

7\. Use `S3 S2 S1 S0` to select the final result



\---



\## 16-Operation Table



| Selector (`S3 S2 S1 S0`) | Operation |

|---|---|

| `0000` | ADD |

| `0001` | SUBTRACT |

| `0010` | MULTIPLY |

| `0011` | LEFT SHIFT |

| `0100` | RIGHT SHIFT |

| `0101` | ROTATE LEFT |

| `0110` | ROTATE RIGHT |

| `0111` | AND |

| `1000` | OR |

| `1001` | XOR |

| `1010` | XNOR |

| `1011` | NAND |

| `1100` | NOR |

| `1101` | GREATER THAN |

| `1110` | EQUAL |

| `1111` | LESS THAN |



\---



\## Arithmetic Equations Used



\### Addition



For addition, the ALU uses full-adder equations.



\#### Sum

\\\[

S = A \\oplus B \\oplus Cin

\\]



\#### Carry-out

\\\[

Cout = AB + ACin + BCin

\\]



\---



\### Subtraction



For subtraction, the ALU uses subtractor equations.



\#### Difference

\\\[

D = A \\oplus B \\oplus Bin

\\]



\#### Borrow-out

\\\[

Bout = BBin + A'B + A'Bin

\\]



In this design, `Cin` is used as the borrow input during subtraction mode.



\---



\## Comparator Section



The ALU also includes comparator outputs for:



\- `A > B`

\- `A = B`

\- `A < B`



For 1-bit input, these operations are straightforward and can be implemented directly using logic expressions. These outputs are also connected to the multiplexer and can be selected through the control lines.



\---



\## How the ALU Was Built



The design was created step by step.



\### Blocks used



\- \*\*Adder block\*\*

\- \*\*Subtractor block\*\*

\- \*\*Logic operation block\*\*

\- \*\*Comparator block\*\*

\- \*\*Shift/Rotate/Multiply block\*\*

\- \*\*Multiplexer output selector\*\*



Each block generates one candidate output. Then the selector chooses which one becomes the final `F` output.



\---



\## Hardware/Implementation Note



The original plan was to use a \*\*16×1 multiplexer\*\*, because the ALU supports \*\*16 operations\*\*.



However, during hardware collection, a practical issue appeared:



\- \*\*16×1 MUX was planned\*\*

\- but in the local market only \*\*8×1 MUX was available\*\*



So the hardware implementation required rethinking or adjustment of the selection structure. This became one of the main practical difficulties of the project.



\---



\## Important Observation About 1-Bit ALU



Although the 1-bit ALU works as a useful learning design, some operations do not behave in a meaningful way in only 1 bit.



\### Operations that become trivial or identical in 1 bit



\#### Multiply

For 1-bit input:

\- `A × B` behaves exactly like `A AND B`



So multiplication in 1-bit does not represent real multi-bit multiplication.



\#### Left Shift / Right Shift

For a single bit:

\- shifting usually produces `0`

\- because there is no neighboring bit to shift into position



\#### Rotate Left / Rotate Right

For a single bit:

\- rotation returns the same bit

\- because one bit rotates into itself



\#### Compare

For 1-bit:

\- comparison works directly

\- but this same idea is not enough for correct multi-bit magnitude comparison later



\---



\## Difficulties Faced



Several problems appeared during design and planning:



\### 1. Multiplexer availability

The design required \*\*16 operation selection\*\*, but only \*\*8×1 MUX\*\* was available in hardware collection.



\### 2. 1-bit and multi-bit behavior are different

Some operations seemed correct in 1-bit but later became problematic for wider ALU design.



\### 3. Future replication issues

Not every operation can be extended properly just by copying the same 1-bit slice many times.



\---



\## Notes for Future 8-Bit Expansion



This 1-bit ALU was intended to be extended later by replicating it \*\*8 times\*\* to form an \*\*8-bit ALU\*\*.



\### Operations that scale naturally



These can be replicated more easily:



\- ADD

\- SUBTRACT

\- AND

\- OR

\- XOR

\- XNOR

\- NAND

\- NOR



These work either through carry-chain logic or independent bitwise operation.



\### Operations that need modification after replication



\#### 1. Shift operations

Shift-left and shift-right need \*\*cross-bit wiring\*\* between ALU slices.



\#### 2. Rotate operations

Rotate-left and rotate-right need wrap-around connections between the first and last bit positions.



\#### 3. Multiply

True 8-bit multiplication cannot be achieved by simple replication of 1-bit multiply.  

It needs a dedicated multiplier structure such as:



\- partial products

\- adder tree

\- or another multiplication method



\#### 4. Greater Than / Less Than / Equal

For 8-bit numbers, correct comparison cannot be done by only comparing each bit independently.  

It needs either:



\- subtraction + flags

\- zero/borrow logic

\- or a dedicated comparator design



\---



\## Learning Outcomes



From this project, the following concepts became clear:



\- how an ALU can be built from basic logic gates

\- how multiplexers are used to select one result from many generated outputs

\- how arithmetic and logic blocks are combined into one unit

\- why some 1-bit operations do not directly represent real multi-bit behavior

\- why datapath scaling requires more than just simple replication for some operations



\---



\## Future Work



This project can be extended into:



\- 4-bit ALU

\- 8-bit ALU

\- execution stage of a CPU

\- datapath integration with register file and control unit

\- Zero flag and compare logic for branch instructions



\---



\## Repository Structure Suggestion



```text

1-bit-alu/

│

├── README.md

├── images/

│   ├── circuit\_diagram.png

│   ├── truth\_table.png

│   └── hardware\_photo.jpg

├── proteus/

│   └── alu\_design.pdsprj

├──BUILD.md

