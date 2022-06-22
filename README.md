# Branch Prediction Simulator

## Overview 



Designed and implemented a Branch Prediction Simulator, a trace-driven simulator, to be able to simulate the behavior of a
(m,n) branch predictor including simple
1-bit and 2-bit predictors.

- **(m,n) predictor** 
    - Record m most recently executed branches as taken / not-taken and use that pattern to
select proper n-bit Branch History Table (BHT)
    - Record last m branches to select between 2 BHTs (i.e., columns in below image)
    - Use lowest a bits of the address to index into the BHT once one is selected (i.e., rows in
below image)
    - Each BHT has an n-bit counter (i.e., the entry itself)


## Usage

The command-line parameters are:
- i : input trace file
- m : global history size
- n : n-bit predictor
- a : number of address bits (Least Significant Bits - LSB) used to index into branch history table
- d : debug flag prints out results of each branch prediction


Example of simulator run:

```
make clean
make
./branchsim -i traces/2bit-good.txt -m 0 -n 1 -a 8

BHT: 1-bit
Address length: 8
History length: 0
Debug mode: 0
------------------------------------------
Misclassification rate: 73.21%
correct: 15
total: 56
BHT used 0 entries
```

Note : Each line in the trace file contains the program counter (pc) of the branch instruction (in the form of a 24-
bit hexadecimal address), and whether that branch was actually taken (T) or not taken (N).

### Credits:

- The structural code was given by Prof. Nael Abu-Ghazaleh and Jason Zellmer. I have added the implementation and extension part of the simulator.