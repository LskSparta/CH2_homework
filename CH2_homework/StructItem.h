#pragma once
#include<string>

using namespace std;

struct ItemInfo
{
    string name;
    int price;
    bool consumable;

    bool operator==(const ItemInfo& other) const {
        return this->name == other.name;
    }

    bool operator<(const ItemInfo& other) const
    {
        return name < other.name;
    }
};