#include "memsim.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 1000;
const int REQUEST_INTERVAL = 10;
const int MEMORY_SIZE = 1000;

// Statistics variables
int satisfied = 0;
int unsatisfied = 0;
int totalReqs = 0;
int smallestBlockReq = INT_MAX;
int largestBlockReq = 0;
int avgReq = 0;
int merges = 0;

// Compare function to sort allocated blocks by lease expiry time
bool compareLease(alloc chunk1, alloc chunk2) {
    return chunk1.second < chunk2.second;
}

// Compare function to sort free blocks by start address
bool compareFreeBlocks(range block1, range block2) {
    return block1.first < block2.first;
}

// Function to merge adjacent free memory blocks
void mergeFreeBlocks(std::vector<range>& freeList) {
    for (size_t i = 0; i < freeList.size() - 1;) {
        if (freeList[i].first + freeList[i].second == freeList[i + 1].first) {
            // Merge adjacent blocks
            freeList[i].second += freeList[i + 1].second;
            freeList.erase(freeList.begin() + i + 1);
            merges++;
        } else {
            i++;
        }
    }
}
