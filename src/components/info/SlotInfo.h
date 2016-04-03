#ifndef SLOTINFO_H
#define SLOTINFO_H

#include <string>

namespace ld
{

struct SlotInfo
{
  SlotInfo() = default;

  std::string type;
  std::string category;
  unsigned count;
};

}

#endif /* SLOTINFO_H */
