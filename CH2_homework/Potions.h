#pragma once

#include<map>
#include<string>

using namespace std;

class Potions
{
private:
	const string name;
	const map<string, int> recipe;
public:
	Potions(string name,  map<string, int> recipe):name(name), recipe(recipe) {};
	bool IsStuffInRecipe(string stuff) const;
	void ShowRecipe() const;
	string GetName() const;
};

