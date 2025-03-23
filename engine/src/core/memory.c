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

static struct memory_stats stats;
void initialize_memory()
{
  platform_zero_memory(&stats, sizeof(stats));
}

void *kallocate(u64 size, memory_tag tag)
{
  if (tag == MEMORY_TAG_UNKNOWN)
  {
    KWARN("kallocate called using MEMORY_TAG_UNKNOWN");
  }

  stats.total_allocated += size;
  stats.tagged_allocations[tag] += size;

  void *block = platform_allocate(size, FALSE);
  platform_zero_memory(block, size);
  return block;
}

void kfree(void *block, u64 size, memory_tag tag)
{
  if (tag == MEMORY_TAG_UNKNOWN)
  {
    KWARN("kfree called using MEMORY_TAG_UNKNOWN. Re-class this allocation.");
  }

  stats.total_allocated -= size;
  stats.tagged_allocations[tag] -= size;

  // TODO: Memory alignment
  platform_free(block, FALSE);
}

void *kzero_memory(void *block, u64 size)
{
  return platform_zero_memory(block, size);
}

void *kcopy_memory(void *dest, const void *source, u64 size)
{
  return platform_copy_memory(dest, source, size);
}

void *kset_memory(void *dest, i32 value, u64 size)
{
  return platform_set_memory(dest, value, size);
}
