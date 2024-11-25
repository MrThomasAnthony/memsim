#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "memsim.h"

int main() {
    long int clock = 0;
    srand(time(0));

    range r;
    alloc a;

    // Initialize the free list and allocated list
    std::vector<range> freeList = {{0, MEMORY_SIZE}};
    std::vector<alloc> allocatedList;

    while (++clock <= TIME_LIMIT) {
        // Generate random memory block size and lease time
        int requestBlock = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
        int requestLease = rand() % (MAX_LEASE - MIN_LEASE) + MIN_LEASE;

        // Update statistics
        avgReq += requestBlock;
        smallestBlockReq = std::min(smallestBlockReq, requestBlock);
        largestBlockReq = std::max(largestBlockReq, requestBlock);
        totalReqs++;

        bool allocated = false;

        // Try to allocate memory from free list
        for (auto it = freeList.begin(); it != freeList.end(); ++it) {
            // If the current free block is large enough
            if (it->second >= requestBlock) {
                // Allocate memory
                r.first = it->first;
                r.second = requestBlock;

                // Create an allocation record
                a.first = r;
                a.second = clock + requestLease;  // Set expiry time as current clock + lease
                allocatedList.push_back(a);

                // Update the free list
                if (it->second > requestBlock) {
                    // There will be remaining memory after allocation
                    it->first += requestBlock;
                    it->second -= requestBlock;
                } else {
                    // If the whole block is allocated, remove it from the free list
                    freeList.erase(it);
                }

                allocated = true;
                break;  // Exit after first successful allocation
            }
        }

        // Check if any leases have expired
        for (auto it = allocatedList.begin(); it != allocatedList.end();) {
            if (clock >= it->second) {
                // Return the block to the free list
                freeList.push_back(it->first);
                it = allocatedList.erase(it);  // Remove the expired allocation
            } else {
                ++it;
            }
        }

        // Sort the free list and allocated list after every operation
        std::sort(freeList.begin(), freeList.end(), compareFreeBlocks);
        std::sort(allocatedList.begin(), allocatedList.end(), compareLease);

        // Merge free blocks after allocation or expiry
        mergeFreeBlocks(freeList);

        // Update statistics for satisfied/unsatisfied requests
        if (allocated) {
            satisfied++;
        } else {
            unsatisfied++;
        }
    }

    // Output statistics
    std::cout << "Total Requests: \t" << totalReqs << std::endl;
    std::cout << "Total Satisfied: \t" << satisfied << std::endl;
    std::cout << "Total Unsatisfied: \t" << unsatisfied << std::endl;
    std::cout << "Smallest Request: \t" << smallestBlockReq << std::endl;
    std::cout << "Largest Request: \t" << largestBlockReq << std::endl;
    std::cout << "Average Request: \t" << avgReq / totalReqs << std::endl;
    std::cout << "Merges Performed: \t" << merges << std::endl;

    // Print out the final free list
    std::cout << "Free List: [ ";
    for (const auto& free : freeList) {
        std::cout << "[" << free.first << "," << free.second << "] ";
    }
    std::cout << "]\n";

    // Print out the final allocated list
    std::cout << "Allocated List:\n";
    for (const auto& alloc : allocatedList) {
        std::cout << "([" << alloc.first.first << "," << alloc.first.second << "]"
             << ", " << alloc.second << ")\n";
    }

    return 0;
}
