# Cache Simulator Assignment CS3339-HW3

## Team Members
Tyrell Drones

## Overview
This program is designed to simulate a set-associative cache by reading a sequence of memory addresses from a file and outputs whether each access is a HIT or MISS. Within the program the cache is organized into mutiple sets based on the total number of entries and associativity. Each memory address is mapped to a specific set using modular arithmetic, and a corresponding tag is extracted to identify whether the requested data is already stored in the cache. For each memory reference, the program computes the set index and tag, checks the corresponding set for a matching valid tag, and outputs HIT if found or MISS if not. In the case of a MISS, the cache is updated by inserting the new tag into an empty line if one is available, or by replacing an existing entry using a First-In, First-Out (FIFO) replacement policy when the set is full.

## How to Compile
The program is written in C++ and can be compiled using the GNU C++ compiler (g++)
```bash
g++ cache_sim.cpp -o cache_sim
```

## How to Run
After compiling the program, it can be executed from the command line by providing the number of cache entries, the associativity, and the input file containing memory references as arguments. The program will then process each address and generate an output file indicating whether each access resulted in a HIT or MISS.”

```bash
./cache_sim <num_entries> <associativity> <input_file>
./cache_sim 4 2 input.txt
```