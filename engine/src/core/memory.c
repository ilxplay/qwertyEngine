#include "memory.h"
#include "../platform/platform.h"
#include "../core/logger.h"

#include <string.h>
#include <stdio.h>

struct memory_stats
{
  u64 total_allocated;
  u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};
