#include "../../engine/src/core/logger.h"
#include "../../engine/src/core/asserts.h"

int main(void)
{

  KFATAL("AAAAAAAA", 3.14f);
  KERROR("AAAAAAAA", 3.14f);
  KWARN("AAAAAAAA", 3.14f);
  KINFO("AAAAAAAA", 3.14f);
  KDEBUG("AAAAAAAA", 3.14f);
  KTRACE("AAAAAAAA", 3.14f);

  KASSERT(1 == 0);
  return 0;
}