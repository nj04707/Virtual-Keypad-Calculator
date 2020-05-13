# Virtual-Keypad-Calculator

## Course Name: Digital Logic and Design

## Video Demonstration: https://www.youtube.com/watch?v=JJUvIpAJsuE

## Project Idea:

Virtual input devices often work on the principles of collision detection and motion capture, governed by "Time of Light" (ToL) which is the time difference between the emission and detection of a light ray. As the speed of light is universally constant, distance can be calculated using half of the time difference between emission and detection. 

Through this project, we test the proof of the concept of distance calculation using the Time of Light (ToL). To do this, we have created a Virtual Keypad Calculator (VKC). The values from the virtual keyboard, with a maximum value of 65535 equivalent 16 bit in signed 2's complement, will be passed to out Adder/Subtractor Circuit which calculates the result and displays it on the LCD screen as well as the 7-Segment Display. It will also be read on the custom built software by Serial Port Communication through FGPA. 

## Project Details: 

The project has 4 essential components:

### 1. Virtual Keypad

The keypad features 10 digits (0-9) and three operators (+,-,=). each of which is calibrated with respect to distance ranges.

### 2. Adder / Subtractor Circuit

The circuit takes up to 16 bits of Augend and Addend (32 bits in total) and performs arithmetic  operations to generate a 16+1 bit output. Firstly, the addend and the augend are converted to 16 bits each thorugh serial to parallel transmission. All the bits of the addend are XOR with the mode bit and then passed on to the Adder IC's. We have used 5 Adder IC's which computes the result. The result can be verifies through the LED lights. To view the result on the 7 segment display, the data is then converted to be sent back to the arduino , as 7 segment display does not accomodate bitwise bits.

The arduino encodes each number in its 7 segment code. This data is then sent back to the circuit through serial to parallel shift registers

### 3. Custom Built Software 

The 16 bit result from the circuit is now read through the FPGA through serial port transmission and displayed onto our custom Software.

### 4. Trainer

The trainer is portable as the contents rest safely inside a fold able  case. It features a Gate Array, 7 Segment Display, Input switches, LED array, LCD display and a JK Flip-flop. 

## Conclusion


The results were fairly accurate in controlled environment but due to environmental noise, the sensor does not perform well in open areas and needs to be re-calibrated.
 
The circuit consists of four independent fast carry look ahead adder IC's which are connected through a ripple carry. The data is fed into the circuit by converting serial data from the IR sensors to parallel  through SIPO  (serial in parallel out). This is accomplished by daisy chaining four 8-bit SIPO shift registers.
 




