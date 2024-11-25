#ifndef MEMSIM_H
#define MEMSIM_H

#include <vector>
#include <utility>
#include <climits>

using range = std::pair<int, int>;

using alloc = std::pair<range, int>;

extern const int MIN_LEASE;
extern const int MAX_LEASE;
extern const int MIN_SIZE;
extern const int MAX_SIZE;
extern const int TIME_LIMIT;
extern const int REQUEST_INTERVAL;
extern const int MEMORY_SIZE;

extern int satisfied;
extern int unsatisfied;
extern int totalReqs;
extern int smallestBlockReq;
extern int largestBlockReq;
extern int avgReq;
extern int merges;

bool compareLease(alloc chunk1, alloc chunk2);
bool compareFreeBlocks(range block1, range block2);
void mergeFreeBlocks(std::vector<range>& freeList);

#endif
