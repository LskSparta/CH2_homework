#pragma once
#include<string>

using namespace std;

class Player;

struct ItemInfo
{
public:
    bool operator==(const ItemInfo& other) const {
        return this->name == other.name;
    }

    bool operator<(const ItemInfo& other) const
    {
        return name < other.name;
    }
    virtual void Consume(Player* player) const {};
    void ShowItemInfo() const;
    string GetName() const;
    int GetPrice() const;
    bool IsConsumable() const;
    ItemInfo(string name, int price, bool consumable);
    virtual ~ItemInfo() {};
protected:
    string name;
    int price;
    bool consumable;
};

class PotionHp : public ItemInfo
{
private:
    int pointHp = 50;
    // ItemInfo을(를) 통해 상속됨
public:
    PotionHp(string name, int price, bool consumable, int pointHp = 50) : ItemInfo(name, price, consumable) {
        pointHp = pointHp;
    };
    void Consume(Player* player) const override;
};

class PotionMp : public ItemInfo
{
private:
    int pointMp = 50;
    // ItemInfo을(를) 통해 상속됨
public:
    PotionMp(string name, int price, bool consumable, int pointMp = 50) : ItemInfo(name, price, consumable) {
        pointMp = pointMp;
    };
    void Consume(Player* player) const override;
};