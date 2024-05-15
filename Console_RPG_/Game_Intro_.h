#pragma once
#include <iostream>
#include <string>
#include <vector>


class Game_Intro_
{
	private:
		std::string strIntroDescription_;
		std::string strPlayerName_;
		int _PlayerPawnChoose{ 1 };
		int _PlayerPathChoose{ 1 };

	public:
		Game_Intro_()
		{
			std::cout << "	DEBUG | Game Intro created !" << std::endl;
			std::cout << std::endl;

			strIntroDescription_ = " In the mystical realm of Eternia, where magic flows like rivers and ancient prophecies whisper of heroes yet to rise, you embark on an epic journey filled with danger, mystery, and adventure.";
		}
		Game_Intro_(std::string LV_Message_)
		{
			std::cout << "	DEBUG | Game Intro created !" << std::endl;
			std::cout << std::endl;

			strIntroDescription_ = LV_Message_;
			//strIntroDescription_ = " In the mystical realm of Eternia, where magic flows like rivers and ancient prophecies whisper of heroes yet to rise, you embark on an epic journey filled with danger, mystery, and adventure.";
		}
		~Game_Intro_()
		{
			std::cout << "	DEBUG | Game Intro destroyed !" << std::endl;
			std::cout << std::endl;
		}
		//void _BeginIntro(std::string LV_Message_);
		void _BeginIntro();
		void _PlayerSetup();
		int _getPawnIndex();
		int _getPathIndex();
		std::string _getPlayerName();
		std::string _getPawnName();
		std::string _getPathName();
		void _IntroPawnText(const int LV_Path_);
		bool _EndIntro();
		void _CrossRoads();

	protected:
};

