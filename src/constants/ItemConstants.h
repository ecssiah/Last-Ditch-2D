#ifndef ITEMCONSTANTS_H
#define ITEMCONSTANTS_H

#include <vector>
#include <unordered_map>

#include "../components/info/WeaponInfo.h"
#include "../components/info/ApparelInfo.h"
#include "../components/info/UtilityInfo.h"
#include "../components/info/ResourceInfo.h"

namespace ld
{

static std::vector<std::string> Weapon_Types;

static std::unordered_map<std::string, WeaponInfo> Weapon_Data;

static std::vector<std::string> Apparel_Types;

static std::unordered_map<std::string, ApparelInfo> Apparel_Data;

static std::vector<std::string> Utility_Types;

static std::unordered_map<std::string, UtilityInfo> Utility_Data;

static std::vector<std::string> Resource_Types;

static std::unordered_map<std::string, ResourceInfo> Resource_Data;

}

#endif /* ITEMCONSTANTS_H */
