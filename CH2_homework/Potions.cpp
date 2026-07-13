#include "Potions.h"

#include<iostream>

bool Potions::IsStuffInRecipe(string stuff) const
{
    if (recipe.find(stuff) != recipe.end()) {
        return true;
    }
    return false;
}

void Potions::ShowRecipe() const
{
    string recipeStr = name + "(";
    for (auto itr = recipe.begin(); itr != recipe.end(); itr++) {
        string stuffName = itr->first;
        int stuffCount = itr->second;
        recipeStr += " " + stuffName + " x" + to_string(stuffCount);
    }
    recipeStr = recipeStr + ")";
    cout << recipeStr << endl;
}

string Potions::GetName() const
{
    return name;
}
