#pragma once
#include <iostream>
#include <string>
#include <vector>


class Enemy
{
	private:
		std::string _EnemyName;
		int _EnemyDealDamage{ 0 };
		int _EnemyHealth{ 0 };

	public:
		Enemy(int LV_EnemyHealth_, int LV_EnemyDealDamage_, std::string LV_EnemyName_) :
			_EnemyHealth(LV_EnemyHealth_), _EnemyDealDamage(LV_EnemyDealDamage_), _EnemyName(LV_EnemyName_)
		{

			//std::cout << "	DEBUG | Enemy " << _EnemyName << " was created" << std::endl;
		}
		~Enemy()
		{

			//std::cout << "	DEBUG | Enemy " << _EnemyName << " was destroyed" << std::endl;
		}

		void _setEnemyHealth(int LV_Health_);
		int _getEnemyHealth();
		int _getEnemyDealDamage();
		std::string _getEnemyName();

};

class Item
{
	private:
		std::string _ItemName;
		int _ItemDamage{ 0 };
		bool _ItemCanHealPlayer{ false };

	public:
		Item(std::string LV_ItemName_, int LV_ItemDamage, bool LV_ItemCanHealPlayer) :
			_ItemName(LV_ItemName_),
			_ItemDamage(LV_ItemDamage),
			_ItemCanHealPlayer(LV_ItemCanHealPlayer)
		{
			//std::cout << "	DEBUG | Item " << _ItemName << " was created" << std::endl;
		}
		~Item()
		{
			//std::cout << "	DEBUG | Item " << _ItemName << " was destroyed" << std::endl;
		}
		
		std::string getItemName()
		{
			return _ItemName;
		}
		int _getItemDamage()
		{
			return _ItemDamage;
		}
		bool _getItemUtility()
		{
			return _ItemCanHealPlayer;
		}
};

class Player_Class_
{
	private:

		struct Struct_Items_ {
			std::string _WeaponName;
			int _WeaponDamage;
			bool _CanHealPlayer;
		};

		Struct_Items_ Item_List_[6] = {
			{"Sword", 25, false},
			{"Axe", 30, false},
			{"Magic Stick", 35, false},
			{"Shawarma", 10, true},
			{"Heal Potion", 20, true},
			{"Golden Apple", 40, true}
		};

		std::string strPlayerName_;
		std::string strPawnName;
		int _PlayerHealth { 100 };
		int _PlayerArmor{ 50 };
		std::vector<Item*> _PlayerInvetory;

	public:
		Player_Class_()
		{
			//std::cout << "	DEBUG | Player_Class spawned !" << std::endl;
		}
		Player_Class_(int LV_Health_, int LV_Armor_, std::string LV_PlayerName, std::string LV_PawnName)
		{
			//std::cout << "	DEBUG | Player_Class spawned !" << std::endl;

			std::cout << std::endl;

			_PlayerHealth = LV_Health_;
			_PlayerArmor = LV_Armor_;
			strPlayerName_ = LV_PlayerName;
			strPawnName = LV_PawnName;

			std::cout << "	GAME | Player Status !" << std::endl <<
				"	Health: " << LV_Health_ << std::endl <<
				"	Armor: " << LV_Armor_ << std::endl <<
				"	Player Name: " << LV_PlayerName << std::endl <<
				"	Pawn Name: " << LV_PawnName << std::endl << 
			std::endl;

		}
		~Player_Class_()
		{
			//std::cout << "	DEBUG | Player_Class destroyed !" << std::endl;
			_destroyPlayerInventory();
		}

		void _setPlayerHealth(int LV_Health_);
		int _getPlayerHealth();
		void _setPlayerArmor(int LV_Armor_);
		int _getPlayerArmor();
		void _givePlayerItem(Item* LV_Item_);
		void _getPlayerInventory();
		void _removeInventoryItem(size_t LV_Item_);
		//size_t _getPlayerInventorySize();
		void _ChestItemGenerate(std::vector<int> LV_ItemsToGenerate);
		void _CreateChest(int LV_Pawn_);

		void _destroyPlayerInventory();
		Item* _generateItem(int LV_Item_);
		Item* _getItemByIndex(int LV_Item_);

	protected:
};

