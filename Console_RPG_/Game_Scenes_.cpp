#include "Game_Scenes_.h"

void _Game_Scene_01_()
{

     // Setup Game Introduction
    // Intro, Start Game

        // Audio Init
        std::string wav_name = "Main_Menu";  // Base name of the WAV file
        std::string filename = "../Console_RPG_/Sounds/" + wav_name + ".wav";  // Adjust the path as needed
        WavFile wav = loadWavFile(filename.c_str());  // Pass the C-string to loadWavFile

        ApplyFadeIn(wav, 3000);
        std::atomic<bool> stopFlag(false);
        std::thread soundThread(BackgroundSoundThread, std::ref(wav), std::ref(stopFlag));


    Game_Intro_* BP_Game_Intro_ = new Game_Intro_();
    BP_Game_Intro_->_BeginIntro();

    if (BP_Game_Intro_->_EndIntro() == true) 
    {
        _Game_Scene_02_(BP_Game_Intro_, wav, stopFlag, soundThread);
    }
    else 
    {
        delete BP_Game_Intro_;
        system("CLS");
        std::cout << "  Quit the Game" << std::endl;

            // Audio Stop
            FadeOutWavFile(wav);
            stopFlag.store(true);
            soundThread.join();
    }
    
}

void _Game_Scene_02_(Game_Intro_* LV_GameIntro_, WavFile& LV_Wav, std::atomic<bool>& LV_StopFlag, std::thread& LV_SoundThread)
{

     // Setup The Player
    // Set Health, Armor, Player Name, Pawn Name

    //system("CLS");

    LV_GameIntro_->_PlayerSetup();

    Player_Class_* BP_Player_ = new Player_Class_(100, 50, LV_GameIntro_->_getPlayerName(), LV_GameIntro_->_getPawnName());

        // Audio Stop
        FadeOutWavFile(LV_Wav);
        LV_StopFlag.store(true);
        LV_SoundThread.join();

    _Game_Scene_03_(BP_Player_, LV_GameIntro_);

}

void _Game_Scene_03_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_)
{
     // Cross Roads Text
    // To Village, To Cave , To Forest
    
    //system("CLS");


        // Audio Init
        std::string wav_name = "Exploring";  // Base name of the WAV file
        std::string filename = "../Console_RPG_/Sounds/" + wav_name + ".wav";  // Adjust the path as needed
        WavFile wav = loadWavFile(filename.c_str());  // Pass the C-string to loadWavFile

        ApplyFadeIn(wav, 3000);
        std::atomic<bool> stopFlag(false);
        std::thread soundThread(BackgroundSoundThread, std::ref(wav), std::ref(stopFlag));

    LV_GameIntro_->_CrossRoads();

    _Game_Scene_04_(LV_Player_, LV_GameIntro_, wav, stopFlag, soundThread);

}

void _Game_Scene_04_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_, WavFile& LV_Wav, std::atomic<bool>& LV_StopFlag, std::thread& LV_SoundThread)
{
     // Chest
    // You find a chest | Open or Not
    
    system("CLS");

    LV_Player_->_CreateChest(LV_GameIntro_->_getPawnIndex());
    LV_Player_->_getPlayerInventory();
    
        // Audio Stop
        FadeOutWavFile(LV_Wav);
        LV_StopFlag.store(true);
        LV_SoundThread.join();

    _Game_Scene_05_(LV_Player_, LV_GameIntro_);
}

void _Game_Scene_05_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_)
{
      // Enemy Battle
     // Win or Lose
    // Remove all Player items then destroy Enemy and Player

    system("CLS");


        // Audio Init
        std::string wav_name = "BattleFinal";  // Base name of the WAV file
        std::string filename = "../Console_RPG_/Sounds/" + wav_name + ".wav";  // Adjust the path as needed
        WavFile wav = loadWavFile(filename.c_str());  // Pass the C-string to loadWavFile

        ApplyFadeIn(wav, 3000);
        std::atomic<bool> stopFlag(false);
        std::thread soundThread(BackgroundSoundThread, std::ref(wav), std::ref(stopFlag));



    if (LV_GameIntro_->_getPathIndex() == 1) {
        Enemy* BP_Enemy_ = new Enemy(80, 30, "Goblin");

        std::cout << "  Enemy is a " << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;
        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_, wav, stopFlag, soundThread);
    }
    else if(LV_GameIntro_->_getPathIndex() == 2) {
        Enemy* BP_Enemy_ = new Enemy(290, 60, "Dragon");

        std::cout << "  Enemy is a " << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;
        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_, wav, stopFlag, soundThread);
    }
    else if(LV_GameIntro_->_getPathIndex() == 3) {
        Enemy* BP_Enemy_ = new Enemy(150, 80, "Giant Spider");

        std::cout << "  Enemy is a " << BP_Enemy_->_getEnemyName() <<
            ", it has Power of " << BP_Enemy_->_getEnemyDealDamage() <<
            " and Health of " << BP_Enemy_->_getEnemyHealth() << std::endl;
        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, BP_Enemy_, wav, stopFlag, soundThread);
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

void _Game_Battle_Enemy_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_, Enemy* LV_Enemy_, WavFile& LV_Wav, std::atomic<bool>& LV_StopFlag, std::thread& LV_SoundThread)
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
            system("CLS");
            std::cout << "  You used the " << LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->getItemName() << std::endl;
            std::cout << "	GAME: You have " << LV_Player_->_getPlayerHealth()
                      << " Health and " << LV_Player_->_getPlayerArmor() << " Armor" << std::endl;

            // Get Player Health + Heal Potion = Player Health
            LV_Player_->_setPlayerHealth(LV_Player_->_getPlayerHealth() + LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->_getItemDamage());
        
            LV_Player_->_removeInventoryItem(_Player_Strategy_ - 1);

            _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, LV_Enemy_, LV_Wav, LV_StopFlag, LV_SoundThread);
            
        }
        else {

            std::random_device rd;
            std::uniform_int_distribution<int> distribution(0, 1);
            _Player_Luck_ = distribution(rd);

            
            // Hit the Enemy
            LV_Enemy_->_setEnemyHealth(LV_Enemy_->_getEnemyHealth() - LV_Player_->_getItemByIndex(_Player_Strategy_ - 1)->_getItemDamage());
            system("CLS");
            std::cout << "	GAME: You hit the " << LV_Enemy_->_getEnemyName() << ", now it has " << LV_Enemy_->_getEnemyHealth() << " health !" << std::endl;

            if (LV_Enemy_->_getEnemyHealth() <= 0) {
                std::cout << "	GAME: You defeated the " << LV_Enemy_->_getEnemyName() << " good job !" << std::endl;
                std::cout << "	GAME: See you next time!" << std::endl;
                delete LV_Player_;
                delete LV_GameIntro_;
                delete LV_Enemy_;

                    // Audio Stop
                    FadeOutWavFile(LV_Wav);
                    LV_StopFlag.store(true);
                    LV_SoundThread.join();
            }
            else
            {
            
                // If your not lucky then the Enemy will succeede to hit you
                if (_Player_Luck_) 
                {
                    //system("CLS");
                    std::cout << "	GAME: The " << LV_Enemy_->_getEnemyName() << " missed the hit !" << std::endl;
                    std::cout << "	GAME: You have " << LV_Player_->_getPlayerHealth() 
                              << " Health and " << LV_Player_->_getPlayerArmor() << " Armor" << std::endl;

                    _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, LV_Enemy_, LV_Wav, LV_StopFlag, LV_SoundThread);
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
                        //system("CLS");
                        std::cout << "	GAME: The " << LV_Enemy_->_getEnemyName() << " have put you to sleep!" << std::endl;
                        std::cout << "	GAME: Mission failed, we go next time!" << std::endl;
                        delete LV_Player_;
                        delete LV_GameIntro_;
                        delete LV_Enemy_;

                            // Audio Stop
                            FadeOutWavFile(LV_Wav);
                            LV_StopFlag.store(true);
                            LV_SoundThread.join();

                    }
                    else {
                        //system("CLS");
                        std::cout << "	GAME: You have been hit by the " << LV_Enemy_->_getEnemyName() << ", now you have " << std::endl <<
                            LV_Player_->_getPlayerHealth() << " Health and " << LV_Player_->_getPlayerArmor() << " Armor" << std::endl;
                        _Game_Battle_Enemy_(LV_Player_, LV_GameIntro_, LV_Enemy_, LV_Wav, LV_StopFlag, LV_SoundThread);
                    }
                }
            }
        }
    }
}