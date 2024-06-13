#pragma once

#include <random>
#include "Game_Intro_.h"
#include "Player_Class_.h"
#include "Game_Utility_.h"

void _Game_Scene_01_();
void _Game_Scene_02_(Game_Intro_* LV_GameIntro_, WavFile& LV_Wav, std::atomic<bool>& LV_StopFlag, std::thread& LV_SoundThread);
void _Game_Scene_03_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_);
void _Game_Scene_04_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_, WavFile& LV_Wav, std::atomic<bool>& LV_StopFlag, std::thread& LV_SoundThread);
void _Game_Scene_05_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_);
void _Game_Battle_Enemy_(Player_Class_* LV_Player_, Game_Intro_* LV_GameIntro_, Enemy* LV_Enemy_, WavFile& LV_Wav, std::atomic<bool>& LV_StopFlag, std::thread& LV_SoundThread);
