// RPG item generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <utility>

//array of string variables
//1. prefixes
//2. item type
//3. suffix
//4. stat type and random value between 5 and 25

std::string itemType[] = {"Halberd", "Aegis", "Helm", "Platemail", "Chainmail", "Studded Leather", "Cloth Robes", "Sandles", "Waders", "Galoshes", "Poulaines"};
int itemTypeMaxIndex = (sizeof(itemType) / sizeof(itemType[0])) - 1;
std::string prefix[] = { "Searing", "Dense", "Brutal", "Keen", "Sparkling", "Glowing", "Holy", "Molten", "Shadowy" };
int prefixMaxIndex = (sizeof(prefix) / sizeof(prefix[0])) - 1;//gets the byte total size and divide by index byte size to find count
std::string suffix[] = { "of Light", "of Giants", "of Speed", "of Swiftness", "of Lifesteal", "of Strength", "of Torment", "of Hunger", "of Fire", "of Lightning", "of the Brutal"};
int suffixMaxIndex = (sizeof(suffix) / sizeof(suffix[0])) - 1;
std::string statType[] = { "Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
int statTypeMaxIndex = (sizeof(statType) / sizeof(statType[0])) - 1;

enum class Rarity {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary,//will only drop once per user
    Ethereal//same as Legendary but more rare
};

std::string rarityToString(Rarity rarity)
{
    switch (rarity) {
    case Rarity::Common: return "Common";
    case Rarity::Uncommon: return "Uncommon";
    case Rarity::Rare: return "Rare";
    case Rarity::Epic: return "Epic";
    case Rarity::Legendary: return "Legendary";
    case Rarity::Ethereal: return "Ethereal";
    default: return "Unknown";
    }
}

std::unordered_map<Rarity, float> rarityMultipliers{
    { Rarity::Common, 1.00f},
    { Rarity::Uncommon, 1.15f},
    { Rarity::Rare, 1.35f},
    { Rarity::Epic, 1.60},
};

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

//Wikkenden Apr 24, 2025
//temp vals would like to make customizable later
// 
//Would like to add toggle later for removing from loot pool

//MUST order from most to least common for getRandomRarity
//If there is ever user input you must write a function to sort in this way
std::unordered_map<Rarity, float, EnumClassHash> rarityDropChance{
    { Rarity::Common, 40.0f},
    { Rarity::Uncommon, 30.0f},
    { Rarity::Rare, 20.0f},
    { Rarity::Epic, 10.0f},
};


struct item {
    std::string itemType;
    std::string prefix;
    std::string suffix;
    std::string statType;
    float minStatRange, maxStatRange;

    Rarity itemRarity;
    float statValue;
};

Rarity getRandomRarity() {
    float roll = rand() % 100 + 1.0f; // Get a number between 1 and 100
    float cumulativeChance = 0.0f;

    for (auto rarity = rarityDropChance.begin(); rarity != rarityDropChance.end(); ++rarity)
    {
        cumulativeChance += rarity->second;
        if (roll < cumulativeChance) {
            return rarity->first;
        }
    }

    return Rarity::Common;
};

item generateItem() {
    item newItem;
    int itemTypeIndex, prefixIndex, suffixIndex, statTypeIndex;

    int minStatValue = 1.0f;
    int maxStatValue = 3.0f;
    
    itemTypeIndex = rand() % itemTypeMaxIndex;
    prefixIndex = rand() % prefixMaxIndex;
    suffixIndex = rand() % suffixMaxIndex;
    statTypeIndex = rand() % statTypeMaxIndex;

    newItem.itemType = itemType[itemTypeIndex];
    newItem.prefix = prefix[prefixIndex];
    newItem.suffix = suffix[suffixIndex];
    newItem.statType = statType[statTypeIndex];
    newItem.itemRarity = getRandomRarity();

    float rarityMultiplier = rarityMultipliers[newItem.itemRarity];

    newItem.statValue = rarityMultiplier * (minStatValue + (std::rand() % (maxStatValue - minStatValue)));
    newItem.minStatRange = rarityMultiplier * minStatValue;
    newItem.maxStatRange = rarityMultiplier * maxStatValue;

    return newItem;
}

int main()
{
    std::srand(std::time(0));
    std::vector<item> items;

    int itemCreationCount = 25;

    for (int i = 0; i < itemCreationCount; ++i) {
        items.push_back(generateItem());
    }

    for (int i = 0; i < items.size(); ++i)
    {
        std::cout << items[i].prefix << " " 
                  << items[i].itemType << " " 
                  << items[i].suffix << "(" 
                  << items[i].statType << " +" 
                  << items[i].statValue << "[" << items[i].minStatRange << "-" << items[i].maxStatRange << "])\n"
                  << "Item Rarity: " 
                  << rarityToString(items[i].itemRarity) << "\n";
    }
    
    std::cout << std::endl;
    system("pause");
}
