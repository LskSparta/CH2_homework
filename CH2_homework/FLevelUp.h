#pragma once

struct FLevelUp
{
private:
	const int expIncrease = 100;
public:
	const int hpUp = 10;
	const int mpUp = 5;
	const int attackUp = 5;
	int GetNextExp(int level) const {
		return level * expIncrease;
	}
};