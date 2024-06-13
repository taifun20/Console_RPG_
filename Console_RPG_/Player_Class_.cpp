#include "Player_Class_.h"

void Player_Class_::_setPlayerHealth(int LV_Health_)
{
    _PlayerHealth = LV_Health_;
}

int Player_Class_::_getPlayerHealth()
{
    return _PlayerHealth;
}

void Player_Class_::_setPlayerArmor(int LV_Armor_)
{
    _PlayerArmor = LV_Armor_;
}

int Player_Class_::_getPlayerArmor()
{
    return _PlayerArmor;
}

void Player_Class_::_givePlayerItem(Item* LV_Item_)
{
    _PlayerInvetory.push_back(LV_Item_);
}

void Player_Class_::_getPlayerInventory()
{
    std::cout << std::endl;
    std::cout << "        Player " << strPlayerName_ << " has the following inventory" << std::endl;
    for (int i = 0; i < _PlayerInvetory.size(); i++)
    {
        std::cout << "        " << i + 1 << ". " << _PlayerInvetory[i]->getItemName() << std::endl;
    }
    std::cout << std::endl;
}

void Player_Class_::_removeInventoryItem(size_t LV_Item_)
{
    //LV_Item_ -= 1;
    delete _PlayerInvetory[LV_Item_];
    _PlayerInvetory.erase(_PlayerInvetory.begin() + LV_Item_);
}

/*size_t Player_Class_::_getPlayerInventorySize()
{
    return _PlayerInvetory.size();
}*/

void Player_Class_::_ChestItemGenerate(std::vector<int> LV_ItemsToGenerate)
{
    for (int i = 0; i < LV_ItemsToGenerate.size(); i++)
    {
        _givePlayerItem(_generateItem(LV_ItemsToGenerate[i]));
    }
}

void Player_Class_::_CreateChest(int LV_Pawn_)
{
    switch (LV_Pawn_)
    {
    case 1:
        _ChestItemGenerate({ 0,3,4,4 });
        break;
    case 2:
        _ChestItemGenerate({ 1,5,5 });
        break;
    case 3:
        _ChestItemGenerate({ 2,4,4,4 });
        break;
    default:
        break;
    }


}

void Player_Class_::_destroyPlayerInventory()
{
    for (int i = 0; i < _PlayerInvetory.size(); i++)
    {
        delete _PlayerInvetory[i];
    }
}

Item* Player_Class_::_generateItem(int LV_Item_)
{
    Item* item = new Item(Item_List_[LV_Item_]._WeaponName, Item_List_[LV_Item_]._WeaponDamage, Item_List_[LV_Item_]._CanHealPlayer);
    return item;
}

Item* Player_Class_::_getItemByIndex(int LV_Item_)
{
    return _PlayerInvetory[LV_Item_];
}

void Enemy::_setEnemyHealth(int LV_Health_)
{
    _EnemyHealth = LV_Health_;
}

int Enemy::_getEnemyHealth()
{
    return _EnemyHealth;
}

int Enemy::_getEnemyDealDamage()
{
    return _EnemyDealDamage;
}

std::string Enemy::_getEnemyName()
{
    return _EnemyName;
}
