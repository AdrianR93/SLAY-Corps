#include<iostream>
#include<vector>
#include <string>
#include<fstream>
#include<Windows.h>
using namespace std;

struct PlayerStats
{
	string name;
	int playerProfession;
	string professionName;
	int level;
	int totalHP;
	int maxHP;
	int heal;
	int str;
	int speed;
	int faith;
	int route;
	bool key;
	int xp;
	int neededXp;
};
PlayerStats MyPlayer;

string demons[] = { "Zombie", "Wyvern", "Imps", "Greater Demon", "Hellhound", "Sucubus", "Ghoul" };
struct DemonStats
{
	int demonHP;
	int demonXp;
	int demonLevel;
	int demonSpecies = sizeof demons / sizeof demons[0];
	string currentDemon;
};
DemonStats RandomDemon;

struct BossStats
{
	string bossName;
	int bossLevel;
	int bossMaxHP;
	int bossTotalHP;
	int bossHeal;
	int bossStr;
};
BossStats PaleRider;


void Menu();
void RollIntro();
void Save();
void LoadCharacter();
void CharacterCreation();
void Status();
void StartFight();
void CombatStatus();
void HUB();
void MovementForward();
void CheckForKey();
void CreateDemon();
void DemonSlaying();
void GameOver();
void LvlUP();
void ChallengeBoss();
void CreateBoss();
void BossStatus();
void BossSlaying();
void RollOutro();
void RollCredits();
void errorTxt();
void pressEnter();
bool is_digits(const std::string& str);

void main()
{
	system("cls");
	Menu();
	enum menu { newCharacter = 1, loadGame, credits };
	bool retryMenu;
	do
	{
		int auxUserMenu = -1;
		retryMenu = false;
		string menuChoice;
		cin >> menuChoice;

		if (is_digits(menuChoice))
		{
			auxUserMenu = stoi(menuChoice);
		}

		switch (auxUserMenu)
		{
		case menu::newCharacter:
			CharacterCreation();
			break;
		case menu::loadGame:
			LoadCharacter();
			break;
		case menu::credits:
			RollCredits();
			break;
		default:
			errorTxt();
			retryMenu = true;
			break;
		}
	} while (retryMenu == true);

	HUB();


}

void RollIntro()
{
	system("cls");
	ifstream inputFile;
	inputFile.open("menu\\Intro.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}

	inputFile.close();

	for (size_t i = 0; i < (menuText.size() - 1); i++)
	{
		cout << menuText[i] << endl;
		cin.get();
	}
	system("cls");
	cin.get();
	cout << menuText[24] << endl;
}

void Menu()
{

	ifstream inputFile;
	inputFile.open("menu\\MainMenu.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}

	inputFile.close();

	for (size_t i = 0; i < 11; i++)
	{
		cout << menuText[i] << endl;
	}
	pressEnter();
	system("cls");

	for (size_t i = 12; i < menuText.size(); i++)
	{
		cout << menuText[i] << endl;
	}
}

void CharacterCreation()
{
	enum professions { Soldier = 1, Hunter = 2, Priest = 3 };
	bool retryProfession;
	RollIntro();
	cin >> MyPlayer.name;
	system("cls");

	do
	{
		ifstream inputFile;
		inputFile.open("menu\\CharacterCreation.txt", ios::in);
		vector<string> menuText;

		if (!inputFile.fail())
		{
			while (inputFile.eof() == false)
			{
				string text;
				getline(inputFile, text);
				menuText.emplace_back(text);
			}
		}

		inputFile.close();

		for (size_t i = 0; i < 7; i++)
		{
			cout << menuText[i] << endl;
		}

		retryProfession = false;
		int auxProfesiones;
		cin >> auxProfesiones;
		system("cls");
		MyPlayer.playerProfession = auxProfesiones;
		switch (auxProfesiones)
		{
		case professions::Soldier:
			MyPlayer.playerProfession = auxProfesiones;
			MyPlayer.professionName = "Soldier";
			MyPlayer.level = 1;
			MyPlayer.str = 15;
			MyPlayer.speed = 5;
			MyPlayer.faith = 2;
			MyPlayer.route = 0;
			MyPlayer.key = false;
			MyPlayer.xp = 0;
			MyPlayer.neededXp = 200;
			MyPlayer.totalHP = 150;
			MyPlayer.maxHP = MyPlayer.totalHP;
			cout << menuText[7] << endl;
			cout << menuText[10] << endl;
			pressEnter();
			break;
		case professions::Hunter:
			MyPlayer.playerProfession = auxProfesiones;
			MyPlayer.professionName = "Hunter";
			MyPlayer.level = 1;
			MyPlayer.str = 10;
			MyPlayer.speed = 13;
			MyPlayer.faith = 8;
			MyPlayer.route = 0;
			MyPlayer.key = false;
			MyPlayer.xp = 0;
			MyPlayer.neededXp = 200;
			MyPlayer.totalHP = 100;
			MyPlayer.maxHP = MyPlayer.totalHP;
			cout << menuText[8] << endl;
			cout << menuText[10] << endl;
			pressEnter();
			break;
		case professions::Priest:
			MyPlayer.playerProfession = auxProfesiones;
			MyPlayer.professionName = "Priest";
			MyPlayer.level = 1;
			MyPlayer.str = 6;
			MyPlayer.speed = 7;
			MyPlayer.faith = 20;
			MyPlayer.route = 0;
			MyPlayer.key = false;
			MyPlayer.xp = 0;
			MyPlayer.neededXp = 200;
			MyPlayer.totalHP = 100;
			MyPlayer.maxHP = MyPlayer.totalHP;
			cout << menuText[9] << endl;
			cout << menuText[10] << endl;
			pressEnter();
			break;
		default:
			errorTxt();
			Sleep(800);
			system("cls");
			retryProfession = true;
			break;
		}
	} while (retryProfession == true);

}

void HUB()
{
	bool retryHUB;
	do
	{
		enum hub { enterBasement = 1, sleepAtBarracks, teleportToBoss, save, mainMenu };
		int auxHub = -1;
		retryHUB = false;
		string hubChoice;
		system("cls");

		ifstream inputFile;
		inputFile.open("menu\\HUB.txt", ios::in);
		vector<string> menuText;

		if (!inputFile.fail())
		{
			while (inputFile.eof() == false)
			{
				string text;
				getline(inputFile, text);
				menuText.emplace_back(text);
			}

		}
		inputFile.close();
		for (size_t i = 0; i < 18; i++)
		{
			cout << menuText[i] << endl;
		}

		cin >> hubChoice;
		if (is_digits(hubChoice))
		{
			auxHub = stoi(hubChoice);
		}

		switch (auxHub)
		{
		case hub::enterBasement:
			cout << menuText[18] << endl;
			pressEnter();
			Status();
			break;
		case hub::sleepAtBarracks:
			if (MyPlayer.totalHP >= MyPlayer.maxHP)
			{
				cout << menuText[19] << endl;
				pressEnter();
				retryHUB = true;
			}
			if (MyPlayer.totalHP < MyPlayer.maxHP)
			{
				MyPlayer.totalHP = MyPlayer.maxHP;
				cout << menuText[20] << endl;
				pressEnter();
				retryHUB = true;
			}
			break;
		case hub::teleportToBoss:
			if (MyPlayer.key == false)
			{
				cout << menuText[21] << endl;
				pressEnter();
				retryHUB = true;
			}
			if (MyPlayer.key == true)
			{
				ChallengeBoss();
			}
			break;
		case hub::save:
			Save();
			retryHUB = true;
			break;
		case hub::mainMenu:
			main();
		default:
			errorTxt();
			pressEnter();
			HUB();
			break;
		}
	} while (retryHUB == true);
}


void Status()
{
	ifstream inputFile;
	inputFile.open("menu\\Status.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}

	}
	inputFile.close();
	system("cls");
	cout << menuText[0] << MyPlayer.route << endl;
	cout << menuText[1] << MyPlayer.totalHP << menuText[2] << MyPlayer.maxHP << endl;
	cout << menuText[3] << MyPlayer.name << endl;
	cout << menuText[4] << MyPlayer.professionName << endl;
	cout << menuText[5] << MyPlayer.level << endl;
	cout << menuText[6] << MyPlayer.xp << endl;
	cout << menuText[7] << MyPlayer.neededXp << endl;
	cout << menuText[8] << menuText[9] << endl;
	CheckForKey();
	MovementForward();
}

void MovementForward()
{
	ifstream inputFile;
	inputFile.open("menu\\MovementForward.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}

	inputFile.close();

	for (size_t i = 0; i < 5; i++)
	{
		cout << menuText[i] << endl;
	}
	
	enum movement { advance = 1, rest, escape, save };
	int auxMovement = -1;
	string movementChoice;
	int auxEscape = rand() % 100 + 1;
	cin >> movementChoice;

	if (is_digits(movementChoice))
	{
		auxMovement = stoi(movementChoice);
	}
	switch (auxMovement)
	{

	case movement::advance:

		int auxRand;
		auxRand = rand() % 100 + 1;
		if (auxRand >= 0 && auxRand < 10)
		{
			MyPlayer.route++;
			cout << menuText[4] << endl;
			pressEnter();
			Status();
		}
		else if (auxRand >= 10 && auxRand < 15)
		{
			MyPlayer.route++;
			cout << menuText[5] << endl;
			pressEnter();
			Status();
		}
		else if (auxRand >= 15 && auxRand < 25)
		{
			MyPlayer.route++;
			cout << menuText[6] << endl;
			pressEnter();;
			Status();
		}
		else if (auxRand >= 25 && auxRand < 35)
		{
			MyPlayer.route++;
			cout << menuText[7] << endl;
			pressEnter();
			Status();
		}
		else if (auxRand >= 35 && auxRand < 50)
		{
			MyPlayer.route++;
			cout << menuText[8] << endl;
			pressEnter();
			Status();
		}
		else if (auxRand >= 50)
		{
			MyPlayer.route++;
			cout << menuText[9] << endl;
			pressEnter();
			StartFight();
		}

		break;
	case movement::rest:
		cout << menuText[11] << endl;
		int auxRest;
		auxRest = rand() % 100 + 1;
		if (MyPlayer.totalHP >= MyPlayer.maxHP)
		{
			cout << menuText[12] << endl;
			pressEnter();
			system("cls");
			Status();
		}
		if (auxRest > 65) {
			if (MyPlayer.totalHP < MyPlayer.maxHP)
			{
				MyPlayer.heal = MyPlayer.maxHP * 0.35;
				MyPlayer.totalHP += MyPlayer.heal;
				if (MyPlayer.totalHP > MyPlayer.maxHP)
				{
					MyPlayer.totalHP = MyPlayer.maxHP;
				}
			}
			cout << menuText[13] << MyPlayer.heal << menuText[14] << endl;
			system("cls");
			Status();
		}
		else
		{
			cout << menuText[15] << endl;
			pressEnter();
			StartFight();
		}
		break;
	case movement::escape:

		cout << menuText[17] << endl;
		Sleep(1000);
		HUB();
		break;
	case movement::save:
		Save();
		Status();
		break;
	default:
		errorTxt();
		Status();
		break;
	}
}

void CheckForKey()
{
	ifstream inputFile;
	inputFile.open("menu\\CheckForKey.txt", ios::in);
	vector<string> menuText;
	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}

	}
	inputFile.close();

	if (MyPlayer.route == 30)
	{
		MyPlayer.key = true;
		cout << menuText[0] << "\n" << endl;
		return;
	}
	else if (MyPlayer.route > 30)
	{
		MyPlayer.key = true;
		cout << menuText[1] << "\n" << endl;
		return;
	}
	else
	{
		return;
	}
}

void StartFight()
{
	ifstream inputFile;
	inputFile.open("menu\\StartFight.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}
	inputFile.close();

	CreateDemon();
	string auxName = demons[rand() % RandomDemon.demonSpecies];
	cout << auxName << menuText[0] << endl;
	RandomDemon.currentDemon = auxName;
	DemonSlaying();
}

void CreateDemon()
{
	RandomDemon.demonLevel = (rand() % 3 + 1) + (MyPlayer.level);
	if (1 < MyPlayer.level < 5)
	{
		RandomDemon.demonHP = (rand() % 11) + 10 * MyPlayer.totalHP * 0.6;
		RandomDemon.demonXp = RandomDemon.demonHP *= 0.5;
		if (RandomDemon.demonLevel == 0 || RandomDemon.demonHP == 0)
		{
			CreateDemon();
		}
	}
	else if (MyPlayer.level > 5) // Tutorial is over :) 
	{
		RandomDemon.demonHP = (rand() % 11) + 20 * MyPlayer.totalHP * 0.8;
		RandomDemon.demonXp = RandomDemon.demonHP * 0.3;
		if (RandomDemon.demonLevel == 0 || RandomDemon.demonHP == 0)
		{
			CreateDemon();
		}
	}
}

void CombatStatus()
{
	ifstream inputFile;
	inputFile.open("menu\\CombatStatus.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}

	}
	inputFile.close();
	system("cls");
	cout << menuText[0] << MyPlayer.totalHP << menuText[1] << MyPlayer.maxHP << menuText[2] << RandomDemon.demonHP << endl;
	cout << menuText[3] << MyPlayer.level << menuText[4] << RandomDemon.demonLevel << endl;
	cout << menuText[5] << RandomDemon.currentDemon << endl;
	cout << menuText[6] << MyPlayer.professionName << endl;
	cout << menuText[7] << MyPlayer.name << endl;
	cout << menuText[8] << MyPlayer.str << endl;
	cout << menuText[9] << MyPlayer.speed << endl;
	cout << menuText[10] << MyPlayer.faith << endl;
	cout << menuText[11] << MyPlayer.xp << endl;
	cout << menuText[12] << MyPlayer.neededXp << endl;
	cout << menuText[13] << endl;

}

void DemonSlaying()
{
	ifstream inputFile;
	inputFile.open("menu\\DemonSlaying.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}

	}
	inputFile.close();
	CombatStatus();
	int combatChoice;
	int playerDamage = MyPlayer.str * MyPlayer.level * 4.5;
	int demonDamage = 9 * MyPlayer.level * 1.5;
	enum battlechoices { attack = 1, parry, pray, escape, save };
	int faithRand = (rand() % 10) * MyPlayer.faith;
	int parryRand = (rand() % 10) * MyPlayer.speed;
	int runRand = rand() % 100 + 1;
	for (size_t i = 0; i < 5; i++)
	{
		cout << menuText[i] << endl;
	}
	cin >> combatChoice;
	switch (combatChoice)
	{
	case battlechoices::attack:
		cout << menuText[6] << playerDamage << menuText[7] << RandomDemon.currentDemon << endl;
		pressEnter();
		RandomDemon.demonHP -= playerDamage;

		if (RandomDemon.demonHP >= 1)
		{
			CombatStatus();
			MyPlayer.totalHP -= demonDamage;
			cout << RandomDemon.currentDemon << menuText[9] << demonDamage << menuText[10] << MyPlayer.totalHP << menuText[11] << endl;
			pressEnter();
			GameOver();
			DemonSlaying();
		}
		else if (RandomDemon.demonHP <= 0)
		{
			RandomDemon.demonHP = 0;
			CombatStatus();
			LvlUP();
			Status();
		}
		break;
	case battlechoices::parry:
		cout << menuText[17] << endl;

		if (parryRand >= 60)
		{
			int playerParry;
			playerParry = playerDamage + (playerDamage * 0.4);
			RandomDemon.demonHP -= playerParry;
			cout << menuText[18] << playerParry << menuText[7] << RandomDemon.currentDemon << menuText[19] << endl;
			pressEnter();
			if (RandomDemon.demonHP >= 1)
			{

				int demonDamageAfterParry = demonDamage * 0.5;
				MyPlayer.totalHP -= demonDamageAfterParry;
				cout << RandomDemon.currentDemon << menuText[21] << demonDamageAfterParry << menuText[22] << MyPlayer.totalHP << menuText[11] << endl;
				pressEnter();
				GameOver();
				DemonSlaying();
			}
			else if (RandomDemon.demonHP <= 0)
			{
				RandomDemon.demonHP = 0;
				CombatStatus();
				LvlUP();
				Status();
			}
		}
		else
		{
			MyPlayer.totalHP -= demonDamage + (demonDamage * 0.6);
			cout << menuText[24] << endl;
			pressEnter();
			GameOver();
			DemonSlaying();
		}
		break;
	case battlechoices::pray:
		cout << menuText[26] << endl;

		if (faithRand >= 60)
		{
			if (MyPlayer.totalHP < MyPlayer.maxHP)
			{
				MyPlayer.heal = MyPlayer.level * MyPlayer.faith * 1.8;
				MyPlayer.totalHP += MyPlayer.heal;
				if (MyPlayer.totalHP > MyPlayer.maxHP)
				{
					MyPlayer.totalHP = MyPlayer.maxHP;
				}
				cout << menuText[27] << MyPlayer.heal << menuText[28] << MyPlayer.totalHP << endl;
				pressEnter();
				DemonSlaying();
			}
			else
			{
				cout << menuText[29] << endl;
				pressEnter();
				DemonSlaying();
			}
		}
		else
		{
			MyPlayer.totalHP -= demonDamage;
			cout << menuText[30] << demonDamage << menuText[31] << MyPlayer.totalHP << endl;
			Sleep(800);
			GameOver();
			DemonSlaying();
		}
		break;
	case battlechoices::escape:
		cout << menuText[33] << endl;

		if (runRand >= 55)
		{
			cout << menuText[34] << endl;
			Status();
		}
		else
		{
			MyPlayer.totalHP -= demonDamage;
			cout << menuText[35] << demonDamage << menuText[36] << MyPlayer.totalHP << endl;
			GameOver();
			DemonSlaying();
		}
		break;
	case battlechoices::save:
		cout << menuText[37] << endl;
		Save();
		DemonSlaying();
		break;
	default:
		errorTxt();
		DemonSlaying();
		break;
	}
}

void GameOver()
{
	ifstream inputFile;
	inputFile.open("menu\\GameOver.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}

	}
	inputFile.close();
	if (MyPlayer.totalHP <= 0)
	{
		MyPlayer.totalHP = 0;
		cout << menuText[0] << endl;
		cout << MyPlayer.name << menuText[1] << MyPlayer.route << menuText[2] << endl;
		cout << menuText[3] << endl;
		Save();
		main();
	}

}

void LvlUP()
{
	ifstream inputFile;
	inputFile.open("menu\\LvlUp.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}

	}
	inputFile.close();
	MyPlayer.xp += RandomDemon.demonXp;
	do
	{
		if (MyPlayer.xp >= MyPlayer.neededXp)
		{
			cout << menuText[0] << endl;
			MyPlayer.level++;
			MyPlayer.neededXp *= 1.65;
			MyPlayer.str += 1;
			MyPlayer.faith += 1;
			MyPlayer.speed += 1;
			MyPlayer.maxHP += 25;
			cout << menuText[1] << "\n" << menuText[2] << MyPlayer.str << "\n" << menuText[3] << MyPlayer.faith << "\n" << menuText[4] << MyPlayer.speed << "\n" << menuText[5] << MyPlayer.maxHP << "\n" << menuText[6] << "\n" << endl;
		}

		else
		{
			cout << menuText[7] << RandomDemon.demonXp << menuText[8] << endl;
		}
	} while (MyPlayer.xp >= MyPlayer.neededXp);
	pressEnter();
}

void RollCredits()
{
	ifstream inputFile;
	inputFile.open("menu\\rollCredits.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}
	inputFile.close();
	for (size_t i = 0; i < menuText.size(); i++)
	{
		cout << menuText[i] << endl;
	}

	pressEnter();
	system("cls");
	main();
}

void ChallengeBoss()
{
	ifstream inputFile;
	inputFile.open("menu\\ChallengeBoss.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}
	cout << menuText[0] << "\n" << menuText[1] << endl;
	pressEnter();
	system("cls");
	cout << menuText[2] << "\n" << menuText[3] << endl;
	pressEnter();
	system("cls");
	cout << menuText[4] << "\n" << menuText[5] << menuText[6] << endl;
	pressEnter();
	CreateBoss();
	BossSlaying();

}

void CreateBoss()
{
	PaleRider.bossName = "Pale Rider";
	PaleRider.bossLevel = MyPlayer.level + 2;
	PaleRider.bossMaxHP = 6500 + MyPlayer.maxHP * 0.8;
	PaleRider.bossTotalHP = PaleRider.bossMaxHP;
	PaleRider.bossStr = MyPlayer.str * 0.15;
	PaleRider.bossHeal = PaleRider.bossTotalHP * 0.15;
}

void BossStatus()
{
	ifstream inputFile;
	inputFile.open("menu\\BossStatus.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}
	system("cls");
	for (size_t i = 13; i < menuText.size(); i++)
	{
		cout << menuText[i] << endl;
	}



	cout << menuText[0] << MyPlayer.totalHP << menuText[1] << MyPlayer.maxHP << menuText[2] << PaleRider.bossTotalHP << menuText[1] << PaleRider.bossMaxHP << endl;
	cout << menuText[3] << MyPlayer.level << menuText[4] << PaleRider.bossLevel << endl;
	cout << menuText[5] << PaleRider.bossName << endl;
	cout << menuText[6] << MyPlayer.professionName << endl;
	cout << menuText[7] << MyPlayer.name << endl;
	cout << menuText[8] << MyPlayer.str << endl;
	cout << menuText[9] << MyPlayer.speed << endl;
	cout << menuText[10] << MyPlayer.faith << endl;
	cout << menuText[11] << endl;

}

void BossSlaying()
{
	ifstream inputFile;
	inputFile.open("menu\\BossSlaying.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}


	BossStatus();
	int bossSecondPhase = PaleRider.bossMaxHP * 0.5;
	int bossCombatchoice;
	int playerDamageToBoss = MyPlayer.str * MyPlayer.level * 4.5;
	int bossDamage = PaleRider.bossStr * PaleRider.bossLevel * 2;
	enum bossBattleChoices { attack = 1, parry, pray, save };
	int faithRand = (rand() % 10) * MyPlayer.faith;
	int parryRand = (rand() % 10) * MyPlayer.speed;
	for (size_t i = 0; i < 5; i++)
	{
		cout << menuText[i] << endl;
	}
	cin >> bossCombatchoice;
	switch (bossCombatchoice)
	{
	case bossBattleChoices::attack:
		cout << menuText[5] << endl;
		PaleRider.bossTotalHP -= playerDamageToBoss;
		cout << menuText[6] << playerDamageToBoss << menuText[7] << PaleRider.bossName << endl;
		pressEnter();
		if (PaleRider.bossTotalHP > bossSecondPhase)
		{
			BossStatus();
			MyPlayer.totalHP -= bossDamage;
			cout << menuText[9] << PaleRider.bossName << menuText[10] << bossDamage << menuText[11] << MyPlayer.totalHP;
			pressEnter();
			GameOver();
			BossSlaying();
		}
		else if ( PaleRider.bossTotalHP > 1 && PaleRider.bossTotalHP <= bossSecondPhase)
		{
			int bossRand = rand() % 100;
			if (bossRand > 50)
			{
				BossStatus();
				MyPlayer.totalHP -= (bossDamage * 1.4);
				cout << menuText[9] << PaleRider.bossName << menuText[12] << bossDamage << menuText[13] << MyPlayer.totalHP;
				pressEnter();
				GameOver();
				BossSlaying();
			}
			else if (bossRand > 20 && bossRand < 50)
			{
				PaleRider.bossTotalHP += PaleRider.bossHeal;
				if (PaleRider.bossTotalHP > PaleRider.bossMaxHP)
				{
					PaleRider.bossTotalHP = PaleRider.bossMaxHP;
				}
				cout << menuText[9] << PaleRider.bossName << menuText[14] << PaleRider.bossHeal << menuText[15] << endl;
				pressEnter();
				BossSlaying();
			}
			else if (bossRand < 20)
			{
				cout << menuText[9] << PaleRider.bossName << menuText[16] << endl;
				pressEnter();
				BossSlaying();
			}
		}
		else if (PaleRider.bossTotalHP <= 0)
		{
			PaleRider.bossTotalHP = 0;
			cout << menuText[18] << PaleRider.bossName << menuText[19] << endl;
			pressEnter();
			RollOutro();
		}
		break;
	case bossBattleChoices::parry:
		cout << menuText[21] << endl;
		if (parryRand >= 60)
		{
			int playerParry;
			playerParry = playerDamageToBoss + (playerDamageToBoss * 0.4);
			RandomDemon.demonHP -= playerParry;
			cout << menuText[22] << playerParry << menuText[23] << PaleRider.bossName << menuText[24] << endl;
			pressEnter();
			BossStatus();
			if (PaleRider.bossTotalHP > bossSecondPhase)
			{
				cout << PaleRider.bossName << menuText[25] << playerParry << menuText[26] << endl;
				pressEnter();
				BossSlaying();
			}

			else if (PaleRider.bossTotalHP > 1 && PaleRider.bossTotalHP < bossSecondPhase)
			{
				MyPlayer.totalHP -= bossDamage * 0.5;
				cout << PaleRider.bossName << menuText[27] << bossDamage << menuText[28] << MyPlayer.totalHP << menuText[29] << endl;
				pressEnter();
				GameOver();
				BossSlaying();
			}

			else if (PaleRider.bossTotalHP <= 0)
			{
				PaleRider.bossTotalHP = 0;
				cout << menuText[18] << PaleRider.bossName << menuText[19] << endl;
				pressEnter();
				RollOutro();

			}
		}
		else
		{
			MyPlayer.totalHP -= bossDamage + (bossDamage * 0.3);
			cout << menuText[30] << endl;
			pressEnter();
			GameOver();
			BossSlaying();
		}
		break;
	case bossBattleChoices::pray:

		if (faithRand >= 60)
		{
			if (MyPlayer.totalHP < MyPlayer.maxHP)
			{
				MyPlayer.heal = MyPlayer.level * MyPlayer.faith * 0.8;
				MyPlayer.totalHP += MyPlayer.heal;
				if (MyPlayer.totalHP > MyPlayer.maxHP)
				{
					MyPlayer.totalHP = MyPlayer.maxHP;
				}
				cout << menuText[32] << MyPlayer.heal << menuText[33] << MyPlayer.totalHP << endl;
				pressEnter();
				BossSlaying();
			}
			else
			{
				cout << menuText[34] << endl;
				pressEnter();
				BossSlaying();
			}
		}
		else
		{
			MyPlayer.totalHP -= bossDamage;
			cout << menuText[35] << bossDamage << menuText[36] << MyPlayer.totalHP << endl;
			pressEnter();
			GameOver();
			BossSlaying();
		}
		break;
	case bossBattleChoices::save:
		Save();
		BossSlaying();
		break;
	default:
		break;
	}
}

void RollOutro()
{
	system("cls");
	ifstream inputFile;
	inputFile.open("menu\\Outro.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}

	inputFile.close();

	for (size_t i = 0; i < menuText.size(); i++)
	{
		cout << menuText[i] << endl;
		Sleep(1000);

	}
	Save();
	RollCredits();
}

void Save()
{
	ifstream inputFile;
	inputFile.open("menu\\SaveFile.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}

	inputFile.close();
	for (size_t i = 0; i < 6; i++)
	{
		cout << menuText[i] << endl;
		Sleep(200);
	}

	ofstream file;

	file.open(MyPlayer.name + ".sav", ios::out | ios::binary);

	int nameSize = MyPlayer.name.size();

	if (!file.fail())
	{
		file.write((char*)&MyPlayer.playerProfession, sizeof(MyPlayer.playerProfession));
		file.write((char*)&MyPlayer.level, sizeof(MyPlayer.level));
		file.write((char*)&MyPlayer.totalHP, sizeof(MyPlayer.totalHP));
		file.write((char*)&MyPlayer.maxHP, sizeof(MyPlayer.maxHP));
		file.write((char*)&MyPlayer.heal, sizeof(MyPlayer.heal));
		file.write((char*)&MyPlayer.str, sizeof(MyPlayer.str));
		file.write((char*)&MyPlayer.speed, sizeof(MyPlayer.speed));
		file.write((char*)&MyPlayer.faith, sizeof(MyPlayer.faith));
		file.write((char*)&MyPlayer.route, sizeof(MyPlayer.route));
		file.write((char*)&MyPlayer.xp, sizeof(MyPlayer.xp));
		file.write((char*)&MyPlayer.neededXp, sizeof(MyPlayer.neededXp));


		file.write((char*)&nameSize, sizeof(nameSize));

		for (int i = 0; i < nameSize; i++)
		{
			file.write((char*)&MyPlayer.name[i], sizeof(MyPlayer.name));
		}
	}
	else
	{
		cout << menuText[6] << endl;
		pressEnter();
		system("cls");
	}
	file.close();

	cout << menuText[7] << endl;
	pressEnter();
}

void LoadCharacter()
{
	ifstream inputFile;
	inputFile.open("menu\\LoadFile.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}
	system("cls");
	cout << menuText[0] << endl;
	string auxLoad;
	cin >> auxLoad;

	ifstream file;

	file.open(auxLoad + ".sav", ios::in | ios::binary);
	int nameSize;


	if (!file.fail())
	{
		if (MyPlayer.level >= 1)
		{
			MyPlayer.name = " ";
			MyPlayer.playerProfession = 0;
			MyPlayer.level = 0;
			MyPlayer.totalHP = 0;
			MyPlayer.maxHP = 0;
			MyPlayer.heal = 0;
			MyPlayer.str = 0;
			MyPlayer.speed = 0;
			MyPlayer.faith = 0;
			MyPlayer.route = 0;
			MyPlayer.xp = 0;
			MyPlayer.neededXp = 0;
		}

		file.read((char*)&MyPlayer.playerProfession, sizeof(MyPlayer.playerProfession));
		file.read((char*)&MyPlayer.level, sizeof(MyPlayer.level));
		file.read((char*)&MyPlayer.totalHP, sizeof(MyPlayer.totalHP));
		file.read((char*)&MyPlayer.maxHP, sizeof(MyPlayer.maxHP));
		file.read((char*)&MyPlayer.heal, sizeof(MyPlayer.heal));
		file.read((char*)&MyPlayer.str, sizeof(MyPlayer.str));
		file.read((char*)&MyPlayer.speed, sizeof(MyPlayer.speed));
		file.read((char*)&MyPlayer.faith, sizeof(MyPlayer.faith));
		file.read((char*)&MyPlayer.route, sizeof(MyPlayer.route));
		file.read((char*)&MyPlayer.xp, sizeof(MyPlayer.xp));
		file.read((char*)&MyPlayer.neededXp, sizeof(MyPlayer.neededXp));

		file.read((char*)&nameSize, sizeof(nameSize));
		for (int i = 0; i < nameSize; i++)
		{
			char auxChar;
			file.read((char*)&auxChar, sizeof(auxChar));
			MyPlayer.name += auxChar;
		}

		if (MyPlayer.playerProfession == 1)
		{
			MyPlayer.professionName = "Soldier";
		}
		else if (MyPlayer.playerProfession == 2)
		{
			MyPlayer.professionName = "Hunter";
		}
		else if (MyPlayer.playerProfession == 3)
		{
			MyPlayer.professionName = "Priest";
		}

		if (MyPlayer.route >= 30)
		{
			MyPlayer.key = true;
		}

		if (MyPlayer.totalHP <= 0)
		{
			MyPlayer.totalHP = MyPlayer.maxHP;
		}
	}

	else
	{
		errorTxt();
		LoadCharacter();
	}
	
	cout << menuText[2] << endl;
	pressEnter();
}

bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

void errorTxt()
{
	ifstream inputFile;
	inputFile.open("menu\\InputError.txt", ios::in);
	vector<string> menuText;

	if (!inputFile.fail())
	{
		while (inputFile.eof() == false)
		{
			string text;
			getline(inputFile, text);
			menuText.emplace_back(text);
		}
	}

	inputFile.close();

	for (size_t i = 0; i < menuText.size(); i++)
	{
		cout << menuText[i] << endl;
	}

}

void pressEnter()
{
	do
	{
		cin.get();
	} while (cin.get() != '\n');
}


