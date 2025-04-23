// RPG item generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>

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

struct item {
    std::string itemType;
    std::string prefix;
    std::string suffix;
    std::string statType;
    int statValue;
};

item generateItem() {
    item newItem;
    int itemTypeIndex, prefixIndex, suffixIndex, statTypeIndex;

    int minStatValue = 5;
    int maxStatValue = 20;
    
    itemTypeIndex = rand() % itemTypeMaxIndex;
    prefixIndex = rand() % prefixMaxIndex;
    suffixIndex = rand() % suffixMaxIndex;
    statTypeIndex = rand() % statTypeMaxIndex;

    newItem.itemType = itemType[itemTypeIndex];
    newItem.prefix = prefix[prefixIndex];
    newItem.suffix = suffix[suffixIndex];
    newItem.statType = statType[statTypeIndex];
    newItem.statValue = minStatValue + (std::rand() % (maxStatValue - minStatValue));

    return newItem;
}

int main()
{
    std::srand(std::time(0));
    std::vector<item> items;

    for (int i = 0; i < 25; ++i) {
        items.push_back(generateItem());
    }

    for (int i = 0; i < items.size(); ++i)
    {
        std::cout << items[i].prefix << " " 
                  << items[i].itemType << " " 
                  << items[i].suffix << "(" 
                  << items[i].statType << " +" 
                  << items[i].statValue << ")\n";
    }
    
    std::cout << std::endl;
    system("pause");
}
