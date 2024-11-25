# Memory Allocation Simulation - MEMSIM

This program simulates memory allocation for managing memory blocks using a first-fit allocation strategy. It simulates memory requests made at regular intervals, tries to satisfy these requests from a list of free memory blocks, and handles the allocation and deallocation (based on lease expiry times). When a memory block's lease expires, it is returned to the free list. The program also handles merging of adjacent free blocks when necessary.

## Problem Description

The program simulates memory allocation where:
- Memory requests are generated at regular intervals.
- Memory blocks are allocated based on a first-fit strategy.
- When a memory request expires, the block is returned to the free list.
- The free list and allocated list are sorted for efficient memory management.
- The simulation gathers statistics about the number of memory requests, number of satisfied and unsatisfied requests, the size of requested blocks, lease durations, and more.

## Features
- **Memory Management**: Simulates memory allocation, deallocation, and merging of free memory blocks.
- **First-fit Allocation**: Allocates the first available memory block that can satisfy the request.
- **Lease Expiry Handling**: Automatically deallocates memory blocks once the lease expires.
- **Sorted Lists**: The free list is sorted by memory location, and the allocated list is sorted by lease expiry time.
- **Merging**: Adjacent free memory blocks are merged when necessary after a memory block is deallocated.

## Simulation Parameters
- `MIN_LEASE = 40`
- `MAX_LEASE = 70`
- `MIN_SIZE = 50`
- `MAX_SIZE = 350`
- `TIME_LIMIT = 1000`
- `REQUEST_INTERVAL = 10`
- `MEMORY_SIZE = 1000`

These parameters control the behavior of the simulation, such as the size and duration of memory blocks requested, the rate at which requests are made, and the total memory available.

## Program Structure

The program is structured into multiple files for better organization and clarity. The main logic of the simulation is contained in `main.cpp`, while all constants, type definitions, and function declarations are stored in header files.

### Files

- **`main.cpp`**: Contains the `main` function, which drives the simulation, handles memory requests, checks for expired leases, and updates statistics.
- **`memory_manager.h`**: Contains type definitions, constants, and function declarations.
- **`memory_manager.cpp`**: Implements the functions declared in `memory_manager.h`.

# Ubuntu

To get started, follow these steps:
1. **Clone the repository:**
   ```bash
   git clone https://github.com/MrThomasAnthony/memsim.git
   cd memsim

2. **Install g++ and ncurses (if not already installed):**

   ```bash
   sudo apt update
   sudo apt install g++

3. **Compile the Game of Life program:**
    ```bash
    g++ main.cpp memsim.cpp -o memsim

4. **Run the GOL Threads program:**
    ```bash
    ./memsim
