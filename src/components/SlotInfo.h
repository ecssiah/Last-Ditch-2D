#ifndef SLOTINFO_H
#define SLOTINFO_H

#include <string>

namespace ld
{

struct SlotInfo
{
  SlotInfo() = default;

  std::string type;
  unsigned count;
};

}

#endif /* SLOTINFO_H */
