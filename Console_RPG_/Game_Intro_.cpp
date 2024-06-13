#include "Game_Intro_.h"
#include "Game_Utility_.h"

//void Game_Intro_::_BeginIntro(std::string LV_Message_)
void Game_Intro_::_BeginIntro()
{
	std::string string_intro_ = "	In the mystical realm of Eternia, where magic flows like rivers and ancient prophecies whisper of heroes yet to rise, you embark on an epic journey filled with danger, mystery, and adventure.";
	std::cout << string_intro_ << std::endl << std::endl;
	//writeStringWithDelay(strIntroDescription_, 20);

	//_EndIntro();
}

void Game_Intro_::_PlayerSetup()
{

	std::cout << "	What is your name" << std::endl;

	std::getline(std::cin, strPlayerName_);
	std::cin.ignore();

	std::cout << "	Hello dear " << strPlayerName_ << " what path do you want to choose ?" << std::endl;
	std::cout 
		<< "	1. Warrior" << std::endl 
		<< "	2. Rogue" << std::endl 
		<< "	3. Wizzard" << std::endl
	;

	std::cin >> _PlayerPawnChoose;

	switch (_PlayerPawnChoose) {
	case 1:
		// TextIntroWarrior();
		_IntroPawnText(1);
		break;
	case 2:
		// TextIntroRogue();
		_IntroPawnText(2);
		break;
	case 3:
		// TextIntroWizzard();
		_IntroPawnText(3);
		break;
	default:
		_PlayerSetup();
		break;
	}

	std::cout << std::endl;

	
}

int Game_Intro_::_getPawnIndex()
{
	return _PlayerPawnChoose;
}

int Game_Intro_::_getPathIndex()
{
	return _PlayerPathChoose;
}

std::string Game_Intro_::_getPlayerName()
{
	return strPlayerName_;
}

std::string Game_Intro_::_getPawnName()
{
	switch (_PlayerPawnChoose) {
	case 1:
		return std::string("Warrior");
		break;
	case 2:
		return std::string("Rogue");
		break;
	case 3:
		return std::string("Wizzard");
		break;
	default:
		return std::string("NONE");
		break;
	}
}

std::string Game_Intro_::_getPathName()
{
	switch (_PlayerPathChoose) {
	case 1:
		return std::string("Village");
		break;
	case 2:
		return std::string("Cave");
		break;
	case 3:
		return std::string("Forest");
		break;
	default:
		return std::string("NONE");
		break;
	}
}

void Game_Intro_::_IntroPawnText(const int LV_Path_)
{
	switch (LV_Path_) {
	case 1:
		// TextIntroWarrior();
		std::cout << "	A strong Warrior" << std::endl;
		break;
	case 2:
		// TextIntroRogue();
		std::cout << "	A strong Rogue" << std::endl;
		break;
	case 3:
		// TextIntroWizzard();
		std::cout << "	A strong Wizzard" << std::endl;
		break;
	default:
		break;
	}
}

bool Game_Intro_::_EndIntro()
{
	std::string _PlayerChoice;
	std::cout << "	Do you want to play ?" << std::endl;
	std::cin >> _PlayerChoice;
	std::cin.ignore();

	if (_PlayerChoice == "Y" or _PlayerChoice == "y" or _PlayerChoice == "YES" or _PlayerChoice == "Yes" or _PlayerChoice == "yes")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game_Intro_::_CrossRoads()
{
	std::cout << "	Choose a path:" << std::endl << std::endl;

	std::cout << "	1. To the Village" << std::endl;
	std::cout << "	2. To the Cave" << std::endl;
	std::cout << "	3. To the Forest" << std::endl;

	std::cout << std::endl;

	std::cin >> _PlayerPathChoose;
	std::cin.ignore();

	if (!(_PlayerPathChoose == 1 || _PlayerPathChoose == 2 || _PlayerPathChoose == 3)) {
		std::cout << "	You can only choose the path from 1 to 3 !" << std::endl;
		_CrossRoads();
	}
	else {
		std::cout << "	You choose to go to " << _getPathName() << std::endl;
	}
}
