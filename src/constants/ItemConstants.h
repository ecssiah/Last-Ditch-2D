#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <string>
#include <vector>
#include <unordered_map>

#include "../components/info/ItemInfo.h"

namespace ld
{

extern std::vector<std::string> Item_Types;

extern std::unordered_map<std::string, ItemInfo> Item_Data;

}

#endif /* ITEMCONSTANTS_H */
