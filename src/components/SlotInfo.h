#ifndef SLOTINFO_H
#define SLOTINFO_H

#include <string>

namespace ld
{

struct SlotInfo
{
  SlotInfo() = default;

  unsigned index;
  unsigned count;
  std::string type;
};

}

#endif /* SLOTINFO_H */
