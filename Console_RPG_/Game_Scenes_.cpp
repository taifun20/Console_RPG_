#include "Game_Scenes_.h"

void _Game_Scene_01_()
{

     // Setup Game Introduction
    // Intro, Start Game

    Game_Intro_* BP_Game_Intro_ = new Game_Intro_();
    BP_Game_Intro_->_BeginIntro();

    if (BP_Game_Intro_->_EndIntro() == true) {
        //system("CLS");
        _Game_Scene_02_(BP_Game_Intro_);
    }
    else {
        delete BP_Game_Intro_;
    }
    //system("CLS");
}

void _Game_Scene_02_(Game_Intro_* LV_GameIntro_)
{

     // Setup The Player
    // Set Health, Armor, Player Name, Pawn Name

    LV_GameIntro_->_PlayerSetup();

    Player_Class_* BP_Player_ = new Player_Class_(100, 50, LV_GameIntro_->_getPlayerName(), LV_GameIntro_->_getPawnName());
    //system("CLS");
    _Game_Scene_03_(BP_Player_, LV_GameIntro_);

}

void _Game_Scene_03_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_)
{
     // Cross Roads Text
    // To Village, To Cave , To Forest

    LV_GameIntro_->_CrossRoads();

    //system("CLS");
    _Game_Scene_04_(LV_Player_, LV_GameIntro_);

}

void _Game_Scene_04_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_)
{
     // Chest
    // You find a chest | Open or Not

    LV_Player_->_CreateChest(LV_GameIntro_->_getPawnIndex());
    LV_Player_->_getPlayerInventory();
    //system("CLS");
    _Game_Scene_05_(LV_Player_, LV_GameIntro_);
}

void _Game_Scene_05_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_)
{
      // Enemy Battle
     // Win or Lose
    // Remove all Player items then destroy Enemy and Player

    if (LV_GameIntro_->_getPathIndex() == 1) {
        Enemy* BP_Enemy_ = new Enemy(30, 10, "Goblin");

        std::cout << "  Enemy is a" << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;
        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_);
    }
    else if(LV_GameIntro_->_getPathIndex() == 2) {
        Enemy* BP_Enemy_ = new Enemy(90, 40, "Dragon");

        std::cout << "  Enemy is a" << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;
        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_);
    }
    else if(LV_GameIntro_->_getPathIndex() == 3) {
        Enemy* BP_Enemy_ = new Enemy(50, 80, "Giant Spider");

        std::cout << "  Enemy is a" << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;
        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_);
    }

    
    /*switch (LV_GameIntro_->_getPathIndex())
    {
    case 1:
        Enemy * BP_Enemy_ = new Enemy(30, 10, "Goblin");

        std::cout << "  Enemy is a" << BP_Enemy_->_getEnemyName() << 
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() << 
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;

        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_);
        break;
    case 2:
        Enemy * BP_Enemy_ = new Enemy(90, 40, "Dragon");

        std::cout << "  Enemy is a" << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;

        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_);
        break;
    case 3:
        Enemy * BP_Enemy_ = new Enemy(50, 80, "Giant Spider");

        std::cout << "  Enemy is a" << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;

        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_);
        break;
    default:
        break;
    }*/

    //system("CLS");
}

void _Game_Battle_Enemy_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_, Enemy* LV_Enemy_)
{
    
    int _Player_Strategy_;
    int _Player_Luck_;

    if (LV_Player_->_getPlayerHealth() >= 5)
    {
        LV_Player_->_getPlayerInventory();

        std::cout << "What are you gona do ?" << std::endl; // Get item, use that item, delete that item if is one use
        std::cin >> _Player_Strategy_;
        std::cin.ignore();
        
        if (LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->_getItemUtility())
        {
            std::cout << "  You used the " << LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->getItemName() << std::endl;

            // Get Player Health + Heal Potion = Player Health
            LV_Player_->_setPlayerHealth(LV_Player_->_getPlayerHealth() + LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->_getItemDamage());
        
            LV_Player_->_removeInventoryItem(_Player_Strategy_ - 1);

            _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, LV_Enemy_);
            
        }
        else {

            std::random_device rd;
            std::uniform_int_distribution<int> distribution(0, 1);
            _Player_Luck_ = distribution(rd);

            
            // Hit the Enemy
            LV_Enemy_->_setEnemyHealth(LV_Enemy_->_getEnemyHealth() - LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->_getItemDamage());

            std::cout << "	GAME: You hit the " << LV_Enemy_->_getEnemyName() << ", now it has " << LV_Enemy_->_getEnemyHealth() << " health !" << std::endl;

            if (LV_Enemy_->_getEnemyHealth() <= 0) {
                std::cout << "	GAME: You defeated the " << LV_Enemy_->_getEnemyName() << " good job !" << std::endl;
                std::cout << "	GAME: See you next time!" << std::endl;
                delete LV_Player_;
                delete LV_GameIntro_;
                delete LV_Enemy_;
            }
            else
            {
            
                // If your not lucky then the Enemy will succeede to hit you
                if (_Player_Luck_) {

                    std::cout << "	GAME: The " << LV_Enemy_->_getEnemyName() << " missed the hit !" << std::endl;
                    _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, LV_Enemy_);
                }
                else
                {
                    // Damage the Armor or the Health of the Player
                    if (LV_Player_->_getPlayerArmor() > 0) {
                        LV_Player_->_setPlayerArmor(LV_Player_->_getPlayerArmor() - LV_Enemy_->_getEnemyDealDamage());
                    }
                    else {
                        LV_Player_->_setPlayerHealth(LV_Player_->_getPlayerHealth() - LV_Enemy_->_getEnemyDealDamage());
                    }


                    if (LV_Player_->_getPlayerArmor() < 0) {
                        LV_Player_->_setPlayerArmor(0);
                    }
                    // If the player health is 0 or less then Game Over
                    if (LV_Player_->_getPlayerHealth() <= 0) {
                        LV_Player_->_setPlayerHealth(0);

                        std::cout << "	GAME: The " << LV_Enemy_->_getEnemyName() << " have put you to sleep!" << std::endl;
                        std::cout << "	GAME: Mission failed, we go next time!" << std::endl;
                        delete LV_Player_;
                        delete LV_GameIntro_;
                        delete LV_Enemy_;

                    }
                    else {
                        std::cout << "	GAME: You have been hit by the " << LV_Enemy_->_getEnemyName() << ", now you have " << std::endl <<
                            LV_Player_->_getPlayerHealth() << " Health and " << LV_Player_->_getPlayerArmor() << " Armor" << std::endl;
                    }
                }
            }
        }
    }
}